#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <utility>
#include <sstream>

using namespace std;

vector<vector<pair<int, double>>> adj;
const int n = 100, m = 513;
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

int main() {
    stringstream ss;
    ss << "../results/adj_" << n << "_" << m << "_neg.txt";
    string filename = ss.str();

    load_adj_from_file(filename);

    BellmanFord(n, s, adj, dist);

    print_dist(s, dist);

    return 0;

}