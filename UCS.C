#include <stdio.h>
#include<conio.h>

#define INF 999999
#define MAX 20

int findMin(int cost[], int visited[], int n) {
    int min = INF, index = -1;
    int i;

    for (i = 0; i < n; i++) {
	if (!visited[i] && cost[i] < min) {
	    min = cost[i];
	    index = i;
	}
    }

    return index;
}

void printPath(int parent[], int start, int goal) {
    int path[MAX];
    int length = 0;
    int current = goal;
    int i;

    while (current != -1) {
	path[length++] = current;
	current = parent[current];
    }

    printf("Path: ");
    for (i = length - 1; i >= 0; i--) {
	printf("%d ", path[i]);
    }
    printf("\n");
}

void UCS(int graph[MAX][MAX], int n, int start, int goal) {
    int cost[MAX], visited[MAX], parent[MAX];
    int nodesExpanded = 0;
    int i, neighbour;

    for (i = 0; i < n; i++) {
	cost[i] = INF;
	visited[i] = 0;
	parent[i] = -1;
    }

    cost[start] = 0;

    while (1) {
	int current = findMin(cost, visited, n);

	if (current == -1)
	    break;

	visited[current] = 1;
	nodesExpanded++;

	if (current == goal)
	    break;

	for (neighbour = 0; neighbour < n; neighbour++) {
	    if (graph[current][neighbour] != 0 && !visited[neighbour]) {
		int newCost = cost[current] + graph[current][neighbour];

		if (newCost < cost[neighbour]) {
		    cost[neighbour] = newCost;
		    parent[neighbour] = current;
		}
	    }
	}
    }

    printf("\nUCS Result\n");

    if (cost[goal] == INF) {
	printf("No path found\n");
    } else {
	printPath(parent, start, goal);
	printf("Cost is %d\n", cost[goal]);
    }

    printf("Nodes Expanded: %d\n", nodesExpanded);
}

int main() {
    int n;
    int graph[MAX][MAX];
    int start, goal;
    int i, j;
    clrscr();
    printf("Enter number of cities (nodes): ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 if no connection):\n");
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    scanf("%d", &graph[i][j]);
	}
    }

    printf("Enter start city (0 to %d): ", n - 1);
    scanf("%d", &start);

    printf("Enter goal city (0 to %d): ", n - 1);
    scanf("%d", &goal);

    UCS(graph, n, start, goal);
    getch();
    return 0;

}
