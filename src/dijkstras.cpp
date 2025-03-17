#include "dijkstras.h"
#include <algorithm>
#include <queue>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visted(numVertices, false);
    distances[source] = 0;
    previous[source] = -1;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({source, 0});

    while(!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();

        if (visted[u]) continue;
        visted[u] = true;

        for(Edge e: G[u]){
            int v = e.dst;
            int weight = e.weight;

            if(!visted[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    for (int i : v)
        cout << i << " ";
    cout << endl;
    cout << "Total cost is " << total << endl;
}