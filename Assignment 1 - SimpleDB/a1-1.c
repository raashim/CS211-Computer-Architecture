// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 100

typedef struct programmingLanguage {
    int id;
    char* language;
    int year;
    char* creator;
    char* paradigm;
    double popularityIndex;
    
    int isDeleted; // internal field, not accessible to user
} language_t;


// step 1: create structs for the other two tables: operatingSystems
// and databases
// include internal field

//the struct for operatingSystems
typedef struct operatingSystems {
    int id;
    char* name;
    int year;
    char* developer;
    char* kernelType;

    int isDeleted; //internal field for operatingSystems
} systems_t;

//the struct for databases
typedef struct databases {
    int id;
    char* name;
    int year;
    char* type;
    char* developer;

    int isDeleted; //internal field for operatingSystems
} databases_t;

// step 2: create typedef struct for storing metadata
typedef struct metadata {
    int count;
    int nextIndex;
    int maxCount; 
} metadata_t;



// step 3: declare the two other arrays of structs
// programmingLanguages has been defined for you already
// TODO: add operatingSystems and databases
language_t* programmingLanguages;

//array of structs for operatingSystems
systems_t* operatingSystems;

//array of structs for databases
databases_t* databases;



// step 4: declare 3 metadata structs, one for each table
//metadata struct for programmingLanguages table
metadata_t metadataPL;

//metadata struct for operatingSystems table
metadata_t metadataOS;

//metadata struct for Databases table
metadata_t metadataDB;




// step 5: jump to L167


// This function takes the user's input and splits it by spaces
// into an array of strings, ignoring spaces that are wrapped in quotes
// There is no need to modify this code.
// You do not need to understand this code
// but you are welcome to research its application
void splitInput(char* input, char** args, int* arg_count) {
    *arg_count = 0;
    int in_quotes = 0; // Flag to track whether we are inside quotes
    char* token_start = input;

    for (char* ptr = input; *ptr != '\0'; ptr++) {
        if (*ptr == '"') {
            // Toggle the in_quotes flag when a quote is encountered
            in_quotes = !in_quotes; 
        }

        if ((*ptr == ' ' || *ptr == '\n') && !in_quotes) {
            // If not inside quotes and a space or newline is found, 
            //consider it as a separator
            *ptr = '\0'; // Replace space or newline with null terminator
            args[(*arg_count)++] = token_start;
            token_start = ptr + 1; // Start of the next token
        }
    }

    // Add the last token (if any) after the loop
    if (*token_start != '\0') {
        // Remove leading and trailing double quotes if they exist
        if (token_start[0] == '"' && token_start[strlen(token_start) - 1] == '"') {
            token_start[strlen(token_start) - 1] = '\0'; // Remove trailing quote
            args[(*arg_count)++] = token_start + 1; // Remove leading quote
        } else {
            args[(*arg_count)++] = token_start;
        }
    }
    args[*arg_count] = NULL;
}


// step 7: implement setup function
// this function is responsible for dynamically allocating the
// particular table. Use the tables declared on L27.
void setup(char* table, int numRows) {
    // int maxCount = numRows; // this might be wrong?

    //have to first test for the particular table
    //since they are strings, you have to use the strcmp function to check
     if(strcmp(table, "programmingLanguages") == 0) {
        //use malloc to assign the needed space
        //since each table in each row contains a struct, you have to
        //allocate size for the number of rows*struct
        programmingLanguages = (language_t*)malloc(numRows * sizeof(language_t));

        //update the metadata values for the programming languages code
        //maxCount would be the number of rows because you cannot insert any 
        //additional elements other than the number of rows
       metadataPL.maxCount = numRows;
 
    } else if (strcmp(table, "operatingSystems") == 0) {
        //repeat the steps from before
        //allocating enough memory space for the items in the table
        operatingSystems = (systems_t*)malloc(numRows * sizeof(systems_t));

        //updating the metadata values for the operatingSystems metadata struct
      metadataOS.maxCount = numRows;

    } else if(strcmp(table, "databases") == 0) {
        //allocating enough memory space for the items in the table
        databases = (databases_t*)malloc(numRows * sizeof(databases_t));

        //updating the metadata values for the databases metadata struct
        metadataDB.maxCount = numRows;
    } 

    // DO NOT TOUCH THIS PRINT
    // REQUIRED FOR AUTOGRADER
    printf("setup complete\n");
}


// step 8: implement insert function
// this function is responsible for updating the corresponding
// fields of the struct located at the next available index
// make sure to use and update your metadata.

