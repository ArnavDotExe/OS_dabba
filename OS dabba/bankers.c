#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

// Function to check if there are enough resources available to satisfy a request
bool isSafeState(int request[], int process_count, int resource_count) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];

    // Initialize work and finish arrays
    for (int i = 0; i < resource_count; i++)
        work[i] = available[i];
    for (int i = 0; i < process_count; i++)
        finish[i] = finished[i];

    // Find an unfinished process that can be satisfied with the current available resources
    int count = 0;
    while (count < process_count) {
        bool found = false;
        for (int i = 0; i < process_count; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < resource_count; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == resource_count) {
                    for (int k = 0; k < resource_count; k++)
                        work[k] += allocation[i][k];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            return false; // No process can be satisfied with the current available resources
    }
    return true;
}

// Function to allocate resources to a process
void allocateResources(int process, int request[], int process_count, int resource_count) {
    // Check if the request exceeds the maximum demand of the process
    for (int i = 0; i < resource_count; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Request exceeds maximum demand\n");
            return;
        }
    }

    // Check if the request can be satisfied with the available resources
    for (int i = 0; i < resource_count; i++) {
        if (request[i] > available[i]) {
            printf("Error: Request cannot be granted immediately\n");
            return;
        }
    }

    // Try allocating resources to the process
    for (int i = 0; i < resource_count; i++) {
        allocation[process][i] += request[i];
        available[i] -= request[i];
        need[process][i] -= request[i];
    }

    // Check if the system is still in a safe state after the allocation
    if (!isSafeState(request, process_count, resource_count)) {
        // Roll back the allocation if it leads to an unsafe state
        for (int i = 0; i < resource_count; i++) {
            allocation[process][i] -= request[i];
            available[i] += request[i];
            need[process][i] += request[i];
        }
        printf("Error: Allocation leads to an unsafe state\n");
        return;
    }

    printf("Request granted successfully\n");
}

int main() {
    int process_count, resource_count;

    printf("Enter the number of processes: ");
    scanf("%d", &process_count);
    printf("Enter the number of resources: ");
    scanf("%d", &resource_count);

    printf("Enter the available resources:\n");
    for (int i = 0; i < resource_count; i++)
        scanf("%d", &available[i]);

    printf("Enter the maximum demand of each process:\n");
    for (int i = 0; i < process_count; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < resource_count; j++)
            scanf("%d", &max[i][j]);
    }

    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < process_count; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < resource_count; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int request[MAX_RESOURCES];
    int process;

    while (true) {
        printf("\nEnter process number and resource request (or -1 to exit): ");
        scanf("%d", &process);
        if (process == -1)
            break;
        if (process < 0 || process >= process_count) {
            printf("Error: Invalid process number\n");
            continue;
        }
        printf("Enter requested resources: ");
        for (int i = 0; i < resource_count; i++)
            scanf("%d", &request[i]);
        allocateResources(process, request, process_count, resource_count);
    }

    return 0;
}
