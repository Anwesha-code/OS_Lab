#include <stdio.h>

#define MAX 100

int main() {
    int pages[MAX], frames[MAX];
    int n, f, i, j, k, pageFaults = 0, next = 0;
    int found;
    int samplePages[] = {1, 3, 0, 3, 5, 6};
    n = 6; 
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
            frames[next] = pages[i];
            next = (next + 1) % f;
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
