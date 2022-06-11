//
// Created by admin on 6/11/22.
//


int main() {

    int max = 1000000;
    double container[max][6];

    for (int i = 0; i < max; i++) {

        for (int j = 0; j < 6; j++) {

            container[i][j] = i * j;
        }
    }
}