// autograder print for insufficient capacity:
// fprintf(stderr, "cannot insert due to insufficient capacity.\n");
void insert(char** args) {

char* tableName = args[1];
int indexToAdd; 
    if ((strcmp(tableName, "programmingLanguages")==0)&& (metadataPL.count< metadataPL.maxCount)) // convert to the right type
    {
        //to find the next index we have to insert at 
        indexToAdd = metadataPL.nextIndex; 
            programmingLanguages[indexToAdd].id = atoi(args[2]);
            ////strdup makes a duplicate of the string the user entered
            programmingLanguages[indexToAdd].language = strdup(args[3]); 
            programmingLanguages[indexToAdd].year = atoi(args[4]);
            programmingLanguages[indexToAdd].creator = strdup(args[5]);
            programmingLanguages[indexToAdd].paradigm = strdup(args[6]);
            programmingLanguages[indexToAdd].popularityIndex = atof(args[7]);
            programmingLanguages[indexToAdd].isDeleted = 0;
            metadataPL.count++; //increment count
            //increment nextIndex so u know where to add to next time
            metadataPL.nextIndex++; 
    }
    else if ((strcmp(tableName, "operatingSystems")==0) && (metadataOS.count<metadataOS.maxCount))
    {
        //to find the next index we have to insert at 
        indexToAdd = metadataOS.nextIndex; 
            operatingSystems[indexToAdd].id = atoi(args[2]);
            operatingSystems[indexToAdd].name = strdup(args[3]);
            operatingSystems[indexToAdd].year = atoi(args[4]);
            operatingSystems[indexToAdd].developer = strdup(args[5]);
            operatingSystems[indexToAdd].kernelType = strdup(args[6]);
            operatingSystems[indexToAdd].isDeleted = 0;
            metadataOS.count++; //increment count
            //increment nextIndex so u know where to add to next time
            metadataOS.nextIndex++; 
    }
    else if ((strcmp(tableName, "databases")==0) && (metadataDB.count<metadataDB.maxCount))
    {
        //to find the next index we have to insert at 
        indexToAdd = metadataDB.nextIndex; 
            databases[indexToAdd].id = atoi(args[2]);
            databases[indexToAdd].name = strdup(args[3]);
            databases[indexToAdd].year = atoi(args[4]);
            databases[indexToAdd].type = strdup(args[5]);
            databases[indexToAdd].developer = strdup(args[6]);
            databases[indexToAdd].isDeleted = 0;
            metadataDB.count++; //increment count
            //increment nextIndex so u know where to add to next time
            metadataDB.nextIndex++; 
        }
    else { 
         fprintf(stderr, "cannot insert due to insufficient capacity.\n");
        return; 
        //we return here because we do not want it to print both the 
        //error message and the insert complete messasge
    }
    // DO NOT TOUCH THIS PRINT
    // REQUIRED FOR AUTOGRADER
   printf("insert complete\n");
}

// step 9: implement soft delete function
// this function is responsible for marking a record as deleted
// you should be updating an internal field flag so that get will
// not display this record.
// You should not be attempting to free/overwrite this record - it remains alloc
// with a updated field
// make use of your metadata
void delete(char* table, int id) {
   // int rows;
   //we dont need to set up a variable for rows cause you can directly call 
//char* table is a pointer to the memory address of a particular table
//first, we have to check what table struct we are working with

if(strcmp(table, "programmingLanguages") == 0) {
    //we have to iterate for all the elements in the programmingLanguages
    //struct so we have to get the maxCount specifically for that particular table
    for(int i = 0; i < metadataPL.maxCount; i++) {
        if(id == programmingLanguages[i].id) {
            //mark the element at index i as "soft-deleted"
            programmingLanguages[i].isDeleted = 1;
           
           /*
            //have to decrease the count bc on a technicality,
            //this element does not exist in the struct anymore
            //no we don't have to reduce count because its a soft delete so we have 
            //still store the elements in there, they are just not visible to the users 
            //metadataPL.count = metadataPL.count - 1;  */          
        }
    }
}
else if(strcmp(table, "operatingSystems") == 0) {
    //we have to iterate for all the elements in the operatingSystems struct
    //so we have to get the maxCount specifically for that particular table
    for(int i = 0; i < metadataOS.maxCount; i++) {
        if(id == operatingSystems[i].id) {
            //mark the element at index i as "soft-deleted"
            operatingSystems[i].isDeleted = 1;
           /*
            //have to decrease the count bc on a technicality,
            //this element does not exist in the struct anymore
            //no we don't have to reduce count because its a soft delete so we have 
            //still store the elements in there, they are just not visible to the users 
            //metadataOS.count = metadataOS.count - 1;     */     
        }
    }
}
else if(strcmp(table, "databases") == 0) {
    //we have to iterate for all the elements in the databases struct
    //so we have to get the maxCount specifically for that particular table
    for(int i = 0; i < metadataDB.maxCount; i++) {
        if(id == databases[i].id) {
            //mark the element at index i as "soft-deleted"
            databases[i].isDeleted = 1;
           /*
            //have to decrease the count bc on a technicality,
            //this element does not exist in the struct anymore
            //no we don't have to reduce count because its a soft delete so we have 
            //still store the elements in there, they are just not visible to the users 
            //metadataDB.count = metadataDB.count - 1;  */        
        }
    } 
}

    // DO NOT TOUCH THIS PRINT
    // REQUIRED FOR AUTOGRADER
    printf("delete complete\n");
}


