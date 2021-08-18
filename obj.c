#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char **argv)
{
	FILE *f;
	float *vert;
	int *ind;
	float *vv, *vtv, *vnv;
	char w[47];
	int vc, vtc, vnc, fc;
	vc = vtc = vnc = fc = 0;

	f = fopen(argv[1], "r");
	if(f == 0){
		perror("fopen");
		exit(-1);
	}
	
	while(fscanf(f, "%s", w) != EOF){
		if(strcmp(w, "v") == 0)
			++vc;	
		else if(strcmp(w, "vt") == 0)
			++vtc;
		else if(strcmp(w, "vn") == 0)
			++vnc;
		else if(strcmp(w, "f") == 0)
			++fc;
	}

	vert = (float*)malloc(sizeof(float)*vc*8);
	ind = (int*)malloc(sizeof(int)*fc*3);

	vv = (float*)malloc(sizeof(float)*vc*3);		
	vtv = (float*)malloc(sizeof(float)*vtc*2);
	vnv = (float*)malloc(sizeof(float)*vnc*3);

	int num = vc*8;

	vc = vtc = vnc = fc = 0;
	int v, vt, vn;

	rewind(f);
	while(fscanf(f, "%s", w) != EOF){
                if(strcmp(w, "v") == 0){
			fscanf(f, "%f %f %f\n", 
			&vv[vc], &vv[vc+1], &vv[vc+2]);
			vc += 3;
                }else if(strcmp(w, "vt") == 0){
			fscanf(f, "%f %f\n", &vtv[vtc], &vtv[vtc+1]);
			vtc += 2;
                }else if(strcmp(w, "vn") == 0){
			fscanf(f, "%f %f %f\n", 
			&vnv[vnc], &vnv[vnc+1], &vnv[vnc+2]);
			vnv += 3;
                }else if(strcmp(w, "f") == 0){
			fscanf(f, "%d/%d/%d", &v, &vt, &vn);	
			vert[fc*24] = vv[(v-1)*3];
			vert[fc*24+1] = vv[(v-1)*3+1];
			vert[fc*24+2] = vv[(v-1)*3+2];
			vert[fc*24+3] = vtv[(vt-1)*2];
			vert[fc*24+4] = vtv[(vt-1)*2+1];
			vert[fc*24+5] = vnv[(vn-1)*3];
			vert[fc*24+6] = vnv[(vn-1)*3+1];
			vert[fc*24+7] = vnv[(vn-1)*3+2];

			fscanf(f, "%d/%d/%d", &v, &vt, &vn);	
			vert[fc*24+8] = vv[(v-1)*3];
                        vert[fc*24+9] = vv[(v-1)*3+1];
                        vert[fc*24+10] = vv[(v-1)*3+2];
                        vert[fc*24+11] = vtv[(vt-1)*2];
                        vert[fc*24+12] = vtv[(vt-1)*2+1];
                        vert[fc*24+13] = vnv[(vn-1)*3];
                        vert[fc*24+14] = vnv[(vn-1)*3+1];
                        vert[fc*24+15] = vnv[(vn-1)*3+2];

			fscanf(f, "%d/%d/%d\n", &v, &vt, &vn);	
			vert[fc*24+16] = vv[(v-1)*3];
                        vert[fc*24+17] = vv[(v-1)*3+1];
                        vert[fc*24+18] = vv[(v-1)*3+2];
                        vert[fc*24+19] = vtv[(vt-1)*2];
                        vert[fc*24+20] = vtv[(vt-1)*2+1];
                        vert[fc*24+21] = vnv[(vn-1)*3];
                        vert[fc*24+22] = vnv[(vn-1)*3+1];
                        vert[fc*24+23] = vnv[(vn-1)*3+2];

			fc++;
                }
        }
/*
	for(int i=0; i<num; ++i)
		printf("%f\n", vert[i]);
*/

	printf("v: %d, vt: %d, vn: %d, f: %d\n", vc, vtc, vnc, fc);
}
