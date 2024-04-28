#include <stdio.h>

#define MEMORY_SIZE 100

int memory[MEMORY_SIZE];

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0; // 0 indicates free memory
    }
}

int allocateMemory(int process_size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        int j;
        for (j = 0; j < process_size; j++) {
            if (memory[i + j] != 0) {
                break; // Not enough contiguous free memory, move to the next block
            }
        }
        if (j == process_size) {
            // Allocate memory
            for (int k = i; k < i + process_size; k++) {
                memory[k] = 1; // 1 indicates allocated memory
            }
            return i; // Return the starting address of the allocated memory
        }
    }
    return -1; // Memory allocation failed
}

void displayMemoryStatus() {
    printf("Memory Status:\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n-----------------------------------------\n");
}

int main() {
    initializeMemory();
    displayMemoryStatus();

    int process_size = 20;
    int allocated_address = allocateMemory(process_size);
    if (allocated_address != -1) {
        printf("Memory allocated for process of size %d at address %d.\n", process_size, allocated_address);
    } else {
        printf("Memory allocation failed for process of size %d.\n", process_size);
    }

    displayMemoryStatus();

    return 0;
}
