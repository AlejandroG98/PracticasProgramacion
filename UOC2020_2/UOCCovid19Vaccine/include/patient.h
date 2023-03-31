#ifndef __PATIENT_H__
#define __PATIENT_H__

#include <stdbool.h>
#include <vaccine.h>
#include "error.h"

// Patient poblational group
typedef enum {
	HEALTH_WORKER = 0,
    ADULT_OVER_80 = 1,
    ADULT_OVER_65 = 2,
    COMORBID = 3,
    ESSENTIAL_WORKER = 4,
    ADULT_OVER_55 = 5,
    ANYONE_ELSE = 6
} tPatientGroup;

// Definition of a patient structure
typedef struct {
    char* name;
    int id;
    char* vaccine;
	int lotID;
    int number_doses;
    tPatientGroup group;
} tPatient;


// Definition of a queue node
typedef struct _tPatientQueueNode {
    tPatient e;
    struct _tPatientQueueNode* next;
} tPatientQueueNode;


// Definition of a queue of patients
typedef struct {
    tPatientQueueNode* first;
    tPatientQueueNode* last;
} tPatientQueue;

// *** PATIENT

// Initialize a patient structure
tError patient_init(tPatient *patient, const char* patientName, int patientId, const char* vaccine, int lotID, int number_doses, tPatientGroup group);

// inoculate a vaccine to a patient
tError patient_inoculate_vaccine(tPatient* patient, const char* vaccine, int lotID);

// Compare two patients
bool patient_compare(tPatient p1, tPatient p2);

// Duplicate a patient
tError patient_duplicate(tPatient *dst, tPatient src);

// Release memory used by patient
void patient_free(tPatient* patient);

// Returns true if the vaccine can be inoculated. 
bool patient_isSuitableForVaccine(tPatient* patient, tVaccine* vaccine);

// Returns true if the patient has been fully vaccinated
bool patient_isVaccinated(tPatient* patient);

// *** PATIENT QUEUE

// Create the patient queue
tError patientQueue_create(tPatientQueue* queue);

// Check if the queue is empty
bool patientQueue_empty(tPatientQueue queue);

// Enqueue a new match to the match queue
tError patientQueue_enqueue(tPatientQueue* queue, tPatient patient);

// Make a copy of the queue
tError patientQueue_duplicate(tPatientQueue* dst, tPatientQueue src);

// Remove all elements of the queue
void patientQueue_free(tPatientQueue* queue);

// Dequeue a patient from the presentation queue
tPatient * patientQueue_dequeue(tPatientQueue* queue);

// Return the first patient from the queue
tPatient* patientQueue_head(tPatientQueue queue);

// create a copy of the queues before calling  patientQueue_compareRecursive
bool patientQueue_compare(tPatientQueue *queue1, tPatientQueue *queue2);

// compare if two queues are equal iteratively,
bool patientQueue_compareIterative(tPatientQueue *queue1, tPatientQueue *queue2);

// compare if two queues are equal recursively.
bool patientQueue_compareRecursive(tPatientQueue *queue1, tPatientQueue *queue2);

// count how many patients already vaccinated with a vaccine technology
int patientQueue_getPatientsPerVaccineTechnologyRecursive(tPatientQueue *queue, tVaccineTable vaccines, tVaccineTec technology);

// count how many patients already vaccinated with a vaccine
int patientQueue_getPatientsPerVaccineRecursive(tPatientQueue *queue, const char* vaccine);

int patientQueue_countPatients_vaccinationBatch(tPatientQueue queue, const char* vaccine,int lotID);


// print all the information of a patient queue in the console
void patientQueue_print(tPatientQueue queue);




#endif // __PATIENT_H__
