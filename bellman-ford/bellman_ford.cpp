#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <utility>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace BellmanFord {

vector<vector<pair<int, double>>> adj;
const int n = 32000, m = 237805;
const int s = 1; // source node index
int n_tmp, m_tmp;
vector<double> dist;

const double INF = numeric_limits<double>::infinity();

void BellmanFord(int n, int s, const vector<vector<pair<int, double>>>& adj, vector<double>& dist) {
    dist.assign(n + 1, INF);
    dist[s] = 0.0;  // the source has distance 0

    for (int i = 1; i <= n; ++i) {
        for (int u = 1; u <= n; ++u) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                double weight = edge.second;
                if (dist[u] != INF && dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 1; u <= n; ++u) {
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            double weight = edge.second;
            if (dist[u] != INF && dist[v] > dist[u] + weight) {
                cerr << "Graph contains a negative-weight cycle" << endl;
                return;
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

}

#ifndef MAIN_FILE
int main() {
    stringstream ss;
    // ss << "../results/adj_" << BellmanFord::n << "_" << BellmanFord::m << "_neg.txt";
    ss << "../results/adj_" << BellmanFord::n << "_" << BellmanFord::m << ".txt";
    string filename = ss.str();

    BellmanFord::load_adj_from_file(filename);

    cout << "n = " << BellmanFord::n << ", m = " << BellmanFord::m << endl;

    auto start = high_resolution_clock::now();
    BellmanFord::BellmanFord(BellmanFord::n, BellmanFord::s, BellmanFord::adj, BellmanFord::dist);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start);
    cout << "Bellman-Ford function execution time: " << duration.count() << " nanoseconds" << endl;

    // BellmanFord::print_dist(BellmanFord::s, BellmanFord::dist);
    
    return 0;

}

#endif