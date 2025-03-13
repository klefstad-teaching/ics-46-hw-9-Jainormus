#include "dijkstras.h"
#include <algorithm>

void print_path(const vector<int>& v, int total) {
    for (auto i : v) {
        cout << i << " ";
    }
    cout << "\nTotal cost is " << total << endl;
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.clear();
    previous.resize(n, -1);
    vector<bool> visited(n, false);
    auto cmp = [](const Edge& left, const Edge& right) { return left.weight > right.weight; };
    priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);
    pq.push(Edge(source, source, 0));
    distance[source] = 0;
    while (!pq.empty()) {
        Edge curr = pq.top();
        pq.pop();
        int u = curr.dst;
        if (visited[u]) continue;
        visited[u] = true;
        for (auto e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Edge(u, v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
