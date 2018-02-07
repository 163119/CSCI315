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
    GraphAL<int> g(10);

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

    cout << g.adjacent(0, 1) << endl;
    cout << g.adjacent(0, 3) << endl;

    cout << g.prims(0) << endl;

    cout << g.dijkstraShortestPath(0, 9) << endl;
    cout << g.floydsShortestPath(0, 5) << endl;

    cout << endl << endl;

    g.depthFirstTraversal(&print);

    cout << endl << endl;

    g.breadthFirstTraversal(&print);

    return 0;
}
