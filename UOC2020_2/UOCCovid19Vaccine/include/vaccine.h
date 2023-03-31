#ifndef __VACCINE__H__
#define __VACCINE__H__

#include <stdbool.h>
#include "error.h"
#include "commons.h"

// Known vaccines
#define ASTRAZENECA_VAC "AZD1222"
#define JANSSEN_VAC "JNJ-78436735"
#define MODERNA_VAC "mRNA-1273"
#define PFIZER_VAC "BNT162b2"

// vaccine technology enumeration
typedef enum {
	NONE = 0,
    ADENOVIRUSES = 1,
    SARSCOV2 = 2,
    INACTIVE = 3,
    PEPTIDE = 4,
    RNA = 5	
} tVaccineTec;

// vaccine phase enumeration
typedef enum {	
    PRECLINICAL = 0,
    PHASE1 = 1,
    PHASE1_2 = 2,
    PHASE2 = 3,
    PHASE2_3 = 4,
    PHASE3 = 5	
} tVaccinePhase;

// Data type to hold data related to a vaccine
typedef struct {
    char* name;
    tVaccineTec vaccineTec;
    tVaccinePhase vaccinePhase;
} tVaccine;

// Table of tVacine elements
typedef struct {
    unsigned int size;    
    tVaccine* elements;
} tVaccineTable;

// **** Functions related to tVaccine

// Initialize a vaccine
tError vaccine_init(tVaccine* vac, const char* name, tVaccineTec tec, tVaccinePhase phase);

// Release memory used by a vaccine
void vaccine_free(tVaccine* vac);

// Compare two vaccines
bool vaccine_equals(tVaccine* vac1, tVaccine* vac2);

// Copy a vaccine
tError vaccine_cpy(tVaccine* dest, tVaccine* src);

// Initialize the Table of countries
void vaccineTable_init(tVaccineTable* table);

// Release the memory used by countryTable structure
void vaccineTable_free(tVaccineTable* table);

// Add a new vaccine to the table
tError vaccineTable_add(tVaccineTable* table, tVaccine vaccine);

// Remove a vaccine from the table
tError vaccineTable_remove(tVaccineTable* table, tVaccine* vaccine);

// Add a new vaccine to the table
tError vaccineTable_cpy(tVaccineTable* dest, tVaccineTable* src);

// Get vaccine by name
tVaccine* vaccineTable_find(tVaccineTable* table, const char* name);

// Get the size of the table
unsigned int vaccineTable_size(tVaccineTable* table);

void vaccineTable_print(tVaccineTable table);

void vaccine_print(tVaccine vac);

// Copy the data of a country to another country



// Add an authorized country to a vaccine
//tError vaccine_add_authorized_country(tVaccine* vac, tCountry* country);

/* 	t
	country
	returns: 	the vaccine technology (tVaccineTechnology) that more patients from that country have used. 
				If the country does not have patients, it returns NO_TYPE. 
				Patients who are not vaccinated yet do not count
*/
//tVaccineTec vaccine_getMostUsedVaccineTechnology(tCountry* country);

#endif // __VACCINE__H__
