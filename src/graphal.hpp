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


#ifndef GRAPHAL_H
#define GRAPHAL_H

/* This class represents a weighted driected graph via an adjacency list.
 * Vertices are given an index, starting from 0 and ascending
 * Class W : W represent the weight that can be associacted with an edge.
 * We will not weight the vertices.
 */

#include <vector>
#include <list>

using namespace std;

template<class W>
class GraphAL {
    private:
        struct node_t {
            int mEndVertex;
            W mWeight;
        };
        vector< list<node_t> > mAList;

        /* Class to begin filling out...*/
        void depthFirstTraversal(void (*visit)(const int node), bool *visited, const int cVertex);
    public:
        /* Initialize an empty graph. */
        GraphAL();

        /* Initialize the Graph with a fixed number of vertices. */
        GraphAL(const int vertices);

        /* Deconstructor shall free up memory */
        ~GraphAL();

        /* Adds amt vertices to the graph. */
        void addVertices(int amt);

        /* Removes a vertex.
         * return wheter sucessful or not
         */
        bool removeVertex(int idx);

        /* Adds an edge with weight W to the graph. */
        bool addEdge(const int start, const int end, const W &weight);

        /*
         * Remove edge from graph.
         */
        bool removeEdge(const int start, const int end);

        void depthFirstTraversal(void (*visit)(const int node));
        void breadthFirstTraversal(void (*visit)(const int node));

        /*
         * Return adjacent weight from start to end (or -1 if they are
         * not adjacent.
         */
        W adjacent(const int start, const int end);

        /* Run dijkstra's ShortestPath returning the smallest weight
         * from start to end.
         * return -1 if a path does not exist!
         */
        W dijkstraShortestPath(const int start, const int end);

        /* Run Floyd's ShortestPath returning the smallest weight
         * from start to end.
         * return -1 if a path does not exist!
         */
        W floydsShortestPath(const int start, const int end);

        /* Returns the TOTAL weight of the minimum spanning tree with the
         * given starting node.
         * You must use Prim's MST.
         */
        W prims(const int start);

        /* Print out the Graph */
        void print();

};

#include "graphal.cpp"

#endif
