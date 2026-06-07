#include <stdio.h>
#include <conio.h>

#define MAX 20
#define INF 9999

int findMinF(int open[], int g[], int h[], int n) {
    int i, min = INF, index = -1;
    int f;

    for (i = 0; i < n; i++) {
        if (open[i] == 1) {
            f = g[i] + h[i];

            if (f < min) {
                min = f;
                index = i;
            }
        }
    }

    return index;
}

void printPath(int parent[], int goal) {
    if (parent[goal] == -1) {
        printf("%d ", goal);
        return;
    }

    printPath(parent, parent[goal]);
    printf("%d ", goal);
}

void aStar(int graph[MAX][MAX], int h[], int n, int start, int goal) {
    int open[MAX], closed[MAX], parent[MAX], g[MAX];
    int i, current, neighbor, newG;
    int nodesExpanded = 0;

    for (i = 0; i < n; i++) {
        open[i] = 0;
        closed[i] = 0;
        parent[i] = -1;
        g[i] = INF;
    }

    g[start] = 0;
    open[start] = 1;

    while (1) {
        current = findMinF(open, g, h, n);

        if (current == -1) {
            printf("No path found!\n");
            return;
        }

        open[current] = 0;
        closed[current] = 1;
        nodesExpanded++;

        if (current == goal) {
            printf("\nA* Result\n");
            printf("Path: ");
            printPath(parent, goal);
            printf("\nTotal Cost: %d", g[goal]);
            printf("\nNodes Expanded: %d", nodesExpanded);
            return;
        }

        for (neighbor = 0; neighbor < n; neighbor++) {
            if (graph[current][neighbor] != 0 && closed[neighbor] == 0) {
                newG = g[current] + graph[current][neighbor];

                if (open[neighbor] == 0 || newG < g[neighbor]) {
                    g[neighbor] = newG;
                    parent[neighbor] = current;
                    open[neighbor] = 1;
                }
            }
        }
    }
}

void main() {
    int graph[MAX][MAX];
    int h[MAX];
    int n, start, goal;
    int i, j;

    clrscr();

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix 0 if no edge:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter heuristic values:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter goal node: ");
    scanf("%d", &goal);

    aStar(graph, h, n, start, goal);

    getch();
}