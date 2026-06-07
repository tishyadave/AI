#include <stdio.h>
#include <conio.h>

#define MAX 100

typedef struct {
    int x, y;
} Node;

Node queue[MAX];
int front = 0, rear = -1;

Node stack[MAX];
int top = -1;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int isValid(int x, int y, int rows, int cols, int maze[10][10], int visited[10][10]) {
    if (x >= 0 && x < rows && y >= 0 && y < cols &&
        maze[x][y] == 0 && visited[x][y] == 0)
        return 1;
    return 0;
}

void printPath(Node parent[10][10], Node start, Node goal) {
    Node path[MAX];
    int length = 0;
    int i;
    Node current;

    current = goal;

    while (!(current.x == start.x && current.y == start.y)) {
        path[length++] = current;
        current = parent[current.x][current.y];
    }

    path[length++] = start;

    printf("Path: ");
    for (i = length - 1; i >= 0; i--) {
        printf("(%d,%d) ", path[i].x, path[i].y);
    }

    printf("\nPath Length: %d\n", length - 1);
}

void BFS(int maze[10][10], int rows, int cols, Node start, Node goal) {
    int visited[10][10] = {0};
    Node parent[10][10];
    Node current;
    int nodesExpanded = 0;
    int found = 0;
    int i, nx, ny;

    front = 0;
    rear = -1;

    queue[++rear] = start;
    visited[start.x][start.y] = 1;

    while (front <= rear) {
        current = queue[front++];
        nodesExpanded++;

        if (current.x == goal.x && current.y == goal.y) {
            found = 1;
            break;
        }

        for (i = 0; i < 4; i++) {
            nx = current.x + dx[i];
            ny = current.y + dy[i];

            if (isValid(nx, ny, rows, cols, maze, visited)) {
                visited[nx][ny] = 1;
                parent[nx][ny] = current;
                queue[++rear].x = nx;
                queue[rear].y = ny;
            }
        }
    }

    printf("\nBFS\n");
    if (found)
        printPath(parent, start, goal);
    else
        printf("No Path Found!\n");

    printf("Nodes Expanded BFS: %d\n", nodesExpanded);
}

void DFS(int maze[10][10], int rows, int cols, Node start, Node goal) {
    int visited[10][10] = {0};
    Node parent[10][10];
    Node current;
    int nodesExpanded = 0;
    int found = 0;
    int i, nx, ny;

    top = -1;
    stack[++top] = start;
    visited[start.x][start.y] = 1;

    while (top >= 0) {
        current = stack[top--];
        nodesExpanded++;

        if (current.x == goal.x && current.y == goal.y) {
            found = 1;
            break;
        }

        for (i = 0; i < 4; i++) {
            nx = current.x + dx[i];
            ny = current.y + dy[i];

            if (isValid(nx, ny, rows, cols, maze, visited)) {
                visited[nx][ny] = 1;
                parent[nx][ny] = current;
                stack[++top].x = nx;
                stack[top].y = ny;
            }
        }
    }

    printf("\nDFS\n");
    if (found)
        printPath(parent, start, goal);
    else
        printf("No Path Found!\n");

    printf("Nodes Expanded DFS: %d\n", nodesExpanded);
}

void main() {
    int rows, cols;
    int maze[10][10];
    Node start, goal;
    int i, j;

    clrscr();

    printf("Enter number of rows and cols max 10: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter maze matrix 0 free 1 obstacle:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    printf("Enter start position x y: ");
    scanf("%d %d", &start.x, &start.y);

    printf("Enter goal position x y: ");
    scanf("%d %d", &goal.x, &goal.y);

    BFS(maze, rows, cols, start, goal);
    DFS(maze, rows, cols, start, goal);

    getch();
}