# CSCI315

## Summary
This repository includes all necessary source code, screenshots, and documentation for the CSCI-315 program required for the Senior Portfolio for student 163119.

## What the program does
This program is essentially a library for creating a Graph with Adjacency Lists.  It allows another program to create Graphs with or without a known number of vertices, add vertices, remove a vertex, add/remove edges, and traverse the graph both via breadth first and depth first algorithms.  Additionally it can return the weight value of the shortest path using either Dijkstra's or Floyd's algorithm's or return the weight of the minimum spanning tree using Prim's algorithm.

## How to compile it
*NOTE:* This program is **not** intended to be run as an independent program, but instead as a component within a larger program.  A test program (main.cpp) has been included to demonstrate the program being run successfully and what outputs it can provide.
*NOTE:* These instructions assume standard Linux OS and terminal.
1. Open terminal
1. cd {INSTALL DIR}/src
1. g++ -o {executable file name} -g -I . graphal.cpp main.cpp
