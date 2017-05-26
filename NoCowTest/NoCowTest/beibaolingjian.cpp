#include<iostream>
#include<vector>
using namespace std;

class Exchange {
public:
	int countWays(vector<int> changes, int n, int x) {
		vector<int> dp(x+1, 0);
		dp[0] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = changes[i]; j <= x; j++) {
				dp[j] += dp[j - changes[i]];
			}//end for
		}// end for
		return dp[x];
	}
};

#ifdef LOCAL
int main()
{
	Exchange exc;
	vector<int> vec = { 158, 259, 312, 378, 778, 1033, 2239, 2449, 3503, 3927, 4009, 4521, 4583, 4774, 4943, 5051, 5350, 5377, 5517, 5901, 6017, 6057, 6073, 6954, 6972, 7109, 7321, 7433, 7841, 7928, 8063, 8079, 8181, 8300, 8561, 8658, 8675, 8695, 8725, 9034, 9223, 9362, 9502, 9506, 9563 };
	int tar = 8503; //ans = 472
	//vector<int> vec = { 5, 10, 25, 1 };
	//int tar = 15; //ans = 6
	cout << exc.countWays(vec, vec.size(), tar) << endl;
	return 0;
}
#endif