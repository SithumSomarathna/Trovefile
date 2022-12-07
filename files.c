//  CITS2002 Project 2 2022
//  Student1:   23614803   SOMARATHNA   SITHUM   100%
//  Student2:   N/A

#include "trove.h"

//	FIND ALL WORDS THAT SATISFY A SPECIFIC LENGTH FROM A FILE
void find_words(char *filename, int length, int fileIndex){
	sprintf(debug_s, "finding words in \"%s\"", filename); print_debug(debug_s);

	FILE *f = fopen(filename, "r");
    if(f == NULL){
    	printf("%s: file failed to open\n", filename);
    	exit(EXIT_FAILURE);
    }

    int numWords = 0;
	int w = 0;
	char word[WORDLEN];
    char c = fgetc(f);
    while(c != EOF || (!feof(f) && !ferror(f))){
    	if(isalnum(c)){
			word[w] = c;
			w++;
		}else{
			if(w != 0){
				word[w] = '\0';
				if(w >= length){
					numWords++;
					hashtable_add(word, fileIndex);
				}
				w = 0;
			}
		}
		c = fgetc(f);
    }
    if(w != 0){
		word[w] = '\0';
		if(w >= length){
			numWords++;
			hashtable_add(word, fileIndex);
		}
		w = 0;
	}

	sprintf(debug_s, "found %i words", numWords); print_debug(debug_s);

	fclose(f);
}

//	ADD WORDS IN A FILE TO HASHTABLE
void add_file(char *filename, int length){
	char buf[PATH_MAX];
	realpath(filename, buf);
	numFiles++;
    filepaths = realloc(filepaths, sizeof(char *) * numFiles);
    CHECK_ALLOC(filepaths);
    int pathLen = strlen(buf);
    filepaths[numFiles-1] = calloc(pathLen, sizeof(char));
    CHECK_ALLOC(filepaths[numFiles-1]);
    filepaths[numFiles - 1] = strdup(buf);
    find_words(filename, length, numFiles-1);
}

//	REMOVE WORDS IN A FILE FROM HASHTABLE
void remove_file(char *filename){
	sprintf(debug_s, "removing words in \"%s\"", filename); print_debug(debug_s);
	char buf[PATH_MAX];
	realpath(filename, buf);
	for(int i=0; i<numFiles; i++){
		if(strcmp(filepaths[i], buf) == 0){
			for(int j=i+1; j<numFiles; j++){
				filepaths[j-1] = filepaths[j];
			}
			numFiles--;
			filepaths = realloc(filepaths, sizeof(char *) * numFiles);
			if(numFiles != 0){
				CHECK_ALLOC(filepaths);
			}
			hashtable_remove(i);
			break;
		}
	}
}

//	TRAVERSE A DIRECTORY AND ADD OR REMOVE FILES FROM HASHTABLE
//	MODE {'a': add files, 'r': remove files}
void traverse_directory(char *dirname, int length, char mode){
	char fullpath[PATH_MAX]; 

    struct stat  stat_buffer;

    if(stat(dirname, &stat_buffer) != 0) {
         printf("%s is not a valid path\n", dirname);
    }
    else if( S_ISDIR( stat_buffer.st_mode )) {

	    DIR *dirp;
	    struct dirent *dp;

	    dirp = opendir(dirname);
	    if(dirp == NULL) {
	        printf("%s: failed to open directory\n", dirname);
	        exit(EXIT_FAILURE);
	    }

	    while((dp = readdir(dirp)) != NULL) {  
	        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
		        sprintf(fullpath, "%s/%s", dirname, dp->d_name);
		        traverse_directory(fullpath, length, mode);
		    }
	    }

	    closedir(dirp);
	}
    else if( S_ISREG( stat_buffer.st_mode )) {
        //printf( "%s\n", realpath(dirname, fullpath));
        if(mode == 'a'){
        	add_file(dirname, length);
        }else if(mode == 'r'){
        	remove_file(dirname);
        }
    }
}

//	PRINT THE FILEPATHS ARRAY (USED FOR DEBUGGING)
void filepaths_print(){
	for(int i=0; i<numFiles; i++){
		printf("[%i]: %s\n", i, filepaths[i]);
	}
}