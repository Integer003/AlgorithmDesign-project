#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

namespace MinSumProduct {

const int n = 100, m = 279;
int n_tmp, m_tmp;
vector<vector<double>> dist;

const double INF = numeric_limits<double>::infinity();

vector<vector<double>> MinSumProduct(const vector<vector<double>>& dist, int n) {
    vector<vector<double>> result = dist;
    for (int k = 0; k < n; ++k) {
        vector<vector<double>> temp(n, vector<double>(n, INF));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int l = 0; l < n; ++l) {
                    if (result[i][l] < INF && dist[l][j] < INF) {
                        temp[i][j] = min(temp[i][j], result[i][l] + dist[l][j]);
                    }
                }
            }
        }
        result = temp;
    }
    return result;
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
    ss << "../results/adj_" << MinSumProduct::n << "_" << MinSumProduct::m << ".txt";
    string filename = ss.str();

    MinSumProduct::load_adj_from_file(filename);

    auto result = MinSumProduct::MinSumProduct(MinSumProduct::dist, MinSumProduct::n);

    MinSumProduct::print_dist(result);

    return 0;
}
