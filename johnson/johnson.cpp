#define MAIN_FILE
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <utility>
#include <sstream>
#include <queue>
#include "../bellman-ford/bellman_ford.cpp"
#include "../dijkstra/dijkstra.cpp"

using namespace std;

namespace Johnson {

const double INF = numeric_limits<double>::infinity();

vector<vector<pair<int, double>>> adj;
const int n = 100, m = 279;
int n_tmp, m_tmp;
vector<vector<double>> all_pairs_dist(n + 1, vector<double>(n + 1, INF));

void Johnson(int n, const vector<vector<pair<int, double>>>& adj) {
    vector<vector<pair<int, double>>> adj_prime = adj;
    vector<double> h(n + 1, 0.0);  // h = dist = phi (feasible potential)
    vector<double> dist(n + 1, INF);

    // Add a new source vertex s' with edges (s', v) of weight 0
    for (int v = 1; v <= n; ++v) {
        adj_prime[0].emplace_back(v, 0.0);
    }

    // Run Bellman-Ford to find the feasible potentials
    BellmanFord::BellmanFord(n, 1, adj_prime, h);

    // Reweight the edges
    for (int u = 1; u <= n; ++u) {
        for (auto& edge : adj_prime[u]) {
            int v = edge.first;
            edge.second += h[u] - h[v];
        }
    }

    // Run Dijkstra for each vertex
    for (int u = 1; u <= n; ++u) {
        Dijkstra::Dijkstra(n, u, adj_prime, dist);
        for (int v = 1; v <= n; ++v) {
            if (dist[v] < INF) {
                all_pairs_dist[u][v] = dist[v] + h[v] - h[u];
            }
        }
    }

}

void load_adj_from_file(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> n_tmp >> m_tmp;
        if (n != n_tmp || m != m_tmp) cerr << "The data in that file doesn't match your request!" << endl;
        adj.resize(n + 1);
        int u, v;
        double weight;
        while (file >> u >> v >> weight) {
            adj[u].emplace_back(v, weight);
            adj[v].emplace_back(u, weight);
        }
        file.close();
    } else {
        cerr << "Unable to open file for reading." << endl;
    }
}

void print_dist(int s, const vector<double>& dist) {
    cout << "Distances from source node " << s << ": " << endl;
    for (size_t i = 1; i < dist.size(); ++i) {
        cout << "Node " << i << ": " << dist[i] << endl;
    }
}

void print_all_pair_dist() {
    // Print all-pairs shortest paths
    for (int u = 1; u <= n; ++u) {
        print_dist(u, all_pairs_dist[u]);
    }
}

}

int main() {
    stringstream ss;
    ss << "../results/adj_" << Johnson::n << "_" << Johnson::m << ".txt";
    string filename = ss.str();

    Johnson::load_adj_from_file(filename);

    Johnson::Johnson(Johnson::n, Johnson::adj);

    Johnson::print_all_pair_dist();

    return 0;
}

