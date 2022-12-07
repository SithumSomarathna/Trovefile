//  CITS2002 Project 2 2022
//  Student1:   23614803   SOMARATHNA   SITHUM   100%
//  Student2:   N/A

#include "trove.h"

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST AND IF SO, APPENDS A NEW FILE INDEX TO ITS FILES ARRAY
bool list_try_insert(LIST *list, char *wanted, int index){
    while(list != NULL) {
		if(strcmp(list->string, wanted) == 0) {
			int *indexes = list->indArray;
			if(indexes[list->numIndexes-1] != index){
				list->numIndexes++;
				indexes = realloc(indexes, sizeof(int) * list->numIndexes);
				CHECK_ALLOC(indexes);
				indexes[list->numIndexes-1] = index;
				list->indArray = indexes;
			}
		    return true;
		}
		list = list->next;
    }
    return false;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM
LIST *list_new_item(char *newstring){
    LIST *new = calloc(1, sizeof(LIST));
    CHECK_ALLOC(new);
    new->string = strdup(newstring);
    CHECK_ALLOC(new->string);
    new->next =  NULL;
    new->indArray = NULL;
    new->numIndexes = 0;
    return new;
}

//	RETURNS THE LIST THAT STORES A SPECIFIC WORD
LIST *list_find(LIST *list, char *wanted){
	while(list != NULL) {
		if(strcmp(list->string, wanted) == 0) {
			return list;
		}
		list = list->next;
    }
    return NULL;
}

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, char *newstring, int index){
    if(list_try_insert(list, newstring, index)) {            // only add each item once
        return list;
    }
    else {                                      // add new item to head of list
    	totalWords++;
        LIST *new   = list_new_item(newstring);
        int *indexes = malloc(sizeof(int));
        CHECK_ALLOC(indexes);
        indexes[0] = index;
        new->indArray = indexes;
        new->numIndexes = 1;
        new->next = list;
        return new;
    }
}

//	REMOVES A SPECIFIC FILE INDEX FROM THE indArray ARRAYS OF A LINKED LIST
//	IF A LIST HAS NO OTHER FILE INDEXES, THE LIST IS DELETED
//	INDEXES OF A HIGHER FILE INDEX ARE DECREMENTED BY 1
void list_remove(LIST *list, int hashIndex, int index){
	LIST *prevList = NULL;
	while(list != NULL){
		int *indexes = list->indArray;
		int numIndexes = list->numIndexes;
		for(int i=0; i<numIndexes; i++){
			if(indexes[i] == index){
				for(int j=i+1; j<numIndexes; j++){
					indexes[j-1] = indexes[j];
					if(indexes[j-1] > index){
						indexes[j-1] -= 1;
					}
				}
				numIndexes -= 1;
				break;
			}else if(indexes[i] > index){
				indexes[i] -= 1;
			}
		}
		if(numIndexes == 0){
			totalWords--;
			if(prevList == NULL){
				hashtable[hashIndex] = list->next;
				free(list);
				list = hashtable[hashIndex];
			}else{
				prevList->next = list->next;
				free(list);
				list = prevList->next;
			}
		}else{
			indexes = realloc(indexes, sizeof(int) * numIndexes);
			CHECK_ALLOC(indexes);
			list->indArray = indexes;
			list->numIndexes = numIndexes;
			prevList = list;
			list = list->next;
		}
	}
}