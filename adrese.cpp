#include <bits/stdc++.h>
#define NMAX 1001
using namespace std;

struct Person {
    string name;
    unordered_set<string> mails;
};

struct GoodPerson {
    string name;
    set<string> mails;
    GoodPerson(string _name, set<string> _mails)
        : name(_name)
        , mails(_mails) {}
};

struct ComparePersons {
    bool operator()(GoodPerson a, GoodPerson b) {
    int sza = a.mails.size();
    int szb = b.mails.size();
    if (sza != szb)
        return sza <= szb;
    else
        return a.name.compare(b.name) <= 0;
    }
};

class Task {
 public:
    void solve() {
        read_input();
        adrese();
    }

 private:
    int n;
    unordered_map<int, Person> persons;
    unordered_map<string, int> mail_person;
    set<string> temp_set_mails;
    string min_name;
    vector<int> adj[NMAX];
    void read_input() {
        ifstream fin("adrese.in");
        fin >> n;
        int k, i, j;
        string name, mail;
        for (i = 0; i < n; ++i) {
            fin >> name >> k;
            Person person;
            person.name = name;
            for (j = 0; j < k; ++j) {
                fin >> mail;
                if (mail_person.find(mail) != mail_person.end()) {
                    adj[mail_person[mail]].push_back(i);
                    adj[i].push_back(mail_person[mail]);
                } else {
                    mail_person.insert(make_pair(mail, i));
                    person.mails.insert(mail);
                }
            }
            persons[i] = person;
        }
        fin.close();
    }

    void DFS_rec(int node, int *visited, int connected_comp) {
        visited[node] = connected_comp;
        temp_set_mails.insert(persons[node].mails.begin(),
            persons[node].mails.end());
        if (min_name.empty()) {
            min_name = persons[node].name;
        } else {
            if (persons[node].name.compare(min_name) <= 0) {
                min_name = persons[node].name;
            }
        }
        int sz_node = adj[node].size(), i;
        for (i = 0; i < sz_node; ++i) {
            if (visited[adj[node][i]] == 0) {
                DFS_rec(adj[node][i], visited, connected_comp);
            }
        }
    }

    int DFS(set<GoodPerson, ComparePersons> &final_person) {
        int visited[n] = {};
        int connected_comp = 1, i;
        for (i = 0; i < n; ++i) {
            if (visited[i] == 0) {
                temp_set_mails.clear();
                min_name.clear();
                DFS_rec(i, visited, connected_comp);
                final_person.insert(GoodPerson(min_name, temp_set_mails));
                connected_comp++;
            }
        }
        return connected_comp - 1;
    }

    void adrese() {
        set<GoodPerson, ComparePersons> final_persons;
        ofstream fout("adrese.out");
        int number_size = DFS(final_persons);
        fout << number_size << endl;
        set<GoodPerson, ComparePersons>::iterator iterator_person;
        set<string>::iterator iterator_mails;
        stringstream solution;
        for (iterator_person = final_persons.begin();
            iterator_person != final_persons.end(); iterator_person++) {
            solution << iterator_person->name << " "
                << iterator_person->mails.size() << endl;
            for (iterator_mails = iterator_person->mails.begin();
                iterator_mails != iterator_person->mails.end();
                iterator_mails++) {
                solution << *iterator_mails << endl;
            }
        }
        fout << solution.str();
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
