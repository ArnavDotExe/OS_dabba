#include <stdio.h>

#define MAX_PARTITIONS 10

struct Partition {
    int id;
    int size;
    int allocated;
};

void bestFit(struct Partition partitions[], int np, int process_size) {
    int min_diff = 999999; // Initialize to a large value
    int best_partition = -1;

    for (int i = 0; i < np; i++) {
        if (!partitions[i].allocated && partitions[i].size >= process_size) {
            int diff = partitions[i].size - process_size;
            if (diff < min_diff) {
                min_diff = diff;
                best_partition = i;
            }
        }
    }

    if (best_partition != -1) {
        partitions[best_partition].allocated = 1;
        printf("Process of size %d allocated to partition %d\n", process_size, partitions[best_partition].id);
    } else {
        printf("Unable to allocate process of size %d\n", process_size);
    }
}

int main() {
    int np; // Number of partitions
    printf("Enter the number of partitions: ");
    scanf("%d", &np);

    struct Partition partitions[MAX_PARTITIONS];

    printf("Enter size of each partition:\n");
    for (int i = 0; i < np; i++) {
        printf("Partition %d: ", i + 1);
        scanf("%d", &partitions[i].size);
        partitions[i].id = i + 1;
        partitions[i].allocated = 0; // Initialize as not allocated
    }

    int nprocesses; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &nprocesses);

    int process_sizes[nprocesses];
    printf("Enter size of each process:\n");
    for (int i = 0; i < nprocesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &process_sizes[i]);
    }

    // Allocate processes using best fit algorithm
    for (int i = 0; i < nprocesses; i++) {
        bestFit(partitions, np, process_sizes[i]);
    }

    return 0;
}
