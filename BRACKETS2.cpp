#include <iostream>
#include <stack>
#include <string>
using namespace std;


bool wellMatched(const string& formula) {
	const string opening("({["), closing(")}]");

	stack<char> openStack;

	for (int i = 0; i < formula.size(); i++) {
		if (opening.find(formula[i]) != -1)
			openStack.push(formula[i]);
		else {
			if (openStack.empty()) return false;

			if (opening.find(openStack.top()) != closing.find(formula[i]))
				return false;

			openStack.pop();
		}
	}
	return openStack.empty();

}

//string check(string str) {
//	stack<char> st;
//	for (int i = 0; i < str.size(); i++) {
//		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
//			st.push(str[i]);
//		else {
//			char t = st.top();
//			st.pop();
//			if (t == '(') t = ')';
//			else if (t == '{') t = '}';
//			else if (t == '[') t = ']';
//			
//			if (t == str[i]) continue;
//			else return "NO";
//
//		}
//	}
//	return "YES";
//}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		string str;
		cin >> str;
		cout << check(str) << endl;

	}
}