#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;



int f(const vector<string>arr) {
	string first = arr[0];

	int move = 0;
	int arrSize = arr.size();
	int size = first.size();
	
	for (int j = 0; j < arrSize-1; j++) {
		if (j % 2 == 0) {
			while (first != arr[j+1]) {
				char tmp = first[size - 1];
				for (int i = size-1; i >0; i--) {
					first[i] = first[i - 1];
				}
				first[0] = tmp;
				move++;
			}
		}
		else {
			while (first != arr[j+1]) {
				char tmp = first[0];
				for (int i = 0; i < size - 1; i++) {
					first[i] = first[i + 1];
				}
				first[size - 1] = tmp;
				move++;
			}
		}
	}
	return move;

}






int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n;
		cin >> n;
		vector<string>arr(n+1);
		for (int i = 0; i <= n; i++) {
			cin >> arr[i];
		}
		cout << f(arr) << endl;

	}
}