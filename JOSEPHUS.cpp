#include <iostream>
#include <vector>
#include <list>
using namespace std;


int n, k;

void josephus(){
	list<int> survivors;
	for (int i = 1; i <= n; i++) survivors.push_back(i);

	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
	
		kill = survivors.erase(kill);
		if (kill == survivors.end()) kill == survivors.begin();

		n--;
		for (int i = 0; i < k - 1; i++) {
			kill++;
			if (kill == survivors.end()) kill = survivors.begin();
		}
	}

	cout << survivors.front() << " " << survivors.back() << endl;
}


int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		cin >> n >> k;
		josephus();
	}
}
