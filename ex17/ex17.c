#include <stdio.h> 
#include <assert.h>
#include <stdlib.h>
#include <errno.h>    //defines integer errno, set by sys calls & some lib funct. in event of error to indicate what went wrong.
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

typedef struct {
	int  id;
	int  set;
	char name[MAX_DATA];
	char email[MAX_DATA];
}   nameAndAddress;           	//hopefully this will make more sense than 
							  	//Zeds fucked up struct Address struct Database blah blah
typedef struct {
	nameAndAddress dbRows[MAX_ROWS];
}   Database;

typedef struct {              	// - Connection is made up of
	FILE      *fp;		  		//   a file pointer called "fp"
    Database  *db;			  	//   a database pointer
}   Connection;				  	//   to that database of 100 rows of nameAndAddress

void die(const char *dieMessage) 			// - die is a function who's input param is a constChar pointer 
{											//   called "dieMessage"
	if(errno) {    							// - set to zero at program startup. Certain std C functions mod value to non zero to signal some types of error.
		perror(dieMessage);       			// - prints error message to stderr (uses our message pointer)
	} else {
		printf("ERROR: %s\n", dieMessage); 	//   otherwise prints ERROR: and our messageptr
	}										//   and exits program with a 1
	exit(1);  }


void print_nameAndAddress(nameAndAddress *addrPtr)
{
	printf("%d %s %s\n", addrPtr->id, addrPtr->name, addrPtr->email); }


void Database_load(Connection *conn)
{
	int rc = (conn->db, sizeof(Database), 1, conn->file);
	if (rc != 1)							//  WHAT IS THE MEANING OF RC???
		die("failed to load database");
}

Connection *Database_open


























