#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include "country.h"
#include "patient.h"

// **** Functions related to management of tCountry objects

// Initialize a country
tError country_init(tCountry* country, const char* name, bool isEU) {
    // Verify pre conditions
    assert(country != NULL);
    assert(name != NULL);

    // Allocate the memory for all the fields, using the length of the provided
    // text plus 1 space for the "end of string" char '\0'.
    // To allocate memory we use the malloc command.
    country->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    country->authVaccines = (tVaccineTable*)malloc(sizeof(tVaccineTable));

    // Check that memory has been allocated for all fields.
    // Pointer must be different from NULL.
    if(country->name == NULL || country->authVaccines == NULL) {
        // Some of the fields have a NULL value, what means that we found
        // some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data. As the fields are strings,
    // we need to use the string copy function strcpy.
    strcpy(country->name, name);

    // Initialize the rest of fields
    country->isEU = isEU;

    // Initialize vaccines table
    vaccineTable_init(country->authVaccines);

    // PR2 EX1
    // Initialize patients queue
    country->patients = (tPatientQueue*)malloc(sizeof(tPatientQueue));
    if(country->patients == NULL) {
        free(country->name);
        return ERR_MEMORY_ERROR;
    }

    patientQueue_create(country->patients);

    // PR3 EX2
    // Initialize vaccination batch stack
    country->vbList = (tVaccinationBatchList*)malloc(sizeof(tVaccinationBatchList));
    if(country->vbList == NULL) {
        free(country->name);
        free(country->patients);
        return ERR_MEMORY_ERROR;
    }

    vaccinationBatchList_create(country->vbList);

    return OK;
}

// Release memory used by country object
void country_free(tCountry* object) {
    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them
    if(object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }

    // Free table of authorized vaccines
    if(object->authVaccines != NULL) {
        vaccineTable_free(object->authVaccines);

        free(object->authVaccines);
        object->authVaccines = NULL;
    }

    // PR2 EX2
    // free patients queue
    if(object->patients != NULL) {
		patientQueue_free(object->patients);
		free(object->patients); 
		object->patients = NULL;
	}


    // PR3 EX2
    // free vaccination batch stack
    if(object->vbList != NULL) {
        vaccinationBatchList_free(object->vbList);
        free(object->vbList);
		object->vbList = NULL;
    }
}

// Compare two country objects
bool country_equals(tCountry * country1, tCountry * country2) {
    // Verify pre conditions
    assert(country1 != NULL);
    assert(country2 != NULL);

    // To see if two countries are equals, usually we need to see ALL the values for their fields are equals.
    // On this case, we can consider name as key identifier and compare only this value

    // Strings are pointers to a table of chars, therefore, cannot be compared  as
    // " country1->name == country2->name ". We need to use a string comparison function

    if(strcmp(country1->name, country2->name) != 0) {
        // Countries are different
        return false;
    }

    // All fields have the same value
    return true;
}

// Copy the data of a country to another country
tError country_cpy(tCountry * dest, tCountry * src) {
    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // Just in case, free space used by destination object.
    country_free(dest);

    // Initialize the element with the new data
    error = country_init(dest, src->name, src->isEU);
    if(error != OK)
        return error;

    // Copy authorized countries
    error = vaccineTable_cpy(dest->authVaccines, src->authVaccines);
    if(error != OK)
        return error;

    // Copy patient queue
    error = patientQueue_duplicate(dest->patients, *src->patients);
    if(error != OK)
        return error;

    // Copy vaccination batch stack
    error = vaccinationBatchList_duplicate(dest->vbList, *src->vbList);
    if(error != OK)
        return error;

    return OK;
}


tVaccine* country_find_vaccine(tCountry * country, const char* name) {
    int i;

    // Verify pre conditions
    assert(country != NULL);
    assert(name != NULL);

    // Search over the table and return once we found the element.
    for(i = 0; i < country->authVaccines->size; i++) {
        if(strcmp(country->authVaccines->elements[i].name, name) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(country->authVaccines->elements[i]);
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}


// Add a new patient
tError country_addPatient(tCountry * country, tPatient patient) {
    // PR2 EX1

    // Check preconditions
    assert(country != NULL);

    // Enqueue the new patient
    return patientQueue_enqueue(country->patients, patient);

}

// Add a new autorized vaccine
tError country_addVaccine(tCountry * country, tVaccine vaccine) {
    // PR2 EX1

    // Check preconditions
    assert(country != NULL);


    // add the new vaccine
    return vaccineTable_add(country->authVaccines, vaccine);

}


/*
	tCountry
	returns: 	the vaccine technology (tVaccineTechnology) that more patients from country_name.
				If the country does not have patients, it returns NONE.
*/
tVaccineTec country_getMostUsedVaccineTechnology(tCountry country) {
    // PR2 EX2
    // Verify pre conditions

    int arrayTechnologies[] = { 0, 0, 0, 0, 0, 0,  };
    int mostUsedtechnology = NONE;
    tVaccine * vaccine = NULL;

    if(patientQueue_empty(*country.patients)) {
        return NONE;
    }

    tPatientQueueNode *nodePtr = country.patients->first;

    while(nodePtr != NULL) {
        if(nodePtr->e.vaccine != NULL) {
            vaccine = vaccineTable_find(country.authVaccines, nodePtr->e.vaccine);
            if(vaccine != NULL) {
                arrayTechnologies[vaccine->vaccineTec]++;
                if(arrayTechnologies[vaccine->vaccineTec] > mostUsedtechnology) {
                    mostUsedtechnology = vaccine->vaccineTec;
                }
            }
        }
        nodePtr = nodePtr->next;
    }

    return mostUsedtechnology;
}

int country_getPatientsPerVaccine(tCountry country, tVaccine vaccine) {
    // PR2 EX3
    tPatientQueue  copy_queue;

    if(patientQueue_empty(*country.patients)) {
        return 0;
    }

    if(!country_find_vaccine(&country, vaccine.name)) {
        return 0;
    }

    patientQueue_duplicate(&copy_queue, *country.patients);

    return patientQueue_getPatientsPerVaccineRecursive(&copy_queue, vaccine.name);
}

// count how many patients already vaccinated with a vaccine technology
int country_getPatientsPerVaccineTechnology(tCountry country, tVaccineTec technology) {
    // PR2 EX3
    tPatientQueue copy_queue;

    if(patientQueue_empty(*country.patients)) {
        return 0;
    }

    if(vaccineTable_size(country.authVaccines) == 0) {
        return 0;
    }

    patientQueue_duplicate(&copy_queue, *country.patients);

    return patientQueue_getPatientsPerVaccineTechnologyRecursive(&copy_queue, *country.authVaccines, technology);
}

// inoculates all available doses of each batch of vaccines to the list of patients who have not received any vaccine
tError country_inoculate_first_vaccine(tCountry* country) {
    // PR3 EX2
	
	// Check PRE Conditions
	assert(country != NULL);
	
	// Create Queue from patients of country parameter
	tPatientQueue *patQueue = country->patients;
	
	// Create Node with first element in Queue
	tPatientQueueNode *patNode = patQueue->first;
	
	// While patient Node is not null
	while(patNode != NULL)
	{
		// For inoculate the patients, 
		// they must have 0 doses for inoculate the FIRST vaccine
		if(patNode->e.number_doses == 0)
		{
			vaccineBatchList_inoculate_first_vaccine(country->vbList, &patNode->e);
		}
		
		// Move to next node
		patNode = patNode->next;
	}
	return OK;
}

// inoculates all available doses of each batch of vaccines to the list of patients who have received 1 vaccine
tError country_inoculate_second_vaccine(tCountry* country) {
    // PR3 EX2
	
	// Check PRE Conditions
	assert(country != NULL);
	
	// Create Queue from patients of country parameter
	tPatientQueue *patQueue = country->patients;
	
	// Create Node with first element in Queue
	tPatientQueueNode *patNode = patQueue->first;
	
	// While patient Node is not null
	while(patNode != NULL)
	{
		// For inoculate the patients, 
		// they must have 1 doses for inoculate the SECOND vaccine
		if(patNode->e.number_doses == 1)
		{
			vaccineBatchList_inoculate_second_vaccine(country->vbList, &patNode->e);
		}
		
		// Move to next node
		patNode = patNode->next;
	}
	return OK;
}

// Returns the percentage of patients in the country who have been vaccinated with all doses
double country_percentage_vaccinated(tCountry* country) {
    // PR3 EX3
	
	// Check PRE Conditions
	assert(country != NULL);
	
	// Create var for save new values
	int PatVaccinate = 0;
	int PatTotal = 0;
	
	// Create Node 
	tPatientQueueNode *PatNode = country->patients->first;
	
	// While Node is not null
	while(PatNode != NULL)
	{	
		// Check if patient is vaccinated calling patient_isVaccinated function
		// if its true, add 1 unit to vaccinated variable
		if(patient_isVaccinated(&PatNode->e))
		{
			PatVaccinate++;
		}
		
		// Move to next node
		PatNode = PatNode->next;
		
		// Add 1 unit to Total Patients
		PatTotal++;
	}
	
	// Return a division of: Vaccinated / Total Patients, using float
	return ((float)PatVaccinate / PatTotal) *100;
}


// **** Functions related to management of tCountryTable objects

// Initialize the table of countries
void countryTable_init(tCountryTable * table) {
    // Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state.
    // That is, with 0 elements.
    table->size = 0;
    // Using dynamic memory, the pointer to the elements
    // must be set to NULL (no memory allocated).
    table->elements = NULL;
}

// Release the memory used by countryTable structure
void countryTable_free(tCountryTable * table) {
    int i;

    // Verify pre conditions
    assert(table != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if(table->elements != NULL) {
        for(i = 0; i < table->size; i++) {
            country_free(&table->elements[i]);
        }
        free(table->elements);
        table->elements = NULL;
        // As the table is now empty, assign the size to 0.
        table->size = 0;
    }
}

// Add a new country to the table
tError countryTable_add(tCountryTable * table, tCountry * country) {
    tCountry* elementsAux;
    tError error;

    // Verify pre conditions
    assert(table != NULL);
    assert(country != NULL);

    // Check if the element is already on the table
    if(countryTable_find(table, country->name))
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
        // by sizeof(type). In this case the type is tCountry.
        elementsAux = (tCountry*)malloc((table->size + 1) * sizeof(tCountry));

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
        // In this case the type is tCountry. We provide the previous block of memory.
        elementsAux = (tCountry*)realloc(table->elements, (table->size + 1) * sizeof(tCountry));
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
    error = country_init(&(table->elements[table->size - 1]), country->name, country->isEU);
    if(error != OK)
        return error;

    return OK;
}

// Remove a country from the table
tError countryTable_remove(tCountryTable * table, tCountry * country) {
    bool found;
    int i;
    tCountry* elementsAux;

    // Verify pre conditions
    assert(table != NULL);
    assert(country != NULL);

    // To remove an element of a table, we will move all elements after this element one position,
    // to fill the space of the removed element.
    found = false;
    for(i = 0; i < table->size; i++) {
        // If the element has been found. Displace this element to the previous element
        // (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1])
        // as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(country_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else
            if(country_equals(&table->elements[i], country)) {
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
            countryTable_free(table);
        } else {
            country_free(&table->elements[table->size - 1]);
            // Modify the used memory. As we are modifying a previously
            // allocated block, we need to use the realloc command.
            elementsAux = (tCountry*)realloc(table->elements, (table->size - 1) * sizeof(tCountry));

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

// Get country by name
tCountry* countryTable_find(tCountryTable * table, const char* name) {
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
unsigned int countryTable_size(tCountryTable * table) {
    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Copy the data of a country to another country
tError countryTable_cpy(tCountryTable* dest, tCountryTable* src) {
    int i;
    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // free dest (just in case)
    countryTable_free(dest);

    // initialize dest
    countryTable_init(dest);

    // add countries from src to dest
    for(i = 0; i < src->size; i++) {
        error = countryTable_add(dest, &src->elements[i]);
        if(error != OK)
            return error;
    }

    return OK;
}

// Prints basic information from the tCountryTable table on the screen
void countryTable_print(tCountryTable table) {
    int i;


    for(i = 0; i < table.size; i++) {
        country_print(table.elements[i]);
    }
    printf("\n");
}

// prints basic information from the tCountry on the screen
void country_print(tCountry country) {
    printf("%s\n", country.name);
    vaccineTable_print(*country.authVaccines);
    patientQueue_print(*country.patients);
}

// Add a patient to a country
tError countryTable_addPatient(tCountryTable * table, const char* name, tPatient patient) {
    assert(table != NULL);
    assert(name != NULL);
    tCountry * country;

    country = countryTable_find(table, name);
    if(country == NULL) {
        return ERR_INVALID_COUNTRY;
    }

    return country_addPatient(country, patient);
}

// Add authorized vaccine to a country
tError countryTable_addVaccine(tCountryTable * table, const char* name, tVaccine vaccine) {
    assert(table != NULL);
    assert(name != NULL);
    tCountry * country;

    country = countryTable_find(table, name);
    if(country == NULL) {
        return ERR_INVALID_COUNTRY;
    }

    return country_addVaccine(country, vaccine);
}

// Returns the number of tCountries that have an authorized vaccine
int countryTable_num_authorized(tCountryTable * table) {
    // PR1 EX3
    int i;
    int count;

    // Verify pre conditions
    assert(table != NULL);

    // Search for countries with one or more authorized vaccines.
    count = 0;
    for(i = 0; i < table->size; i++) {
        // Check the number of authorized countries
        if(vaccineTable_size(table->elements[i].authVaccines) > 0) {
            // increase the number of developers
            count = count + 1;
        }
    }

    // Return the number of developers found.
    return count;
}
