#include <stdio.h>

#define MAX_FRAMES 3

int main() {
    int n, frames[MAX_FRAMES], pages[MAX_FRAMES], page_hits = 0, page_faults = 0, frame_count = 0, i, j, k, found;

    printf("Enter the number of page requests: ");
    scanf("%d", &n);

    printf("Enter the page reference sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames to -1, indicating they are empty
    for (i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    // FIFO Page Replacement Algorithm
    for (i = 0; i < n; i++) 
    {
        found = 0;
        // Check if page is already in frame
        for (j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                page_hits++;
                break;
            }
        }
        // If page not found, replace the oldest page
        if (!found) 
        {
            if (frame_count < MAX_FRAMES) 
            {
                frames[frame_count] = pages[i];
                frame_count++;
            } else 
            {
                // Replace the oldest page
                for (j = 0; j < MAX_FRAMES - 1; j++) 
                {
                    frames[j] = frames[j + 1];
                }
                frames[MAX_FRAMES - 1] = pages[i];
            }
            page_faults++;
        }

        // Print current state of frames
        printf("Current state of frames: ");
        for (k = 0; k < frame_count; k++) {
            printf("%d ", frames[k]);
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", page_faults);
    printf("Total page hits: %d\n", page_hits);
    

    return 0;
}