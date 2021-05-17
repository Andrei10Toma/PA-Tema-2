#include <bits/stdc++.h>
using namespace std;

struct Node {
    int pos_x;
    int pos_y;
    int distance;
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m, start_pos_x, start_pos_y;
    char map[2051][2051];

    void read_input() {
        ifstream fin("poduri.in");
        fin >> n >> m;
        fin >> start_pos_x >> start_pos_y;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                fin >> map[i][j];
            }
        }
    }

    bool is_in_map(int pos_x, int pos_y) {
        return pos_x <= n && pos_x >= 1 && pos_y <= m && pos_y >= 1;
    }

    int poduri() {
        int min_distance = -1;
        vector<vector<Node>> distances(n + 1, vector<Node>(m + 1));
        vector<vector<bool>> visited(n + 1, vector<bool> (m + 1, false));
        queue<Node> bfs_queue;
        // initalise the fields of the starting node
        distances[start_pos_x][start_pos_y].pos_x = start_pos_x;
        distances[start_pos_x][start_pos_y].pos_y = start_pos_y;
        distances[start_pos_x][start_pos_y].distance = 0;
        visited[start_pos_x][start_pos_y] = true;
        // start a BFS on the matrix from the starting position and check if
        // we can exit the matrix from the starting position
        bfs_queue.push(distances[start_pos_x][start_pos_y]);
        while (!bfs_queue.empty()) {
            Node node = bfs_queue.front();
            if (map[node.pos_x][node.pos_y] == 'V') {
                // check if Gigel can go South
                if (is_in_map(node.pos_x + 1, node.pos_y)) {
                    if (map[node.pos_x + 1][node.pos_y] != '.' &&
                        visited[node.pos_x + 1][node.pos_y] == false) {
                        distances[node.pos_x + 1][node.pos_y].pos_x =
                            node.pos_x + 1;
                        distances[node.pos_x + 1][node.pos_y].pos_y =
                            node.pos_y;
                        distances[node.pos_x + 1][node.pos_y].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x + 1][node.pos_y] = true;
                        bfs_queue.push(distances[node.pos_x + 1][node.pos_y]);
                    }
                // exits the matrix so the minimum distance was found
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }
                // check if Gigel can go North
                if (is_in_map(node.pos_x - 1, node.pos_y)) {
                    if (map[node.pos_x - 1][node.pos_y] != '.' &&
                        visited[node.pos_x - 1][node.pos_y] == false) {
                        distances[node.pos_x - 1][node.pos_y].pos_x =
                            node.pos_x - 1;
                        distances[node.pos_x - 1][node.pos_y].pos_y =
                            node.pos_y;
                        distances[node.pos_x - 1][node.pos_y].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x - 1][node.pos_y] = true;
                        bfs_queue.push(distances[node.pos_x - 1][node.pos_y]);
                    }
                // exits the matrix so the minimum distance was found
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }

            } else if (map[node.pos_x][node.pos_y] == 'O') {
                // check if Gigel can go East
                if (is_in_map(node.pos_x, node.pos_y + 1)) {
                    if (map[node.pos_x][node.pos_y + 1] != '.' &&
                        visited[node.pos_x][node.pos_y + 1] == false) {
                        distances[node.pos_x][node.pos_y + 1].pos_x =
                            node.pos_x;
                        distances[node.pos_x][node.pos_y + 1].pos_y =
                            node.pos_y + 1;
                        distances[node.pos_x][node.pos_y + 1].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x][node.pos_y + 1] = true;
                        bfs_queue.push(distances[node.pos_x][node.pos_y + 1]);
                    }
                // exits the matrix so the minimum distance was found
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }
                // check if Gigel can go West
                if (is_in_map(node.pos_x, node.pos_y - 1)) {
                    if (map[node.pos_x][node.pos_y - 1] != '.' &&
                        visited[node.pos_x][node.pos_y - 1] == false) {
                        distances[node.pos_x][node.pos_y - 1].pos_x =
                            node.pos_x;
                        distances[node.pos_x][node.pos_y - 1].pos_y =
                            node.pos_y - 1;
                        distances[node.pos_x][node.pos_y - 1].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x][node.pos_y - 1] = true;
                        bfs_queue.push(distances[node.pos_x][node.pos_y - 1]);
                    }
                // exits the matrix so the minimum distance was found
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }
            } else if (map[node.pos_x][node.pos_y] == 'D') {
                // first check North and South (same in the case 'V')
                if (is_in_map(node.pos_x + 1, node.pos_y)) {
                    if (map[node.pos_x + 1][node.pos_y] != '.' &&
                        visited[node.pos_x + 1][node.pos_y] == false) {
                        distances[node.pos_x + 1][node.pos_y].pos_x =
                            node.pos_x + 1;
                        distances[node.pos_x + 1][node.pos_y].pos_y =
                            node.pos_y;
                        distances[node.pos_x + 1][node.pos_y].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x + 1][node.pos_y] = true;
                        bfs_queue.push(distances[node.pos_x + 1][node.pos_y]);
                    }
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }

                if (is_in_map(node.pos_x - 1, node.pos_y)) {
                    if (map[node.pos_x - 1][node.pos_y] != '.' &&
                        visited[node.pos_x - 1][node.pos_y] == false) {
                        distances[node.pos_x - 1][node.pos_y].pos_x =
                            node.pos_x - 1;
                        distances[node.pos_x - 1][node.pos_y].pos_y =
                            node.pos_y;
                        distances[node.pos_x - 1][node.pos_y].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x - 1][node.pos_y] = true;
                        bfs_queue.push(distances[node.pos_x - 1][node.pos_y]);
                    }
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }
                if (is_in_map(node.pos_x, node.pos_y + 1)) {
                    if (map[node.pos_x][node.pos_y + 1] != '.' &&
                        visited[node.pos_x][node.pos_y + 1] == false) {
                        distances[node.pos_x][node.pos_y + 1].pos_x =
                            node.pos_x;
                        distances[node.pos_x][node.pos_y + 1].pos_y =
                            node.pos_y + 1;
                        distances[node.pos_x][node.pos_y + 1].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x][node.pos_y + 1] = true;
                        bfs_queue.push(distances[node.pos_x][node.pos_y + 1]);
                    }
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }
                // check West and East (same with the case "O")
                if (is_in_map(node.pos_x, node.pos_y - 1)) {
                    if (map[node.pos_x][node.pos_y - 1] != '.' &&
                        visited[node.pos_x][node.pos_y - 1] == false) {
                        distances[node.pos_x][node.pos_y - 1].pos_x =
                            node.pos_x;
                        distances[node.pos_x][node.pos_y - 1].pos_y =
                            node.pos_y - 1;
                        distances[node.pos_x][node.pos_y - 1].distance =
                            distances[node.pos_x][node.pos_y].distance + 1;
                        visited[node.pos_x][node.pos_y - 1] = true;
                        bfs_queue.push(distances[node.pos_x][node.pos_y - 1]);
                    }
                } else {
                    min_distance = distances[node.pos_x][node.pos_y].distance
                        + 1;
                    break;
                }
            }
            bfs_queue.pop();
        }
        return min_distance;
    }

    int get_result() { return poduri(); }

    void print_output(int result) {
        ofstream fout("poduri.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (std::nothrow) Task();
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
