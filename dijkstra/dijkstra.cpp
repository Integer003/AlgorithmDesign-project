#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <utility>
#include <sstream>

using namespace std;

namespace Dijkstra {



vector<vector<pair<int, double>>> adj_d;
const int n_d = 100, m_d = 279;
const int s_d = 1; // source node index
int n_d_tmp, m_d_tmp;
vector<double> dist_d;

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
        file >> n_d_tmp >> m_d_tmp;
        if (n_d != n_d_tmp || m_d != m_d_tmp) cerr << "The data in that file doesn't match your request!" << endl;
        adj_d.resize(n_d + 1);
        int u, v;
        double weight;
        while (file >> u >> v >> weight) {
            adj_d[u].emplace_back(v, weight);
            adj_d[v].emplace_back(u, weight);
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
    ss << "../results/adj_" << Dijkstra::n_d << "_" <<Dijkstra::m_d << ".txt";
    string filename = ss.str();

    Dijkstra::load_adj_from_file(filename);

    // // test - Passed!
    // cout << "n = " << n_d << ", m = " << m_d << endl;
    // cout << fixed << setprecision(2);
    // for (int i = 1; i <= n_d; i++) {
    //     for (auto& edge : adj[i]) {
    //         int j = edge.first;
    //         double weight = edge.second;
    //         if (i < j) {
    //             cout << "Edge (" << i << ", " << j << "), weight = " << weight << endl;
    //         }
    //     }
    // }

    Dijkstra::Dijkstra(Dijkstra::n_d, Dijkstra::s_d, Dijkstra::adj_d, Dijkstra::dist_d);

    Dijkstra::print_dist(Dijkstra::s_d, Dijkstra::dist_d);

    return 0;
}

#endif