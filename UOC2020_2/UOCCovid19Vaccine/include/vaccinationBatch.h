#ifndef __VACCINATION_BATCH__H__
#define __VACCINATION_BATCH__H__

#include <stdbool.h>
#include "error.h"
#include "commons.h"
#include "vaccine.h"
#include "patient.h"

// Data type to hold data related to a vaccine
typedef struct {
    int lotID;
    tVaccine* vaccine;
    int quantity;
} tVaccineBatch;

// Definition of a list node
typedef struct _tVBSNode {
    tVaccineBatch e;
    struct _tVBSNode* next;
} tVaccinationBatchListNode;

// List of tVaccineBatch elements
typedef struct {
    tVaccinationBatchListNode *first;
	tVaccinationBatchListNode *last;
	int size;
} tVaccinationBatchList;

// **** Functions related to tVaccinationBatch

// Initialize a vaccination batch
tError vaccinationBatch_init(tVaccineBatch* vb, int id, tVaccine* vac, int num);

// Release memory used by a vaccination batch
void vaccinationBatch_free(tVaccineBatch* vb);

// Compare two vaccination batches
bool vaccinationBatch_equals(tVaccineBatch vb1, tVaccineBatch vb2);

// Copy a vaccine batch
tError vaccinationBatch_cpy(tVaccineBatch* dest, tVaccineBatch* src);


// **** Functions related to tVaccinationBatchList

// Create the list 
tError vaccinationBatchList_create(tVaccinationBatchList *list);

// Will return true if list is empty
bool vaccinationBatchList_empty(tVaccinationBatchList list);

// Frees all elements in the list
void vaccinationBatchList_free(tVaccinationBatchList *list);

// Duplicate list
tError vaccinationBatchList_duplicate(tVaccinationBatchList *dest, tVaccinationBatchList src);

// inoculate first vaccine to a patient form a batch list
void vaccineBatchList_inoculate_first_vaccine(tVaccinationBatchList* vbList, tPatient* patient);

// inoculate second vaccine to a patient form a batch list
void vaccineBatchList_inoculate_second_vaccine(tVaccinationBatchList* vbList, tPatient* patient);

// recursive function to explore all batches for inoculate to a patient
void vaccineBatchList_inoculate(tVaccinationBatchList* vbList, tPatient* patient);

// Insert/adds a new Vaccine Batch  to the tVaccinationBatchList 
tError vaccineBatchList_insert(tVaccinationBatchList* list, tVaccineBatch vaccineBatch, int index);

// Deletes a tBestVideoType from the tTopGender list
tError vaccineBatchList_delete(tVaccinationBatchList* list, int index);

// Gets tVaccinationBatchListNode from given position, NULL if out of bounds
tVaccinationBatchListNode* vaccineBatchList_get(tVaccinationBatchList list, int index);

// Gets lotID from given position, -1 if out of bounds
int vaccineBatchList_getlotID(tVaccinationBatchList list, int index);

// Swap two elements in the list
tError vaccineBatchList_swap(tVaccinationBatchList* queue, int index_dst, int index_src);

// Sorts input list using quickSort algorithm
tError vaccineBatchList_quicksort(tVaccinationBatchList *queue);

// Sorts input list using quickSort algorithm
void vaccineBatchList_quickSortRecursive(tVaccinationBatchList *list, int head, int tail);

// Helper function - Print a queue in the console - use for debugging
void vaccineBatchList_print(tVaccinationBatchList list);

#endif // __VACCINATION_BATCH__H__
