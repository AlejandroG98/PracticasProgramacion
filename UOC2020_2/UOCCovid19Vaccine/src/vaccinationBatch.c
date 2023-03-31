#include <stdio.h>
#include <stdio.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "patient.h"
#include "vaccinationBatch.h"
#include "country.h"

// Initialize a vaccine batch
tError vaccinationBatch_init(tVaccineBatch* vb, int id, tVaccine* vac, int num) {
    tError error;

    // Verify pre conditions
    assert(vb != NULL);
    assert(vac != NULL);

    // Allocate the memory for the name string field, using the length of the provided
    // text plus 1 space for the "end of string" char '\0'.
    // To allocate memory we use the malloc command.
    vb->vaccine = (tVaccine*)malloc(sizeof(tVaccine));

    // Check that memory has been allocated.
    // Pointer must be different from NULL.
    if(vb->vaccine == NULL) {
        return ERR_MEMORY_ERROR;
    } else {
        vb->vaccine->name = NULL;
    }

    // Once the memory is allocated, copy the data.
    vb->lotID = id;
    vb->quantity = num;
    error = vaccine_cpy(vb->vaccine, vac);

    // check if any error occured
    if(error != OK)
        return error;

    return OK;
}

// Release memory used by a vaccine batch
void vaccinationBatch_free(tVaccineBatch* vb) {
    // Verify pre conditions
    assert(vb != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them
    if(vb->vaccine != NULL) {
        vaccine_free(vb->vaccine);
        free(vb->vaccine);
        vb->vaccine = NULL;
    }

    vb->lotID = 0;
    vb->quantity = 0;
}

// Compare two vaccine batches
bool vaccinationBatch_equals(tVaccineBatch vb1, tVaccineBatch vb2) {
    bool result;

    result = true;
    // To see if two vaccines batches are equal, we need to see if their ids are equal.
    if(vb1.lotID != vb2.lotID) {
        // names are different
        result = false;
    }

    // All fields have the same value
    return result;
}

// Copy a vaccine batch
tError vaccinationBatch_cpy(tVaccineBatch* dest, tVaccineBatch* src) {
    tError error;

    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);

    // free dest vaccine (just in case)
    vaccinationBatch_free(dest);

    // initialize dest with src values.
    error = vaccinationBatch_init(dest, src->lotID, src->vaccine, src->quantity);
    // check if any error occured
    if(error != OK)
        return error;

    return OK;
}

// Create the list
tError vaccinationBatchList_create(tVaccinationBatchList *list) {
    // PR3 EX1
	
	// Check PRE Conditions
	assert(list != NULL);
	
	// Set the First and Last element to Null and set size = 0 for create list
	list->first= NULL;
	list->last = NULL;
    list->size = 0;
	
	return OK;
}



// Will return true if list is empty
bool vaccinationBatchList_empty(tVaccinationBatchList list) {
    // PR3 EX1

	// If the size's list is 0 means empty
    return list.size == 0;
}

// Frees all elements in the list
void vaccinationBatchList_free(tVaccinationBatchList *list) {
    // PR3 EX1
	
	// Check PRE Conditions
	assert(list != NULL);
	
	// Create var for next step
	int i;
	
	// Loop the list and delete calling delete function with list and index (i) values	
	for(i=list->size-1; i>=0; i--)
	{
		vaccineBatchList_delete(list, i);
	}
	
	// Set First and Last element to null
	list->first = NULL;
	list->last = NULL;
}

// Insert/adds a new Vaccine Batch  to the tVaccinationBatchList
tError vaccineBatchList_insert(tVaccinationBatchList* list, tVaccineBatch vaccineBatch, int index) {
    // PR3_EX1

	// Check PRE Conditions
	assert(list != NULL);
	
	// Allocate memory for the new node
	tVaccinationBatchListNode *BatchListNode = (tVaccinationBatchListNode*)malloc(sizeof(tVaccinationBatchListNode));
	
	// Create Node for prior moves
	tVaccinationBatchListNode *PriorNode;
	
	// Check if index is OUT of range
	// If its true, set ERROR Invalid Index
	if(index > list->size)
	{
		return ERR_INVALID_INDEX;
	}
	
	// Check if new node is null
	if(BatchListNode == NULL)
	{
		return ERR_MEMORY_ERROR;
	}
	
	// Init Batch with BatchListNode->e and vaccineBatch values
	vaccinationBatch_init(&BatchListNode->e, vaccineBatch.lotID, vaccineBatch.vaccine, vaccineBatch.quantity);
	
	// Set NULL the next position
	BatchListNode->next = NULL;
	
	// If index is 0, save values in next and first positions on pointers
	if(index == 0)
	{
		BatchListNode->next = list->first;
		list->first = BatchListNode;
	}
	else
	{
		// Call _get function sending list and index values
		// Save the result in PriorNode
		PriorNode = vaccineBatchList_get(*list, index - 1);
		
		// If PriorNode is not null, save values in next positions of both pointers
		if(PriorNode != NULL)
		{
			BatchListNode->next = PriorNode->next;
			PriorNode->next = BatchListNode;
		}
		else
		{
			// Liberate BatchListNode and set ERROR Index
			free(BatchListNode);
			return ERR_INVALID_INDEX;
		}
	}
	
	// Add 1 unit of size
	list->size++;
	
	// Compare the index with size, if are equal, set BatchListNode values in last
	if(index == list->size)
	{
		list->last = BatchListNode;
	}

	return OK;
}

