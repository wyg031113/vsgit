#include <iostream>
#include <map>
#include <stack>
#include <string>
using namespace std;
class ChkExpression {
public:
	bool chkLegal(string A) {
		// write code here
		
		A.append("#");
		string left = "[,{,(";
		string right = "],},)";
		string  arth = "+-*/#";
		map<char, int> pri;
		pri['+'] = 1;
		pri['-'] = 1;
		pri['*'] = 2;
		pri['/'] = 2;
		pri['#'] = 0;
		map<char, char> mp;
		mp[']'] = '[';
		mp['}'] = '{';
		mp[')'] = '(';
		stack<char> op;
		stack<char> num;
		for (int i = 0; i < A.size(); i++) {
			if (left.find(A[i]) != string::npos) { //²Ù×÷·û
				op.push(A[i]);
			}
			else if (right.find(A[i]) != string::npos) {
				while (true) {
					if (op.top() == mp[A[i]]) {
						op.pop();
						break;
					}
					if (arth.find(op.top()) == string::npos || num.size() < 2)
						return false;
					num.pop();
					num.pop();
					num.push('x');
					op.pop();
				}
			}
			else if (arth.find(A[i]) != string::npos) {
				while (!op.empty() && arth.find(op.top()) != string::npos && pri[A[i]] <= pri[op.top()]) {
					if (num.size() < 2)
						return false;
					op.pop();
					num.pop();
					num.pop();
					num.push('x');
				}
				op.push(A[i]);


			}
			else { //Êý
				num.push(A[i]);
			}
		}
		if (op.size() == 1 && op.top() == '#' && num.size() == 1 &&
			arth.find(num.top()) == string::npos &&
			left.find(num.top()) == string::npos &&
			right.find(num.top()) == string::npos)
			return true;
		else
			return false;
	}
};
int main()
{
	string str = "1+1";
	ChkExpression ce;
	while (cin >> str) {
		cout << ce.chkLegal(str) << endl;
	}
}



