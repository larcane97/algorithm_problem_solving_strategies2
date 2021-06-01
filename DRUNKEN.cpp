#include <iostream>
#include <vector>
#include<map>
#include <algorithm>
using namespace std;

const int INF = 987654321;
const int MAX_V = 500;
int V, E, T;
int adj[MAX_V][MAX_V];
int W[MAX_V][MAX_V];
int delays[MAX_V];


void input() {
	cin >> V >> E;

	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			adj[i][j] = INF;

	for (int i = 0; i < V; i++)
		cin >> delays[i];

	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a][b] = c;
		adj[b][a] = c;
	}
	
}



void solve() {
	input();
	vector<pair<int, int>>order;

	for (int i = 0; i<V; i++)
		order.push_back(make_pair(delays[i], i));
	sort(order.begin(), order.end());

	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			if (i == j) W[i][j] = 0;
			else W[i][j] = adj[i][j];
	
	for (int k = 0; k < V; k++) {
		int w = order[k].second;
		for(int i=0;i<V;i++)
			for (int j = 0; j < V; j++) {
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				if (w == i || w == j) continue;
				W[i][j] = min( adj[i][w] + delays[w] + adj[w][j], W[i][j]);
			}
	}

	cin >> T;
	for (int i = 0; i < T; i++) {
		int a, b;
		cin >> a >> b;
		cout << W[a][b] << "\n";
	}

}

int main() {
	solve();

}