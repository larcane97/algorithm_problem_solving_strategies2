#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>


using namespace std;

const int ALPHABETS = 26;

int toNumber(const char ch) { return ch - 'A'; }


struct TrieNode {
	TrieNode* children[ALPHABETS];
	int terminal;
	int first;

	TrieNode() :first(-1),terminal(-1) {
		memset(children, 0, sizeof(children));
	}

	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}
	

	void insert(const char* key,int id) {
		if (first == -1) first = id;
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			if (children[next] == NULL)
				children[next] = new TrieNode();
			children[next]->insert(key + 1,id);
		}
	}

	int type(const char* key, int id) {
		if (*key == 0) return 0;
		if (first == id) return 1;
		
		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}



	TrieNode* find(const char* key) {
		if (*key == 0)
			return this;
		
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);

	}

};

int countKeys(TrieNode* trie, const char* word) {
	TrieNode* node = trie->find(word);
	if (node == NULL || node->terminal == -1) return strlen(word);

	return trie->type(word, node->terminal);
}

TrieNode* readInput(int words) {
	vector<pair<int, stssring>> input;
	for (int i = 0; i < words; i++) {
		char buf[11];
		int freq;
		scanf("%s %d", buf, &freq);
		input.push_back(make_pair(-freq, buf));
	}
	sort(input.begin(), input.end());

	TrieNode* trie = new TrieNode();
	for (int i = 0; i < words; i++)
		trie->insert(input[i].second.c_str(), i);
	trie->first = -1;
	return trie;
}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n, m;
		cin >> n >> m;
		TrieNode* trie = readInput(n);
		int ret = 0;
		for (int i = 0; i < m; i++) {
			char word[11];
			scanf("%s", word);
			ret += countKeys(trie, word);
		}
		cout << ret << endl;
	}
}