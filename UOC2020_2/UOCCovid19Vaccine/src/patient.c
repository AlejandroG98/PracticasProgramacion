#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "vaccine.h"
#include "patient.h"
#include "vaccinationBatch.h"


// Initialize a patient structure
tError patient_init(tPatient *patient, const char* patientName, int patientId, const char* vaccine, int lotID, int number_doses, tPatientGroup group) {
    // Check preconditions
    assert(patient != NULL);
    assert(patientName != NULL);
    assert(patientId > 0);

    // Allocate the memory for patient and vaccine name, using the length of the provided text plus 1 space for the "end of string" char '\0'. To allocate memory we use the malloc command.
    patient->name = (char*) malloc((strlen(patientName) + 1) * sizeof(char));
    // Check that memory has been allocated for all fields.
    // Pointer must be different from NULL.
    if(patient->name == NULL) {
        // Some of the fields have a NULL value, what means that we found
        // some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }
    // Once the memory is allocated, copy the data. As the fields are strings,
    // we need to use the string copy function strcpy.
    strcpy(patient->name, patientName);

    if(vaccine != NULL) {
        patient->vaccine = (char*) malloc((strlen(vaccine) + 1) * sizeof(char));
        if(patient->vaccine == NULL) {
            free(patient->name);
            return ERR_MEMORY_ERROR;
        }
        strcpy(patient->vaccine, vaccine);
		patient->lotID = lotID;
    } else {
        patient->vaccine = NULL;
		patient->lotID = 0;
    }

    patient->id = patientId;
    patient->number_doses = number_doses;
    patient->group = group;

    return OK;
}

// inoculate a vaccine to a patient
tError patient_inoculate_vaccine(tPatient* patient, const char* vaccine, int lotID) {
    // Verify pre conditions
    assert(patient != NULL);
    assert(vaccine != NULL);


    if((patient->vaccine != NULL) && (strcmp(patient->vaccine, vaccine) != 0)) {
        return ERR_INVALID_VACCINE;
    }

    if(patient->vaccine != NULL) {
        patient->number_doses++;
    } else {

        patient->vaccine = (char*) malloc((strlen(vaccine) + 1) * sizeof(char));
        if(patient->vaccine == NULL) {
            free(patient->name);
            patient->name = NULL;
            return ERR_MEMORY_ERROR;
        }
        strcpy(patient->vaccine, vaccine);
        patient->number_doses = 1;
		patient->lotID = lotID;
    }
	
    return OK;
}

// Release memory used by patient
void patient_free(tPatient* patient){
	if (patient == NULL)
		return;
    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them
    if(patient->name != NULL) {
        free(patient->name);
        patient->name = NULL;
    }
	
	if(patient->vaccine != NULL) {
        free(patient->vaccine);
        patient->vaccine = NULL;
    }
	
	patient->id = 0;
}


// Compare two patients
bool patient_compare(tPatient p1, tPatient p2) {
    // Compare the values of both structures
    return (strcmp(p1.name, p2.name) == 0  && p1.id == p2.id);
}

// Duplicate a patient
tError patient_duplicate(tPatient *dst, tPatient src) {
    // Check preconditions
    assert(dst != NULL);

    // Copy the values of both structures
    return patient_init(dst, src.name, src.id, src.vaccine, src.lotID, src.number_doses, src.group);
}

// Returns true if the vaccine can be inoculated.
bool patient_isSuitableForVaccine(tPatient* patient, tVaccine* vaccine) {
    // PR3 EX2
	
	// Check PRE Conditions
	assert(patient != NULL);
    assert(vaccine != NULL);
	
	// Pass patient value to patient_isVaccinated function
	// If its true, its vaccinated, return false
	if(patient_isVaccinated(patient))
	{
		return false;
	}
	// ELSE IF patient doses is +0 and 
	// patient's vaccine is different to vaccine name, return false
	else if(patient->number_doses >0 && strcmp(patient->vaccine, vaccine->name) != 0)
	{
		return false;
	}
	// ELSE IF patient's group is: over 65 y.o or over 80 y.o and
	// the vaccine for inoculate is Astrazeneca, return false
	else if((patient->group == ADULT_OVER_65 || patient->group == ADULT_OVER_80) && strcmp(vaccine->name, ASTRAZENECA_VAC))
	{
		return false;
	}
	
	// Return true if the vaccine can be inocculated
	return true;
}

// Returns true if the patient has been fully vaccinated
bool patient_isVaccinated(tPatient* patient) {
    // With more than one dose anyone is vaccinated. 
    if(patient->number_doses > 1) 
        return true;
    
    // Check if it is a Janssen vaccine with one or more doses
    if(patient->vaccine != NULL && patient->number_doses > 0)
        if(strcmp(patient->vaccine, JANSSEN_VAC) == 0)
            return true;
            
    return false;
}

// Create the patient queue
tError patientQueue_create(tPatientQueue* queue) {
    // PR2 EX1
    // Check preconditions
    assert(queue != NULL);

    // Assign pointers to NULL
    queue->first = NULL;
    queue->last = NULL;
    return OK;
}

// Check if the queue is empty
bool patientQueue_empty(tPatientQueue queue) {
    // PR2 EX1
    return queue.first == NULL;
}

// Enqueue a new match to the match queue
tError patientQueue_enqueue(tPatientQueue* queue, tPatient patient) {
    // PR2 EX1

    tPatientQueueNode *tmp;

    // Check preconditions
    assert(queue != NULL);

    tmp = (tPatientQueueNode*) malloc(sizeof(tPatientQueueNode));
    if(tmp == NULL) {
        return ERR_MEMORY_ERROR;
    } else {
        if(patient_duplicate(&tmp->e, patient) != OK) {
            free(tmp);
            return ERR_MEMORY_ERROR;
        }
        tmp->next = NULL;
        if(queue->first == NULL) {
            // empty queue
            queue->first = tmp;
        } else {
            queue->last->next = tmp;
        }
        queue->last = tmp;
    }

    return OK;
}

// Make a copy of the queue
tError patientQueue_duplicate(tPatientQueue* dst, tPatientQueue src) {
    tPatientQueueNode *pNode;
    tError error;
    // Check preconditions
    assert(dst != NULL);

    // Initialize the new queue
    error = patientQueue_create(dst);

    if(error != OK) {
        return error;
    }
    // Assign pointer to first element
    pNode = src.first;
    while(pNode != NULL) {
        // Enqueue the current element to the output queue
        error = patientQueue_enqueue(dst, pNode->e);
        if(error != OK) {
            patientQueue_free(dst);
            return error;
        }
        // Move to next element
        pNode = pNode->next;
    }

    return OK;

}


// Remove all elements of the queue
void patientQueue_free(tPatientQueue* queue){
	// PR2 EX2	
    // Check preconditions
    assert(queue != NULL);
    tPatient * patient;
    // Remove all elements
    while(!patientQueue_empty(*queue)) {
        patient = patientQueue_dequeue(queue);
		patient_free(patient);
		free(patient);
    }
    
    // Check postconditions
    assert(queue->first == NULL);
    assert(queue->last == NULL);

	}


// Dequeue a patient from the presentation queue
tPatient* patientQueue_dequeue(tPatientQueue* queue) {

    tPatientQueueNode *node = NULL;
    tPatient *patient;

    if(patientQueue_empty(*queue)) {
        return NULL;
    }

    patient = (tPatient*)malloc(sizeof(tPatient));
    if(patient == NULL)
        return NULL;

    if(patient_duplicate(patient, queue->first->e) != OK) {
        free(patient);
        return NULL;
    }

    node = queue->first;
    queue->first = queue->first->next;


    patient_free(&(node->e));

    if(queue->first == NULL) {
        queue->last = NULL;
    }

    free(node);
    return patient;


}

// Return the first patient from the queue
tPatient* patientQueue_head(tPatientQueue queue) {

    if(patientQueue_empty(queue)) {
        return NULL;
    } else {
        return &queue.first->e;
    }

}

// create a copy of the queues before calling  patientQueue_compareRecursive
bool patientQueue_compare(tPatientQueue *queue1, tPatientQueue *queue2){
	bool equal = false;
	
	tPatientQueue  copy_queue1, copy_queue2;

	patientQueue_duplicate(&copy_queue1,*queue1);
	patientQueue_duplicate(&copy_queue2,*queue2);
	
	equal = patientQueue_compareRecursive(&copy_queue1, &copy_queue2);
	
	patientQueue_free(&copy_queue1);
	patientQueue_free(&copy_queue2);
	
	return equal;
	
}


// create a copy of the queues before calling  patientQueue_compareRecursive
bool patientQueue_compareIterative(tPatientQueue *queue1, tPatientQueue *queue2){
	
	tPatientQueue  copy_queue1, copy_queue2;
	tPatient* patient1, * patient2; 

 	if(patientQueue_empty(*queue1) && patientQueue_empty(*queue2) ) {
        return true;
    }
	
	patientQueue_duplicate(&copy_queue1,*queue1);
	patientQueue_duplicate(&copy_queue2,*queue2);
	
	while(!patientQueue_empty(copy_queue1)) {
		// Get the head
		patient1 = patientQueue_dequeue(&copy_queue1);
		patient2 = patientQueue_dequeue(&copy_queue2);
		
		
		if(patient1 == NULL || patient2 == NULL){		
	
			patientQueue_free(&copy_queue1);
			patientQueue_free(&copy_queue2);
			patient_free(patient1);
			patient_free(patient2);
			free(patient1);
			free(patient2);
			return false;
		}
		else if (!patient_compare(*patient1,*patient2)) {
			patientQueue_free(&copy_queue1);
			patientQueue_free(&copy_queue2);
			patient_free(patient1);
			patient_free(patient2);
			free(patient1);
			free(patient2);
			return false;

		}
		
		
		patient_free(patient1);
		patient_free(patient2);
		free(patient1);
		free(patient2);
		
	}
	
	patientQueue_free(&copy_queue1);
	patientQueue_free(&copy_queue2);

	return true;	
	
}


// compare if two queues are equal recursively.
bool patientQueue_compareRecursive(tPatientQueue *queue1, tPatientQueue *queue2){
	// PR2 EX3	
	bool flag;
	tPatient* patient1, * patient2; 
	
    if(patientQueue_empty(*queue1) && patientQueue_empty(*queue2) ) {
        flag = true ;
	}
    else
    {
		patient1 = patientQueue_dequeue(queue1);
		patient2 = patientQueue_dequeue(queue2);
		
        if(patient1 == NULL || patient2 == NULL){			
			flag = false;
			
			patient_free(patient1);
			patient_free(patient2);
			free(patient1);
			free(patient2);
			
		}
		else if (!patient_compare(*patient1,*patient2)) {
			
			
			flag = false;
			patient_free(patient1);
			patient_free(patient2);
			free(patient1);
			free(patient2);

		}
        else{
            patient_free(patient1);
			patient_free(patient2);
			free(patient1);
			free(patient2);
			return patientQueue_compareRecursive ( queue1, queue2);
		}
	}
			 
    

			
    return (flag) ;	
   
}


// count how many patients already vaccinated with a vaccine
int patientQueue_getPatientsPerVaccineRecursive(tPatientQueue *queue, const char* vaccine){
	// PR2 EX3
	int vaccinated_patients = 0;    
    tPatient* patient; 

    // Base cases
    // 1) The queue is empty => score = 0
    if(patientQueue_empty(*queue)) {
        return 0;
    }
    
    // Recursion
    
    // Get the head
     patient = patientQueue_dequeue(queue);
    
    // check if have been vacinnated 
	if( (patient->vaccine!=NULL) && (strcmp(patient->vaccine, vaccine) == 0) ) {
        // names are different
       vaccinated_patients++;
    }
	
	patient_free(patient);
	free(patient);
    
    return vaccinated_patients + patientQueue_getPatientsPerVaccineRecursive(queue, vaccine);

}



// count how many patients already vaccinated with a vaccine technology
int patientQueue_getPatientsPerVaccineTechnologyRecursive(tPatientQueue *queue, tVaccineTable vaccines, tVaccineTec technology){
	// PR2 EX3
	int vaccinated_technology = 0;    
    tPatient* patient; 
    tVaccine* vaccine; 

    // Base cases
    // 1) The queue is empty => score = 0
    if(patientQueue_empty(*queue)) {
        return 0;
    }
    
    // Recursion
    
    // Get the head
     patient = patientQueue_dequeue(queue);
    
    // check if use the technology
	if( patient->vaccine!=NULL) {
		vaccine = vaccineTable_find(&vaccines,patient->vaccine);
		if ( (vaccine != NULL) && (vaccine->vaccineTec ==technology) ){			
			vaccinated_technology++;
		}
    }
    patient_free(patient);
	free(patient);
	
    return vaccinated_technology + patientQueue_getPatientsPerVaccineTechnologyRecursive(queue, vaccines, technology);

}

int patientQueue_countPatients_vaccinationBatch(tPatientQueue queue, const char* vaccine,int lotID){
	// PR3_EX3	
	
	// Check PRE Conditions
	assert(vaccine != NULL);
	
	// Check if vaccine parameter is different to:
	// Astrazeneca, Janssen, Moderna and Pfizer
	// If its different, return 0
	if((strcmp(vaccine, ASTRAZENECA_VAC) != 0) && (strcmp(vaccine, JANSSEN_VAC) != 0) && (strcmp(vaccine, MODERNA_VAC) != 0) && (strcmp(vaccine, PFIZER_VAC) != 0))
	{
		return 0;
	}
	
	// Create var for save Total Patients
	int PatTotal = 0;
	
	// Create Node
	tPatientQueueNode *PatNode = queue.first;
	
	// While Node is not null
	while(PatNode != NULL)
	{
		// If LotID from Node->e is equal to lotID parameter
		if(PatNode->e.lotID == lotID)
		{
			// Add 1 unit from Total Patients
			PatTotal++;
		}
		
		// Move to next node
		PatNode = PatNode->next;
	}
	
	// Return the Total Patients
	return PatTotal;
}


// Helper function - Print a queue in the console - use for debugging
void patientQueue_print(tPatientQueue queue) {
    tPatientQueueNode *nodePtr = queue.first;
    int i = 0;

    while(nodePtr != NULL) {
		
        printf("%d) %s group %d %d dosis %d %s batch %d\n", i, nodePtr->e.name, nodePtr->e.group, nodePtr->e.id, nodePtr->e.number_doses, nodePtr->e.vaccine, nodePtr->e.lotID);
        nodePtr = nodePtr->next;
        i++;
    }

    printf("\n");
}
