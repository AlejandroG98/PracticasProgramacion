#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "country.h"
#include "test_pr2.h"
#include "country.h"
#include "vaccine.h"
#include "developer.h"
#include "patient.h"

#define NUMBER_PATIENTS 100
#define NUMBER_VACCINES 3

// Run all tests for PR2
bool run_pr2(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");

    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);

    ok = run_pr2_ex1(section) && ok;
    ok = run_pr2_ex2(section) && ok;
    ok = run_pr2_ex3(section) && ok;

    return ok;
}

// Run all tests for PR2
bool run_pr2_ex1(tTestSection* test_section) {
  bool passed = true, failed = false;    
    tError err;
    
    tCountry spain, germany, eeuu, uk, france;
    tVaccine pfizer_vaccine, moderna_vaccine, oxford_vaccine;
	tPatient garcia, gonzalez, rodriguez ;
	tCountryTable countries_eu;
	tPatientQueue patiens_list;
	bool list_created = false;
	
	
	// PRETEST 0: Test implemented functions
    failed = false;
    start_test(test_section, "PR2_EX1_0", "Test implemented functions");
	
	countryTable_init(&countries_eu);

    err=country_init(&spain, "Spain", true);
	if(err!=OK) {
        failed = true;
    } 
	
	country_init(&germany, "Germany", true);
	country_init(&eeuu, "EEUU", false);
	country_init(&uk, "UK", false);
	country_init(&france, "France", true);

	countryTable_add(&countries_eu, &spain);
	countryTable_add(&countries_eu, &germany);
	countryTable_add(&countries_eu, &france);

    vaccine_init(&pfizer_vaccine, "BNT162b2", RNA, PHASE3); //Pfizer
    vaccine_init(&moderna_vaccine, "mRNA-1273", RNA, PHASE3); //Moderna
    vaccine_init(&oxford_vaccine, "AZD1222", ADENOVIRUSES, PHASE3); //Oxford

    country_addVaccine(&spain,pfizer_vaccine);
    country_addVaccine(&spain,moderna_vaccine);
    country_addVaccine(&spain,oxford_vaccine);    

    err=patient_init(&garcia, "Mrs. Garcia", 1,pfizer_vaccine.name, 0, 2, ANYONE_ELSE);
	if(err!=OK) {
        failed = true;
    } 
	patient_init(&gonzalez, "Mr. Gonzalez", 2,moderna_vaccine.name, 0, 1, ANYONE_ELSE);	
    patient_init(&rodriguez, "Mrs. Rodriguez", 3,oxford_vaccine.name, 0, 1, ANYONE_ELSE);
   
	
    if(failed) {
        end_test(test_section, "PR2_EX1_0", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_0", true);
    }
  
    // TEST 1: Initialize the queue of patients
    failed = false;
    start_test(test_section, "PR2_EX1_1", "Initialize the queue of patients");
    
    err=patientQueue_create(&patiens_list);
    
	if(err!=OK) {
        failed = true;
    } else
		{
		if(patiens_list.first != NULL || patiens_list.last != NULL) {
			failed = true;
		} else {
			
			list_created = true;
		}
	}
    
    if(failed) {
        end_test(test_section, "PR2_EX1_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_1", true);
    }

	// TEST 2: Test empty method with empty queue
    failed = false;
    start_test(test_section, "PR2_EX1_2", "Test empty method with empty queue");
    
    if(patiens_list.first != NULL || patiens_list.last != NULL) {
        failed = true;
    }
    
    if(!patientQueue_empty(patiens_list)) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX1_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_2", true);
    }

     // TEST 3: Enqueue a new patient
    failed = false;
    start_test(test_section, "PR2_EX1_3", "Enqueue a new patient");
    
    err=patientQueue_enqueue(&patiens_list, garcia);
    
    if(err!=OK) {
        failed = true;
    } else
    {
        // Else added to exectue Test with not implemented functions
        if(patiens_list.first == NULL || patiens_list.last == NULL) {
            failed = true;
        }

        if(patiens_list.first != patiens_list.last) {
            failed = true;
        }
        
        if(!patient_compare(garcia, patiens_list.first->e)) {
            failed = true;
        }
    }    
    
    if(failed) {
        end_test(test_section, "PR2_EX1_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_3", true);
    }
    
    // TEST 4: Enqueue multiple patients
    failed = false;
    start_test(test_section, "PR2_EX1_4", "Enqueue multiple patients");
    
    err=patientQueue_enqueue(&patiens_list, gonzalez);
    
    if(err!=OK) {
        failed = true;
    } else
    {
        // Else added to exectue Test with not implemented functions
        if(patiens_list.first == NULL || patiens_list.last == NULL) {
            failed = true;
        }

        if(patiens_list.first == patiens_list.last) {
            failed = true;
        }
        
        if(!patient_compare(garcia, patiens_list.first->e)) {
            failed = true;
        }
        if(!patient_compare(gonzalez, patiens_list.last->e)) {
            failed = true;
        }
    }

    err=patientQueue_enqueue(&patiens_list, rodriguez);
    
    if(err!=OK) {
        failed = true;
    } else
    {
        // Else added to exectue Test with not implemented functions
        if(patiens_list.first == NULL || patiens_list.last == NULL) {
            failed = true;
        }

        if(patiens_list.first == patiens_list.last) {
            failed = true;
        }
        
        if(!patient_compare(garcia, patiens_list.first->e)) {
            failed = true;
        }
        if(!patient_compare(rodriguez, patiens_list.last->e)) {
            failed = true;
        }
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX1_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_4", true);
    }

    // TEST 5: Add a patient with invalid country
    failed = false;
    start_test(test_section, "PR2_EX1_5", "Add a patient with invalid country");
    
    if(!list_created) {
        failed = true;
    }

    err = countryTable_addPatient(&countries_eu, "non_existing_country", garcia);
    if (err != ERR_INVALID_COUNTRY) {
        failed = true;
    }
        
    
    if(failed) {
        end_test(test_section, "PR2_EX1_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_5", true);
    }    
	
	// TEST 6: Add a patient in a country
    failed = false;
    start_test(test_section, "PR2_EX1_6", "Add a patient in a country");

    err = countryTable_addPatient(&countries_eu, "Spain", garcia);
    if (err != OK) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR2_EX1_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_6", true);
    }        
        
    // Remove used data

    country_free(&spain);
    country_free(&germany);
    country_free(&eeuu);
    country_free(&uk);
    country_free(&france);

    vaccine_free(&pfizer_vaccine);
    vaccine_free(&moderna_vaccine);
    vaccine_free(&oxford_vaccine);

	countryTable_free(&countries_eu);
	
	patient_free(&garcia);
	patient_free(&rodriguez);
	patient_free(&gonzalez);
	
    patientQueue_free(&patiens_list);
	
    return passed;
}

