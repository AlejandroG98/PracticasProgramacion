#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>
#include "developer.h"

// **** Functions related to management of tDeveloper objects
// Initialize a developer object
tError developer_init(tDeveloper* dev, const char* name, const char* country, tVaccine* vaccine) {
    // PR1 EX3

    tError error;

    // Verify pre conditions
    assert(dev != NULL);
    assert(name != NULL);
    assert(country != NULL);
    assert(vaccine != NULL);

    // Allocate the memory for all the fields, using the length of the provided
    // text plus 1 space for the "end of string" char '\0'.
    // To allocate memory we use the malloc command.
    dev->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    dev->country = (char*)malloc((strlen(country) + 1) * sizeof(char));
    dev->vaccine = (tVaccine*)malloc(sizeof(tVaccine));

    // Check that memory has been allocated for all fields.
    // Pointer must be different from NULL.
    if(dev->name == NULL || dev->country == NULL || dev->vaccine == NULL) {
        // Some of the fields have a NULL value, what means that we found
        // some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Initialize values to avoid problem using code in different operative systems
	dev->vaccine->name = NULL;
	dev->vaccine->vaccineTec = NONE;	
	dev->vaccine->vaccinePhase = PRECLINICAL;

    // Once the memory is allocated, copy the data. As the fields are strings,
    // we need to use the string copy function strcpy.
    strcpy(dev->name, name);
    strcpy(dev->country, country);    

    error = vaccine_cpy(dev->vaccine, vaccine);
    if(error != OK)
        return error;

    return OK;
}

// Release memory used by developer object
void developer_free(tDeveloper* object) {
    // PR1 EX3

    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them
    if(object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }

    if(object->country != NULL) {
        free(object->country);
        object->country = NULL;
    }

    if(object->vaccine != NULL) {
        vaccine_free(object->vaccine);
        free(object->vaccine);
        object->vaccine = NULL;
    }
}

// Compare two developer objects
bool developer_equals(tDeveloper* dev1, tDeveloper* dev2) {
    // PR1 EX3

    // Verify pre conditions
    assert(dev1 != NULL);
    assert(dev2 != NULL);

    // To see if two developers are equals, usually we need to see ALL the values for their fields are equals.
    // On this case, we can consider name as key identifier and compare only this value

    // Strings are pointers to a table of chars, therefore, cannot be compared  as
    // " dev1->name == dev2->name ". We need to use a string comparison function

    if(strcmp(dev1->name, dev2->name) != 0) {
        // Developers are different
        return false;
    }

    // All fields have the same value
    return true;
}

// Copy the data of a developer to another developer
tError developer_cpy(tDeveloper* dest, tDeveloper* src) {
    // PR1 EX3

    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // Just in case, free space used by destination object.
    developer_free(dest);

    // Initialize the element with the new data
    error = developer_init(dest, src->name, src->country, src->vaccine);
    if(error != OK)
        return error;

    return OK;
}


// **** Functions related to management of tDeveloperTable objects

// Initialize the table of developers
void developerTable_init(tDeveloperTable* table) {
    // PR1 EX3

    // Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state.
    // That is, with 0 elements.
    table->size = 0;
    // Using dynamic memory, the pointer to the elements
    // must be set to NULL (no memory allocated).
    table->elements = NULL;
}

// Release the memory used by tDeveloperTable structure
void developerTable_free(tDeveloperTable* table) {
    // PR1 EX3

    int i;

    // Verify pre conditions
    assert(table != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if(table->elements != NULL) {
        for(i = 0; i < table->size; i++) {
            developer_free(&table->elements[i]);
        }
        free(table->elements);
        table->elements = NULL;
        // As the table is now empty, assign the size to 0.
        table->size = 0;
    }
}

// Add a new developer to the table
tError developerTable_add(tDeveloperTable* table, tDeveloper* dev) {
    // PR1 EX3

    tDeveloper* elementsAux;
    tError error;

    // Verify pre conditions
    assert(table != NULL);
    assert(dev != NULL);

    // Check if the element is already on the table
    if(developerTable_find(table, dev) >= 0)
        return ERR_DUPLICATED;

    // The first step is to allocate the required space.
    // There are two methods to manage the
    // memory (malloc and realloc). Malloc allows
    // to allocate a new memory block, while realloc
    // allows to modify an existing memory block.
    if(table->size == 0) {  // Empty table
        // Since the table is empty, and we do not have any previous memory block,
        // we have to use malloc. The amount of memory we need is the number of
        // elements (will be 1) times the size of one element, which is computed
        // by sizeof(type). In this case the type is tDeveloper.
        elementsAux = (tDeveloper*)malloc((table->size + 1) * sizeof(tDeveloper));

        // Check that the memory has been allocated
        if(elementsAux == NULL) {
            // Error allocating or reallocating the memory
            return ERR_MEMORY_ERROR;
        } else {
            table->elements = elementsAux;
            // set the table size to one
            table->size = 1;
        }
    } else { // table with elements
        // Since the table is not empty, we already have a memory block.
        // We need to modify the size of this block, using the realloc command.
        // The amount of memory we need is the number of elements times
        // the size of one element, which is computed by sizeof(type).
        // In this case the type is tDeveloper. We provide the previous block of memory.
        elementsAux = (tDeveloper*)realloc(table->elements, (table->size + 1) * sizeof(tDeveloper));
        // Check that the memory has been allocated
        if(elementsAux == NULL) {
            // Error allocating or reallocating the memory
            return ERR_MEMORY_ERROR;
        } else {
            table->elements = elementsAux;
            // Increase the number of elements of the table
            table->size = table->size + 1;
        }
    }

    // Once we have the block of memory, which is an array of tCountry elements,
    // we initialize the new element (which is the last one). The last element
    // is " table->elements[table->size - 1] " (we start counting at 0)
    error = developer_init(&(table->elements[table->size - 1]), dev->name, dev->country, dev->vaccine);
    if(error != OK)
        return error;

    return OK;
}

// Remove a developer from the table
tError developerTable_remove(tDeveloperTable* table, tDeveloper* dev) {
    // PR1 EX3

    bool found;
    int i;
    tDeveloper* elementsAux;

    // Verify pre conditions
    assert(table != NULL);
    assert(dev != NULL);

    // To remove an element of a table, we will move all elements after this element one position,
    // to fill the space of the removed element.
    found = false;
    for(i = 0; i < table->size; i++) {
        // If the element has been found. Displace this element to the previous element
        // (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1])
        // as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(developer_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else
            if(developer_equals(&table->elements[i], dev)) {
                // The current element is the element we want to remove. Set found flag to true to start element movement.
                found = true;
            }
    }

    // Once removed the element, we need to modify the memory used by the table.
    if(found) {
        // If we are removing the last element, we will free
        // the last/remaining element in table / assign pointer
        // to NULL
        if(table->size <= 1) {
            developerTable_free(table);
        } else {
            developer_free(&table->elements[table->size - 1]);
            // Modify the used memory. As we are modifying a previously
            // allocated block, we need to use the realloc command.
            elementsAux = (tDeveloper*)realloc(table->elements, (table->size - 1) * sizeof(tDeveloper));

            // Check that the memory has been allocated
            if(elementsAux == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            } else {
                table->elements = elementsAux;
                // Succesfully allocated, set new table size
                table->size = table->size - 1;
            }
        }
    } else {
        // If the element was not in the table, return an error.
        return ERR_NOT_FOUND;
    }

    return OK;
}


// Given a tDeveloper find the position it occupies in the tDevelope table
int developerTable_find(tDeveloperTable* table, tDeveloper* dev) {
    // PR1 EX3

    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(dev != NULL);

    // Search over the table and return once we found the element.
    for(i = 0; i < table->size; i++) {
        if(developer_equals(&table->elements[i], dev)) {
            // Return the position of the element
            return i;
        }
    }

    // The element has not been found. Return ERR_NOT_FOUND.
    return ERR_NOT_FOUND;
}

// Get the size of the table
unsigned int developerTable_size(tDeveloperTable* table)  {
    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Prints basic information from the tDeveloper table on the screen
void developerTable_print(tDeveloperTable* table) {
    int i;

    // Verify pre conditions
    assert(table != NULL);

    for(i = 0; i < table->size; i++) {
        developer_print(&table->elements[i]);
    }
    printf("\n");
}

// prints basic information from the tDeveloper on the screen
void developer_print(tDeveloper* dev) {
    // Verify pre conditions
    assert(dev != NULL);

    printf("%s %s %s\n", dev->name, dev->country, dev->vaccine->name);
}
