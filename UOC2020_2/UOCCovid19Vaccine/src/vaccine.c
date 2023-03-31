#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "patient.h"
#include "vaccine.h"
#include "country.h"

// Initialize a vaccine
tError vaccine_init(tVaccine* vac, const char* name, tVaccineTec tec, tVaccinePhase phase) {
    // PR1 EX2

    // Verify pre conditions
    assert(vac != NULL);
    assert(name != NULL);

    // Allocate the memory for the name string field, using the length of the provided
    // text plus 1 space for the "end of string" char '\0'.
    // To allocate memory we use the malloc command.
    vac->name = (char*)malloc((strlen(name) + 1) * sizeof(char));

    // Check that memory has been allocated.
    // Pointer must be different from NULL.
    if(vac->name == NULL) {
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data.
    vac->vaccineTec = tec;
    vac->vaccinePhase = phase;

    // As the fields are strings, we need to use the string copy function strcpy.
    strcpy(vac->name, name);


    return OK;
}

// Release memory used by a vaccine
void vaccine_free(tVaccine* vac) {
    // PR1 EX2

    // Verify pre conditions
    assert(vac != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them
    if(vac->name != NULL) {
        free(vac->name);
        vac->name = NULL;
    }

    vac->vaccineTec = NONE;

    vac->vaccinePhase = PRECLINICAL;


}

// Compare two vaccines
bool vaccine_equals(tVaccine* vac1, tVaccine* vac2) {
    // PR1 EX2

    bool result;

    // Verify pre conditions
    assert(vac1 != NULL);
    assert(vac2 != NULL);

    result = true;
    // To see if two vaccines are equals, we need to see if the names are equals.
    // Strings are pointers to a table of chars, therefore, cannot be compared  as
    // vac1->name == vac2->name ". We need to use a string comparison function
    if(strcmp(vac1->name, vac2->name) != 0) {
        // names are different
        result = false;
    }

    // All fields have the same value
    return result;
}

// Copy a vaccine
tError vaccine_cpy(tVaccine* dest, tVaccine* src) {
    // PR1 EX2

    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // free dest vaccine (just in case)
    vaccine_free(dest);

    // initialize dest with src values.
    error = vaccine_init(dest, src->name, src->vaccineTec, src->vaccinePhase);
    // check if any error occured
    if(error != OK)
        return error;

    return OK;
}

tVaccineTec vaccine_getMostUsedVaccineTechnology(tCountryTable* countries) {

    // Verify pre conditions
    assert(countries != NULL);

    tPatientQueueNode *nodePtr;
    tVaccine *vaccine;
    int technologies[] = { 0, 0, 0, 0, 0, 0 };
    int moreUsedTechnology = 0;
    int mostUsedTechnology = NONE;


    for(int i = 0; i < countries->size; i++) {



        if(patientQueue_empty(*countries->elements[i].patients)) {
            continue;
        }

        nodePtr = countries->elements[i].patients->first;

        int i = 0;

        while(nodePtr != NULL) {

            if(nodePtr->e.vaccine != NULL) {
                vaccine = country_find_vaccine(&countries->elements[i], nodePtr->e.vaccine);
                technologies[vaccine->vaccineTec]++;
            }


        }

    }

    for(int i = 0; i < 6; i++) {
        if(technologies[i] > moreUsedTechnology) {
            mostUsedTechnology = i;
            moreUsedTechnology = technologies[i];
        }
    }

    return mostUsedTechnology;

}


// **** Functions related to management of tVaccineTable objects



// Initialize the table of vaccines
void vaccineTable_init(tVaccineTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state.
    // That is, with 0 elements.
    table->size = 0;
    // Using dynamic memory, the pointer to the elements
    // must be set to NULL (no memory allocated).
    table->elements = NULL;
}

// Release the memory used by vaccineTable structure
void vaccineTable_free(tVaccineTable* table) {
    int i;

    // Verify pre conditions
    assert(table != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if(table->elements != NULL) {
        for(i = 0; i < table->size; i++) {
            vaccine_free(&table->elements[i]);
        }
        free(table->elements);
        table->elements = NULL;
        // As the table is now empty, assign the size to 0.
        table->size = 0;
    }
}

// Add a new vaccine to the table
tError vaccineTable_add(tVaccineTable* table, tVaccine vaccine) {
    tVaccine* elementsAux;

    // Verify pre conditions
    assert(table != NULL);

    // Check if the element is already on the table
    if(vaccineTable_find(table, vaccine.name))
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
        // by sizeof(type). In this case the type is tVaccine.
        elementsAux = (tVaccine*)malloc((table->size + 1) * sizeof(tVaccine));

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
        // In this case the type is tVaccine. We provide the previous block of memory.
        elementsAux = (tVaccine*)realloc(table->elements, (table->size + 1) * sizeof(tVaccine));
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

    // Once we have the block of memory, which is an array of tVaccine elements,
    // we initialize the new element (which is the last one). The last element
    // is " table->elements[table->size - 1] " (we start counting at 0)

    return vaccine_init(&(table->elements[table->size - 1]), vaccine.name, vaccine.vaccineTec, vaccine.vaccinePhase);

}

// Remove a vaccine from the table
tError vaccineTable_remove(tVaccineTable* table, tVaccine* vaccine) {
    bool found;
    int i;
    tVaccine* elementsAux;

    // Verify pre conditions
    assert(table != NULL);
    assert(vaccine != NULL);

    // To remove an element of a table, we will move all elements after this element one position,
    // to fill the space of the removed element.
    found = false;
    for(i = 0; i < table->size; i++) {
        // If the element has been found. Displace this element to the previous element
        // (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1])
        // as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(vaccine_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else
            if(vaccine_equals(&table->elements[i], vaccine)) {
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
            vaccineTable_free(table);
        } else {
            vaccine_free(&table->elements[table->size - 1]);
            // Modify the used memory. As we are modifying a previously
            // allocated block, we need to use the realloc command.
            elementsAux = (tVaccine*)realloc(table->elements, (table->size - 1) * sizeof(tVaccine));

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

// Get vaccine by name
tVaccine* vaccineTable_find(tVaccineTable* table, const char* name) {
    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(name != NULL);

    // Search over the table and return once we found the element.
    for(i = 0; i < table->size; i++) {
        if(strcmp(table->elements[i].name, name) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}



// Get the size of the table
unsigned int vaccineTable_size(tVaccineTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Copy the data of a vaccine to another vaccine
tError vaccineTable_cpy(tVaccineTable* dest, tVaccineTable* src) {
    int i;
    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // free dest (just in case)
    vaccineTable_free(dest);

    // initialize dest
    vaccineTable_init(dest);

    // add vaccines from src to dest
    for(i = 0; i < src->size; i++) {
        error = vaccineTable_add(dest, src->elements[i]);
        if(error != OK)
            return error;
    }

    return OK;
}

// Prints basic information from the tDeveloper table on the screen
void vaccineTable_print(tVaccineTable table) {
    int i;


    for(i = 0; i < table.size; i++) {
        vaccine_print(table.elements[i]);
    }
    printf("\n");
}

// prints basic information from the tVaccine on the screen
void vaccine_print(tVaccine vac) {

    printf("%s %d %d\n", vac.name, vac.vaccineTec, vac.vaccinePhase);
}