// Deletes a tBestVideoType from the tTopGender list
tError vaccineBatchList_delete(tVaccinationBatchList* list, int index) {
    // PR3_EX1

    // Check PRE Conditions
	assert(list != NULL);
	
	// Create Nodes
	tVaccinationBatchListNode *BatchListNode; 
	tVaccinationBatchListNode *PriorNode; 
	
	// Check if index is OUT of range
	// If its true, set ERROR Invalid Index
	if(index > list->size)
	{
		return ERR_INVALID_INDEX;
	}
	
	// Check if the list is empty with empty function
	// If its true, set ERROR Empty List
	if(vaccinationBatchList_empty(*list))
	{
		return ERR_EMPTY_LIST;
	}
	
	// If index is 0, save the list first value in BatchListNode
	if(index == 0)
	{
		BatchListNode = list->first;
		
		// Check if its null, set ERROR Empty List
		if(BatchListNode == NULL)
		{
			return ERR_EMPTY_LIST;
		}
		else
		{
			// List first position save next BatchListNode values
			list->first = BatchListNode->next;
		}
	}
	else
	{
		// Call _get function sending list and index values
		// Save the result in PriorNode
		PriorNode = vaccineBatchList_get(*list, index-1);
		
		// Check if PriorNode is not null
		if(PriorNode != NULL)
		{
			// Save on BatchListNode the next PriorNode values
			BatchListNode = PriorNode->next;
			
			// Check if BatchListNode is null
			if(BatchListNode == NULL)
			{
				return ERR_INVALID_INDEX;
			}
			else
			{
				// Save on next PriorNode element, the next BatchListNode values 
				PriorNode->next = BatchListNode->next;
			}
		}
		else
		{
			return ERR_INVALID_INDEX;
		}
	}
	
	// Set new list size, cutting one unit
	list->size = list->size - 1;
	
	// Check if list size are higher than 0
	if(list->size > 0)
	{
		// Call _get function with list and size values and save it on last list position
		list->last = vaccineBatchList_get(*list, list->size);
	}
	else
	{
		// Set NULL the last position
		list->last = NULL;
	}
	
	// Liberate BatchListNode
	free(BatchListNode);
	
	return OK;
}

// Gets tVaccinationBatchListNode from given position, NULL if out of bounds
tVaccinationBatchListNode* vaccineBatchList_get(tVaccinationBatchList list, int index) {
    // PR3_EX2

	// Create var for loop
	int i=0;
	
	// Create Node with first element of the list
	tVaccinationBatchListNode *BatchListNode = list.first;
	
	// Check if index parameter is higher than list size
	// OR list is empty, calling _empty function
	if(list.size < index || vaccinationBatchList_empty(list))
	{
		return NULL;
	}
	
	// While i value is lower than index and
	// BatchListNode is not null
	while(i< index && BatchListNode != NULL)
	{
		// On BatchListNode save next BatchListNode values
		BatchListNode = BatchListNode->next;
		
		// Increase i
		i++;
	}
	
	// Return BatchListNode value
	return BatchListNode;
	
}

// Duplicate list
tError vaccinationBatchList_duplicate(tVaccinationBatchList *dest, tVaccinationBatchList src) {
    tVaccinationBatchListNode *currNode = NULL;
    tVaccinationBatchListNode *nextNode = NULL;
    tError err;

    // free list (just in case)
    vaccinationBatchList_free(dest);

    // Initialize new list
    err = vaccinationBatchList_create(dest);
    if(err != OK)
        return err;

    // Duplicate the list
    currNode = src.first;
    while(currNode != NULL && err == OK) {
        nextNode = currNode->next;
        err = vaccineBatchList_insert(dest, currNode->e, 0);
        currNode = nextNode;
    }
    return err;
}

// inoculate first vaccine to a patient form a batch list
void vaccineBatchList_inoculate_first_vaccine(tVaccinationBatchList* vbList, tPatient* patient) {
    // PR3 EX2
	
	// Check PRE Conditions
	assert(vbList != NULL);
	assert(patient != NULL);
	
	// Call _inoculate function and send the parameters for inoculate patients
	vaccineBatchList_inoculate(vbList, patient);
}

// inoculate second vaccine to a patient form a batch list
void vaccineBatchList_inoculate_second_vaccine(tVaccinationBatchList* vbList, tPatient* patient) {
    // PR3 EX2
	
	// Check PRE Conditions
	assert(vbList != NULL);
	assert(patient != NULL);
	
	// Call _inoculate function and send the parameters for inoculate patients
	vaccineBatchList_inoculate(vbList, patient);
}

