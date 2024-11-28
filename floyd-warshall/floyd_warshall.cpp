#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace FloydWarshall {

const int n = 2000, m = 10750;
int n_tmp, m_tmp;
vector<vector<double>> dist;

const double INF = numeric_limits<double>::infinity();

void FloydWarshall(int n, vector<vector<double>>& dist) {  // really easy to implement!
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

void load_adj_from_file(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file >> n_tmp >> m_tmp;
        if (n != n_tmp || m != m_tmp) cerr << "The data in that file doesn't match your request!" << endl;
        dist.assign(n, vector<double>(n, INF));
        for (int i = 0; i < n; ++i) dist[i][i] = 0.0;
        int u, v;
        double weight;
        while (file >> u >> v >> weight) {
            dist[u-1][v-1] = weight;
            dist[v-1][u-1] = weight;
        }
        file.close();
    } else {
        cerr << "Unable to open file for reading." << endl;
    }
}

void print_dist(const vector<vector<double>>& dist) {
    cout << "All-pairs shortest paths:" << endl;
    for (size_t i = 0; i < dist.size(); ++i) {
        cout << "Distances from source node " << i + 1 << endl;
        for (size_t j = 0; j < dist[i].size(); ++j) {
            if (dist[i][j] == INF) {
                cout << "Node " << j + 1 << ": INF" << endl;
            } else {
                cout << "Node " << j + 1 << ": " << dist[i][j] << endl;
            }
        }
        cout << endl;
    }
}

}

int main() {
    stringstream ss;
    ss << "../results/adj_" << FloydWarshall::n << "_" << FloydWarshall::m << ".txt";
    string filename = ss.str();

    FloydWarshall::load_adj_from_file(filename);

    cout << "n = " << FloydWarshall::n << ", m = " << FloydWarshall::m << endl;

    auto start = high_resolution_clock::now();
    FloydWarshall::FloydWarshall(FloydWarshall::n, FloydWarshall::dist);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start);
    cout << "Floyd-Warshall function execution time: " << duration.count() << " nanoseconds" << endl;

    // FloydWarshall::print_dist(FloydWarshall::dist);

    return 0;
}
