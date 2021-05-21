#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>>adj;
vector<int>sccId;
vector<int> discovered;

stack<int>st;

int sccCounter, vertextCounter;

int scc(int here) {
	int ret = discovered[here] = vertextCounter++;
	// 자신과 자신의 자식 노드(tree edge)를 모두 저장
	st.push(here);
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];

		if (discovered[there] == -1)
			ret = min(ret, scc(there));
		// there이 먼저 발견되었고( discovered[there] < discovered[here] )
		// scc로 분리되지 않은 경우( finished[there] = false => back edge )
		// back edge이므로 최소 위치를 저장
		else if (sccId[there] == -1)
			ret = min(ret, discovered[there]);
	}
	// for문이 끝난 후, ret = 자신과 연결된 모든 edge를 방문해 back edge 중 가장 높이 올라갈 수 있는 값 저장
	
	// 자식 노드에서 최대가 자신일 경우,
	// 자신과 자신의 자식노드를 하나의 ssc로 구성
	if (ret == discovered[here]) {
		while (true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t == here) break;
		}
		sccCounter++;
	}
	return ret;
}

vector<int> tarjanSCC() {
	sccId = discovered = vector<int>(adj.size(), -1);
	sccCounter = vertextCounter = 0;

	for (int i = 0; i < adj.size(); i++)
		if (discovered[i] == -1) scc(i);

	return sccId;
}

