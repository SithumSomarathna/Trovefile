//  CITS2002 Project 2 2022
//  Student1:   23614803   SOMARATHNA   SITHUM   100%
//  Student2:   N/A

#include "trove.h"

//	WRITE THE CONTENTS OF DATA STRUCTURES TO TROVE FILE
void troveFile_write(char *filename){
	sprintf(debug_s, "writing trove-file"); print_debug(debug_s);

	char gzFile[PATH_MAX];
	strcpy(gzFile, "gzip - > ");
	strcat(gzFile, filename);

	FILE *f = popen(gzFile, "w");												// Write to compressed file as a stream of data
	sprintf(debug_s, "compressing trove-file"); print_debug(debug_s);
	if(f == NULL){
		printf("%s: file failed to open\n", filename);
    	exit(EXIT_FAILURE);
	}

	fprintf(f, "numFiles: %i\n", numFiles);										// Write information on the filepaths array
	for(int i=0; i<numFiles; i++){
		fprintf(f, "%s\n", filepaths[i]);
	}

	for(int i=0; i<HASHTABLE_SIZE; i++){										// Write information on the hashtable
		if(hashtable[i] != NULL){
			int listSize = 0;
			LIST *list = hashtable[i];
			while(list != NULL){
				list = list->next;
				listSize++;
			}
			fprintf(f, "[%i] %i\n", i, listSize);
			list = hashtable[i];
			while(list != NULL){
				fprintf(f, "%s: %i", list->string, list->numIndexes);
				for(int j=0; j<list->numIndexes; j++){
					fprintf(f, " %i", list->indArray[j]);
				}
				fprintf(f, "\n");
				list = list->next;
			}
		}
	}

	fclose(f);
}

// READ THE CONTENTS OF TROVE FILE TO DATA STRUCTURES
void troveFile_read(char *filename){
	sprintf(debug_s, "reading trove-file"); print_debug(debug_s);

	if(access(filename, F_OK) != 0){
		printf("Trove file not found\n");
		exit(EXIT_FAILURE);
	}

	int fd[2];
	if(pipe(fd) == -1){															// Create a pipe
		printf("pipe() failed\n");
		exit(EXIT_FAILURE);
	}

	sprintf(debug_s, "decompressing trove-file"); print_debug(debug_s);

	switch(fork()){																// Create a child process
		case -1:
			printf("fork() failed\n");
			exit(EXIT_FAILURE);
			break;
		case 0:																	// Child process decompresses the file
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);											// Child's STDOUT is set to the write end of the pipe
			close(fd[1]);
			execl("/usr/bin/zcat", "/usr/bin/zcat", filename, NULL);			// Send the output of zcat into pipe as a data stream
			break;
		default:
			close(fd[1]);

			FILE *f = fdopen(fd[0], "r");										// Read data from the read end of the pipe as a data stream
			if(f == NULL){
				printf("%s: file failed to open\n", filename);
				exit(EXIT_FAILURE);
			}

			fscanf(f, "numFiles: %i\n", &numFiles);								// Read information on the filepaths array
			filepaths = realloc(filepaths, sizeof(char *) * numFiles);
			CHECK_ALLOC(filepaths);
			char buf[PATH_MAX];
			for(int i=0; i<numFiles; i++){
				fscanf(f, "%s", buf);
		        int pathLen = strlen(buf);
		        filepaths[i] = malloc(sizeof(char) * pathLen);
		        CHECK_ALLOC(filepaths[i]);
		        filepaths[i] = strdup(buf);
			}

			fgetc(f);

			int hashIndex;
			int numLists;
			int index;
			while(fscanf(f, "[%i] %i\n", &hashIndex, &numLists) == 2){			// Read information on the hastable

				for(int i=0; i<numLists; i++){
					char word[WORDLEN];
					int numIndexes;
					fscanf(f, "%[^:]: ", word);
					fscanf(f, "%i", &numIndexes);
					for(int j=0; j<numIndexes-1; j++){
						fscanf(f, " %i", &index);
						hashtable_add(word, index);
					}
					fscanf(f, " %i\n", &index);
					hashtable_add(word, index);
				}
			}

			close(fd[0]);

			break;

			
	}
}