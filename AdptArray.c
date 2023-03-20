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
    for(int i=0; i<pADT->size; i++){
        if(pADT->pElement[i])
            pADT->delElement(pADT->pElement[i]);
    }
    free(pADT->pElement);
    free(pADT);
}

Result SetAdptArrayAt(PAdptArray pADT, int i, PElement pElement){
    PElement* newpElement;
    if(NULL == pADT || NULL == pElement || i < 0)
        return FAIL;
    if(i >= pADT->size) {
        newpElement = (PElement*) calloc(i+1, sizeof(PElement));
        if(newpElement == NULL){
            return FAIL;
        }
        memcpy(newpElement, pADT->pElement, pADT->size * sizeof(pElement));
        free(pADT->pElement);
        pADT->pElement = newpElement;
    }
    if (pADT->pElement[i]) {
        pADT->delElement(pADT->pElement[i]);
    }
    pADT->pElement[i] = pADT->copyElement(pElement);
    pADT->size = (i >= pADT->size) ? (i+1) : pADT->size;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pADT, int i){
    int newi = -1;
    if(NULL != pADT->pElement[i]) {
        newi = i;
    }
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