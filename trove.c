//  CITS2002 Project 2 2022
//  Student1:   23614803   SOMARATHNA   SITHUM   100%
//  Student2:   N/A

#include "trove.h"

int main(int argc, char *argv[])
{
	progname = argv[0];			// Identify and store the program name
	hashtable = hashtable_new();// Initialise hashtable
	filepaths = malloc(0);		// Initialise filepaths array
	int mode = 0;				// {1: build, 2: remove, 3: update}
	int length = 4;				// minimum length for searched words
	bool length_given = false;	// boolean to check if length is given
	char *file = "/tmp/trove";	// filepath to store trove file
	int opt;
	while((opt = getopt(argc, argv, OPTLIST)) != -1){	// Process command line options
		switch(opt){
			case 'f':
				file = optarg;
				break;
			case 'b':
				if(mode != 0){
					usage_error();
				}
				mode = 1;
				break;
			case 'r':
				if(mode != 0){
					usage_error();
				}
				mode = 2;
				break;
			case 'u':
				if(mode != 0){
					usage_error();
				}
				mode = 3;
				break;
			case 'l':
				length = atoi(optarg);
				length_given = true;
				break;
		}
	}

	argc -= optind;
    argv += optind;

	if(argc == 0){
		usage_error(progname);
	}

    if(mode != 0){		// Need to modify or create a trove file
    	switch(mode){
    		case 1:		// Build
    			sprintf(debug_s, "building trove-file"); print_debug(debug_s);
    			for(int i=0; i<argc; i++){
    				sprintf(debug_s, "reading directory \"%s\"", argv[i]); print_debug(debug_s);
		    		traverse_directory(argv[i], length, 'a');	
		    	}
		    	troveFile_write(file);
		    	sprintf(debug_s, "%i unique files", numFiles); print_debug(debug_s);
		    	sprintf(debug_s, "%i unique words", totalWords); print_debug(debug_s);
    			break;
    		case 2:		// Remove
    			troveFile_read(file);
    			for(int i=0; i<argc; i++){
    				sprintf(debug_s, "removing directory \"%s\"", argv[i]); print_debug(debug_s);
		    		traverse_directory(argv[i], length, 'r');	
		    	}
		    	troveFile_write(file);
		    	sprintf(debug_s, "%i unique files", numFiles); print_debug(debug_s);
		    	sprintf(debug_s, "%i unique words", totalWords); print_debug(debug_s);
    			break;
    		case 3:		// Update
    			troveFile_read(file);
    			for(int i=0; i<argc; i++){
    				sprintf(debug_s, "updating directory \"%s\"", argv[i]); print_debug(debug_s);
		    		traverse_directory(argv[i], length, 'r');
		    		traverse_directory(argv[i], length, 'a');	
		    	}
		    	troveFile_write(file);
		    	sprintf(debug_s, "%i unique files", numFiles); print_debug(debug_s);
		    	sprintf(debug_s, "%i unique words", totalWords); print_debug(debug_s);
    			break;
    	}  	
    	
    }else{				// Need to search for a word
    	if(length_given || argc != 1){
    		usage_error(progname);
    	}
    	troveFile_read(file);
    	hashtable_list_files(argv[0]);
    	sprintf(debug_s, "%i unique files", numFiles); print_debug(debug_s);
    	sprintf(debug_s, "%i unique words", totalWords); print_debug(debug_s);
    }

	exit(EXIT_SUCCESS);
}
