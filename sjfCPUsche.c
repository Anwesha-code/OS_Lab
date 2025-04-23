#include <stdio.h>

int main() {
    int n = 4;
    int process[] = {1, 2, 3, 4};
    int arrivalTime[] = {0, 1, 2, 3};
    int burstTime[] = {6, 8, 7, 3};

    int waitingTime[10], turnaroundTime[10];
    int totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burstTime[i] > burstTime[j]) {
                int temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;

                temp = arrivalTime[i];
                arrivalTime[i] = arrivalTime[j];
                arrivalTime[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    waitingTime[0] = 0;
    for (int i = 1; i < n; i++) {
        waitingTime[i] = 0;
        for (int j = 0; j < i; j++)
            waitingTime[i] += burstTime[j];
        waitingTime[i] -= arrivalTime[i];
        if (waitingTime[i] < 0) waitingTime[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
        totalWT += waitingTime[i];
        totalTAT += turnaroundTime[i];
    }

    printf("Process\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", process[i], arrivalTime[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }

    printf("\nAverage Waiting Time = %.2f", (float)totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)totalTAT / n);

    return 0;
}
