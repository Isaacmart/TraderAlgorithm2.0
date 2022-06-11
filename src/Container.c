//
// Created by admin on 6/11/22.
//
#include <stdlib.h>
int main (int argc, char *argv[]) {

    int max = 1000000;
    double container[max][6];

    for (int i = 0; i < max; i++) {

        for (int j = 0; j < 6; j++) {
            container[i][j] = i * j;
        }
    }

}
