//  CITS2002 Project 2 2022
//  Student1:   23614803   SOMARATHNA   SITHUM   100%
//  Student2:   N/A

#include "trove.h"

//	HASH ALGORITH FOR HASHING STRINGS
uint32_t hash_string(char *string){
    uint32_t hash = 0;

    while(*string != '\0') {
        hash = hash*33 + *string;
        ++string;
    }
    return hash;
}

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE
HASHTABLE *hashtable_new(void){
    HASHTABLE   *new = calloc(HASHTABLE_SIZE, sizeof(LIST *));

    CHECK_ALLOC(new);
    return new;
}

//  ADD A NEW STRING-FILEINDEX PAIR TO A GIVEN HASHTABLE
void hashtable_add(char *string, int index){
    uint32_t h   = hash_string(string) % HASHTABLE_SIZE;    // choose list

    hashtable[h] = list_add(hashtable[h], string, index);
}

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE AND RETURN ITS LIST
LIST *hashtable_find(char *string){
    uint32_t h	= hash_string(string) % HASHTABLE_SIZE;     // choose list

    return list_find(hashtable[h], string);
}

//	PRINT THE STORED DATA IN A HASHTABLE (USED FOR DEBUGGING)
void hashtable_print(){
	printf("\t\nHASHTABLE:\n\n");
	for(int i=0; i<HASHTABLE_SIZE; i++){
		if(hashtable[i] != NULL){
			printf("\t[%i]\n", i);
			LIST *list = hashtable[i];
			while(list != NULL){
				printf("\t\t%s: ", list->string);
				for(int j=0; j<list->numIndexes-1; j++){
					printf("%i,", list->indArray[j]);
				}
				printf("%i\n", list->indArray[list->numIndexes-1]);
				list = list->next;
			}
		}
	}
}

//	SEARCH THROUGH HASHTABLE AND LIST ALL FILES THAT CONTAIN A SPECIFIC WORD
void hashtable_list_files(char *word){
	sprintf(debug_s, "searching for \"%s\"", word); print_debug(debug_s);

	LIST *list = hashtable_find(word);
	if(list == NULL){
		printf("%s: Searched word not found\n", progname);
		exit(EXIT_FAILURE);
	}
	for(int i=0; i<list->numIndexes; i++){
		if(access(filepaths[list->indArray[i]], F_OK) == 0){
			printf("%s\n", filepaths[list->indArray[i]]);
		}
	}
}

// REMOVE A FILE INDEX FROM THE HASHTABLE
void hashtable_remove(int index){
	for(int i=0; i<HASHTABLE_SIZE; i++){
		if(hashtable[i] != NULL){
			list_remove(hashtable[i], i, index);
		}
	}
}