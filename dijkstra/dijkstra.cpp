#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <utility>
#include <sstream>

using namespace std;

vector<vector<pair<int, double>>> adj;
const int n = 10, m = 11;
const int s = 1; // source node index
int n_tmp, m_tmp;
vector<double> dist;

const double INF = numeric_limits<double>::infinity();

void Dijkstra(int n, int s, const vector<vector<pair<int, double>>>& adj, vector<double>& dist) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> heap;

    dist.assign(n + 1, INF);
    dist[s] = 0.0;

    heap.emplace(0.0, s);

    while (!heap.empty()) {
        int u = heap.top().second;
        double dist_u = heap.top().first;
        heap.pop();

        // if (dist_u > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            double weight = edge.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                heap.emplace(dist[v], v);
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
    ss << "../results/adj_" << n << "_" << m << ".txt";
    string filename = ss.str();

    load_adj_from_file(filename);

    // // test - Passed!
    // cout << "n = " << n << ", m = " << m << endl;
    // cout << fixed << setprecision(2);
    // for (int i = 1; i <= n; i++) {
    //     for (auto& edge : adj[i]) {
    //         int j = edge.first;
    //         double weight = edge.second;
    //         if (i < j) {
    //             cout << "Edge (" << i << ", " << j << "), weight = " << weight << endl;
    //         }
    //     }
    // }

    Dijkstra(n, s, adj, dist);

    print_dist(s, dist);

    return 0;
}