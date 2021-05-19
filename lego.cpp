#include<bits/stdc++.h>
using namespace std;
int k, n, t;
vector<int> final_solution;
int max_dimensions = INT_MIN;

bool check(vector<int> &solution, vector<int> &domain) {
    if (domain[solution[0]] == 1) {
        int sz_solution = solution.size();
        int dp_size = t * domain[solution[sz_solution - 1]];
        vector<int> dp(dp_size + 1, INT_MAX);
        for (int i = 0; i < sz_solution; i++) {
            dp[domain[solution[i]]] = 1;
        }
        for (int i = 1; i <= dp_size; i++) {
            if (dp[i] != 1) {
                for (int j = sz_solution - 1; j >= 1; j--) {
                    if (i % domain[solution[j]] == 0) {
                        dp[i] = i / domain[solution[j]];
                        break;
                    }
                }
                // find the minimum for every solution
                for (int j = sz_solution - 1; j >= 0; j--) {
                    if (domain[solution[j]] < i) {
                        dp[i] = min(dp[i], 1 + dp[i - domain[solution[j]]]);
                    }
                }
            }
        }
        int max_seq_dp = INT_MIN;
        int contor = 0;
        for (int i = 1; i <= dp_size; i++) {
            if (dp[i] <= t) {
                contor++;
                if (i == dp_size) {
                    if (contor > max_seq_dp) {
                        max_seq_dp = contor;
                    }
                }
            } else {
                if (contor > max_seq_dp) {
                    max_seq_dp = contor;
                }
                contor = 0;
            }
        }
        if (max_seq_dp > max_dimensions) {
            max_dimensions = max_seq_dp;
            vector<int> tmp_sol;
            for (int i = 0; i < sz_solution; i++) {
                tmp_sol.push_back(domain[solution[i]]);
            }
            final_solution = tmp_sol;
        }
        return true;
    }
    return false;
}

void back(int step, int stop, vector<int> &domain,
        vector<int> &solution) {
    if (step == stop) {
        check(solution, domain);
        return;
    }
    unsigned i = step > 0 ? solution[step - 1] + 1 : 0;
    for (; i < domain.size(); ++i) {
        solution[step] = i;
        back(step + 1, stop, domain, solution);
    }
}

int main() {
    ifstream fin("lego.in");
    fin >> k >> n >> t;
    vector<int> domain(k), solution(n);
    for (int i = 0; i < k; ++i) {
        domain[i] = i + 1;
    }
    back(0, n, domain, solution);
    ofstream fout("lego.out");
    fout << max_dimensions << endl;
    int fsz = final_solution.size();
    for (int i = 0; i < fsz; i++) {
        fout << final_solution[i] << " ";
    }
    fout << endl;
}
