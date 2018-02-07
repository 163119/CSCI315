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

#ifdef GRAPHAL_H

#include <iostream>
#include <queue>
#include <list>
#include <vector>

using namespace std;

// Constructor for an empty Graph
template<class W>
GraphAL<W>::GraphAL() {
}

// Constructor for Graph with preset number of vertices
template<class W>
GraphAL<W>::GraphAL(const int vertices) {
    if (vertices <= 0) return;

    mAList.resize(vertices);
    for (int i = 0; i < vertices; i++) {
        list<node_t> l;
        mAList.push_back(l);
    }
}

// Modifies graph to add vertices
template<class W>
void GraphAL<W>::addVertices(int amt) {
    mAList.resize(mAList.size() + amt);

    for (int i = 0; i < amt; i++) {
        list<node_t> l;
        mAList.push_back(l);
    }
}

//Moves the highest numbered vertex to the vertex to be removed.  So
//vertex numbers will change.
template<class W>
bool GraphAL<W>::removeVertex(int idx) {
    if (idx < 0 || idx >= mAList.size()) return false;

    for (int i = 0; i < mAList.size(); i++) { //remove all paths to idx
        if (i == idx) continue;
        while (removeEdge(i, idx)) {}
    }

    mAList[idx] = mAList[mAList.size() - 1]; //vertex idx will now be the last vertex

    mAList.erase((mAList.end()-1)); //removes the last vertex which is now just a copy
    mAList.resize(mAList.size() - 1);

    for (int i = 0; i < mAList.size(); i++) { //changes paths from the removed vertex to idx
        if (i == idx) continue;
        for (typename list<node_t>::iterator it = mAList[i].begin(); it != mAList[i].end(); it++) {
            if (it->mEndVertex == mAList.size()) it->mEndVertex = idx;
        }
    }
    return true;
}

// Modifies graph to add an edge between two known vertices with a weight.
template<class W>
bool GraphAL<W>::addEdge(const int start, const int end, const W &weight){
    if (start < 0 || start >= mAList.size()) return false;
    if (end < 0 || end >= mAList.size()) return false;

    node_t node;
    node.mEndVertex = end;
    node.mWeight = weight;

    mAList[start].push_back(node);

    return true;
}

// Modifies graph to remove an edge between vertices if one exists
template<class W>
bool GraphAL<W>::removeEdge(const int start, const int end) {
    if (start < 0 || start >= mAList.size()) return false;
    if (end < 0 || end >= mAList.size()) return false;

    bool found = false;
    for (typename list<node_t>::iterator it = mAList[start].begin(); it != mAList[start].end(); it++) {
        if (it->mEndVertex == end) {
                found = true;
                it = mAList[start].erase(it);
        }
    }

    return found;
}

// Prints out a representation of the graph
template<class W>
void GraphAL<W>::print() {
    for (int i = 0; i < mAList.size(); i++) {
        for (typename list<node_t>::iterator it = (mAList[i].begin()); it != mAList[i].end(); it++) {
            cout << i << " " << it->mEndVertex << " " << it->mWeight << endl;
        }
    }
}

// Runs through a depth first traversal of graph and running the function paramenter on the vertex.
template<class W>
void GraphAL<W>::depthFirstTraversal(void (*visit)(const int node)) {
    if (mAList.size() <= 0) return;

    bool *visited = new bool[mAList.size()];
    for (int i = 0; i < mAList.size(); i++) visited[i] = false;

    depthFirstTraversal(visit, visited, 0);

    delete[] visited;

    return;
}

// Recursive function for DFS traversal
template<class W>
void GraphAL<W>::depthFirstTraversal(void (*visit)(const int node), bool *visited, const int cVertex) {
    if (!visited[cVertex]) {
        visited[cVertex] = true;
        visit(cVertex);

        for (typename list<node_t>::iterator it = mAList[cVertex].begin(); it != mAList[cVertex].end(); it++) {
            depthFirstTraversal(visit, visited, it->mEndVertex);
        }
    }

    return;
}

// Breadth first traversal running the provided function on each vertex.
template<class W>
void GraphAL<W>::breadthFirstTraversal(void (*visit)(const int node)) {
    if (mAList.size() <= 0) return;

    bool *visited = new bool[mAList.size()];

    for (int i = 0; i < mAList.size(); i++) visited[i] = false;

    queue<int> q;

    q.push(0);

    while (!q.empty()) {
        int cVertex = q.front();
        q.pop();

        if (!visited[cVertex]) {
            visit(cVertex);
            visited[cVertex] = true;

            typename list<node_t>::iterator it = mAList[cVertex].begin();

            for (; it != mAList[cVertex].end(); it++) {
                q.push(it->mEndVertex);
            }
        }
    }

    delete[] visited;
    return;
}

