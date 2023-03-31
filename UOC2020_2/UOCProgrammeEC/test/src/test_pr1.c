#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "country.h"
#include "test_pr1.h"
#include "country.h"
#include "vaccine.h"
#include "developer.h"

// Run all tests for PR1
bool run_pr1(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR1", "Tests for PR1 exercices");

    section = testSuite_getSection(test_suite, "PR1");
    assert(section != NULL);

    ok = run_pr1_ex1(section) && ok;
    ok = run_pr1_ex2(section) && ok;
    ok = run_pr1_ex3(section) && ok;

    return ok;
}

// Run all tests for PR1
bool run_pr1_ex1(tTestSection* test_section) {
    bool passed = true, failed = false;

    tError err;
    tCountryTable countries;
    tCountry country1, country2, country3, country4;
    tCountry* countryAux;

    // TEST 1: Initialize the table of countries
    failed = false;
    start_test(test_section, "PR1_EX1_1", "Initialize the table of countries");
    countryTable_init(&countries);

    if(countryTable_size(&countries) != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX1_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_1", true);
    }

    // TEST 2: Initialize a country
    failed = false;
    start_test(test_section, "PR1_EX1_2", "Initialize a country");

    err = country_init(&country1, "Spain", true);

    if(err != OK){
        failed = true;
	}
	else if (!patientQueue_empty(*country1.patients)){
		failed = true;
	}

    err = country_init(&country2, "United Kingdom", false);

    if(err != OK)
        failed = true;

    if(country_equals(&country1, &country2)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX1_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_2", true);
    }

    // TEST 3: Add a new country
    failed = false;
    start_test(test_section, "PR1_EX1_3", "Add a new country");

    err = countryTable_add(&countries, &country1);
    if(err != OK) {
        failed = true;
    }
    if(countryTable_size(&countries) != 1) {
        failed = true;
    }
    countryAux = countryTable_find(&countries, "Spain");
    if(countryAux == NULL) {
        failed = true;
    } else
        if(!country_equals(countryAux, &country1)) {
            failed = true;
        }

    if(failed) {
        end_test(test_section, "PR1_EX1_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_3", true);
    }

    // TEST 4: Add more countries
    failed = false;
    start_test(test_section, "PR1_EX1_4", "Add more countries");

    country_init(&country3, "Germany", true);

    country_init(&country4, "China", false);

    err = countryTable_add(&countries, &country3);
    if(err != OK) {
        failed = true;
    }

    if(countryTable_size(&countries) != 2) {
        failed = true;
    }

    countryAux = countryTable_find(&countries, "Germany");
    if(countryAux == NULL) {
        failed = true;
    }
    if(!country_equals(countryAux, &country3)) {
        failed = true;
    }
    err = countryTable_add(&countries, &country4);
    if(err != OK) {
        failed = true;
    }

    if(countryTable_size(&countries) != 3) {
        failed = true;
    }

    countryAux = countryTable_find(&countries, "China");
    if(countryAux == NULL) {
        failed = true;
    } else
        if(!country_equals(countryAux, &country4)) {
            failed = true;
        }

    if(failed) {
        end_test(test_section, "PR1_EX1_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_4", true);
    }

    // TEST 5: Remove a country
    failed = false;
    start_test(test_section, "PR1_EX1_5", "Remove a country");

    countryAux = countryTable_find(&countries, "Germany");
    if(countryAux == NULL) {
        failed = true;
    }

    err = countryTable_remove(&countries, &country3);
    if(err != OK) {
        failed = true;
    }

    if(countryTable_size(&countries) != 2) {
        failed = true;
    }

    countryAux = countryTable_find(&countries, "Germany");
    if(countryAux != NULL) {
        failed = true;
    }

    countryAux = countryTable_find(&countries, "China");
    if(countryAux == NULL) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX1_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_5", true);
    }

    // TEST 6: Remove a non existing country
    failed = false;
    start_test(test_section, "PR1_EX1_6", "Remove a non existing country");

    err = countryTable_remove(&countries, &country3);
    if(err != ERR_NOT_FOUND) {
        failed = true;
    }

    if(countryTable_size(&countries) != 2) {
        failed = true;
    }

    countryAux = countryTable_find(&countries, "Germany");
    if(countryAux != NULL) {
        failed = true;
    }

    countryAux = countryTable_find(&countries, "Spain");
    if(countryAux == NULL) {
        failed = true;
    }

    countryAux = countryTable_find(&countries, "China");
    if(countryAux == NULL) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX1_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_6", true);
    }


    // Remove used memory
    country_free(&country1);
    country_free(&country2);
    country_free(&country3);
    country_free(&country4);

    countryTable_free(&countries);
    return passed;
}

