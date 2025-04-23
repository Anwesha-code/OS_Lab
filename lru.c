#include <stdio.h>

#define MAX 100

int findLRU(int time[], int f) {
    int i, min = time[0], pos = 0;

    for (i = 1; i < f; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[MAX], frames[MAX], time[MAX];
    int n, f, i, j, pos, pageFaults = 0, counter = 0;
    int found;

    int samplePages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    n = 12; 
    f = 3;  

    for (i = 0; i < n; i++)
        pages[i] = samplePages[i];

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (i = 0; i < n; i++) {
        found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter; 
                found = 1;
                break;
            }
        }

        if (!found) {
            if (i < f) {
                frames[i] = pages[i];
                counter++;
                time[i] = counter;
            } else {
                pos = findLRU(time, f);
                frames[pos] = pages[i];
                counter++;
                time[pos] = counter;
            }
            pageFaults++;

            printf("Page %d caused a fault. Frames: ", pages[i]);
            for (j = 0; j < f; j++)
                if (frames[j] != -1) printf("%d ", frames[j]);
            printf("\n");
        } else {
            printf("Page %d is already in a frame.\n", pages[i]);
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
