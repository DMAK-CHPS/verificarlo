#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>

int is_wrong(const char* s1, const char* s2)
{
	if(!isdigit(s1[0]) && !isdigit(s2[0])){
		return 0;
	}

	if(isdigit(s1[0]) && isdigit(s2[0])){
		double dout = atof(s1);
		double dres = atof(s2);

		if(fabs(dres - dout) <= 0.1){
			return 0;
		}
	}

	return 1;
}

int main(int argc, char const *argv[])
{
	FILE *f1 =  fopen("RES/res_canc_detect_FLOAT", "r"),
			 *f2 =  fopen("OUTPUT/output_canc_detect_FLOAT", "r"),
			 *out = fopen("test.log", "wr");
	int cpt = 0;
	int f_scan_test;
	assert(f1 != NULL);
	assert(f2 != NULL);
	assert(out != NULL);

	fprintf(out,"OUTPUT/output_canc_detect_FLOAT\n");
	for(int i = 0; i < 22; i++){
		for(int j = 0; j < 23; j++){
			char s1[100] = {}, s2[100] = {};
			f_scan_test = fscanf(f1,"%s ",(char*)&s1);
			assert(f_scan_test > 0);
			f_scan_test = fscanf(f2,"%s ",(char*)&s2);
			assert(f_scan_test > 0);
			if(is_wrong(s1,s2)){
				fprintf(out,"line %d column %d \t- %s %s\n", i+1, j+1, s1, s2);
				cpt++;
			}
		}
	}

	fclose(f1);
	fclose(f2);

	f1 = fopen("RES/res_canc_detect_DOUBLE", "r");
	f2 = fopen("OUTPUT/output_canc_detect_DOUBLE", "r");
	assert(f1 != NULL);
	assert(f2 != NULL);

	fprintf(out,"OUTPUT/output_canc_detect_DOUBLE\n");
	for(int i = 0; i < 51; i++){
		for(int j = 0; j < 52; j++){
			char s1[100] = {}, s2[100] = {};
			f_scan_test = fscanf(f1,"%s ",(char*)&s1);
			assert(f_scan_test > 0);
			f_scan_test = fscanf(f2,"%s ",(char*)&s2);
			assert(f_scan_test > 0);
			if(is_wrong(s1,s2)){
				fprintf(out,"line %d column %d \t- %s %s\n", i+1, j+1, s1, s2);
				cpt++;
			}
		}
	}

	fclose(f1);
	fclose(f2);

	return (cpt/((22.0*23.0)*2.0 + (51.0*52.0)*2.0) >= 0.2);
}