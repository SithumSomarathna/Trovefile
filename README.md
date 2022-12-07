# Trovefile
- Builds and modifies a compressed index of the contents of files in given directories
- Searches compressed index to output which files contains the searched string

Input/Output: 
The trove utility may be invoked in one of two ways, with command-line options indicating the actions to be performed

1. ./trove [-f trovefile] word
The first invocation requests trove to list the absolute pathname of files containing the indicated word. Filenames are simply listed one-per-line. If any file does not exist at the time of the search (it may have been deleted since the trove-file was built), then the file is not listed.

2. ./trove [-f trovefile] [-b|-r|-u] [-l length] filelist
The second invocation requests trove to build a new index, to remove information from an existing index, or to update an existing index. A filelist is a sequence of one-or-more filenames or directory names. The contents of each named file will be indexed, and each named directory (and its subdirectories) will be traversed to locate files to be indexed.

The following command-line options are supported:
[-b] build a new trove-file from the contents of a filelist. The new trove-file will replace an existing trove-file of the same name.]
[-f trovefile] provide the name of the trove-file to be built or searched. If the -f option is not provided, the default name of the trove-file is /tmp/trove
[-l length] only words of at least the indicated length should be added to the trove-file. length must be a positive integer, for example: -l 6. If the -l option is not provided, the default length is 4.
[-r] if any of the files from the filelist appear in the trove-file, remove all of their information from the trove-file.
[-u] update the trove-file with the contents of all files in the filelist. If the information from any of the files already exists in the trove-file, then that (old) information is first removed.
