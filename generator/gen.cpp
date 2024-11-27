// generate random graph with n vertices.
#include <iostream>
#include <random>
#include <iomanip>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

const int n = 10;
int m;
const bool neg = true;

// Use the adjacent table to represent the direct graph
// each pair includes target vertex and the weight of the correspoing edge
vector<pair<int, double>> adj[n + 1];  // don't consider 0, reduce the risk of errors
int fa[n + 1];  // father

std::mt19937 rnd(time(0));

bool random_bool(int x, int y) {
    std::uniform_int_distribution<int> dist(1, y);
    return dist(rnd) <= x;
}

double random_weight(double min_weight, double max_weight) {
    std::uniform_real_distribution<double> dist(min_weight, max_weight);
    return dist(rnd);
}

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

void save_adj_to_file(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << n << " " << m << endl;
        for (int i = 1; i <= n; i++) {
            for (auto& edge : adj[i]) {
                int j = edge.first;
                double weight = edge.second;
                if (i < j) {
                    file << i << " " << j << " " << weight << endl;
                }
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

int main() {
    for(int i = 1; i <= n; i++) fa[i] = i;

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if (random_bool(static_cast<int>(10 * log2(n)), 10 * n)) {
                double weight = random_weight(0.0, 10.0); // weight range [0.0, 10.0)
                if (neg)
                    weight -= 0.03;
                adj[i].emplace_back(j, weight);
                adj[j].emplace_back(i, weight);
                m++, merge(i, j);
            }
        }
    }

    // make sure the graph is connected
    for(int i = 2; i <= n; i++) {
        if(find(i) != find(1)) {
            std::uniform_int_distribution<int> dist(1, i - 1);
            int j = dist(rnd);
            double weight = random_weight(0.0, 10.0);
            if (neg)
                weight -= 0.03;
            adj[i].emplace_back(j, weight);
            adj[j].emplace_back(i, weight);
            m++, merge(i, j);
        }
    }

    stringstream ss;
    if (!neg)
        ss << "../results/adj_" << n << "_" << m << ".txt";
    else
        ss << "../results/adj_" << n << "_" << m << "_neg.txt";
    string filename = ss.str();

    save_adj_to_file(filename);

    // // test: print the edges
    cout << "n = " << n << ", m = " << m << endl;
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

    return 0;
}