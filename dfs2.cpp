#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>>adj;
vector<int>discovered, finished;
int time;
void dfs2(int here) {
	discovered[here] = ++time;
	for (int i = 0; i< adj[here].size(); i++) {
		int there = adj[here][i];
		if (discovered[there] == -1) {
			printf("[%d %d] is %s", here, there, "tree");
			dfs2(there);
		}
		else {
			if (discovered[here] < discovered[there])
				printf("[%d %d] is %s", here, there, "forward");
			else if(!finished[there])
				printf("[%d %d] is %s", here, there, "backward");
			else
				printf("[%d %d] is %s", here, there, "cross");
		}
	}
	finished[here] = 1;
}

vector<vector<int>>adj;
vector<int>discovered;
vector<bool> isCutvertex;
int time = 0;

int findCutVertex(int here, bool isRoot=true) {
	discovered[here] = ++time;
	int ret = discovered[here];
	int children = 0;
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		if (discovered[there] == -1) {
			children++;
			int subtree = findCutVertex(there, false);
			if (!isRoot && subtree >= discovered[here])
				isCutvertex[here] = true;
			ret = min(ret, subtree);
		}
		else
			ret = min(ret, discovered[there]);
	}
	if (isRoot) isCutvertex[here] = (children >= 2);
	return ret;

}