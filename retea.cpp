#include <bits/stdc++.h>
#define NMAX 10001
using namespace std;
vector<int> adj[NMAX];
int n, m;
ifstream fin("retea.in");
ofstream fout("retea.out");
vector<int> parent;
vector<int> found;
vector<int> low_link;
vector<int> solution;
unordered_set<int> cvs;
int timestamp;

void read_input() {
    fin >> n >> m;
    parent.resize(n + 1);
    found.resize(n + 1);
    low_link.resize(n + 1);
    solution.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        solution[i] = n - 1;
    }
    int i, x, y;
    for (i = 0; i < m; i++) {
        fin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
}

void DFS(int node) {
    // find the cut vertexes with Tarjan's algorithm
    int children = 0;
    found[node] = ++timestamp;
    low_link[node] = found[node];
    for (int neigh : adj[node]) {
        if (parent[neigh] != -1) {
            if (neigh != parent[node]) {
                low_link[node] = min(low_link[node], found[neigh]);
            }
            continue;
        }
        parent[neigh] = node;
        children++;
        DFS(neigh);
        low_link[node] = min(low_link[node], low_link[neigh]);
        if (parent[node] != node && low_link[neigh] >= found[node]) {
            cvs.insert(node);
        }
    }
    if (parent[node] == node && children > 1) {
        cvs.insert(node);
    }
}

void DFS_restricted(int start_node, int restrict_node, vector<bool> &visited,
    int &number_elements) {
    visited[start_node] = true;
    number_elements++;
    for (int neigh : adj[start_node]) {
        if (neigh != restrict_node && visited[neigh] == false) {
            DFS_restricted(neigh, restrict_node, visited, number_elements);
        }
    }
}

int main() {
    int number_elements = 0;
    read_input();
    for (int i = 1; i <= n; i++) {
        parent[i] = -1;
        found[i] = INT_MAX;
        low_link[i] = INT_MAX;
    }
    for (int i = 1; i <= n; i++) {
        if (parent[i] == -1) {
            parent[i] = i;
            DFS(i);
        }
    }
    for (int el : cvs) {
        // iterate through the graph ignoring the cut vertexes
        vector<bool> visited(n + 1, false);
        for (int i = 1; i <= n; i++) {
            if (i != el && visited[i] == false) {
                // count the elements of the remaining connected components
                number_elements = 0;
                DFS_restricted(i, el, visited, number_elements);
                solution[el] += (n - number_elements) * number_elements;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (cvs.find(i) == cvs.end()) {
            // the node is not a cut vertex so just the calls to him and
            // the calls initiated by him will be lost
            solution[i] += n - 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        fout << solution[i] << endl;
    }
}
