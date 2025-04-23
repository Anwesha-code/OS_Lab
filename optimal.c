#include <stdio.h>
#define MAX 100

int findOptimal(int pages[], int frames[], int n, int index, int f) {
    int farthest = index, result = -1;

    for (int i = 0; i < f; i++) {
        int j;
        for (j = index + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == n) 
            return i;
    }

    return result == -1 ? 0 : result;
}

int main() {
    int pages[MAX], frames[MAX];
    int n, f, i, j, k, pageFaults = 0, found;

    int samplePages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    n = 12; 
    f = 3;  

    for (i = 0; i < n; i++)
        pages[i] = samplePages[i];

    for (i = 0; i < f; i++)
        frames[i] = -1;

    for (i = 0; i < n; i++) {
        found = 0;

        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos;

            if (i < f) {
                frames[i] = pages[i];
            } else {
                pos = findOptimal(pages, frames, n, i, f);
                frames[pos] = pages[i];
            }

            pageFaults++;

            printf("Page %d caused a fault. Frames: ", pages[i]);
            for (k = 0; k < f; k++)
                if (frames[k] != -1) printf("%d ", frames[k]);
            printf("\n");
        } else {
            printf("Page %d is already in a frame.\n", pages[i]);
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
