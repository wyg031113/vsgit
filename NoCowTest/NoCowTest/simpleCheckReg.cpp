#include <iostream>
#include <map>
#include <string>
#include <stack>
using namespace std;
class ChkExpression {
public:
	bool chkLegal(string A)
	{
		stack<char> stack;
		for (int i = 0; i < A.size(); i++)
		{
			if (A[i] == '{' || A[i] == '(' || A[i] == '[')
			{
				stack.push(A[i]);
			}
			else if (A[i] == '}' || A[i] == ')' || A[i] == ']')
			{
				int a = stack.size();
				if (a < 1)return false;

				else stack.pop();
			}
		}
		if (stack.size() > 0)
			return false;
		return true;
	}
};



int main()
{
	ChkExpression ce;
	string s;
	while (cin >> s) {
		cout << ce.chkLegal(s) << endl;
	}
}