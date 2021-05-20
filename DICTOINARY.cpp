#include <iostream>
#include <vector>
using namespace std;

int toNumber(const char& ch) {
	return ch - 'a';
}

vector<vector<int>>adj;


void makeGraph(const vector<string>& words) {
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	for (int j = 1; j < words.size(); j++) {
		int i = j - 1, len = min(words[i].size(), words[j].size());

		for (int k = 0; k < len; k++) {
			if (words[i][k] != words[j][k]) {
				int a = toNumber(words[i][k]);
				int b = toNumber(words[j][k]);
				adj[a][b] = 1;
				break;
			}
		}
	}
}

vector<int> seen, order;

void dfs(int here) {
	seen[here] = 1;

	for (int there = 0; there < adj.size(); there++) {
		if (adj[here][there]&& !seen[there])
			dfs(there);
	}
	order.push_back(here);
}

vector<int> topologicalSort() {
	int m = adj.size();
	seen = vector<int>(m, 0);
	order.clear();
	for (int i = 0; i < m; i++) {
		if (!seen[i])
			dfs(i);
	}
	reverse(order.begin(), order.end());

	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			if (adj[order[j]][order[i]])
				return vector<int>();
		}
	}
	return order;

}


int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		vector<string> words;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			words.push_back(s);
		}

		makeGraph(words);
		vector<int>ret = topologicalSort();
		if (ret.size() == 0) cout << "ERROR";
		else
			for (int i = 0; i < ret.size(); i++)
				printf("%c ", ret[i] + 'a');
		cout << endl;

			
	}

}
