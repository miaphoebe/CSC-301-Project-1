/*
 * CSC-301
 * project1.cpp
 * Fall 2025
 *
 * Partner 1:
 * Partner 2:
 * Date:
 */

#include "project1.hpp"

using namespace std;

/*
 * swap
 */
void swap(vector<double> &arrayToSort, int index1, int index2) {
    double temp = arrayToSort[index1];
    arrayToSort[index1] = arrayToSort[index2];
    arrayToSort[index2] = temp;
    return;
}

/*
 * selectionSort
 */
void selectionSort(vector<double> &arrayToSort) {
    int len = arrayToSort.size();
    for (int i = 0; i < len - 1; i++) {
        int min = i;
        for (int j = i + 1; j < len; j++) {
            if(arrayToSort[j] < arrayToSort[min]) {
                min = j;
            }
        }
        swap(arrayToSort, i, min);
    }
    return;
}

/*
 * insertionSort
 */
void insertionSort(vector<double> &arrayToSort) {
    int len = arrayToSort.size();
    if (len <= 1){
        return;
    }
    for (int i = 1; i < len; i++) {
        for(int j = i; j > 0 && arrayToSort[j] < arrayToSort[j - 1]; j--) {
            swap(arrayToSort, j, j - 1);
        }
    }
    return;
}

/*
 * bubbleSort
 */
void bubbleSort(vector<double> &arrayToSort) {
    bool sorted = false;
    int len = arrayToSort.size();
    for(int i = 0; i < len - 1 && (!sorted); i++){
        sorted = true;
        for (int j = 0; j < len - 1 - i; j++){
            if (arrayToSort[j + 1] < arrayToSort[j]){
                swap(arrayToSort, j, j + 1);
                sorted = false;
            }
        }
        if (sorted){
            break;
        }
    }
    return;
}

/*
 * merge
 * This helper function will merge two sorted arrays into one sorted array by
 * comparing the values in each, and adding each smallest value to the new array
 * to ensure that all elements in the input lists will be properly sorted.
 * 
 * Inputs: a pointer to the vector-type array we want to sort, a lower bound, a
 *         midpoint index, and an upper bound
 * Output: void; sorts the pointer array with all elements from both inputs
 */
void merge(vector<double> &arrayToSort, int lower, int mid, int upper) {
    // copying values from respective "left" and "right" split lists into new arrays
    vector<double> leftArray(arrayToSort.begin() + lower, arrayToSort.begin() + mid);
    vector<double> rightArray(arrayToSort.begin() + mid, arrayToSort.begin() + upper);
    /* 
     * leftIndex and rightIndex keep track of where we are in each "left" and "right"
     * list
     */
    int leftIndex = 0;
    int rightIndex = 0;
    /*
     * arrayIndex keeps track of the index we're at the in the sorted array we are
     * merging values from both lists into
     */
    int arrayIndex = lower;

    while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            // copies .eft list value into the new array and subsequently increments
            arrayToSort[arrayIndex++] = leftArray[leftIndex++];
        } else {
            arrayToSort[arrayIndex++] = rightArray[rightIndex++];
        } // if/else
    } // while

    // following while loops occur for potential leftover elements
    while (leftIndex < leftArray.size()) {
        arrayToSort[arrayIndex++] = leftArray[leftIndex++];
    } // while

    while (rightIndex < rightArray.size()) {
        arrayToSort[arrayIndex++] = rightArray[rightIndex++];  
    } // while

    return;
} // merge

/*
 * mergeSortSplit
 * This helper function splits a list into two sublists for mergeSort. When the
 * lists are recursively split, they will be recursively merged. This essentially
 * performs all the calls for the merge sort work.
 * 
 * Inputs: a pointer to the vector-type array we want to sort, a lower bound,
 *         and an upper bound
 * Outputs: void; splits the pointer array into different lists separated by the
 *          'lower' and 'upper' values
 */
