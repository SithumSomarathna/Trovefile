//  CITS2002 Project 2 2022
//  Student1:   23614803   SOMARATHNA   SITHUM   100%
//  Student2:   N/A

#include "trove.h"

int totalWords;						// Total number of words found

char **filepaths;					// Array of filepaths stored in trove file

int numFiles;						// Number of filepaths in filepaths array

char *progname;						// The name of this program

HASHTABLE *hashtable;				// A hastable that will store all words