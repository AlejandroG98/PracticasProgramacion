#ifndef __COUNTRY__H__
#define __COUNTRY__H__

#include <stdbool.h>
#include "error.h"
#include "commons.h"
#include "patient.h"
#include "vaccine.h"
#include "vaccinationBatch.h"

// Data type to hold data related to a Country
typedef struct {   
    bool isEU; 
	char* name;
	tVaccineTable* authVaccines;
	tPatientQueue* patients;
    tVaccinationBatchList* vbList;
} tCountry;

// Table of tCountry elements
typedef struct {
    unsigned int size;

    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS.
    // That means that we are using the same amount of memory when the table is empty and
    // when is full. We cannot add more elements than MAX_ELEMENTS.
    // tCountry elements[MAX_ELEMENTS];

    // Using dynamic memory, the elements is a pointer to a region of memory.
    // Initially, we have no memory (NULL), and we need to allocate memory
    // when we want to add elements. We can add as many elements as we want,
    // the only limit is the total amount of memory of our computer.
    tCountry* elements;
} tCountryTable;

// **** Functions related to management of tCountry objects

// Initialize a country object
tError country_init(tCountry* country, const char* name, bool isEU);

// Release memory used by country object
void country_free(tCountry* object);

// Compare two country objects
bool country_equals(tCountry* country1, tCountry* country2);

// Copy the data of a country to another country
tError country_cpy(tCountry* dest, tCountry* src);

tVaccine* country_find_vaccine(tCountry* country, const char* name);

// Add a new patient
tError country_addPatient(tCountry* country, tPatient patient);

// Add a new vaccine
tError country_addVaccine(tCountry* country, tVaccine vaccine);

/* 	
	tCountry	
	returns: 	the vaccine technology (tVaccineTechnology) that more patients from country_name. 
				If the country does not have patients, it returns NONE. 
*/
tVaccineTec country_getMostUsedVaccineTechnology(tCountry country);

// prints information of a country on the console
void country_print(tCountry country);

// count how many patients already vaccinated the country has with that vaccine
int country_getPatientsPerVaccine(tCountry country, tVaccine vaccine);

// count how many patients already vaccinated with a vaccine technology
int country_getPatientsPerVaccineTechnology(tCountry country, tVaccineTec technology);

// inoculates all available doses of each batch of vaccines to the list of patients who have not received any vaccine
tError country_inoculate_first_vaccine(tCountry* country);

// inoculates all available doses of each batch of vaccines to the list of patients who have received 1 vaccine
tError country_inoculate_second_vaccine(tCountry* country);

// Returns the percentage of patients in the country who have been vaccinated with all doses
double country_percentage_vaccinated(tCountry* country);

// **** Functions related to management of tCountryTable objects

// Initialize the Table of countries
void countryTable_init(tCountryTable* table);

// Release the memory used by countryTable structure
void countryTable_free(tCountryTable* table);

// Add a new country to the table
tError countryTable_add(tCountryTable* table, tCountry* country);

// Remove a country from the table
tError countryTable_remove(tCountryTable* table, tCountry* country);

// Get country by name
tCountry* countryTable_find(tCountryTable* table, const char* name);

// Add a patient to a country
tError countryTable_addPatient(tCountryTable* table, const char* name, tPatient patient);

// Add authorized vaccine to a country
tError countryTable_addVaccine(tCountryTable* table, const char* name, tVaccine vaccine);
	
// Get vaccine by name
tCountry* countryTable_find_vaccine(tCountryTable* table, const char* name);

// Get the size of the table
unsigned int countryTable_size(tCountryTable* table);

// Copy the data of a country to another country
tError countryTable_cpy(tCountryTable* dest, tCountryTable* src);

// prints information of a countryTable on the console
void countryTable_print(tCountryTable table);

// Returns the number of tCountries that have an authorized vaccine 
int countryTable_num_authorized(tCountryTable* table);

// Add an authorized country to a vaccine
tError countryTable_add_authorized_vaccine(tCountryTable* table, const char* country_name,tVaccine* vac);

#endif // __COUNTRY__H__
