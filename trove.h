#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/wait.h>

#define	OPTLIST	"f:brul:"			// List of possible command line option characters
#define WORDLEN 100					// Maximum lenght of a word
#define HASHTABLE_SIZE 1300			// Size of hashtable
#define CHECK_ALLOC(p) if(p == NULL) { printf("%s: Memory allocation failed\n", progname); exit(EXIT_FAILURE); }
#define DEBUG true					// All debug statements are printed if this is true

char debug_s[PATH_MAX + 30];		// Buffer string for debug messages

//	DEFINE STRUCTURE FOR LINKED LIST
typedef struct _list {
     char *string;					// The word that is stored
     int *indArray;					// An array of the indexes of files from the filepaths array that contain this word
     int numIndexes;				// The number of indexes in the indArray array
     struct _list *next;			// A pointer to the next list
} LIST;

//	DEFINE STRUCTURE FOR HASHTABLE
typedef	LIST *HASHTABLE;

extern int totalWords;						// Total number of words found

extern char **filepaths;					// Array of filepaths stored in trove file

extern int numFiles;						// Number of filepaths in filepaths array

extern char *progname;						// The name of this program

extern HASHTABLE *hashtable;				// A hastable that will store all words



extern void print_debug(char *string);

extern bool list_try_insert(LIST *list, char *wanted, int index);

extern LIST *list_new_item(char *newstring);

extern LIST *list_find(LIST *list, char *wanted);

extern LIST *list_add(LIST *list, char *newstring, int index);

extern void list_remove(LIST *list, int hashIndex, int index);

extern uint32_t hash_string(char *string);

extern HASHTABLE *hashtable_new(void);

extern void hashtable_add(char *string, int index);

extern LIST *hashtable_find(char *string);

extern void hashtable_print();

extern void hashtable_list_files(char *word);

extern void hashtable_remove(int index);

extern void find_words(char *filename, int length, int fileIndex);

extern void add_file(char *filename, int length);

extern void remove_file(char *filename);

extern void traverse_directory(char *dirname, int length, char mode);

extern void filepaths_print();

extern void troveFile_write(char *filename);

extern void troveFile_read(char *filename);

extern void usage_error();


