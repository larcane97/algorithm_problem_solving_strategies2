#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>>graph;
vector<int> seen;


bool makeGraph(vector<string>& words) {
	int m = words.size();
	int degreeCount = 0;
	graph = vector<vector<int>>(m, vector<int>(m, 0));
	seen = vector<int>(m, 0);
	for (int j = 0; j < m; j++) {
		for (int i = 0; i < m; i++) {
			if (i == j) continue;

			int a_end = words[j][words[j].size() - 1] - 'a';
			int b_first = words[i][0] - 'a';
			if (a_end == b_first) {
				graph[j][i] = 1;
				degreeCount++;
			}
		}
	}
	return  degreeCount != 0 && degreeCount % 2 == 0;
}


void solve(int here,vector<int>& ret) {
	seen[here] = 1;
	for (int there = 0; there < graph.size(); there++) {
		if (graph[here][there] > 0 && !seen[there]) {
			graph[here][there]--;
			graph[there][here]--;
			solve(there, ret);
		}
	}
	ret.push_back(here);
}



int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n;
		cin >> n;
		vector<string>words(n);
		for (int i = 0; i < n; i++)
			cin >> words[i];

		if (makeGraph(words)) {
			vector<int>ret;
			solve(0, ret);
			reverse(ret.begin(), ret.end());
			for (int i = 0; i < ret.size(); i++)
				cout << words[ret[i]] << " ";
			cout << endl;
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}
		

	}
	
}


