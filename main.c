#include <stdio.h>
#include <stdlib.h>
#include <Imlib2.h>
#include <string.h>
#include <arpa/inet.h>

Imlib_Image c;
Imlib_Image t;
int hal;
int hs;
int wm;
int i;
FILE *f;

int
main(int argc, char **argv)
{
	hs = 0;
	wm = 0;

	for(i=3; i<argc; i+=3){
		t = imlib_load_image(argv[i]);
		imlib_context_set_image(t);
		int h = imlib_image_get_height();
		int w = imlib_image_get_width();		
		
		if(w > wm)
			wm = w;
		hs += h;
	}

	c = imlib_create_image(wm, hs);	

	int p = 0;

	imlib_context_set_image(c);
	imlib_image_set_has_alpha(1);

	for(i=3; i<argc; i+=3){
		t = imlib_load_image(argv[i]);
		imlib_context_set_image(t);
		int h = imlib_image_get_height();
		int w = imlib_image_get_width();

		imlib_context_set_image(c);
		imlib_blend_image_onto_image(t, 1, 0, 0, w, h, 0, p, w, h);
		p += h;
	}
	

	imlib_image_set_format("ff");
	char file[47] = {0};
	memmove(file, argv[1], strlen(argv[1]));
	
	if(atoi(argv[2]))
		strcat(file, ".cb");
	else
		strcat(file, ".ff");
	imlib_save_image(file);

	if(atoi(argv[2])){
		f = fopen(file, "r+");
		fseek(f, 0, SEEK_END);
	}else{	
		char cf[47] = {0};
		memmove(cf, argv[1], strlen(argv[1]));
		strcat(cf, ".ca");
		f = fopen(cf, "w");	
	}
	fprintf(f, "%d\n", (argc-3)/3);

	p = 0;

	for(i=3; i<argc; i+=3){
		t = imlib_load_image(argv[i]);
		imlib_context_set_image(t);
		int h = imlib_image_get_height();
		int w = imlib_image_get_width();

		fprintf(f, "%s: %d: %d: ", argv[i], atoi(argv[i+1]), atoi(argv[i+2]));
		fprintf(f, "%f %f %f %f %f %f %f %f", 
			(float)w / (float)(wm) / atoi(argv[i+1]),
			(float)p / (float)(hs),
			(float)w / (float)(wm) / atoi(argv[i+1]),
			(float)(p+h) / (float)(hs) / atoi(argv[i+2]),
			0.0,
			(float)(p+h) / (float)(hs) / atoi(argv[i+2]),
			0.0,
			(float)(p) / (float)(hs));
		fprintf(f, "\n");
		p += h;
	}
	
	if(atoi(argv[2]) == 0)
		fprintf(f, "%s;\n", file);
	fclose(f);
}
/* weird bug puts weird characters at the file names */

