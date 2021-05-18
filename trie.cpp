#include <cstring>

const int alphabets = 26;
int tonumber(char ch) { return ch - 'a'; };

struct trienode {
	trienode* children[alphabets];
	bool terminal;

	trienode() : terminal(false) {
		memset(children, 0, sizeof(children));
	}

	~trienode() {
		for (int i = 0; i < alphabets; i++)
			if (children[i])
				delete children[i];
	}

	void insert(const char* key) {
		if (*key == 0)
			terminal = true;
		else {
			int next = tonumber(*key);
			if (children[next] == NULL)
				children[next] = new trienode();
			children[next]->insert(key + 1);
		}
	}

	trienode* find(const char* key) {
		if (*key == 0) return this;
		int next = tonumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}


};