#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class Mixture {
public:
	bool dfs(string &a, string &b, string &c, int i, int j, int k)
	{
#ifdef LOCAL
		cout << i << " " << j << " " << k << endl;
#endif
		if (i == n_ && j == m_ && k == v_)
			return true;
		bool ans = false;
		if (i < n_ && k < v_ && c[k] == a[i])
			ans = dfs(a, b, c, i + 1, j, k + 1);
		if (!ans && j < m_ && k < v_ && c[k] == b[j])
			ans = dfs(a, b, c, i, j + 1, k + 1);
		return ans;
	}
	bool dp_calc(string &A, int n, string &B, int m, string &C, int v)
	{
		if (n + m != v)
			return false;
		memset(dp, 0, sizeof(dp));
		dp[0][0] = true;
		for(int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++) {
				if (i == 0 && j == 0)
					dp[i][j] = 1;
				else if (i == 0) {
					dp[i][j] = (B[j-1] == C[j-1] && dp[i][j - 1]);
				}
				else if (j == 0) {
					dp[i][j] = (A[i-1] == C[i-1] && dp[i - 1][j]);
				}
				else {
					dp[i][j] = ((B[j-1] == C[i+j-1] && dp[i][j - 1]) ||
						        (A[i-1] == C[i+j-1] && dp[i - 1][j]));
				}
			}
		return dp[n][m];
	}
#ifdef LOCAL
	void show(int n, int m)
	{
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= m; j++)
				cout << dp[i][j];
			cout << endl;
		}
	}
#endif
	bool chkMixture(string A, int n, string B, int m, string C, int v) {
		// write code here
		n_ = n;
		m_ = m;
		v_ = v;
		bool b = false;
		b = dfs(A, B, C, 0, 0, 0);
		//b =  dp_calc(A, n, B, m, C, v);
#ifdef LOCAL
		show(n, m);
#endif
		return b;

	}
private:
	int n_;
	int m_;
	int v_;
	int dp[101][101];
};
#ifdef LOCAL
int main()
{
	string a = "bcbccabccacccbcac";
	string b = "abbbacaabccbccaaaabbcbcbaaacccbaaba";
	string c = "babbbacaabccbccaaaabbcbcbaaacccbaabacbccabccacccbcac";
	Mixture mix;
	cout << mix.chkMixture(a, 17, b, 35, c, 52) << endl;

}
#endif