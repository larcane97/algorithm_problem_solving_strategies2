#include <iostream>
#include <vector>
using namespace std;


const int INF = 987654321;
const int MAX_V = 200;

int adj[MAX_V][MAX_V];
int V, M, N;

void floyd() {
	
	for(int k=0;k<V;k++)
		for(int i=0;i<V;i++)
			for (int j = 0; j < V; j++) 
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

}

bool update(int a, int b, int c) {
	if (adj[a][b] <= c) return false;
	for (int x = 0; x < V; x++)
		for (int y = 0; y < V; y++)
			// adj[x][y] = ������ �ּ� �Ÿ�
			// adj[x][a] + c + adj[b][y] = x~a �Ÿ� + �߰��� ������ �Ÿ� + b~y �Ÿ�
			// adj[x][b] + c + adj[a][y] = x~b �Ÿ� + �߰��� ������ �Ÿ� + a~y �Ÿ�
			// �߿��� �ּҰ����� ����
			adj[x][y] = min(adj[x][y],
				min(adj[x][a] + c + adj[b][y], adj[x][b] + c + adj[b][y])
			);
	return true;
}

void solve() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		cin >> V >> M >> N;

		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (i == j) adj[i][j] = 0;
				else adj[i][j] = INF;

		for (int i = 0; i < M; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			adj[a][b] = c;
			adj[b][a] = c;
		}

		floyd();

		int ret = 0;
		for (int i = 0; i < N; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			if (!update(a, b, c))ret++;
		}
		cout << ret << "\n";

	}
}

int main() {
	solve();
}