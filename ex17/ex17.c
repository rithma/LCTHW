#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>   //defines the integer variable errno, which is set by system calls and some library functions in the event of an error to indicate what went wrong.
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {    //database Struct is a fixed length array of Address structs
	struct Address rows[MAX_ROWS];    
};

struct Connection {  //Connection is a struct made up of:
	FILE *file;      //a pointer to a file
	struct Database *db;  //a pointer to that database of 100 rows of Address
};

void die(const char *message)
{
	if(errno){
		perror(message);
	}else{
		printf("ERROR: %s\n", message);
	}
	exit(1);
}

void Address_print(struct Address *addr)        //
{                           //members will use an arrow 
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
    	die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));

	if(!conn)    {
		die("Memory error");
	}
    
    conn->db = malloc(sizeof(struct Database));      //THIS IS THE PART I WAS MISSING, making a bus fault 10
    
    if (!conn->db) {
        die("Memory error");
    }

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	}else{
		conn->file = fopen(filename, "r+");

		if (conn->file) {
			Database_load(conn);
		}
	}

	if (!conn->file)
		die("failed to open the file");

	return conn;
	}

void Database_close(struct Connection *conn)
{
	if (conn) {
		if (conn->file)
			fclose(conn->file);
		if (conn->db)
			free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);

	if (rc != 1) {
		die("failed to write database");
	}

	rc = fflush(conn->file);

	if (rc == -1) {
		die("cannot flush database");
	}
}

void Database_create(struct Connection *conn)
{
	int i = 0;

	for(i = 0; i < MAX_ROWS; i++) {
		//make a prototype to initialize it
		struct Address addr = { .id = i, .set = 0 };
		//then just assign it
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name,
	const char *email)
{
	struct Address *addr = &conn->db->rows[id];  //get the [id] element of rows, which is in db, 
	if(addr->set)  //if set = 1                  //which is in conn, and get the address of it. 
		die("Already set, delete it first)");

	addr->set = 1;

	//warning: bug, read how to break and fix...
	char *res = strncpy(addr->name, name, MAX_DATA);
	addr->name[MAX_DATA - 1] = '\0';
	//demo the strncpy bug
	if (!res)
		die("name copy failed");

	res = strncpy(addr->email, email, MAX_DATA);
	if (!res)
		die("Name copy failed");
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];  //one pointer is returned. see 109
                                                 //to that ONE element
	if(addr->set) {
		Address_print(addr);                     //pass the pointer to address print
	}else{
		die("ID is not set");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = 0 };   //creates empty addr 
	conn->db->rows[id] = addr;                     //and assigns it to nameAndAddress struct at row[id]
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;

	for (i = 0; i < MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];

		if (cur->set) {
			Address_print(cur);
		}
	}
}

int main (int argc, char *argv[])
{
	if (argc < 3)
		die("USAGE: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if (argc > 3) id = atoi(argv[3]);
	if (id >= MAX_ROWS) die("there's not that many records");

	switch(action) {
		case 'c':
		Database_create(conn);
		Database_write(conn);
		break;

		case 'g':
		if (argc != 4)
			die("need an ID to get");

		Database_get(conn,id);
		break;

		case 's':
		if (argc !=6)
			die("need id, email to set");
     
        Database_set(conn, id, argv[4], argv[5]);
        Database_write(conn);
        break;

        case 'd':
        if (argc != 4)
        	die("Need id to delete");

        Database_delete(conn, id);
        Database_write(conn);
        break;

        case 'l':
        Database_list(conn);
        break;
        default:

            die("invalid action: c=create, g=get, s=set, d=del, l=list");
}

Database_close(conn);

return 0;

}


