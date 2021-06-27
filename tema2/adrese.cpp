#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Person {
  string name;
  vector<string> emails;
};

int find_parent(int node, vector<int> parent) {
  // parcurg iterativ pana ajung la parintele adevarat
  for (; node != parent[node]; node = parent[node]) {
  	continue;
  }

  return node;
}

void do_union(int node1, int node2, vector<int> &parent, vector<Person> &people,
              vector<int> &height) {
  int p1 = find_parent(node1, parent);
  int p2 = find_parent(node2, parent);
  if (p1 != p2) {
    if (height[p1] > height[p2]) {
      parent[p2] = p1;
      // alegem numele cel mai mic lexicografic
      if (people[p1].name > people[p2].name) {
        people[p1].name = people[p2].name;
      }
    } else if (height[p2] > height[p1]) {
      parent[p1] = p2;
      if (people[p2].name > people[p1].name) {
        people[p2].name = people[p1].name;
      }
    } else {
      parent[p2] = p1;
      if (people[p1].name > people[p2].name) {
        people[p1].name = people[p2].name;
      }
      // crestem inaltimea arborelui
      height[p1]++;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);  // pentru viteza
  int n, j, nr_adrese, i;
  string nume, adresa;
  vector<Person> people;
  unordered_map<string, vector<int>> mail_to_ids;
  vector<int> chosen_nodes;

  ifstream fin("adrese.in");
  ofstream fout("adrese.out");
  fin >> n;
  vector<int> parent;
  i = 0;
  do {
  	parent.push_back(i);
  	i++;
  } while (i < n);

  vector<int> height(n, 0);

  i = 0;
  do {
    fin >> nume;
    fin >> nr_adrese;

    Person new_person;
    new_person.name = nume;
    vector<string> list;
    new_person.emails = list;
    people.push_back(new_person);

    j = 0;
    do {
    	fin >> adresa;
    	mail_to_ids[adresa].push_back(i);
    	j++;
    } while (j < nr_adrese);

    i++;
  } while (i < n);

  for (auto &element : mail_to_ids) {
    // unim nodurile 2 cate 2
    int length = element.second.size();
    for (i = 1; i < length; i++) {
      do_union(element.second[i - 1], element.second[i], parent, people,
               height);
    }

    int p = find_parent(element.second[0], parent);
    people[p].emails.push_back(element.first);
  }

  for (i = 0; i < n; i++) {
    if (find_parent(i, parent) == i) {
      chosen_nodes.push_back(i);
      // pun indicii intr-un vector separat
    }
  }

  int length = chosen_nodes.size();
  fout << length << "\n";

  // sortez conform criteriilor din enunt
  sort(chosen_nodes.begin(), chosen_nodes.end(),
       [&people](int a, int b) -> bool {
         if (people[a].emails.size() != people[b].emails.size()) {
           return people[a].emails.size() < people[b].emails.size();
         }
         return people[a].name < people[b].name;
       });

  for (i = 0; i < length; i++) {
    fout << people[chosen_nodes[i]].name;
    fout << " ";
    fout << people[chosen_nodes[i]].emails.size() << "\n";
    // sortez lexicografic la final adresele de email folosite
    sort(people[chosen_nodes[i]].emails.begin(),
         people[chosen_nodes[i]].emails.end());
    for (auto el : people[chosen_nodes[i]].emails) {
      fout << el << "\n";
    }
  }
  fin.close(); fout.close();
  return 0;
}
