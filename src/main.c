//
// Created by admin on 6/12/22.
//
#include "Container.h"


int main(int argc, char *argv[]) {


    double* ptr;
    double arr[20][COLUMNS];
    ptr = *arr;

    for (int i = 0; i < 20; i++) {

        for (int j =0; j < COLUMNS; j++) {
            arr[i][j] = 1;
        }
    }
    print_array(&ptr, 5);
}