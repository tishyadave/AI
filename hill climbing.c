hill climbing
#include <stdio.h>
#include <conio.h>

/* Function to calculate f(x) = -x^2 + 6x */
long f(long x) {
    return -(x * x) + (6 * x);
}

/* Main Function */
void main() {
    long current_x = 0;
    long step_size = 1; /* Looking at neighbors x+1 and x-1 */
    int step_count = 1;
    
    long current_val, next_neighbor, prev_neighbor, next_val, prev_val;
    long best_neighbor_x, best_neighbor_val;

    clrscr(); /* Turbo C specific clear screen */

    printf("Starting Hill Climbing search at x = %ld\n", current_x);
    printf("Objective function: f(x) = -x^2 + 6x\n");
    printf("------------------------------------------\n");

    while (1) {
        current_val = f(current_x);

        /* Generate local step neighbors */
        next_neighbor = current_x + step_size;
        prev_neighbor = current_x - step_size;

        /* Evaluate states */
        next_val = f(next_neighbor);
        prev_val = f(prev_neighbor);

        printf("Step %d: Current state x = %ld, f(x) = %ld\n", step_count, current_x, current_val);
        printf(" Neighbors: f(%ld) = %ld, f(%ld) = %ld\n", next_neighbor, next_val, prev_neighbor, prev_val);

        /* Determine the highest value neighbor */
        if (next_val > prev_val) {
            best_neighbor_x = next_neighbor;
            best_neighbor_val = next_val;
        } else {
            best_neighbor_x = prev_neighbor;
            best_neighbor_val = prev_val;
        }

        /* Check if the best neighbor improves upon the current state value */
        if (best_neighbor_val > current_val) {
            printf(" -> Best neighbor found at x = %ld. Climbing up...\n\n", best_neighbor_x);
            current_x = best_neighbor_x;
            step_count++;
        } else {
            /* Local or global peak reached where no neighborhood point is higher */
            printf(" -> No better neighbor exists. Peak reached! Algorithm stops.\n");
            break;
        }
    }

    printf("------------------------------------------\n");
    printf("Final Execution Result:\n");
    printf("Maximum Value found at local peak x = %ld\n", current_x);
    printf("Maximized f(%ld) = %ld\n", current_x, f(current_x));

    getch(); /* Turbo C specific hold screen */
}