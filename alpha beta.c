alpha beta
#include <stdio.h>
#include <conio.h>

#define MAX_LEAVES 8

#define INF 999 

int pruneCount = 0;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int alphaBeta(int depth, int nodeIndex, int isMax, int values[], int alpha, int beta, int maxDepth) {
    int i, val;
    int best;

    
    if (depth == maxDepth) {
        return values[nodeIndex];
    }

    if (isMax) {
        best = -INF;        
               for (i = 0; i < 2; i++) {
            val = alphaBeta(depth + 1, nodeIndex * 2 + i, 0, values, alpha, beta, maxDepth);
            best = max(best, val);
            alpha = max(alpha, best);
            
                        if (beta <= alpha) {
                pruneCount++;
                printf(" Pruning at MAX node (Depth %d, Child %d skipped)\n", depth, i + 1);
                break;
            }
        }
        return best;
    } else {
        best = INF;         
                for (i = 0; i < 2; i++) {
            val = alphaBeta(depth + 1, nodeIndex * 2 + i, 1, values, alpha, beta, maxDepth);
            best = min(best, val);
            beta = min(beta, best);
            
            /* Alpha-Beta Pruning condition */
            if (beta <= alpha) {
                pruneCount++;
                printf(" Pruning at MIN node (Depth %d, Child %d skipped)\n", depth, i + 1);
                break;
            }
        }
        return best;
    }
}

void main() {
    /* Example leaf nodes for a tree of depth 3 (2^3 = 8 leaves) */
    int leafValues[MAX_LEAVES] = {3, 5, 6, 9, 1, 2, 0, -1};
    int maxDepth = 3;
    int optimalValue;

    clrscr(); 
    printf("Starting Alpha-Beta Pruning...\n");
    printf("Initial Alpha = -999, Beta = 999\n\n--- Execution Steps ---\n");

   
    optimalValue = alphaBeta(0, 0, 1, leafValues, -INF, INF, maxDepth);

    printf("\n--- Results ---\n");
    printf("The optimal value at the root is: %d\n", optimalValue);
    printf("Total number of branches pruned: %d\n", pruneCount);

   
    if (leafValues[0] >= leafValues[4]) {
        printf("Best decision for MAX: Choose Left Move\n");
    } else {
        printf("Best decision for MAX: Choose Right Move\n");
    }

    getch(); 
}