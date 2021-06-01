#include <vector>
using namespace std;

const int MAX_V = 50;

int V;
int adj[MAX_V][MAX_V];
int C[MAX_V][MAX_V][MAX_V];

void allPairShortestPath1() {
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			if (i != j)
				C[0][i][j] = min(adj[i][j], adj[i][0] + adj[0][i]);
			else
				C[0][i][j] = 0;

	for (int k = 1; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				C[k][i][j] = min(C[k - 1][i][j], C[k - 1][i][k] + C[k - 1][k][j]);

}


// memory optimized
int V;
int adj[MAX_V][MAX_V];

void floyd() {
	for (int i = 0; i < V; i++) adj[i][i] = 0;
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	
}

// 경로 저장

int V;
int adj[MAX_V][MAX_V];
int via[MAX_V][MAX_V];

void floyd2() {
	for (int i = 0; i < V; i++) adj[i][i] = 0;
	memset(via, -1, sizeof(via));
	for(int k=0;k<V;k++)
		for(int i=0;i<V;i++)
			for(int j=0;j<V;j++)
				if (adj[i][j] > adj[i][k] + adj[k][j]) {
					via[i][j] = k;
					adj[i][j] = adj[i][k] + adj[k][j];
				}

}

void reconstruct(int u, int v, vector<int>& path) {
	if (via[u][v] == -1) {
		path.push_back(u);
		if (u != v) path.push_back(v);
	}
	else {
		int w = via[u][v];
		reconstruct(u, w, path);
		path.pop_back();
		reconstruct(w, v, path);
	}
}
