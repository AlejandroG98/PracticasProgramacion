#ifndef __DEVELOPER__H__
#define __DEVELOPER__H__

#include <stdbool.h>
#include "error.h"
#include "commons.h"
#include "vaccine.h"
#include "patient.h"

// Data type to hold data related to a Developer
typedef struct {
    char* name;
    char* country;
    tVaccine* vaccine;
} tDeveloper;

// Table of tDeveloper elements
typedef struct {
    unsigned int size;

    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS.
    // That means that we are using the same amount of memory when the table is empty and
    // when is full. We cannot add more elements than MAX_ELEMENTS.
    // tDeveloper elements[MAX_ELEMENTS];

    // Using dynamic memory, the elements is a pointer to a region of memory.
    // Initially, we have no memory (NULL), and we need to allocate memory
    // when we want to add elements. We can add as many elements as we want,
    // the only limit is the total amount of memory of our computer.
    tDeveloper* elements;
} tDeveloperTable;

// **** Functions related to management of tDeveloper objects

// Initialize a developer object
tError developer_init(tDeveloper* dev, const char* name, const char* country, tVaccine* vaccine);

// Release memory used by developer object
void developer_free(tDeveloper* object);

// Compare two developer objects
bool developer_equals(tDeveloper* dev1, tDeveloper* dev2);

// Copy the data of a developer to another developer
tError developer_cpy(tDeveloper* dest, tDeveloper* src);

// **** Functions related to management of tDeveloperTable objects

// Initialize the table of developers
void developerTable_init(tDeveloperTable* table);

// Release the memory used by tDeveloperTable structure
void developerTable_free(tDeveloperTable* table);

// Add a new developer to the table
tError developerTable_add(tDeveloperTable* table, tDeveloper* dev);

// Remove a developer from the table
tError developerTable_remove(tDeveloperTable* table, tDeveloper* dev);

// Returns the number of tDeveloper that have an authorized vaccine in at least one country
int developerTable_num_authorized(tDeveloperTable* table);

// Returns the position of the tDeveloper table with the vaccine that has more countries that
// authorize it, in case of a tie it would select the first one in the table.
int developerTable_most_popular(tDeveloperTable* table);

// Given a tDeveloper find the position it occupies in the tDevelope table
int developerTable_find(tDeveloperTable* table, tDeveloper* dev);

// Get the size of the table
unsigned int developerTable_size(tDeveloperTable* table);

// Prints basic information from the tDeveloper table on the screen
void developerTable_print(tDeveloperTable* table);

// prints basic information from the tDeveloper on the screen
void developer_print(tDeveloper* dev);

#endif // __DEVELOPER__H__
