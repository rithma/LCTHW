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
	FILE      *fp;		  	      	//   a file pointer called "fp"
    Database  *db;			  	    //   a database pointer
}   Connection;				  	      //   to that database of 100 rows of nameAndAddress

void die(const char *dieMessage) 			// - die is a function who's input param is a constChar pointer 
{											                //   called "dieMessage"
	if(errno) {    							        // - set to zero at program startup. Certain std C functions mod value to non zero to signal some types of error.
		perror(dieMessage);       			  // - prints error message to stderr (uses our message pointer)
	} else {
		printf("ERROR: %s\n", dieMessage); 	 //   otherwise prints ERROR: and our messageptr
	}										                   //   and exits program with a 1
	exit(1);  }


void print_nameAndAddress(nameAndAddress *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email); 
}


/*
***** fread() *****
will read a count of items of a specified size from the provided IO stream (FILE* stream).
It returns the number of items successfully read from the stream. If it returns a number less than the
requested number of items, the IO stream can be considered empty (or otherwise broken).
*/
//   --FREAD()--
//size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
//fread() reads data from the given stream into the array pointed to, by ptr.

void Database_load(Connection *conn)
{              //  database  // db size  // 1 item // filestream name ptr                                  
	int rc = fread(conn->db, sizeof(Database), 1, conn->fp);
	if (rc != 1)						                               	//  WHAT IS THE MEANING OF RC???
		die("failed to load database");                       //  fread returns a 1 for 1 item read.  is RC for "read check"?
}






/*

function "DATABASE_OPEN" takes (filename* and 'mode'),returns "connection"...
CONNECTION struct contains filename* and associated database.

FOPEN()
The C library function FILE *fopen(const char *filename, const char *mode)
opens the filename pointed to, by filename using the given mode.
*/
Connection * Database_open(const char *filename, char mode)
{

//malloc returns a pointer to a newly created spot  "CONN" who's the size of
//the two pointers,  *fp - file pointer, and *db - database pointer

	Connection *conn = malloc(sizeof(Connection));   

    if (!conn) {                         //if no conn ptr, then die. 
    	die ("memory error");
    }
//CONN member *db (remember conn->db, conn->fp) assigned Database size chunk of menory

    conn->db = malloc(sizeof(Database));    //A POINTER TO DATABASE

    if(!conn->db) {                     //if no conn->db ptr, die. 
    	die("memory error");
    }


    if (mode == 'c') {                    //create mode either opens
		conn->fp = fopen(filename, "w");      // "w" creates an empty file for writing
	}else{
		conn->fp = fopen(filename, "r+");     // or read and update mode, file must exist

		if (conn->fp) {                      //if there IS an fp pointer inside the conn pointer
			Database_load(conn);               //THEN CALL DATABASE LOAD FUNCTION to the CONN ptr.  
		}
	}

	if (!conn->fp)
		die("failed to open the file");

//THIS ENTIRE FUNCTION CHECKS TO SEE IF CONN HAS *DB&*FP, THEN SPITS OUT CONN!!!!!
	return conn;                    //returns db pointer 'conn' which is used in the rest of the functions
	}                               //OH SHIT THIS IS WHERE CONN GETS CREATED!!!!
	                                //the fucking thing RETURNS a pointer.   which is why "Connection * Database_open"







void Database_close(Connection *conn)  //function takes CONN, returns nothing.
{
    if (conn) {                        //if conn exists then : 
        if(conn->fp) {                 //if conn->fp exists:
            fclose(conn->fp);          //fclose fp
        }
        if(conn->db) {                 //if conn->db
        	free(conn->db);              //free (unmalloc) db
        }
            free(conn);                //then free the conn pointer
    }
}



/*    DATABASE WRITE
     ----------------
  -  rewind()  
     The C library function void rewind(FILE *stream)
     sets the file position to the beginning of the file of the given stream.
  -  fwrite()
     size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) 
     writes data from the array pointed to, by ptr to the given stream. 
     (return value has to be the same as the nmemb (number of elements) value)
  -  fflush()
     int fflush(FILE *stream) flushes the output buffer of a stream.    
*/


void Database_write(Connection *conn)
{
	rewind(conn->fp);                                            //rewinds
	int rc = fwrite(conn->db, sizeof(Database), 1, conn->fp);    //rc gets creates from filestream
	if (rc != 1) {
		die("failed to write database");
	}

	rc = fflush(conn->fp);                                      //conn->fp gets flushed 
	

}












int main (int argc, char *argv[]) 
{
//conn has to get declared here to work inside main...
Connection *conn = Database_open("file.txt", 'c');
print_nameAndAddress(conn);










return 0;
}
























