#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class Expression {
public:
	const int MOD = 10007;
	int dp[151][151][2];
	int ec(int a, int b, char op) {
		switch (op) {
		case '&':
			return a && b;
		case '|':
			return a || b;
		case '^':
			return ((a ^ b) != 0);
			throw "bad op";
		}
		return 0;
	}
	void calc(int i, int j, int k, char op)
	{
		for (int a = 0; a < 2; a++)
			for (int b = 0; b < 2; b++) {
				int c = ec(a, b, op);
				dp[i][j][c] += (dp[i][k][a] * dp[k + 1][j][b]) % MOD;
				dp[i][j][c] %= MOD;
			}
	}
	int countWays(string exp, int len, int ret) {
		// write code here

		memset(dp, 0, sizeof(dp));
		string A;
		string B;
		for (int i = 0; i < len; i++) {
			if (i & 1) {
				B += exp.substr(i, 1);
			}
			else {
				A += exp.substr(i, 1);
			}
		}
		for (int i = 0; i < A.size(); i++)
			for (int k = 0; k < 2; k++)
				dp[i][i][k] = ((A[i] - '0') == k);

		for (int step = 2; step <= A.size(); step++) {
			for (int i = 0; i < A.size(); i++) {
				int j = i + step - 1;
				if (j >= A.size())
					break;
				for (int k = i; k < j; k++) {
					calc(i, j, k, B[k]);
				}
			}
		}
		return dp[0][A.size() - 1][ret];
	}
};

#ifdef LOCAL
int main()
{
	Expression exp;
	cout << exp.countWays("1^0|0|1", 7, 0) << endl;
}
#endif