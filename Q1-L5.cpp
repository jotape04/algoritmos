#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct node {
    int vertexNumber;
    int time;
    bool isPortal;
    node *next;
};

struct adjList {
    node *head;
};

struct graph {
    int vertexQuantity;
    adjList *array;
};

node *createNode(int vertexNumber, int time, bool isPortal) {
    node *newNode = new node;
    newNode->vertexNumber = vertexNumber;
    newNode->time = time;
    newNode->isPortal = isPortal;
    newNode->next = nullptr;
    return newNode;
}

graph *createGraph(int vertexQuantity) {
    graph *newGraph = new graph;
    newGraph->vertexQuantity = vertexQuantity;
    newGraph->array = new adjList[vertexQuantity];
    for (int i=0; i<vertexQuantity; i++)
        newGraph->array[i].head = nullptr;
    return newGraph;
}

void addEdge(adjList *list, int vertexNumber, int time, bool isPortal) {
    node *newNode = createNode(vertexNumber, time, isPortal);
    newNode->next = list->head;
    list->head = newNode;
}

int matrixToVertex(int x, int y, int columnQuantity) {
    return x*columnQuantity + y;
}

bool isPortalOpen (int currentTime, int portalTime) {
    return currentTime % portalTime == 0;
}

int djikstra(graph *maze, int portalTime) {
    int *distance = new int[maze->vertexQuantity];
    bool *visited = new bool[maze->vertexQuantity];

    for (int i=0; i<maze->vertexQuantity; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    distance[0] = 0;

    int currentTime = 0;

    for (int i=0; i<maze->vertexQuantity-1; i++) {
        int minDistance = INT_MAX;
        int minIndex;

        for (int j=0; j<maze->vertexQuantity; j++) {
            if (!visited[j] && distance[j] <= minDistance) {
                minDistance = distance[j];
                minIndex = j;
            }
        }

        visited[minIndex] = true;

        node *current = maze->array[minIndex].head;
        while (current != nullptr) {
            if (!visited[current->vertexNumber] && distance[minIndex] != INT_MAX && distance[minIndex] + current->time < distance[current->vertexNumber]) {
                if (current->isPortal) {
                    if (isPortalOpen(currentTime, portalTime)) {
                        distance[current->vertexNumber] = distance[minIndex] + 1;
                    }
                    else {
                        distance[current->vertexNumber] = distance[minIndex] + current->time - (currentTime % portalTime) + 1;
                    }
                } else {
                    distance[current->vertexNumber] = distance[minIndex] + current->time;
                }
            }
            current = current->next;
        }

        currentTime++;
    }

    return distance[maze->vertexQuantity-1];
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int mazeNumber;
    cin >> mazeNumber;

    for (int m=0; m<mazeNumber; m++) {
        int rowQuantity, columnQuantity;
        cin >> rowQuantity >> columnQuantity;

        graph *maze = createGraph(rowQuantity*columnQuantity);
        int counter = 0;
        for (int i=0; i<rowQuantity; i++) {
            for (int j=0; j<columnQuantity; j++) {
                string adjacency;
                cin >> adjacency;

                for (int k=0; k<adjacency.length(); k++) {
                    if (adjacency[k] == 'N') {
                        addEdge(&maze->array[counter], counter-columnQuantity, 1, false);
                    } else if (adjacency[k] == 'S') {
                        addEdge(&maze->array[counter], counter+columnQuantity, 1, false);
                    } else if (adjacency[k] == 'W') {
                        addEdge(&maze->array[counter], counter-1, 1, false);
                    } else if (adjacency[k] == 'E') {
                        addEdge(&maze->array[counter], counter+1, 1, false);
                    }
                }

                counter++;
            }
        }

        int portalQuantity, portalTime;
        cin >> portalQuantity >> portalTime;

        for (int i=0; i<portalQuantity; i++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            int vertex1 = matrixToVertex(x1, y1, columnQuantity);
            int vertex2 = matrixToVertex(x2, y2, columnQuantity);

            addEdge(&maze->array[vertex1], vertex2, portalTime, true);
        }
        
        cout << m << ": " << djikstra(maze, portalTime) << endl;
    }

    return 0;
}
