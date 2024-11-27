#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <utility>
#include <sstream>

using namespace std;

namespace BellmanFord {

vector<vector<pair<int, double>>> adj_b;
const int n_b = 100, m_b = 291;
const int s_b = 1; // source node index
int n_b_tmp, m_b_tmp;
vector<double> dist_b;

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
    for (int u = 1; u <= n_b; ++u) {
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
        file >> n_b_tmp >> m_b_tmp;
        if (n_b != n_b_tmp || m_b != m_b_tmp) cerr << "The data in that file doesn't match your request!" << endl;
        adj_b.resize(n_b + 1);
        int u, v;
        double weight;
        while (file >> u >> v >> weight) {
            adj_b[u].emplace_back(v, weight);
            adj_b[v].emplace_back(u, weight);
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
    ss << "../results/adj_" << BellmanFord::n_b << "_" << BellmanFord::m_b << "_neg.txt";
    string filename = ss.str();

    BellmanFord::load_adj_from_file(filename);

    BellmanFord::BellmanFord(BellmanFord::n_b, BellmanFord::s_b, BellmanFord::adj_b, BellmanFord::dist_b);

    BellmanFord::print_dist(BellmanFord::s_b, BellmanFord::dist_b);

    return 0;

}

#endif