// Determines if two vertices are adjacent to one another (contain an edge between)
//ASSUMES AN INT CAN BE CAST AS W
template<class W>
W GraphAL<W>::adjacent(const int start, const int end) {
    if (start < 0 || start >= mAList.size()) return -1;
    if (end < 0 || end >= mAList.size()) return -1;

    for (typename list<node_t>::iterator it = mAList[start].begin(); it != mAList[start].end(); it++) {
        if (it->mEndVertex == end) return it->mWeight;
    }

    return -1;
}

// Determines the shortest path between two vertices via Dijkstra's Algorithm.
template<class W>
W GraphAL<W>::dijkstraShortestPath(const int start, const int end) {
    bool *visited = new bool[mAList.size()];
    W *shortestPath = new W[mAList.size()];
    for (int i = 0; i < mAList.size(); i++) {
        shortestPath[i] = -1;
        visited[i] = false;
        if (i == start) shortestPath[i] = 0;
    }

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int cVertex = q.front();
        q.pop();

        for (typename list<node_t>::iterator it = mAList[cVertex].begin(); it != mAList[cVertex].end(); it++) {
            if (shortestPath[it->mEndVertex] == -1) {
                shortestPath[it->mEndVertex] = shortestPath[cVertex] + it->mWeight;
            } else if (shortestPath[it->mEndVertex] > (shortestPath[cVertex] + it->mWeight)) {
                shortestPath[it->mEndVertex] = shortestPath[cVertex] + it->mWeight;
            }
        }

        visited[cVertex] = true;

        W minW = -1;
        int nVertex = -1;

        for (int i = 0; i < mAList.size(); i++) {
            if (visited[i]) continue;

            if (shortestPath[i] == -1) continue;

            if (minW == -1) {
                minW = shortestPath[i];
                nVertex = i;
            } else if (minW > shortestPath[i]) {
                minW = shortestPath[i];
                nVertex = i;
            }
        }

        if (nVertex != -1) q.push(nVertex);
    }

    W ret = shortestPath[end];
    delete[] shortestPath;
    delete[] visited;

    return ret;
}

// Floyd's algorithm between two specific points is unnecessary, just run dijkstra's
template<class W>
W GraphAL<W>::floydsShortestPath(const int start, const int end) {
    return dijkstraShortestPath(start, end);
}

// Returns minimum spanning tree of the graph containing the provided vertex.
template<class W>
W GraphAL<W>::prims(const int start) {
    list<int> visited;
    list<int> toVisit;
    list<node_t> edgesUsed;

    for (int i = 0; i < mAList.size(); i++) {
        if (i == start) visited.push_back(i);
        else toVisit.push_back(i);
    }

    while (!toVisit.empty()) {
        list<node_t> validEdges;

        for (typename list<int>::iterator i = visited.begin(); i != visited.end(); i++) {
            for (typename list<node_t>::iterator it = mAList[*i].begin(); it != mAList[*i].end(); it++) {
                for (typename list<int>::iterator j = toVisit.begin(); j != toVisit.end(); j++) {
                    if (it->mEndVertex == *j) { validEdges.push_back((*it)); }
                }
            }
        }

        if (validEdges.size() == 0) break;

        node_t minEdge = *(validEdges.begin());

        for (typename list<node_t>::iterator i = validEdges.begin(); i != validEdges.end(); i++) {
            if (i->mWeight < minEdge.mWeight) {
                    minEdge = *i;
            }
        }

        visited.push_back(minEdge.mEndVertex);
        for (typename list<int>::iterator it = toVisit.begin(); it != toVisit.end(); it++) {
                if (*it == minEdge.mEndVertex) {
                        toVisit.erase(it);
                        break;
                }
        }
        edgesUsed.push_back(minEdge);
    }

    if (edgesUsed.size() == 0) return 0;

    W sum = 0;

    for (typename list<node_t>::iterator i = edgesUsed.begin(); i != edgesUsed.end(); i++) sum += i->mWeight;

    return sum;
}

// Destructor
template<class W>
GraphAL<W>::~GraphAL() {
}

#endif
