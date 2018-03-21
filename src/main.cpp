/*
 *	Student Name:		Christopher Aumen
 *	Program Name:		Graph with Adjacency List
 *	Creation Date:		November 23, 2016
 *	Last Modified Date:	January 28, 2018
 *	CSCI Course:		CSCI-315 Data Structures
 *	Grade Received:		100
 *	Comments regarding design:
 *		This program is an implementation of a Graph with Adjacency Lists.
 *		It is not designed to be run as an independent executable, but as
 *		a piece of a larger program.
 */


#include "graphal.hpp"
#include <iostream>

using namespace std;

// Function for printing the vertex for functions requiring function parameter.
void print(const int node) {
    cout << node << endl;
}

// Test program to determine if each function works as intended.
int main(int argc, char *argv[]) {
    cout << "Graph Library Test\nCreating 10-node graph...\n";

    GraphAL<int> g(10);
    
    cout << "Adding weighted edges\n";
    g.addEdge(0, 1, 3);
    g.addEdge(0, 2, 7);
    g.addEdge(0, 4, 9);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 5, 10);
    g.addEdge(4, 3, 9);
    g.addEdge(5, 6, 2);
    g.addEdge(5, 7, 2);
    g.addEdge(6, 9, 6);
    g.addEdge(7, 8, 2);
    g.addEdge(8, 9, 2);

    cout << "Checking adjaceny of 0 to 1 and 0 to 3 (Should be weight 3, and -1 to indicate no adjacency):\n";
    cout << g.adjacent(0, 1) << endl;
    cout << g.adjacent(0, 3) << endl;

    cout << "Running prims algorithm (Minimum spanning tree weight: 33)\n";
    cout << g.prims(0) << endl;

    cout << "Running dijkstra's algorithm from node 0 to node 9 (Shortest path: 23): \n";
    cout << g.dijkstraShortestPath(0, 9) << endl;

    cout << "Running floyd's algorithm from node 0 to node 5 (Shortest path: 17): \n";
    cout << g.floydsShortestPath(0, 5) << endl;

    cout << endl << endl;

    cout << "Running a depth first traversal (0 1 3 5 6 9 7 8 2 4): \n";
    g.depthFirstTraversal(&print);

    cout << endl << endl;

    cout << "Running a breadth first traversal (0 1 2 4 3 5 6 7 9 8): \n";
    g.breadthFirstTraversal(&print);

    return 0;
}
