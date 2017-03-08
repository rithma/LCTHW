#include "dbg.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>


const size_t MAX_LINE = 1024;


int list_files (glob_t *pglob) 
{
    char *line = calloc(MAX_LINE, 1);
    FILE *file = fopen(".logfind", "r");
    int glob_flags = GLOB_TILDE;
    int i = 0;
    int rc = -1;

    check(pglob != NULL, "Invalid glob_t given.");
    check_mem(line);
    check(file, "failed to open .logfind, make that first");

    rc = glob("*.h", glob_flags, NULL, pglob);
    check(rc == 0, "Failed to glob");
    rc = glob("*.c", glob_flags | GLOB_APPEND, NULL, pglob);
    check(rc == 0, "Failed to glob");

    for (i = 0; i < pglob->gl_pathc; i++) {
        debug("Matched files: %s", pglob->gl_pathv[i]);
    }

    rc = 0;

error:
    if(line) free(line);
    return rc;

}

int scan_file(const char *filename, int search_len, char *search_for[])
{
	char *line = calloc(MAX_LINE, 1);
	FILE *file = fopen(filename, "r");
	char *found = NULL;
	int i = 0;

	check_mem(line);
	check(file, "Failed to open file: %s", filename);

    // read each line of the file and search that line for the contents
    
    // char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream 
    // and stores it into the string pointed to by str. It stops when either (n-1) characters are read,
    // the newline character is read, or the end-of-file is reached, whichever comes first.
    while(fgets(line, MAX_LINE-1, file) != NULL && found == NULL) {
    	for(i = 0; i < search_len && found == NULL; i++) {
    		found = strcasestr(line, search_for[i]);
    		if(found) {
    			printf("%s\n", filename);
    		}
    	}
    }

    free(line);
    fclose(file);
    return 0;

error:
    if(line) free(line);
    if(file) fclose(file);

    return -1;

}



int main(int argc, char * argv[]) {
    int i = 0;


    glob_t files_found;
    check(argc > 1, "USAGE: ./logfind word word word");
    check(list_files(&files_found) == 0, "failed to list files");
    for(i = 0; i < files_found.gl_pathc; i++) {
        scan_file(files_found.gl_pathv[i], argc, argv);        //glob returns a struct with a path count(pathc) and a path vector (pathv) of matches.
    }

    globfree(&files_found);











	scan_file("logfind.c", argc, argv);

	return 0;

error:
    return 1;
}












/* ************* ************** ***************** ****************

logfind.c:54:5: error: use of undeclared label 'error'
    check(pglob != NULL, "invalid glob_t given.");
    ^
./dbg.h:35:48: note: expanded from macro 'check'
    log_err(M, ##__VA_ARGS__); errno = 0; goto error; }
                                               ^
1 error generated.

*/
