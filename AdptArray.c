//
// Created by Lara Abu Hamad on 15/03/2023.
//

#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"


typedef struct AdptArray_{
    PElement* pElement;
    int size;
    COPY_FUNC copyElement;
    DEL_FUNC delElement;
    PRINT_FUNC printElement;
} AdptArray_;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    PAdptArray pADT = malloc(sizeof(AdptArray_));
    if (pADT) {
        //initialize the variables/functions:
        pADT->pElement = NULL;
        pADT->size = 0;
        pADT->copyElement = copyFunc;
        pADT->delElement = delFunc;
        pADT->printElement = printFunc;
        return pADT;
    }
    return NULL;
}

void DeleteAdptArray(PAdptArray pADT){
    //Loop over all PAdtArray elements, if not NULL then delete it.
    for(int i=0; i<pADT->size; i++){
        if(pADT->pElement[i])
            pADT->delElement(pADT->pElement[i]);
    }
    //Freeing the PAdtArray.
    free(pADT->pElement);
    free(pADT);
}

Result SetAdptArrayAt(PAdptArray pADT, int i, PElement pElement){
    PElement* newpElement;
    //If the pAdtArray or the PElement is NULL or the given index is smaller than 0, return FAIL.
    if(NULL == pADT || NULL == pElement || i < 0)
        return FAIL;
    if(i >= pADT->size) {
        //Create new PElement* with the size of the given PElement.
        newpElement = (PElement*) calloc(i+1, sizeof(PElement));
        if(newpElement == NULL){
            return FAIL;
        }
        //Copy old elements to the new PElement created and freeing the old one.
        memcpy(newpElement, pADT->pElement, pADT->size * sizeof(pElement));
        free(pADT->pElement);
        pADT->pElement = newpElement;
    }
    //Make sure to free the element at index i if not NULL.
    if (pADT->pElement[i]) {
        pADT->delElement(pADT->pElement[i]);
    }
    //Save a copy of given PElement to PElements of the PAdtArray.
    pADT->pElement[i] = pADT->copyElement(pElement);
    //Increasing size by 1 if needed.
    pADT->size = (i >= pADT->size) ? (i+1) : pADT->size;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pADT, int i){
    int newi = -1;
    if(NULL != pADT->pElement[i]) {
        newi = i;
    }
    //If  is positive and smaller than PAdtArray size then it returns a copy of the element at index i else it returns NULL.
    return (newi>=0 && newi<pADT->size) ? pADT->copyElement(pADT->pElement[newi]) : NULL;
}

int GetAdptArraySize(PAdptArray pADT){
    return (pADT->size > 0) ? pADT->size : -1;
}

void PrintDB(PAdptArray pADT){
    for(int i=0; i<pADT->size; i++){
        if(pADT->pElement[i])
            pADT->printElement(pADT->pElement[i]);
    }
}