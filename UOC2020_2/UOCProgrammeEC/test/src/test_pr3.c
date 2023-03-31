#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "country.h"
#include "test_pr3.h"
#include "country.h"
#include "vaccine.h"
#include "developer.h"
#include "patient.h"
#include "vaccinationBatch.h"

#define NUMBER_PATIENTS 5000
#define MAX_NUMBER_DOSES 100
#define NUMBER_BATCHS 20


// Run all tests for PR3
bool run_pr3(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR3", "Tests for PR3 exercices");

    section = testSuite_getSection(test_suite, "PR3");
    assert(section != NULL);

    ok = run_pr3_ex1(section) && ok;
    ok = run_pr3_ex2(section) && ok;
    ok = run_pr3_ex3(section) && ok;

    return ok;
}

// Run all tests for PR3
bool run_pr3_ex1(tTestSection* test_section) {
    bool passed = true, failed = false;
    tError err;
    tVaccinationBatchList vaccineBatchList, empty_vaccinationBatch;
    tVaccine pfizer_vaccine, moderna_vaccine, oxford_vaccine, janssen_vaccine;
    tVaccineBatch oxford_batch, pfizer_batch, moderna_batch, janssen_batch, copyBatch;
    bool list_created = false;

    vaccine_init(&pfizer_vaccine, PFIZER_VAC, RNA, PHASE3); //Pfizer
    vaccine_init(&moderna_vaccine, MODERNA_VAC, RNA, PHASE3); //Moderna
    vaccine_init(&oxford_vaccine, ASTRAZENECA_VAC, ADENOVIRUSES, PHASE3); //Oxford
    vaccine_init(&janssen_vaccine, JANSSEN_VAC, ADENOVIRUSES, PHASE3); //Janssen

    // TEST 1: Initialize a vaccinationBatch List
    failed = false;
    start_test(test_section, "PR3_EX1_1", "Initialize a vaccinationBatch List");

    err = vaccinationBatchList_create(&vaccineBatchList);

    if(err != OK) {
        failed = true;
    } else {
        if(vaccineBatchList.first != NULL || vaccineBatchList.size != 0) {
            failed = true;
        } else {
            list_created = true;
        }
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_1", true);
    }

    // TEST 2: Initialize a vaccination batches
    failed = false;
    start_test(test_section, "PR3_EX1_2", "Initialize vaccination batches");

    err = vaccinationBatch_init(&pfizer_batch, 1234, &pfizer_vaccine, 10);
    if(err != OK) {
        failed = true;
    }

    err = vaccinationBatch_init(&moderna_batch, 234, &moderna_vaccine, 10);
    if(err != OK) {
        failed = true;
    }

    err = vaccinationBatch_init(&oxford_batch, 20, &oxford_vaccine, 100);
    if(err != OK) {
        failed = true;

    }

    err = vaccinationBatch_init(&janssen_batch, 20, &janssen_vaccine, 50);
    if(err != OK)
        failed = true;

    if(failed) {
        end_test(test_section, "PR3_EX1_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_2", true);
    }


    // TEST 3: vaccineBatch operations
    failed = false;

    start_test(test_section, "PR3_EX1_3", "vaccineBatch operations");

    if(vaccinationBatch_equals(pfizer_batch, moderna_batch)) {
        failed = true;
    }

    if(!vaccinationBatch_equals(pfizer_batch, pfizer_batch)) {
        failed = true;
    }

    copyBatch.vaccine =  NULL;
    copyBatch.lotID = 0;
    copyBatch.quantity = 0;

    err = vaccinationBatch_cpy(&copyBatch, &pfizer_batch);

    if(err != OK) {
        failed = true;
    }

    if(!vaccinationBatch_equals(copyBatch, pfizer_batch)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_3", true);
    }

    // TEST 4: Insert a new bath in the vaccineBatch List

    failed = false;
    start_test(test_section, "PR3_EX1_4", "Insert a new bath in the vaccineBatch List");

    if(list_created) {

        err = vaccineBatchList_insert(&vaccineBatchList, pfizer_batch, 0);
        if(err != OK) {
            failed = true;
        }

        if(vaccineBatchList.size != 1) {
            failed = true;
        }

        err = vaccineBatchList_insert(&vaccineBatchList, pfizer_batch, 10);
        if(err != ERR_INVALID_INDEX) {
            failed = true;
        }
    } else {
        failed = true;
    }


    if(failed) {
        end_test(test_section, "PR3_EX1_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_4", true);
    }


    // TEST 5: Test vaccinationBatchList_empty
    failed = false;
    start_test(test_section, "PR3_EX1_5", "Test vaccinationBatchList_empty");

    vaccinationBatchList_create(&empty_vaccinationBatch);

    if(vaccinationBatchList_empty(vaccineBatchList)) {
        failed = true;
    }

    if(!vaccinationBatchList_empty(empty_vaccinationBatch)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_5", true);
    }

    // TEST 6: Insert more batches into the vaccineBatch List

    failed = false;
    start_test(test_section, "PR3_EX1_6", "Insert more batches into the vaccineBatch List");

    if(list_created) {

        // insert at the begining
        err = vaccineBatchList_insert(&vaccineBatchList, moderna_batch, 0);
        if(err != OK) {
            failed = true;
        } else {
            if(vaccineBatchList.size != 2) {
                failed = true;
            }

            if(!vaccinationBatch_equals(moderna_batch, vaccineBatchList_get(vaccineBatchList, 0)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(pfizer_batch, vaccineBatchList_get(vaccineBatchList, 1)->e)) {
                failed = true;
            }
        }

        // insert at the end
        err = vaccineBatchList_insert(&vaccineBatchList, oxford_batch, 1);
        if(err != OK) {
            failed = true;
        } else {
            if(vaccineBatchList.size != 3) {
                failed = true;
            }

            if(!vaccinationBatch_equals(moderna_batch, vaccineBatchList_get(vaccineBatchList, 0)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(pfizer_batch, vaccineBatchList_get(vaccineBatchList, 2)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(oxford_batch, vaccineBatchList_get(vaccineBatchList, 1)->e)) {
                failed = true;
            }
        }

        // insert at the middle
        err = vaccineBatchList_insert(&vaccineBatchList, janssen_batch, 2);
        if(err != OK) {
            failed = true;
        } else {

            if(vaccineBatchList.size != 4) {
                failed = true;
            }

            if(!vaccinationBatch_equals(moderna_batch, vaccineBatchList_get(vaccineBatchList, 0)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(pfizer_batch, vaccineBatchList_get(vaccineBatchList, 3)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(oxford_batch, vaccineBatchList_get(vaccineBatchList, 1)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(janssen_batch, vaccineBatchList_get(vaccineBatchList, 2)->e)) {
                failed = true;
            }
        }
    } else {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_6", true);
    }

    // TEST 7: Delete a bath from the vaccineBatch List

    failed = false;
    start_test(test_section, "PR3_EX1_7", "Delete a bath from the vaccineBatch List");

    if(list_created) {

        // delete in the middle
        err = vaccineBatchList_delete(&vaccineBatchList, 1);
        if(err != OK) {
            failed = true;
        } else {
            if(vaccineBatchList.size != 3) {
                failed = true;
            }

            if(!vaccinationBatch_equals(moderna_batch, vaccineBatchList_get(vaccineBatchList, 0)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(pfizer_batch, vaccineBatchList_get(vaccineBatchList, 2)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(janssen_batch, vaccineBatchList_get(vaccineBatchList, 1)->e)) {

                failed = true;
            }
        }

        // in the end
        err = vaccineBatchList_delete(&vaccineBatchList, 2);
        if(err != OK) {
            failed = true;
        } else {
            if(vaccineBatchList.size != 2) {
                failed = true;
            }

            if(!vaccinationBatch_equals(moderna_batch, vaccineBatchList_get(vaccineBatchList, 0)->e)) {
                failed = true;
            }

            if(!vaccinationBatch_equals(janssen_batch, vaccineBatchList_get(vaccineBatchList, 1)->e)) {
                failed = true;
            }
        }

        // in the beggining
        err = vaccineBatchList_delete(&vaccineBatchList, 0);
        if(err != OK) {
            failed = true;
        } else {
            if(vaccineBatchList.size != 1) {
                failed = true;
            }

            if(!vaccinationBatch_equals(janssen_batch, vaccineBatchList_get(vaccineBatchList, 0)->e)) {
                failed = true;
            }
        }

        err = vaccineBatchList_delete(&vaccineBatchList, 0);
        if(err != OK) {
            failed = true;
        } else {
            if(vaccineBatchList.size != 0) {
                failed = true;
            }
            if(!vaccinationBatchList_empty(vaccineBatchList)) {
                failed = true;
            }

        }


        err = vaccineBatchList_delete(&vaccineBatchList, 0);
        if(err != ERR_EMPTY_LIST) {
            failed = true;
        }
    } else {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_7", true);
    }

    vaccinationBatchList_free(&vaccineBatchList);

    vaccinationBatch_free(&pfizer_batch);
    vaccinationBatch_free(&moderna_batch);
    vaccinationBatch_free(&oxford_batch);
    vaccinationBatch_free(&janssen_batch);
    vaccinationBatch_free(&copyBatch);

    vaccine_free(&pfizer_vaccine);
    vaccine_free(&moderna_vaccine);
    vaccine_free(&oxford_vaccine);
    vaccine_free(&janssen_vaccine);

    return passed;
}

// Run tests for PR3 exercise 2
bool run_pr3_ex2(tTestSection* test_section) {
    bool passed, failed;
    tError err;
    tCountry spain, germany, france;
    tPatient garcia, gonzalez, rodriguez;
    tVaccine pfizer_vaccine, moderna_vaccine, oxford_vaccine, janssen_vaccine;
    tVaccineBatch oxford_batch, pfizer_batch, moderna_batch, janssen_batch;

    passed = true;

    // PRE TEST
    country_init(&spain, "Spain", true);
    country_init(&germany, "Germany", true);
    country_init(&france, "France", true);

    vaccine_init(&pfizer_vaccine, PFIZER_VAC, RNA, PHASE3); //Pfizer
    vaccine_init(&moderna_vaccine, MODERNA_VAC, RNA, PHASE3); //Moderna
    vaccine_init(&oxford_vaccine, ASTRAZENECA_VAC, ADENOVIRUSES, PHASE3); //Oxford
    vaccine_init(&janssen_vaccine, JANSSEN_VAC, ADENOVIRUSES, PHASE3); //Janssen

    country_addVaccine(&spain, pfizer_vaccine);
    country_addVaccine(&spain, moderna_vaccine);
    country_addVaccine(&spain, oxford_vaccine);
    country_addVaccine(&spain, janssen_vaccine);

    patient_init(&garcia, "Mrs. Garcia", 1, NULL, 0, 0, ANYONE_ELSE);
    patient_init(&gonzalez, "Mr. Gonzalez", 2, NULL, 0, 0, ANYONE_ELSE);
    patient_init(&rodriguez, "Mrs. Rodriguez", 3, NULL, 0, 0, ANYONE_ELSE);

    // TEST 1: Inoculate first dose to a country without batches and patients
    failed = false;
    start_test(test_section, "PR3_EX2_1", "Inoculate first dose to a country without batches and patients");

    country_inoculate_first_vaccine(&spain);

    if(spain.patients == NULL || spain.vbList == NULL) {
        failed = true;
    } else {
        if(spain.patients->first != NULL) failed = true;
        if(spain.vbList->first != NULL) failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX2_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_1", true);
    }

    // TEST 2: Inoculate first dose to a country without batches
    failed = false;
    start_test(test_section, "PR3_EX2_2", "Inoculate first dose to a country without batches");

    country_addPatient(&spain, garcia);
    country_addPatient(&spain, gonzalez);
    country_addPatient(&spain, rodriguez);

    country_inoculate_first_vaccine(&spain);

    if(spain.patients == NULL || spain.vbList == NULL) {
        failed = true;
    } else {
        if(patientQueue_empty(*spain.patients)) failed = true;
        if(spain.vbList->first != NULL) failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX2_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_2", true);
    }

    // TEST 3: Inoculate first dose to a country without patients
    failed = false;
    start_test(test_section, "PR3_EX2_3", "Inoculate first dose to a country without patients");

    vaccinationBatch_init(&pfizer_batch, 1234, &pfizer_vaccine, 1);
    vaccinationBatch_init(&moderna_batch, 234, &moderna_vaccine, 1);
    vaccinationBatch_init(&oxford_batch, 20, &oxford_vaccine, 1);

    err = vaccinationBatchList_create(france.vbList);
    if(err != OK) {
        failed = true;
        france.vbList = NULL;
    } else {
        vaccineBatchList_insert(france.vbList, oxford_batch, 0);
        vaccineBatchList_insert(france.vbList, moderna_batch, 1);
        vaccineBatchList_insert(france.vbList, pfizer_batch, 2);

        err = country_inoculate_first_vaccine(&france);
        if (err == OK) {
            if(france.patients == NULL || france.vbList == NULL || france.vbList->first == NULL) {
                failed = true;
            } else {
                if(!patientQueue_empty(*france.patients)) failed = true;
                if(france.vbList->first->e.lotID != 20) failed = true;
            }
        } else {
            failed = true;
        }
    }
    if(failed) {
        end_test(test_section, "PR3_EX2_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_3", true);
    }

    // TEST 4: Inoculate first dose to a country
    failed = false;
    start_test(test_section, "PR3_EX2_4", "Inoculate first dose to a country");

    country_addPatient(&france, garcia);
    country_addPatient(&france, gonzalez);
    country_addPatient(&france, rodriguez);
    
    err = country_inoculate_first_vaccine(&france);
    if (err == OK) {
        if(france.patients == NULL || patientQueue_empty(*france.patients) || france.vbList == NULL || france.vbList->first == NULL) {
            failed = true;
        } else {
            if(france.vbList->first->e.lotID != 20) failed = true;
            if(france.vbList->first->e.quantity != 0) failed = true;
            if(france.vbList->first->next->e.quantity != 0) failed = true;
            if(france.vbList->first->next->next->e.quantity != 0) failed = true;
            if(strcmp(france.patients->first->e.vaccine, ASTRAZENECA_VAC) != 0) failed = true;
            if(strcmp(france.patients->first->next->e.vaccine, MODERNA_VAC) != 0) failed = true;
            if(strcmp(france.patients->first->next->next->e.vaccine, PFIZER_VAC) != 0) failed = true;
        }
    } else {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX2_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_4", true);
    }

    // TEST 5: Inoculate first dose to a country with already one dose
    failed = false;
    start_test(test_section, "PR3_EX2_5", "Inoculate first dose to a country with already one dose");

    vaccineBatchList_insert(france.vbList, pfizer_batch, 0);
    err = country_inoculate_first_vaccine(&france);
    if (err == OK) {
        if(france.vbList == NULL || france.vbList->first == NULL) {
            failed = true;
        } else {
            if(vaccineBatchList_get(*france.vbList, 0)->e.lotID != 1234) failed = true;
            if(vaccineBatchList_get(*france.vbList, 0)->e.quantity != 1) failed = true;
        }
    } else {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX2_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_5", true);
    }

    // TEST 6: Inoculate second dose to a country
    failed = false;
    start_test(test_section, "PR3_EX2_6", "Inoculate second dose to a country");

    err = country_inoculate_second_vaccine(&france);
    if (err == OK) {
        if(france.patients == NULL || france.vbList == NULL || france.vbList->first == NULL) {
            failed = true;
        } else {
            if(france.vbList->first->e.lotID != 1234) failed = true;
            if(france.vbList->first->e.quantity != 0) failed = true;
            if(france.patients->first->next->next->e.number_doses != 2) failed = true;
        }
    } else {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX2_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_6", true);
    }

    // TEST 7: Inoculate second dose to a Jassen country
    failed = false;
    start_test(test_section, "PR3_EX2_7", "Inoculate second dose to a Jassen country");

    country_addPatient(&germany, garcia);
    country_addPatient(&germany, gonzalez);
    country_addPatient(&germany, rodriguez);

    vaccinationBatch_init(&janssen_batch, 2454, &janssen_vaccine, 10);

    err = vaccinationBatchList_create(germany.vbList);
    if(err != OK) {
        failed = true;
        germany.vbList = NULL;
    } else {
        vaccineBatchList_insert(germany.vbList, janssen_batch, 0);

        err = country_inoculate_first_vaccine(&germany);
        if(err == OK) {
            err = country_inoculate_second_vaccine(&germany);
            if(err != OK) {
                failed = true;
            }
        }
        else {
            failed = true;
        }
    }
    if(germany.patients == NULL || germany.vbList == NULL || germany.vbList->first == NULL) {
        failed = true;
    } else {
        if(germany.vbList->first->e.lotID != 2454) failed = true;
        if(germany.vbList->first->e.quantity != 7) failed = true;
        if(germany.patients->first->next->next->e.number_doses != 1) failed = true;
        if(germany.patients->first->next->e.number_doses != 1) failed = true;
        if(germany.patients->first->e.number_doses != 1) failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX2_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_7", true);
    }

    // TEST 8: Percentage of vaccinated country
    failed = false;
    start_test(test_section, "PR3_EX2_8", "Percentage of vaccinated country");

    if(germany.patients == NULL || germany.vbList == NULL ||
            france.patients == NULL || france.vbList == NULL ||
            spain.patients == NULL || spain.vbList == NULL) {
        failed = true;
    } else {
        if(country_percentage_vaccinated(&spain) != 0.0) failed = true;
        if(trunc(country_percentage_vaccinated(&france) * 1000.) != trunc((1.0 / 3.0 * 100.0) * 1000.)) failed = true;

        if(country_percentage_vaccinated(&germany) != 100.0) failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX2_8", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_8", true);
    }

    // Free used memory
    country_free(&spain);
    country_free(&germany);
    country_free(&france);

    patient_free(&garcia);
    patient_free(&rodriguez);
    patient_free(&gonzalez);

    vaccine_free(&pfizer_vaccine);
    vaccine_free(&moderna_vaccine);
    vaccine_free(&oxford_vaccine);
    vaccine_free(&janssen_vaccine);
    vaccinationBatch_free(&pfizer_batch);
    vaccinationBatch_free(&moderna_batch);
    vaccinationBatch_free(&oxford_batch);
    vaccinationBatch_free(&janssen_batch);

    return passed;
}

// Run tests for PR3 exercise 3
bool run_pr3_ex3(tTestSection* test_section) {
    bool passed = true, failed = false;
    tError err;
    tCountry spain, dummy_country;
    tVaccine oxford_vaccine, pfizer_vaccine, dummy_vaccine;
    tVaccineBatch oxford_batchs[NUMBER_BATCHS], pfizer_batchs[NUMBER_BATCHS];
    tVaccinationBatchList vaccineBatchList;
    tPatient patients [NUMBER_PATIENTS];
    char name[13];
    tPatientQueue patiens_list1, patiens_list2, empty_patien_list ;
    int number_doses, numberPatients, patientGroup;
    int lastIdPfizer, lastIdOxford;

    patientQueue_create(&patiens_list1);
    patientQueue_create(&patiens_list2);
    patientQueue_create(&empty_patien_list);

    country_init(&spain, "Spain", true);
    country_init(&dummy_country, "Dummy", true);

    vaccine_init(&oxford_vaccine, ASTRAZENECA_VAC, ADENOVIRUSES, PHASE3); //Oxford
    vaccine_init(&pfizer_vaccine, PFIZER_VAC, RNA, PHASE3); //Pfizer
    vaccine_init(&dummy_vaccine, "Dummy Vaccine", NONE, PRECLINICAL);

    country_addVaccine(&spain, oxford_vaccine);

    srand(time(0));
    number_doses = rand() % ((10 + 1) - MAX_NUMBER_DOSES) + MAX_NUMBER_DOSES;
    for(int i = 0; i < NUMBER_BATCHS; i++) {
        lastIdPfizer = (i + 1) * 100;
        lastIdOxford = i + 1000 ;
        vaccinationBatch_init(&oxford_batchs[i], lastIdOxford, &oxford_vaccine, number_doses);
        vaccineBatchList_insert(spain.vbList, oxford_batchs[i], 0);
        vaccinationBatch_init(&pfizer_batchs[i], lastIdPfizer, &pfizer_vaccine, number_doses);
        vaccineBatchList_insert(spain.vbList, pfizer_batchs[i], 0);
    }

    srand(time(0));
    for(int i = 0; i < NUMBER_PATIENTS; i++) {
        patientGroup = rand() % ((ANYONE_ELSE + 1) - HEALTH_WORKER) + HEALTH_WORKER;
        snprintf(name, 13, "%s_%04d", "Patient", i + 1);
        patient_init(&patients[i], name, i + 1, NULL, 0, 0, patientGroup);
        country_addPatient(&spain, patients[i]);
        country_addPatient(&dummy_country, patients[i]);
    }

    country_inoculate_first_vaccine(&spain);
    country_inoculate_second_vaccine(&spain);

    // TEST 1: number of patients vacunated with wrongs country, vaccine or batch
    failed = false;
    start_test(test_section, "PR3_EX3_1", "Test patientQueue_countPatients_vaccinationBatch with wrong data");

    numberPatients = patientQueue_countPatients_vaccinationBatch(*dummy_country.patients, ASTRAZENECA_VAC, lastIdOxford);
    if(numberPatients != 0) failed = true;

    numberPatients = patientQueue_countPatients_vaccinationBatch(*spain.patients, "Dummy Vaccine", lastIdOxford);
    if(numberPatients != 0) failed = true;

    numberPatients = patientQueue_countPatients_vaccinationBatch(*spain.patients, ASTRAZENECA_VAC, 123456);
    if(numberPatients != 0) failed = true;

    numberPatients = patientQueue_countPatients_vaccinationBatch(*spain.patients, "Dummy Vaccine", lastIdOxford);
    if(numberPatients != 0) failed = true;

    if(failed) {
        end_test(test_section, "PR3_EX3_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_1", true);
    }

    // TEST 2: number of patients vacunated with a vaccine batch
    failed = false;
    start_test(test_section, "PR3_EX3_2", "Number of patients vacunated with a vaccine batch");


    numberPatients = patientQueue_countPatients_vaccinationBatch(*spain.patients, ASTRAZENECA_VAC, lastIdOxford);
    if(numberPatients != number_doses) failed = true;

    numberPatients = patientQueue_countPatients_vaccinationBatch(*spain.patients, PFIZER_VAC, lastIdPfizer);
    if(numberPatients != number_doses) failed = true;

    numberPatients = patientQueue_countPatients_vaccinationBatch(*spain.patients, PFIZER_VAC, 5);
    if(numberPatients != 0) failed = true;

    if(failed) {
        end_test(test_section, "PR3_EX3_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_2", true);
    }

    // TEST 3: Order a vaccinationBatch List with quicksort
    failed = false;
    start_test(test_section, "PR3_EX3_3", "Order a vaccinationBatch List with quicksort");

    err = vaccinationBatchList_create(&vaccineBatchList);
    if(err != OK) {
        failed = true;
    } else {
        for(int i = 0; i < NUMBER_BATCHS; i++) {
            vaccinationBatch_free(&oxford_batchs[i]);
        }

        srand(time(0));
        for(int i = 0; i < NUMBER_BATCHS; i++) {
            int batchId = rand() % ((1 + 1) - 100) + 100;
            vaccinationBatch_init(&oxford_batchs[i], batchId, &oxford_vaccine, 100);
            vaccineBatchList_insert(&vaccineBatchList, oxford_batchs[i], 0);
        }

        // shuffle vaccine batchs
        for(int i = 0; i < NUMBER_BATCHS - 1; i++) {
            int j = i + rand() / (RAND_MAX / (NUMBER_BATCHS - i) + 1);
            vaccineBatchList_swap(&vaccineBatchList, i, j);
        }

        vaccineBatchList_quicksort(&vaccineBatchList);

        int lastLotID = 0;
        int lotId = 0;
        for(int i = 0; i < NUMBER_BATCHS - 1; i++) {
            lotId = vaccineBatchList_get(vaccineBatchList, i)->e.lotID;
            if(lastLotID > lotId) {
                failed = true;
            }
            lastLotID = lotId;
        }
    }

    if(failed) {
        end_test(test_section, "PR3_EX3_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_3", true);
    }

    // Remove used data

    country_free(&spain);
    country_free(&dummy_country);

    vaccine_free(&oxford_vaccine);
    vaccine_free(&pfizer_vaccine);
    vaccine_free(&dummy_vaccine);

    for(int i = 0; i < NUMBER_BATCHS; i++) {
        vaccinationBatch_free(&oxford_batchs[i]);
        vaccinationBatch_free(&pfizer_batchs[i]);

    }

    for(int i = 0; i < NUMBER_PATIENTS; i++) {
        patient_free(&patients[i]);

    }

    patientQueue_free(&patiens_list1);
    patientQueue_free(&patiens_list2);

    vaccinationBatchList_free(&vaccineBatchList);

    return passed;
}
