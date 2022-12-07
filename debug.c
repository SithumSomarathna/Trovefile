//  CITS2002 Project 2 2022
//  Student1:   23614803   SOMARATHNA   SITHUM   100%
//  Student2:   N/A

#include "trove.h"

//	PRINT A DEBUG MESSAGE IF DEBUG VARIABLE IS ENABLED
void print_debug(char *string){
	if(DEBUG){
		printf("\t%s\n", string);
	}
}

//	PRINT AN ERROR THAT SHOWS THE CORRECT USAGE OF THE PROGRAM
void usage_error(){
	printf("%s: Usage: ./trove  [-f trovefile]  word OR ./trove  [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist\n", progname);
	exit(EXIT_FAILURE);
}