// step 10: implement modify function
// this function is responsible for overwriting all of the contents of all
// records that match an ID.
// make use of your metadata
// !!!NOTE: The structs store pointers. Make sure to free any allocated
// memory before overwriting it!!!
void modify(char** args) {
//i think char** args is a pointer to the array 
//of input values that the user puts in

//we have to first check to see what table we're working with
char* tableName = args[1];
int indexToChange;
//find the index value they want to change
//can keep this as a global variable in the function so that you dont
//have to redefine it for every if statement
//have to use atoi to convert from a string to

if(strcmp(tableName, "programmingLanguages") == 0) {
    indexToChange = atoi(args[2]);
    for(int i = 0; i < metadataPL.maxCount; i++) {
        //check to see if the id the user inputted 
        //matches the id we want to change in the struct
        if(indexToChange == programmingLanguages[i].id) {
            /*
           //we have to free the dynamically allocated strings (bc dynamically allocated means
           //that malloc was used, hence we have to use free to free the memory)
           //in this case, the members we have to free are language, creator, and paradigm
           //we only have to free the variables for that particular index not for everything */
           free(programmingLanguages[i].paradigm);
           free(programmingLanguages[i].creator);
           free(programmingLanguages[i].language);

           //once u free the dynamically allocated memories, you 
           //can reassign and overwrite the prev values

            programmingLanguages[i].id = atoi(args[3]);
            programmingLanguages[i].language = strdup(args[4]);
            programmingLanguages[i].year = atoi(args[5]);
            programmingLanguages[i].creator = strdup(args[6]);
            programmingLanguages[i].paradigm = strdup(args[7]);
            programmingLanguages[i].popularityIndex = atof(args[8]); 

        }
    }

} else if(strcmp(tableName, "operatingSystems") == 0) {
    indexToChange = atoi(args[2]);
    for(int i = 0; i < metadataOS.maxCount; i++) {
        if(indexToChange == operatingSystems[i].id) {
            /*
            //we have to free the dynamically allocated strings (bc dynamically allocated means
           //that malloc was used, hence we have to use free to free the memory)
           //in this case, the members we have to free are name, developer, and type
           //we only have to free the variables for that particular index not for everything */
           free(operatingSystems[i].kernelType);
           free(operatingSystems[i].developer);
           free(operatingSystems[i].name);

            //once u free the dynamically allocated memories, 
            //you can reassign and overwrite the prev values
            operatingSystems[i].id = atoi(args[3]);
            operatingSystems[i].name = strdup(args[4]);
            operatingSystems[i].year = atoi(args[5]);
            operatingSystems[i].developer = strdup(args[6]);
            operatingSystems[i].kernelType = strdup(args[7]);
        }
    }

} else if(strcmp(tableName, "databases") == 0) {
    indexToChange = atoi(args[2]);
    for(int i = 0; i < metadataDB.maxCount; i++) {
         if(indexToChange == databases[i].id) {
         /*
        //we have to free the dynamically allocated strings (bc dynamically allocated means
        //that malloc was used, hence we have to use free to free the memory)
        //in this case, the members we have to free are name, developer, and kernelType
        //we only have to free the variables for that particular index not for everything */

            free(databases[i].name);
            free(databases[i].developer);
            free(databases[i].type);

            //once u free the dynamically allocated memories, 
            //you can reassign and overwrite the prev values
            databases[i].id = atoi(args[3]);
            databases[i].name = strdup(args[4]);
            databases[i].year = atoi(args[5]);
            databases[i].type = strdup(args[6]);
            databases[i].developer = strdup(args[7]);
        }
    }
}

    // DO NOT TOUCH THIS PRINT
    // REQUIRED FOR AUTOGRADER
    printf("modify complete\n");
}