//  function to explore all batches for inoculate to a patient
void vaccineBatchList_inoculate(tVaccinationBatchList* vbList, tPatient* patient) {
    // PR3 EX2
	
	// Check PRE Conditions
	assert(vbList != NULL);
	assert(patient != NULL);
	
	// Create Node with first BatchList values
	tVaccinationBatchListNode *BatchListNode = vbList->first;
	
	// While BatchListNode is not null
	while(BatchListNode != NULL)
	{
		// Check if BatchListNode->e.quantity is higher than 0 and
		// Call _isSuitableForVaccine function with patient and BatchListNode->e vaccine if the result is true 
		if(BatchListNode->e.quantity >0 && patient_isSuitableForVaccine(patient, BatchListNode->e.vaccine))
		{
			// Call patient_inoculate_vaccine function and send patient, 
			// BatchListNode->e.vaccine name and BatchListNode->e lotID
			patient_inoculate_vaccine(patient, BatchListNode->e.vaccine->name, BatchListNode->e.lotID);
			
			// Decrease one unit of BatchListNode->e.quantity
			BatchListNode->e.quantity--;
			
		}
		
		// Move to next element
		BatchListNode = BatchListNode->next;
	}
}

// Sorts input list using quickSort algorithm
void vaccineBatchList_quickSortRecursive(tVaccinationBatchList *list, int low, int high) {
    // PR3_EX3
	
	// Check PRE Conditions
	assert(list != NULL);

	// Create variables for QuickSort
	int i,j,pivot;
	
	// If low value is lower than high
	if(low < high)
	{
		// Save new values on i and j var
		i = low;
		j = high;
		
		// Call _getlotID function sending list and low values
		// And save it on pivot var
		pivot = vaccineBatchList_getlotID(*list,low);
		
		// While i is lower than j (low < high)
		while(i < j)
		{
			// While i <= high value and
			// The result of the call _getLostID(list,i) is lower or equal than pivot
			while(i <= high && vaccineBatchList_getlotID(*list,i) <= pivot)
			{
				// Increase one unit of i
				i++;
			}
			
			// While j >= low value and
			// The result of the call _getLostID(list,j) is higher than pivot
			while(j >= low && vaccineBatchList_getlotID(*list,j) > pivot)
			{
				// Decrease one unit of j
				j--;
			}
			
			// Check if i is lower than j
			if(i < j)
			{
				// Call _swap function and send list,i,j values
				vaccineBatchList_swap(list,i,j);
			}
		}
		
		// Call _swap function and send list,low,j values 
		vaccineBatchList_swap(list,low,j);
		
		// Call _QuickSortRecursive function and send list,low,j-1 values 
		vaccineBatchList_quickSortRecursive(list, low, j-1);
		
		// Call _QuickSortRecursive function and send list,j+1, high values 
		vaccineBatchList_quickSortRecursive(list, j+1, high);
	}	
}

//    The main function for quick sort
tError vaccineBatchList_quicksort(tVaccinationBatchList *queue) {
    // PR3_EX3
    
	// Call QuickSortRecursive function sending
	// Parameter and 0 (low position) and queue size -1 (high position)
	vaccineBatchList_quickSortRecursive(queue,0,queue->size-1);
	return OK;
}

// Swap two elements in the list
tError vaccineBatchList_swap(tVaccinationBatchList* list, int index_dst, int index_src) {

    assert(list != NULL);
    assert(index_dst >= 0);
    assert(index_src >= 0);
    assert(index_dst < list->size);
    assert(index_src < list->size);

    tError err;
    tVaccinationBatchListNode * node_src, *node_dst;
    tVaccineBatch tmp;

    if(index_dst == index_src) {
        return ERR_INVALID_INDEX;
    }

    tmp.vaccine =  NULL;
    tmp.lotID = 0;
    tmp.quantity = 0;

    node_src = vaccineBatchList_get(*list, index_src);
    node_dst = vaccineBatchList_get(*list, index_dst);

    err = vaccinationBatch_cpy(&tmp, &node_src->e);
    if(err == OK) {
        vaccinationBatch_free(&node_src->e);
        err = vaccinationBatch_cpy(&node_src->e, &node_dst->e);
        if(err == OK) {
            vaccinationBatch_free(&node_dst->e);
            vaccinationBatch_cpy(&node_dst->e, &tmp);
        }
    }

    vaccinationBatch_free(&tmp);

    return err;
}

// Gets lotID from given position, -1 if out of bounds
int vaccineBatchList_getlotID(tVaccinationBatchList list, int index) {

    int i, lotID;
    tVaccinationBatchListNode *prev;

    // Loop until find index position
    i = 0;
    prev = list.first;
    while(i < index && (prev != NULL)) {
        prev = prev->next;
        i++;
    }

    if(prev == NULL) {
        lotID = -1 ;
    } else {
        lotID = prev->e.lotID;
    }

    return lotID;
}

// Helper function - Print a queue in the console - use for debugging
void vaccineBatchList_print(tVaccinationBatchList list) {
    tVaccinationBatchListNode *nodePtr = list.first;;


    while(nodePtr != NULL) {

        printf("%s) lotId %d quantity %d \n", nodePtr->e.vaccine->name, nodePtr->e.lotID, nodePtr->e.quantity);
        nodePtr = nodePtr->next;

    }

    printf("\n");
}
