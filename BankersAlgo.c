#include <stdio.h>
#include <stdbool.h>

#define P 5      //******* */ Number of processes
#define R 3      //********* */ Number of resource types

int available[R] = {3, 3, 2}; // Available instances of resources

int max[P][R] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

int allocation[P][R] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int need[P][R];

void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe() {
    int work[R];
    bool finish[P] = {false};
    int safeSequence[P];

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    int count = 0;
    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is NOT in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return true;
}

int main() {
    calculateNeed();
    isSafe();
    return 0;
}
