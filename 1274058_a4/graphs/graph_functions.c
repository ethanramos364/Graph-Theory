/* Ethan Ramos
   1274058
   2024-12-01
   CIS*2520 — Assignment #4
*/ 
#include "graph.h"
/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    FILE *fptr = fopen(filename, "r");

    if(fptr==NULL){
        printf("Error opening file");
        return NULL;
    }
    int totalVertices = 0;
    for (int i = 0; i < 5;i++){
        totalVertices++;
        for (int j = 0; j < 5;j++){
            //nested for loop scan each value into the corresponding position in the adjmatrix
            fscanf(fptr,"%d",&(graph)->adjMatrix[i][j]);            
            
        }
    }
    createAdjacencyList(graph);
    graph->numVertices = totalVertices;
    fclose(fptr);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    for (int i = 0; i < 5;i++){
        //print the vertex's adjacency list are processing
        printf("\nVertex %d:",i+1);
        if(graph->adjList[i]!=NULL){
            Node* temp=graph->adjList[i];
            while(temp!=NULL){
                //while the adjacency list has more entries print the vertex and its weight
                printf("-> %d (%d) ",temp->vertex,graph->adjMatrix[i][temp->vertex-1]);
                temp = temp->next;
            }

        }
        else{
            printf("\nadjlist position was null");
        }
        //print null at the end of each adjacency list
        printf("NULL");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
*/
void createAdjacencyList(Graph *graph)
{
    Node *temp;
    for (int i = 0; i < 5;i++){
        graph->adjList[i] = NULL;
        for (int j = 0; j < 5;j++){
            // if the position in the position in the adjacency matrix is not 0 add the node to the adjacency list
            if(graph->adjMatrix[i][j]!=0){
                Node * newNode= createNode(j+1);
                //if null make it the first entry
                if(graph->adjList[i]==NULL){
                    graph->adjList[i] = newNode;
                }
                //if not null traverse to the end of the list then add the entry at the end
                else{
                    temp = graph->adjList[i];
                while(temp->next!=NULL){
                    temp = temp->next;
                }
                temp->next= newNode ;
                }
                
            }
        }
    }
    
    return;
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    //initialize the queue front and rear
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;
    //add the first vertex to the queue and post increment the rear
    queue[rear++] = startVertex+1;
    int discoveredSet[MAX_VERTICES]={0}; //init discovered set elements to 0
    discoveredSet[startVertex] = 1; //set the 1st pos in discovered set to true
    //while still element in queue
    while(front<rear){
        //dequeue and get current vertex and print it
        int currentVertex = queue[front++];
        printf("%d ",currentVertex);
        Node *temp = graph->adjList[currentVertex-1]; //set temp equal to the current vertex to check in the adj list & adjust index (-1 for 0 based)
        while(temp!=NULL){
            int neighbour = temp->vertex; //set neighbour to temp vertex 
            if(discoveredSet[neighbour-1]!=1){ //if the position of neighbour in discovered set is not true add the neighbour to the queue and set it as discovered
                queue[rear++] = neighbour;
                discoveredSet[neighbour-1] = 1;
            }
            temp = temp->next;
        }
    }
    return;
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    int stack[MAX_VERTICES]; //init stack and top
    int top = -1;
    stack[++top] = startVertex; //top to start vertex (0 based)
    int discoveredSet[MAX_VERTICES]={0}; //discovered set positions to false
    discoveredSet[startVertex] = 1; //set first to true
    while(top!=-1){
        int currentVertex = stack[top--]; //pop the stack get current vertex
        printf("%d ",currentVertex+1); //print it +1 since 0 based
        Node * temp = graph->adjList[currentVertex]; 
        while (temp != NULL) {
            if (discoveredSet[temp->vertex-1]!=1) {
                stack[++top] = temp->vertex-1;  //if temp vertex discovered set not true add it to stack and set it as discovered
                discoveredSet[temp->vertex -1] = 1; 
            }
            temp = temp->next;
        }
    }
    return;
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    int numVertices = graph->numVertices; 
    int distance[MAX_VERTICES];        //distance and visited array set visited to false  
    int visited[MAX_VERTICES]={0};     

    distance[startVertex] = 0;  
    //set all distance to large number except 1
    for (int i = 1; i < numVertices; i++) {
        distance[i] = 1000; // Set distance to "infinity"
    }
    

    // Main loop for Dijkstra's algorithm
    for (int count = 0; count < numVertices - 1; count++) {
        // Find the vertex with the smallest distance that hasn't been visited
        int minDistance = INT_MAX;
        int u = -1;
        for (int i = 0; i < numVertices; i++) {
            if (visited[i]!=1) {
                if(distance[i] < minDistance){ //if distance is less than current min set min to current
                   minDistance = distance[i];
                    u = i; 
                }                
            }
        }
        visited[u] = 1; //set visited true

        for (int j = 0; j < numVertices; j++) {
            int weight = graph->adjMatrix[u][j]; //get weight from adj matrix
            if (weight > 0 && visited[j]!=1) {  //if weight is >0 (this means that it has an edge) and has not been visited
                int alt = distance[u] + weight; 
                if (alt < distance[j]) {  // Check if we found a shorter path
                    distance[j] = alt; //set path = to the alternative path
                }
            }
        }
    }

    printf("Shortest distances from vertex %d:\n", startVertex + 1); //display in correct format
    for (int i = 0; i < numVertices; i++) {
        printf("Shortest distance from vertex %d to vertex %d: %d\n",
               startVertex + 1, i + 1, distance[i]);
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph)
{
    if (graph == NULL) {
        printf("free failed");
        return;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        Node *current = graph->adjList[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);     //free temp
        }
    }

    // Free the graph 
    free(graph);
}