// step 11: implement get function
// this function is responsible for fetching all non-deleted records
// make use of your metadata
// Make sure to follow guidelines for format in writeup
// see examples as well
// Use %lf for formatting double data type
void get(char* table) {
//check what table we're working with
     if(strcmp(table, "programmingLanguages") == 0) {
    //print the titles for the table columns
    printf("id,language,year,creator,paradigm,popularityIndex\n");
    for(int i = 0; i < metadataPL.maxCount; i++) {
        if(programmingLanguages[i].isDeleted == 0) {  
            //if the element we're working with is deleted  
            printf("%d,%s,%d,%s,%s,%lf\n",
                programmingLanguages[i].id,
                programmingLanguages[i].language,
                programmingLanguages[i].year,
                programmingLanguages[i].creator,
                programmingLanguages[i].paradigm,
                programmingLanguages[i].popularityIndex
            );
        }
    }

} else if(strcmp(table, "operatingSystems") == 0) {
        //print the titles for the table columns
        printf("id,name,year,developer,kernelType\n");
        for(int i = 0; i < metadataOS.maxCount; i++) {
            if(operatingSystems[i].isDeleted == 0) { 
                //if the element we're working with is not deleted
                printf("%d,%s,%d,%s,%s\n",
                operatingSystems[i].id,
                operatingSystems[i].name,
                operatingSystems[i].year,
                operatingSystems[i].developer,
                operatingSystems[i].kernelType
                );
            }
        }

} else if(strcmp(table, "databases") == 0) {
        //print the titles for the table columns
        printf("id,name,year,type,developer\n");
        for(int i = 0; i < metadataDB.maxCount; i++) {
            if(databases[i].isDeleted == 0) { 
                //if the element we're working with is not deleted
                printf("%d,%s,%d,%s,%s\n",
                databases[i].id,
                databases[i].name,
                databases[i].year,
                databases[i].type,
                databases[i].developer      
                );
            }
        }
    }
}

// step 12: implement exit function
// this function should free all allocated memory
// Make sure to avoid memory leaks by freeing any allocated memory
// inside a struct (char*) before freeing the struct pointer
void exitProgram() {
    //we have to free the invidiual elements for each struct 
    //before we free the whole struct

    //you have to repeat the same process for 3 structs because
    //we have to free the memory of all three of the structs

    //freeing invidiual elements for PL struct
    for(int i = 0; i < metadataPL.maxCount; i++) {
        free(programmingLanguages[i].language);
        free(programmingLanguages[i].creator);
        free(programmingLanguages[i].paradigm);
    }
    //free the whole PL struct
    free(programmingLanguages); 

    //free the individual elements for the OS struct 
    for(int i = 0; i < metadataOS.maxCount; i++) {
        free(operatingSystems[i].name);
        free(operatingSystems[i].developer);
        free(operatingSystems[i].kernelType);
    }
    //free the whole OS struct
    free(operatingSystems);

    //free the individual elements of the DB struct
    for(int i = 0; i < metadataDB.maxCount; i++) {
        free(databases[i].name);
        free(databases[i].type);
        free(databases[i].developer);
    }
    //free the whole DB struct
    free(databases); 

    exit(0); 
}

// this code is responsible for parsing the user's
// input, and determining based on the command
// which function to send it to.
// You do not have to modify this code, but you should
// understand it.
void execute_cmd(char** args, int arg_count) {
    char* cmd = args[0];
    if (strcmp(cmd, "setup") == 0) {
        setup(args[1], atoi(args[2]));
    } else if (strcmp(cmd, "insert") == 0) {
        insert(args);
    } else if (strcmp(cmd, "delete") == 0) {
        delete(args[1], atoi(args[2]));
    } else if (strcmp(cmd, "modify") == 0) {
        modify(args);
    } else if (strcmp(cmd, "get") == 0) {
        get(args[1]);
    } else if (strcmp(cmd, "exit") == 0) {
        exitProgram();
    } else {
        printf("\n");
    }
}

// step 6: initialize the default metadata values here
// jump to L76
void initializeMetadata() {
    metadataPL.count = 0; 
    metadataOS.count = 0; 
    metadataDB.count = 0; 

    metadataPL.nextIndex = 0; 
    metadataOS.nextIndex = 0; 
    metadataDB.nextIndex = 0; 
}

// this code creates the interactive shell
// you do not need to modify this
// You do not need to understand this code
// but you are welcome to research its application
void cmd_loop() {
    char input[MAX_INPUT_SIZE];
    ssize_t bytes_read;
    printf("Usage: \n");
    printf("setup {table} {numRows}\n");
    printf("insert {table} {data}\n");
    printf("delete {table} {id}\n");
    printf("modify {table} {id} {data}\n");
    printf("get {table}\n\n");
    initializeMetadata();
    while (1) {
        printf("CS211> ");
        fflush(stdout);
       
        // Read user input using the read() system call
        bytes_read = read(STDIN_FILENO, input, sizeof(input));
       
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
       
        if (bytes_read == 0) {
            printf("\n");
            break;
        }
       
        // Null-terminate the input
        input[bytes_read] = '\0';

        char** args = (char**)malloc(MAX_ARGS_SIZE * sizeof(char*));
        int arg_count;

        splitInput(input, args, &arg_count);
       
        // Execute the user's command
        execute_cmd(args, arg_count);
        free(args);
    }
}

//main method
int main() {
    cmd_loop();
}