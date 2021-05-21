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
	// �ڽŰ� �ڽ��� �ڽ� ���(tree edge)�� ��� ����
	st.push(here);
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];

		if (discovered[there] == -1)
			ret = min(ret, scc(there));
		// there�� ���� �߰ߵǾ���( discovered[there] < discovered[here] )
		// scc�� �и����� ���� ���( finished[there] = false => back edge )
		// back edge�̹Ƿ� �ּ� ��ġ�� ����
		else if (sccId[there] == -1)
			ret = min(ret, discovered[there]);
	}
	// for���� ���� ��, ret = �ڽŰ� ����� ��� edge�� �湮�� back edge �� ���� ���� �ö� �� �ִ� �� ����
	
	// �ڽ� ��忡�� �ִ밡 �ڽ��� ���,
	// �ڽŰ� �ڽ��� �ڽĳ�带 �ϳ��� ssc�� ����
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

