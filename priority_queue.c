#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int pid;
    int burstTime;
    int priority;
} Process;

typedef struct {
    Process processes[MAX];
    int size;
} PriorityQueue;

// Insert process in sorted order (lower priority number comes first)
void insert(PriorityQueue* pq, Process p) {
    int i = pq->size - 1;

    // Shift processes to make room for the new process
    while (i >= 0 && pq->processes[i].priority > p.priority) {
        pq->processes[i + 1] = pq->processes[i];
        i--;
    }

    pq->processes[i + 1] = p;
    pq->size++;
}

// Remove and return the process with highest priority
Process dequeue(PriorityQueue* pq) {
    return pq->processes[--pq->size];
}

int main() {
    int n;
    PriorityQueue pq;
    pq.size = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Process p;
        p.pid = i + 1;
        printf("\nEnter burst time for P%d: ", p.pid);
        scanf("%d", &p.burstTime);
        printf("Enter priority for P%d (lower = higher priority): ", p.pid);
        scanf("%d", &p.priority);
        insert(&pq, p);
    }

    printf("\n--- Priority Scheduling using Priority Queue ---\n");
    printf("PID\tPriority\tBurst\tWaiting\tTurnaround\n");

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    // Dequeue from front of queue (which has the highest priority)
    for (int i = 0; i < n; i++) {
        Process p = pq.processes[i];

        int waitingTime = currentTime;
        int turnaroundTime = waitingTime + p.burstTime;

        printf("P%d\t%d\t\t%d\t%d\t%d\n", p.pid, p.priority, p.burstTime, waitingTime, turnaroundTime);

        totalWT += waitingTime;
        totalTAT += turnaroundTime;

        currentTime += p.burstTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}