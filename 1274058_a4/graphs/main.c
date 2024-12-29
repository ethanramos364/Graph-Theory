/* Ethan Ramos
   1274058
   2024-12-01
   CIS*2520 — Assignment #4
*/ 
#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int choice;
    // int startVertex = 1;
    Graph * graph = readGraph(argv[1]);
    do
    {

        // Display the options
        prompt();

        // Get user input
        printf("Enter a Choice: ");
        scanf("%d", &choice);

        /*
         * You will need to add all the cases here.
         * Call the relevant functions in each case.
         * Make sure to handle invalid inputs or edge cases.
         */

        switch (choice) {
            case 1:
                displayAdjacencyList(graph);
                break;
            case 2:
                bfs(graph,0);
                break;
            case 3:
                dfs(graph,0);
                break;
            case 4:
                dijkstra(graph, 0);
                break;
            case 5:
                printf("quiting...");
                freeGraph(graph);
                return false;

            default:
                // Code for default case
                break;
        }

    } while (true);
    
    return 0;
}
