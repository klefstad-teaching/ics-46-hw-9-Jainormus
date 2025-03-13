#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("../src/small.txt", G);
    vector<int> previous;
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);
    vector<int> shortest = extract_shortest_path(distance, previous, 3);
    int total_weight = 0;
    for (auto i : shortest) {
        total_weight += distance[i];
    }
    print_path(shortest, total_weight);
}