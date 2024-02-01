#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int chan;
int bytes;
int width;
int height;
void *data;

int
main(int argc, char **argv)
{
	if(argc < 2)
		return -1;

	FILE *f;
	char *path;
	char *end;

	bytes = 1; // limited to 8-bit
	if(argc > 2)
		stbi_set_flip_vertically_on_load(1);
	data = stbi_load(argv[1], &width, &height, &chan, 0);
	if(data == 0)
		return -1;

	path = argv[1];
	for(end = path + strlen(path); *end != '.'; --end)
		;
	end[1] = 'i';
	end[2] = 'm';
	end[3] = '\0';


	f = fopen(path,"w");
	fwrite(&chan,4,1,f);
	fwrite(&bytes,4,1,f);
	fwrite(&width,4,1,f);
	fwrite(&height,4,1,f);
	fwrite(data,chan * bytes * width * height,1,f);

	free(data);
}
