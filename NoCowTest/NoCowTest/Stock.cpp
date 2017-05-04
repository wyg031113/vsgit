#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
class Stock {
public:
	int maxProfit(vector<int> prices, int n) {
		// write code here
		if (n == 1)
			return 0;
		if (n == 2)
			return abs(prices[1] - prices[0]);
		vector<int> v1, v2;
		v1.push_back(0);
		v2.push_back(0);
		int low1 = prices[0];
		int high = prices[n - 1];
		for (int i = 1; i < n; i++) {
			v1.push_back(max(v1[i-1], prices[i] - low1));
			low1 = min(low1, prices[i]);

			v2.push_back(max(v2[i-1], high - prices[n - i - 1]));
			high = max(high, prices[n - i - 1]);
		}
		int ans = 0;
		for (int i = 1; i < n - 1; i++) {
			ans = max(ans, v1[i] + v2[n-i - 1]);
		}
		return ans;
	}
	int maxProfit2(vector<int> prices, int n) {
		// write code here
		if (n == 1)
			return 0;
		if (n == 2)
			return abs(prices[1] - prices[0]);
		memset(dp, 0, sizeof(dp));
		for (int j = 1; j <= 2; j++) {
			int maxv = dp[0][j - 1] - prices[0];
			for (int i = 1; i <= n; i++) {
				dp[i][j] = std::max(dp[i - 1][j], maxv + prices[i-1]);
				maxv = std::max(maxv, dp[i][j - 1] - prices[i-1]);
			}
		}
		return dp[n][2];
	}
private:
	int dp[501][3];
};
int main()
{
	Stock sk;
	cout << sk.maxProfit2({ 10,22,5,75,65,80 }, 6) << endl;
}