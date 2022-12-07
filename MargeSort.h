#pragma once
#include <iostream>
using namespace std;

void merge(int array[], short const left, short const mid, short const right)
{
    short const sArr1 = mid - left + 1;
    short const subArrayTwo = right - mid;

  
    short* leftArray = new short[sArr1];
    short* rightArray = new short[subArrayTwo];

    
    for (auto i = 0; i < sArr1; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    short indS1 = 0;

    short indS2 = 0;

    short indM = left;

    while (indS1 < sArr1
        && indS2 < subArrayTwo) {
        if (leftArray[indS1]
            <= rightArray[indS2]) {
            array[indM]
                = leftArray[indS1];
            indS1++;
        }
        else {
            array[indM]
                = rightArray[indS2];
            indS2++;
        }
        indM++;
    }
    

    while (indS1 < sArr1) {
        array[indM]
            = leftArray[indS1];
        indS1++;
        indM++;
    }
    
    while (indS2 < subArrayTwo) {
        array[indM]
            = rightArray[indS2];
        indS2++;
        indM++;
    }
    delete[] leftArray;
    delete[] rightArray;
}


void mergeSort(int array[], short const begin, short const end)
{
    if (begin >= end)
        return; 

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}



