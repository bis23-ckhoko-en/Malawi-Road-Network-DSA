# Malawi Road Network – DSA Assignment group 14

## 1. Project Overview

This project implements a road network system for Malawi using C++ and Data Structures and Algorithms (DSA).

The system represents towns as vertices and roads as weighted edges. The weights represent distances between towns in kilometres.

The project demonstrates how graph algorithms can be used to solve real-world transportation problems.

## 2. Algorithms Used

### Dijkstra's Shortest Path Algorithm

Dijkstra's algorithm is used to find the shortest distance between two towns in the road network.

### Kruskal's Minimum Spanning Tree (MST)

Kruskal's algorithm is used to find the Minimum Spanning Tree, connecting all towns with the minimum possible total road distance without creating cycles.

## 3. Data Structures Used

- Graph
- Adjacency List
- Edge List
- Priority Queue
- Disjoint Set Union (DSU)
- Vectors

## 4. Technologies Used

- Programming Language: C++
- Compiler: GCC / G++
- Development Environment: Visual Studio Code or Dev-C++

## 5. Project Features

- Represents a road network using a weighted graph.
- Finds the shortest route between two towns.
- Calculates the shortest distance in kilometres.
- Generates a Minimum Spanning Tree.
- Handles invalid inputs and file errors.


## 6. Project Files

- `malawi_roads.cpp` – Main C++ source code containing the road network data and algorithms.
- `README.md` – Project documentation.


## 7. How to Compile and Run

No external data file is required because the road network data is stored directly in the C++ program.

Compile using:

```bash
g++ -std=c++17 malawi_roads.cpp -o malawi_roads
```

Run on Windows:

```bash
malawi_roads.exe
```

On Linux:

```bash
./malawi_roads
```

## 8. Data Format

The road network data uses the following format:

```text
Town1,Town2,Distance
```

Distances are measured in kilometres.

## 9. Conclusion

This project demonstrates the practical application of graph theory and graph algorithms in solving transportation and road network problems in Malawi.