// Run tests for PR1 exercise 2
bool run_pr1_ex2(tTestSection* test_section) {
    bool passed = true, failed = false;

    tError err;
    tCountry country1, country2;
    tVaccine vac1, vac2;

    // PRE TEST: Create countries
    country_init(&country1, "Germany", true);
    country_init(&country2, "Spain", false);

    // TEST 1: Initialize a vaccine
    failed = false;
    start_test(test_section, "PR1_EX2_1", "Initialize a vaccine");

    err = vaccine_init(&vac1, "BNT162b2", RNA, PHASE3);
    if(err != OK) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX2_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_1", true);
    }

    // TEST 2: Adding an authorized vaccine  to a country
    failed = false;
    start_test(test_section, "PR1_EX2_2", "Adding an authorized vaccine to a country");

    err = vaccine_init(&vac2, "mRNA-1273", RNA, PHASE3);
    if(err != OK) {
        failed = true;
    }

    err = country_addVaccine(&country1,vac2);
    if(err != OK) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX2_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_2", true);
    }

    // TEST 3: Compare two vaccines
    failed = false;
    start_test(test_section, "PR1_EX2_3", "Compare two vaccines");

    if(!vaccine_equals(&vac1, &vac1)) {
        failed = true;
    }

    if(vaccine_equals(&vac2, &vac1)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX2_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_3", true);
    }

    // TEST 4: Copy a vaccine
    failed = false;
    start_test(test_section, "PR1_EX2_4", "Copy a vaccine");

    err = vaccine_cpy(&vac1, &vac2);
    if(err != OK) {
        failed = true;
    }

    if(!vaccine_equals(&vac1, &vac2)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX2_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_4", true);
    }

    // Remove used memory
    country_free(&country1);
    country_free(&country2);

    vaccine_free(&vac1);
    vaccine_free(&vac2);

    return passed;
}