void mergeSortSplit(vector<double> &arrayToSort, int lower, int upper) {
    // ensure that the list can be split (i.e. is not a singleton or empty)
    if ((upper - lower) > 1) {
        // finds the middle portion of the array for all possible real values
        int mid = lower + ((upper - lower) / 2);
        // make a list of the "left" elements (from indices 0 to mid)
        mergeSortSplit(arrayToSort, lower, mid);
        // make a list of the "right" elements (from mid to (arrayToSort.size() - 1))
        mergeSortSplit(arrayToSort, mid, upper);
        merge(arrayToSort, lower, mid, upper);
    } // if

    return;
} // mergeSortSplit

/*
 * mergeSort
 * This function recursively sorts an array using the merge sort algorithm. This
 * method splits an array into sublists and progressively merges these
 * elements into sorted sublists until the array is completly merged and sorted.
 * 
 * Inputs: a pointer to the vector-type array we want to sort
 * Output: void; sorts the designated array via merge sort
 */
void mergeSort(vector<double> &arrayToSort) {
    // checking for the base cases
    if (arrayToSort.size() <= 1) {
        return;
    } // if

    // called on full list to perform merge sort mechanics
    mergeSortSplit(arrayToSort, 0, arrayToSort.size());
    return;
} // mergeSort

/*
 * partition
 * This helper function computes the pivot value when a (sub)list is
 * partitioned. It does so by using the last element as the pivot. It also
 * goes through the sublist indeces and will swap values that are less than
 * or equal to the pivot to create a sorted list.
 * 
 * Inputs: a pointer to the vector-type array we want to sort, a lower bound, and
 *         an upper bound
 * Outputs: void; derives a pivot value for (sub)list and sorts based off of that
 *          value
 */
int partition(vector<double> &arrayToSort, int lower, int upper) {
    // we're using the last element as the pivot
    double pivot = arrayToSort[upper - 1];

    // setting the lower bound; we are provided the upper bound
    int bound = lower;
    for (int i = lower; i < upper - 1; i++) {
        if (arrayToSort[i] <= pivot) {
            // swap when the value at index i is less than or equal to the pivot
            swap(arrayToSort[i], arrayToSort[bound]);
            // increase the lower bound at each swap
            bound++;
        } // if
    } // for

    // swap upper bound value into place
    swap(arrayToSort[upper - 1], arrayToSort[bound]);
    return bound;
} // partition

/*
 * quickSortHelper
 * This helper function recursively calls itself to partition the list(s) and sort
 * the elements in the sublists based on the pivot value. This essentially
 * performs all the calls for the quick sort work.
 *
 * Inputs: a pointer to the vector-type array we want to sort, a lower bound i,
 * and an upper bound j
 *      Note that i is inclusive (i.e., is the first element of subarray).
 *      Note that j is not inclusive (i.e., off the end of the subarray).
 * Outputs: void; continuously partitions into sublists based on the generated pivot
 *          value
 */
void quickSortHelper(vector<double> &arrayToSort, int i, int j) {
    if (i < j - 1) {
        int pivotIndex = partition(arrayToSort, i, j);
        // sort the left side of the pivot
        quickSortHelper(arrayToSort, i, pivotIndex);
        // sort the right side of the pivot
        quickSortHelper(arrayToSort, pivotIndex + 1, j);
    } // if
    return;
} // quickSortHelper

/*
 * quickSort
 * This function sorts values using the quick sort method. It will choose a
 * pivot element (in helper functions), 'partitions' the array based off that element,
 * and sorts each partition until the whole list is sorted.
 * 
 * Inputs: a pointer to the vector-type array we want to sort
 * Outputs: void; sorts the designated array via quicksort
 */
void quickSort(vector<double> &arrayToSort) {
    // checking for the base cases
    if (arrayToSort.size() <= 1) {
        return;
    } // if

    // called on the full list to partition and sort
    quickSortHelper(arrayToSort, 0, arrayToSort.size());
    return;
} // quickSort
