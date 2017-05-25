#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class AscentSequence {
public:
	int binary_find_max(vector<int> & cnts, int n, int val)
	{
		int L = 1, R = n;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (cnts[mid] >= val) {
				R = mid - 1;
			}
			else {
				L = mid + 1;
			}
		}
		return L - 1;
	}
	void print(vector<int> &v)
	{
		for (auto x : v)
			cout << x << " ";
		cout << endl;
	}
	int findLongest(vector<int> A, int n) {
		// write code here
		vector<int> dp(n, 0);
		vector<int> cnts(n + 1, 0x7fffffff);
		int ans = 0;
		cnts[0] = 0;
		for (int i = 0; i < n; i++) {
			//int t = binary_find_max(cnts, i, A[i]);
			int t = 0;
			auto ite = std::lower_bound(cnts.begin() + 1, cnts.begin() + i + 1, A[i]);
			if (ite != cnts.begin())
				t = ite - cnts.begin() - 1;
			dp[i] = t + 1;
			cnts[dp[i]] = min(cnts[dp[i]], A[i]);
			ans = max(ans, dp[i]);
		}//end for
		// print(dp);
		// print(cnts);
		return ans;
	}
};
#ifdef LOCAL
int main()
{
	AscentSequence asx;
	vector<int> vec = { 2, 1, 4, 3, 1, 5, 6 };
	//vector<int> vec = {157,232,6};
	cout << asx.findLongest(vec, vec.size()) << endl;
	return 0;
}
#endif