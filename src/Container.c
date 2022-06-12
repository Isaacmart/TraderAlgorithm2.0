//
// Created by admin on 6/11/22.
//
#include <stdlib.h>
#include <stdio.h>
#include "Container.h"


void insert_new(double *arr[], double *line, int size) {

    for (int i = 1; i < size - 1; i++) {
        arr[i-1] = arr[i];
    }
    arr[size-1] = line;
}

double* get_array(double* arr[], int size, int index) {

    double *ptr;
    if ((index < 6) && (index >= 0)) {
        double new_arr[size];
        ptr = new_arr;

        for (int i = 0; i < size; i++) {
            new_arr[i] = arr[i][index];
        }
    }
    return ptr;
}


void print_array(double* arr[], int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%f |", arr[i][j]);
        }
        printf("\n");
    }
}

