#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for(i = 1; i < n; ++i) {
        if(time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, page_faults = 0;

    // Input the number of frames
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);

    // Input the number of pages
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);

    // Input the reference string
    printf("Enter the reference string: ");
    for(i = 0; i < no_of_pages; ++i) {
        scanf("%d", &pages[i]);
    }

    // Initialize the frame array and time array with -1
    for(i = 0; i < no_of_frames; ++i) {
        frames[i] = -1;   // All frames are initially empty
        time[i] = 0;      // Initialize time to 0
    }

    printf("\nPage Table State (LRU):\n\n");

    // Main logic for LRU page replacement
    for(i = 0; i < no_of_pages; ++i) {
        flag1 = flag2 = 0;

        // Check if the page is already in one of the frames
        for(j = 0; j < no_of_frames; ++j) {
            if(frames[j] == pages[i]) {
                counter++;
                time[j] = counter;  // Update the time for the page (recently used)
                flag1 = flag2 = 1;  // Page is already in the frame
                break;
            }
        }

        // If the page is not in any frame
        if(flag1 == 0) {
            // Check if there is an empty frame
            for(j = 0; j < no_of_frames; ++j) {
                if(frames[j] == -1) {  // Empty frame found
                    counter++;
                    page_faults++;
                    frames[j] = pages[i];  // Insert the page into the empty frame
                    time[j] = counter;     // Update the time of usage
                    flag2 = 1;
                    break;
                }
            }
        }

        // If there are no empty frames, find the LRU page
        if(flag2 == 0) {
            pos = findLRU(time, no_of_frames);  // Find the least recently used page
            counter++;
            page_faults++;
            frames[pos] = pages[i];  // Replace the LRU page with the new page
            time[pos] = counter;     // Update the time of usage for the new page
        }

        // Display the current state of the frames after each reference
        for(j = 0; j < no_of_frames; ++j) {
            if(frames[j] != -1)  // Print only valid page numbers
                printf("%d ", frames[j]);
            else
                printf("- ");  // Print "-" for empty frames
        }
        printf("\n");
    }

    // Output the total number of page faults
    printf("\nTotal Page Faults = %d\n", page_faults);

    return 0;
}