// Run tests for PR1 exercise 3
bool run_pr1_ex3(tTestSection* test_section) {
    bool passed = true, failed = false;

    tError err;
    tCountry country1, country2, country3;
    tVaccine vac1, vac2, vac3, vac4;
    tDeveloper dev1, dev2, dev3, dev4, dev5, dev6, dev7;
    tDeveloperTable dev_tab, dev_tab2;

    // PRE TEST: Create countries
    country_init(&country1, "Spain", true);
    country_init(&country2, "United Kingdom", false);
    country_init(&country3, "EEUU", false);

    // PRE TEST: Create vaccines
    vaccine_init(&vac1, "BNT162b2", RNA, PHASE3); //Pfizer
    vaccine_init(&vac2, "mRNA-1273", RNA, PHASE3); //Moderna
    vaccine_init(&vac3, "AZD1222", ADENOVIRUSES, PHASE3); //AstraZeneca
    vaccine_init(&vac4, "XYZ", SARSCOV2, PHASE1_2); //fake

    country_addVaccine(&country1,vac1);
    country_addVaccine(&country3,vac1 );

    country_addVaccine(&country1,vac2);
    country_addVaccine(&country2,vac2);
    country_addVaccine(&country3,vac2);

    country_addVaccine(&country1,vac3);

    // TEST 1: Initialize developers
    failed = false;
    start_test(test_section, "PR1_EX3_1", "Initialize developers");

    err = developer_init(&dev1, "Pfizer", "EEUU", &vac1);
    if (err != OK || strcmp(dev1.name, "Pfizer") != 0) {
        failed = true;
    }

    err = developer_init(&dev2, "Moderna", "EEUU", &vac2);
    if (err != OK || strcmp(dev2.name, "Moderna") != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX3_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_1", true);
    }

    // TEST 2: Copy a developer
    failed = false;
    start_test(test_section, "PR1_EX3_2", "Copy a developer");
    err = developer_cpy(&dev2, &dev1);
    if (err != OK || strcmp(dev1.name, dev2.name) != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX3_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_2", true);
    }

    // TEST 3: Compare different developers
    failed = false;
    start_test(test_section, "PR1_EX3_3", "Compare different developers");

    err = developer_init(&dev3, "AstraZeneca", "United Kingdom", &vac3);
    if(err != OK) {
        failed = true;
    }

    if(developer_equals(&dev1, &dev3)) {
        failed = true;
    }
    if(developer_equals(&dev3, &dev1)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX3_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_3", true);
    }

    // TEST 4: Compare equal developers
    failed = false;
    start_test(test_section, "PR1_EX3_4", "Compare equal developers");

    if(!developer_equals(&dev1, &dev2)) {
        failed = true;
    }
    if(!developer_equals(&dev2, &dev1)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX3_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_4", true);
    }

    // TEST 5: Initialize the table of developers
    failed = false;
    start_test(test_section, "PR1_EX3_5", "Initialize the table of developers");

    developerTable_init(&dev_tab);

    if(developerTable_size(&dev_tab) != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX3_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_5", true);
    }

    // TEST 6: Add developers to the developers table
    failed = false;
    start_test(test_section, "PR1_EX3_6", "Add developers to the developers table");

    // add dev1
    err = developerTable_add(&dev_tab, &dev1);
    if(err != OK) {
        failed = true;
    }

    if(developerTable_size(&dev_tab) != 1) {
        failed = true;
    }
    if(developerTable_find(&dev_tab, &dev1) != 0) {
        failed = true;
    }

    // add dev3
    err = developerTable_add(&dev_tab, &dev3);
    if(err != OK) {
        failed = true;
    }
    if(developerTable_size(&dev_tab) != 2) {
        failed = true;
    }
    if(developerTable_find(&dev_tab, &dev3) != 1) {
        failed = true;
    }

    // add repeated developer
    err = developerTable_add(&dev_tab, &dev2);
    if(err != ERR_DUPLICATED) {
        failed = true;
    }
    if(developerTable_size(&dev_tab) != 2) {
        failed = true;
    }
    if(developerTable_find(&dev_tab, &dev2) != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX3_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_6", true);
    }

    // TEST 7: Remove a developer
    failed = false;
    start_test(test_section, "PR1_EX3_7", "Remove a developer");

    err = developerTable_remove(&dev_tab, &dev3);
    if(err != OK) {
        failed = true;
    }

    if(developerTable_size(&dev_tab) != 1) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX3_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_7", true);
    }

    // PRETEST: Create a table with 4 developers (3 authorized, 1 non-authorized)
    developer_init(&dev4, "Pfizer", "EEUU" ,&vac1);
    developer_init(&dev5, "Moderna", "EEUU", &vac2);
    developer_init(&dev6, "AstraZeneca", "United Kingdom", &vac3);
    developer_init(&dev7, "FakeLab", "Spain", &vac4);
    developerTable_init(&dev_tab2);
    developerTable_add(&dev_tab2, &dev4);
    developerTable_add(&dev_tab2, &dev5);
    developerTable_add(&dev_tab2, &dev6);
    developerTable_add(&dev_tab2, &dev7);

    
 

    // Remove used memory
    country_free(&country1);
    country_free(&country2);
    country_free(&country3);

    vaccine_free(&vac1);
    vaccine_free(&vac2);
    vaccine_free(&vac3);
    vaccine_free(&vac4);

    developer_free(&dev1);
    developer_free(&dev2);
    developer_free(&dev3);
    developer_free(&dev4);
    developer_free(&dev5);
    developer_free(&dev6);
    developer_free(&dev7);

    developerTable_free(&dev_tab);
    developerTable_free(&dev_tab2);

    return passed;
}
