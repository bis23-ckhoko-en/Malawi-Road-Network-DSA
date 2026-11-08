
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include <limits>
#include <tuple>
using namespace std;

// Structure for a road connecting two towns
struct Road {
    int destination;
    int distance;
};

// Structure for roads used in Kruskal's algorithm
struct Edge {
    int start, end, distance;
};

// Graph class represents the Malawi road network
class Graph {
public:
    vector<string> towns;
    map<string, int> townNumber;
    vector<vector<Road>> adjacencyList;
    vector<Edge> roads;

    int addTown(string name) {
        if (townNumber.count(name))
            return townNumber[name];

        int id = towns.size();
        townNumber[name] = id;
        towns.push_back(name);
        adjacencyList.push_back({});
        return id;
    }

    void addRoad(string a, string b, int distance) {
        int u = addTown(a);
        int v = addTown(b);

        // Roads are assumed to be two-way
        adjacencyList[u].push_back({v, distance});
        adjacencyList[v].push_back({u, distance});

        roads.push_back({u, v, distance});
    }

    int findTown(string name) {
        if (townNumber.count(name))
            return townNumber[name];
        return -1;
    }

    void buildGraph() {
        // Road data: Town A, Town B, Distance in kilometres
        vector<tuple<string, string, int>> data = {
            {"Chitipa", "Karonga", 110},
            {"Karonga", "Rumphi", 150},
            {"Rumphi", "Mzuzu", 68},
            {"Mzuzu", "Nkhata Bay", 50},
            {"Mzuzu", "Mzimba", 65},
            {"Mzimba", "Kasungu", 165},
            {"Kasungu", "Lilongwe", 130},
            {"Kasungu", "Dowa", 80},
            {"Dowa", "Lilongwe", 55},
            {"Kasungu", "Nkhotakota", 115},
            {"Nkhotakota", "Salima", 100},
            {"Salima", "Lilongwe", 100},
            {"Salima", "Dedza", 100},
            {"Lilongwe", "Mchinji", 110},
            {"Lilongwe", "Dedza", 85},
            {"Dedza", "Ntcheu", 65},
            {"Ntcheu", "Mwanza", 70},
            {"Ntcheu", "Balaka", 90},
            {"Mwanza", "Blantyre", 91},
            {"Balaka", "Liwonde", 40},
            {"Balaka", "Mangochi", 70},
            {"Liwonde", "Mangochi", 75},
            {"Liwonde", "Zomba", 55},
            {"Zomba", "Blantyre", 65},
            {"Blantyre", "Thyolo", 40},
            {"Blantyre", "Mulanje", 70},
            {"Thyolo", "Mulanje", 45},
            {"Blantyre", "Chikwawa", 50},
            {"Chikwawa", "Nsanje", 100}
        };

        for (auto road : data) {
            addRoad(get<0>(road), get<1>(road), get<2>(road));
        }
    }
};

// Dijkstra's algorithm finds the shortest route
void dijkstra(Graph &g, int start, int finish) {
    const int INF = numeric_limits<int>::max();

    int n = g.towns.size();
    vector<int> distance(n, INF);
    vector<int> previous(n, -1);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        if (currentDistance != distance[current])
            continue;

        for (const Road &road : g.adjacencyList[current]) {
            int newDistance = currentDistance + road.distance;

            if (newDistance < distance[road.destination]) {
                distance[road.destination] = newDistance;
                previous[road.destination] = current;

                pq.push({newDistance, road.destination});
            }
        }
    }

    if (distance[finish] == INF) {
        cout << "No route exists between these towns.\n";
        return;
    }

    vector<int> path;

    for (int current = finish; current != -1;
         current = previous[current]) {
        path.push_back(current);
    }

    reverse(path.begin(), path.end());

    cout << "\nSHORTEST ROUTE\n";

    for (int i = 0; i < path.size(); i++) {
        cout << g.towns[path[i]];

        if (i < path.size() - 1)
            cout << " -> ";
    }

    cout << "\nTotal distance: "
         << distance[finish] << " km\n";
}

// Disjoint Set class helps Kruskal detect cycles
class DisjointSet {
    vector<int> parent, rankValue;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rankValue.assign(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findRoot(int x) {
        if (parent[x] != x)
            parent[x] = findRoot(parent[x]);

        return parent[x];
    }

    bool unite(int a, int b) {
        a = findRoot(a);
        b = findRoot(b);

        if (a == b)
            return false;

        if (rankValue[a] < rankValue[b])
            swap(a, b);

        parent[b] = a;

        if (rankValue[a] == rankValue[b])
            rankValue[a]++;

        return true;
    }
};

// Kruskal's algorithm finds a minimum spanning tree
void kruskal(Graph &g) {
    vector<Edge> sortedRoads = g.roads;

    sort(sortedRoads.begin(), sortedRoads.end(),
         [](Edge a, Edge b) {
             return a.distance < b.distance;
         });

    DisjointSet sets(g.towns.size());

    int totalDistance = 0;
    int selectedRoads = 0;

    cout << "\nMINIMUM SPANNING TREE - KRUSKAL'S ALGORITHM\n";

    for (const Edge &road : sortedRoads) {
        if (sets.unite(road.start, road.end)) {
            cout << "SELECT: "
                 << g.towns[road.start] << " - "
                 << g.towns[road.end] << " ("
                 << road.distance << " km)\n";

            totalDistance += road.distance;
            selectedRoads++;
        }
    }

    cout << "\nNumber of selected roads: "
         << selectedRoads << endl;

    cout << "Total MST distance: "
         << totalDistance << " km\n";

    if (selectedRoads != (int)g.towns.size() - 1)
        cout << "The graph is disconnected.\n";
}

int main() {
    Graph graph;
    graph.buildGraph();

    cout << "====================================\n";
    cout << "       MALAWI ROAD NETWORK\n";
    cout << "====================================\n";

    cout << "Towns loaded: " << graph.towns.size() << endl;
    cout << "Roads loaded: " << graph.roads.size() << endl;

    int choice;

    do {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Find shortest route (Dijkstra)\n";
        cout << "2. Find minimum spanning tree (Kruskal)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            return 1;
        }

        if (choice == 1) {
            string startTown, finishTown;

            cout << "Enter starting town: ";
            cin >> ws;
            getline(cin, startTown);

            cout << "Enter destination town: ";
            getline(cin, finishTown);

            int start = graph.findTown(startTown);
            int finish = graph.findTown(finishTown);

            if (start == -1 || finish == -1) {
                cout << "Town not found. Check spelling and capital letters.\n";
            } else {
                dijkstra(graph, start, finish);
            }
        }
        else if (choice == 2) {
            kruskal(graph);
        }
        else if (choice == 3) {
            cout << "Thank you for using the program!\n";
        }
        else {
            cout << "Invalid choice. Enter 1, 2 or 3.\n";
        }

    } while (choice != 3);

    return 0;
}
