#include <stdio.h>
#include <stdlib.h>

int full = 0, empty = 10, mutex = 1, x = 0;

void producer() {
    ++full;
    empty = empty - 1;
    mutex = mutex - 1;
    x++;
    printf("\nproducer produces item %d", x);
    mutex = mutex + 1;
}

void consumer() {
    --full;
    mutex = mutex - 1;
    empty = empty + 1;
    printf("\nconsumer consumes item %d", x);
    x--;
    mutex = mutex + 1;
}

int main() {
    int n, choice;

    printf("1. producer");
    printf("\n2. consumer");
    printf("\n3. exit");

    do {
        printf("\nenter your choice");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if(mutex == 1 && empty != 0) {
                    producer();
                } else {
                    printf("buffer is full");
                }
                break;
            case 2:
                if(mutex == 1 && full != 0) {
                    consumer();
                } else {
                    printf("buffer is empty");
                }
                break;
            default:
                exit(0);
                break;
        }
    } while(choice <= 3);

    return 0;
}