// Run tests for PR2 exercise 2
bool run_pr2_ex2(tTestSection* test_section) {
    bool passed = true, failed = false;  
 	
	tError err;
	tCountry spain, germany, eeuu, uk, france;
	tCountry * country;
    tVaccine pfizer_vaccine, moderna_vaccine, oxford_vaccine;
	tPatient garcia, gonzalez, rodriguez ;
	tPatient * head_patient;
	tCountryTable countries_eu;
	tPatientQueue patiens_list;
	bool list_created = false;	
	   
	
	countryTable_init(&countries_eu);

    country_init(&spain, "Spain", true);	
	country_init(&germany, "Germany", true);
	country_init(&eeuu, "EEUU", false);
	country_init(&uk, "UK", false);
	country_init(&france, "France", true);

	countryTable_add(&countries_eu, &spain);
	countryTable_add(&countries_eu, &germany);
	countryTable_add(&countries_eu, &france);

    vaccine_init(&pfizer_vaccine, "BNT162b2", RNA, PHASE3); //Pfizer
    vaccine_init(&moderna_vaccine, "mRNA-1273", RNA, PHASE3); //Moderna
    vaccine_init(&oxford_vaccine, "AZD1222", ADENOVIRUSES, PHASE3); //Oxford

	countryTable_addVaccine(&countries_eu,"Spain",pfizer_vaccine);
    countryTable_addVaccine(&countries_eu,"Spain",moderna_vaccine);
    countryTable_addVaccine(&countries_eu,"Spain",oxford_vaccine);     
    
    patient_init(&garcia, "Mrs. Garcia", 1, NULL, 0,0, ANYONE_ELSE);	
	patient_init(&gonzalez, "Mr. Gonzalez", 2,NULL, 0,0, ANYONE_ELSE);	
    patient_init(&rodriguez, "Mrs. Rodriguez", 3,NULL, 0,0, ANYONE_ELSE);   
	
   
	// TEST 1: Request the head  patient of an country with no patients 
    failed = false;
    start_test(test_section, "PR2_EX2_1", "Request the head  patient of an country with no patients ");
    
    
    err=patientQueue_create(&patiens_list);
    
	if(err!=OK) {
        failed = true;
    } else
		{
		if(patiens_list.first != NULL || patiens_list.last != NULL) {
			failed = true;
		} else {
			
			list_created = true;
		}
	}
    
    head_patient = patientQueue_head(patiens_list);
    
    if(head_patient != NULL) {
        failed = true;
    }    
    
    if(failed) {
        end_test(test_section, "PR2_EX2_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_1", true);
    }

	// TEST 2: Get the head patient of a country with many patients
    failed = false;
    start_test(test_section, "PR2_EX2_2", "Get the head patient of a country with many patients");
    
	
	
	if (list_created){
	
		countryTable_addPatient(&countries_eu, "Spain", garcia);
		countryTable_addPatient(&countries_eu, "Spain", gonzalez);
		countryTable_addPatient(&countries_eu, "Spain", rodriguez);
		
		
		country = countryTable_find(&countries_eu,"Spain");
		
		if (country!= NULL && !patientQueue_empty(*(country->patients)))
		{
				
			head_patient = patientQueue_head(*country->patients);
			
			if(list_created) {
				if (head_patient == NULL) {
					failed = true;
				} else {
					if (!patient_compare(*head_patient,garcia)){
						failed = true;
					}				
				   
				}
			} else {
				failed = true;
			}
		}
		else{
			// Functions are not implemented
			failed = true;
		}
		
	}
	else{
		
		failed = true;
	} 
	
    if(failed) {
        end_test(test_section, "PR2_EX2_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_2", true);
    }

	// TEST 3: Dequeue from country with multiple patients
    failed = false;
    start_test(test_section, "PR2_EX2_3", "Dequeue from country with multiple patients");
	
	country = countryTable_find(&countries_eu,"Spain");
    
    if(list_created) {

		head_patient = patientQueue_dequeue(country->patients);// NOW country with two patients

        if (head_patient == NULL) {
            failed = true;
        } else {        
                if (!patient_compare(*head_patient,garcia)){
                failed = true;
				}
				else{
					patient_free(head_patient);
					free(head_patient);
					}
        }
    } else {
        failed = true;
    }    
    
	if(list_created) {
		head_patient = patientQueue_dequeue(country->patients);// NOW country with just one patient
        if (head_patient == NULL) {
            failed = true;
        } else {        
                if (!patient_compare(*head_patient,gonzalez)){
                failed = true;
            }else{
					patient_free(head_patient);
					free(head_patient);
					}
        }
    } else {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX2_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_3", true);
    }
    

	
	// TEST 4: Dequeue from country with just one patient
    failed = false;
    start_test(test_section, "PR2_EX2_4", "Dequeue from country with just one patient");
    
    if(list_created) {
		head_patient = patientQueue_dequeue(country->patients);// NOW country with no patients

        if (head_patient == NULL) {
            failed = true;
        } else {        
                if (!patient_compare(*head_patient,rodriguez)){
                failed = true;
				}
				else{
					patient_free(head_patient);
					free(head_patient);
				}
        }
		
		if (!patientQueue_empty(*(country->patients))){
			failed = true;
		} 
    } else {
        failed = true;
    }
    
	   
    
    if(failed) {
        end_test(test_section, "PR2_EX2_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_4", true);
    }
	
	// TEST 5: Dequeue from a country with no patients 
    failed = false;
    start_test(test_section, "PR2_EX2_5", "Dequeue from a country with no patients ");
    
    if(list_created) {
		head_patient = patientQueue_dequeue(country->patients);// NOW country with no patients
        if (head_patient != NULL) {
            failed = true;
        }         
    } else {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR2_EX2_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_5", true);
    }
	
	// TEST 6: Innoculate a vaccine to a patient
    failed = false;
    start_test(test_section, "PR2_EX2_6", "Innoculate a vaccine to a patient");
   
	
	
	err=patient_inoculate_vaccine(&garcia,moderna_vaccine.name,0);
	
	if (err != OK || garcia.vaccine == NULL || garcia.number_doses!=1)
	{
        failed = true;
		
    }
	else if (strcmp(garcia.vaccine, moderna_vaccine.name)){
			failed = true;
	}
	
	err=patient_inoculate_vaccine(&garcia,pfizer_vaccine.name,0);

    if (err != ERR_INVALID_VACCINE)
	{
		failed = true;
        
    }

	else if ( strcmp(garcia.vaccine, moderna_vaccine.name) || garcia.number_doses!=1)
	{
		failed = true;
	}
	
	err=patient_inoculate_vaccine(&garcia,moderna_vaccine.name,0);

	if (err != OK || garcia.vaccine == NULL || garcia.number_doses!=2)
	{
        failed = true;
		
    }
	else if (strcmp(garcia.vaccine, moderna_vaccine.name)){
		failed = true;
	}
	
    if(failed) {
        end_test(test_section, "PR2_EX2_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_6", true);
	}

	
	// TEST 7: Get most used vaccine technology from a country  
    failed = false;
    start_test(test_section, "PR2_EX2_7", "Get most used vaccine technology from a country");
   
   	patient_inoculate_vaccine(&gonzalez,pfizer_vaccine.name,0);
	
	patient_inoculate_vaccine(&rodriguez,oxford_vaccine.name,0);
	patient_inoculate_vaccine(&rodriguez,oxford_vaccine.name,0);

	countryTable_addPatient(&countries_eu, "Spain", rodriguez);

	country = countryTable_find(&countries_eu,"Spain");

	if (country_getMostUsedVaccineTechnology(*country)!= ADENOVIRUSES){
		failed = true;
	}
		
	countryTable_addPatient(&countries_eu, "Spain", garcia);
	countryTable_addPatient(&countries_eu, "Spain", gonzalez);
		   
	if (country_getMostUsedVaccineTechnology(*country)!= RNA){
		failed = true;
	}
	   
	if (country_getMostUsedVaccineTechnology(germany)!= NONE){
		failed = true;
	} 
	
    if(failed) {
        end_test(test_section, "PR2_EX2_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_7", true);
    }
	
	// TEST 8: free a country with a table of patients
    failed = false;
    start_test(test_section, "PR1_EX2_8", "free a country with a table of patients");

    country_free(&spain);
	
	if (list_created && spain.patients!=NULL){
		 failed = true;
	}

    if(failed) {
        end_test(test_section, "PR1_EX2_8", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_8", true);
    }
	
	// Remove used data
	
	
	countryTable_free(&countries_eu);

    
    country_free(&germany);
    country_free(&eeuu);
    country_free(&uk);
    country_free(&france);

    vaccine_free(&pfizer_vaccine);
    vaccine_free(&moderna_vaccine);
    vaccine_free(&oxford_vaccine);
	
	
	patient_free(&garcia);
	patient_free(&gonzalez);
	patient_free(&rodriguez);
	
    patientQueue_free(&patiens_list);

    return passed;
}

// Run tests for PR2 exercise 3
bool run_pr2_ex3(tTestSection* test_section) {
	
	bool passed = true, failed = false;  

    tError err = false;;
    tCountry spain, foo_country;
    tVaccine vaccines[3], foo_vaccine;
	tPatient patients [NUMBER_PATIENTS], foo_patients[NUMBER_PATIENTS];
	char name[13];
	tPatientQueue patiens_list1, patiens_list2, empty_patien_list ;	
	int number_patients, expected_number_patients;
	bool list_created = true;
	
	patientQueue_create(&patiens_list1);
    patientQueue_create(&patiens_list2);
    patientQueue_create(&empty_patien_list);
	
	if(patiens_list1.first != NULL || patiens_list1.last != NULL) {
		list_created = false;
	}
	
	err = country_init(&spain, "Spain", true);
	if (err!=OK){
		list_created = false;
		}
	
	country_init(&foo_country, "Foo country", true);	
	
	
    vaccine_init(&vaccines[0], "BNT162b2", RNA, PHASE3); //Pfizer
    vaccine_init(&vaccines[1], "mRNA-1273", RNA, PHASE3); //Moderna
    vaccine_init(&vaccines[2], "AZD1222", ADENOVIRUSES, PHASE3); //Oxford
    vaccine_init(&foo_vaccine, "Foo-Vaccine", NONE, PRECLINICAL); //foo vaccine

	for(int i=0; i<NUMBER_VACCINES; i++){
		country_addVaccine(&spain,vaccines[i]);
	}
    
	
	for(int i=0;i<NUMBER_PATIENTS;i++){
		if(i == NUMBER_PATIENTS/2){
			// add foo patient
			patient_init(&foo_patients[i], "foo_patient", i+1, NULL, 0,0, ANYONE_ELSE);	
			}
		else {
			snprintf(name, 13,"%s_%04d", "Patient", i+1);
			patient_init(&foo_patients[i], name, i+1, NULL, 0,0, ANYONE_ELSE);					
		}
		patient_inoculate_vaccine(&foo_patients[i],vaccines[i%3].name,0);
		patientQueue_enqueue(&patiens_list2, foo_patients[i]);	

	}
	
	for(int i=0;i<NUMBER_PATIENTS;i++){
		
		snprintf(name, 13,"%s_%04d", "Patient", i+1);
		patient_init(&patients[i], name, i+1, NULL, 0,0, ANYONE_ELSE);	
		patient_inoculate_vaccine(&patients[i],vaccines[i%3].name,0);
		country_addPatient(&spain, patients[i]);
	}

    
	
	
	// TEST 0: Compare two patients queries iteratively
    failed = false;
    start_test(test_section, "PR2_EX3_0", "Compare two patients queries iteratively ");
	
	if (list_created && patientQueue_duplicate(&patiens_list1,*spain.patients)==OK){
		
		if (!patientQueue_compareIterative(spain.patients,&patiens_list1)){
			failed = true;
		}
		if (patientQueue_compareIterative(&patiens_list1,&patiens_list2)){
			failed = true;
		}
		if (!patientQueue_compareIterative(&empty_patien_list,&empty_patien_list)){
			failed = true;
		}
		if (patientQueue_compareIterative(&patiens_list1,&empty_patien_list)){
			failed = true;
		}
	}
	else {
		failed = true;
	}
    
    if(failed) {
        end_test(test_section, "PR2_EX3_0", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_0", true);
    }
	
	// TEST 1: Compare two patients queries recursively
    failed = false;
    start_test(test_section, "PR2_EX3_1", "Compare two patients queries recursively ");
	
	if (list_created){
		if (!patientQueue_compare(spain.patients,&patiens_list1)){
			failed = true;
		}
		if (patientQueue_compare(&patiens_list1,&patiens_list2)){
			failed = true;
		}
		if (!patientQueue_compare(&empty_patien_list,&empty_patien_list)){
			failed = true;
		}
		if (patientQueue_compare(&patiens_list1,&empty_patien_list)){
			failed = true;
		}
	}
	else {
		failed = true;
	}
    
    if(failed) {
        end_test(test_section, "PR2_EX3_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_1", true);
    }
	
	// TEST 2: How many patients already vaccinated in a country

    failed = false;
    start_test(test_section, "PR2_EX3_2", "How many patients already vaccinated in a country");
	
	if (list_created){
		if (country_getPatientsPerVaccine(foo_country,vaccines[0])!=0){
			failed = true;
		}
		if (country_getPatientsPerVaccine(spain,foo_vaccine)!=0){
			failed = true;
		}
		expected_number_patients = NUMBER_PATIENTS/3+ (NUMBER_PATIENTS % NUMBER_VACCINES != 0);
		number_patients = country_getPatientsPerVaccine(spain,vaccines[0]);
		if (expected_number_patients!=number_patients){
			failed = true;
		}
		expected_number_patients = NUMBER_PATIENTS/3;
		number_patients = country_getPatientsPerVaccine(spain,vaccines[2]);

		if (expected_number_patients!=number_patients){
			failed = true;
		}
		
	}
	else {
		failed = true;
	}
    
    if(failed) {
        end_test(test_section, "PR2_EX3_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_2", true);
    }
	
	// TEST 3: How many patients have been vaccinated with a technology

    failed = false;
    start_test(test_section, "PR2_EX3_3", "How many patients have been vaccinated with a technology");
	
	if (list_created){
		if (country_getPatientsPerVaccineTechnology(foo_country,RNA)!=0){
			failed = true;
		}
		if (country_getPatientsPerVaccineTechnology(spain,PEPTIDE)!=0){
			failed = true;
		}
		expected_number_patients = 2*NUMBER_PATIENTS/3+ (NUMBER_PATIENTS % NUMBER_VACCINES != 0);
		number_patients = country_getPatientsPerVaccineTechnology(spain,RNA);
		if (expected_number_patients!=number_patients){
			failed = true;
		}
		expected_number_patients = NUMBER_PATIENTS/3;
		number_patients = country_getPatientsPerVaccineTechnology(spain,ADENOVIRUSES);

		if (expected_number_patients!=number_patients){
			failed = true;
		}
		
	}
	else {
		failed = true;
	}
    
    if(failed) {
        end_test(test_section, "PR2_EX3_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_3", true);
    }
	
	// Remove used data	
	
    country_free(&spain);   
    country_free(&foo_country);   

	for(int i=0;i<NUMBER_VACCINES;i++){
		vaccine_free(&vaccines[i]);
	}
	
	vaccine_free(&foo_vaccine);
	
	
	for(int i=0;i<NUMBER_PATIENTS;i++){
		patient_free(&patients[i]);
		patient_free(&foo_patients[i]);

	}
	
	patientQueue_free(&patiens_list1);
	patientQueue_free(&patiens_list2);


    return passed;
}
