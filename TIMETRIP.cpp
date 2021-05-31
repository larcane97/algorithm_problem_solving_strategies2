#include <iostream>
#include <vector>
using namespace std;

int V;
const int MAX_V = 100;
const int INF = 987654321;
vector<pair<int, int>>adj[MAX_V];
bool reachable[MAX_V][MAX_V];

int bellman2(int src, int target) {
	vector<int>upper(V, INF);
	upper[src] = 0;

	for (int iter = 0; iter < V-1; iter++) {
		for (int here = 0; here < V; here++) {
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;

				upper[there] = min(upper[there], cost + upper[here]);

			}
		}
	}

	for (int here = 0; here < V; here++) {
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;

			if (upper[here] + cost < upper[there]) {
				if (reachable[src][here] && reachable[here][target])
					return -INF;
			}
		}
	}
	return upper[target];
}


void input() {
	for (int i = 0; i < MAX_V; i++) adj[i].clear();
	int W;
	cin >> V >> W;
	for (int i = 0; i < W; i++) {
		int a, b, d;
		cin >> a >> b >> d;
		adj[a].push_back(make_pair(b, d));
	}

}


int solve() {
	input();
	
	int shortest = bellman2(0, 1);
	if (shortest != -INF) cout << "UNREACHABLE" << endl;
	else {
		cout << shortest << " ";
		for (int i = 0; i < V; i++)
			for (int j = 0; j < adj[i].size(); j++)
				adj[i][j] = make_pair(adj[i][j].first, -adj[i][j].second);

		int longest = bellman2(0, 1);
		if (longest == -INF) cout << "INFINITY";
		else cout << longest << endl;
	}
}


int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {

	}
}