/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Info
{
	int no;
	int w = 0;
	int h = 0xfffffff;
};
int bin_search(vector<Info> &vec, int n, Info p)
{
	int L = 1, R = n;
	int mid;
	int ans = -1;
	while (L <= R) {
		mid = (L + R) >> 1;
		if (vec[mid].h <= p.h && p.w == vec[mid].w) {
			ans = mid;
			L = mid + 1;
			//break;
		}
		if (vec[mid].h <= p.h && vec[mid].w <= p.w) {
			L = mid + 1;
			ans = mid;
		//	break;
		}
		R = mid - 1;
	}
	return ans;
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int n;
	while (cin >> n) {
		vector<Info> vec;
		for (int i = 0; i < n; i++) {
			Info p;
			cin >> p.no >> p.w >> p.h;
			vec.push_back(p);
		}
		sort(vec.begin(), vec.end(),
			[](const Info &a, const Info &b)
		      {if (a.w == b.w) return a.h < b.h; else return a.w <= b.w; });

		vector<int> dp(n + 1, 0);
		vector<Info> g(n + 1);
		g[0].h = 0;
		int ans = 0;
		for (int i = 0; i < n; i++) {
			dp[i] = 1;
			int k = bin_search(g, i, vec[i]);
			if (k != -1) {
				dp[i] = std::max(dp[i], k + 1);
			}
			if (g[dp[i]].h > vec[i].h)
				g[dp[i]] = vec[i];
			ans = std::max(ans, dp[i]);
			cout << dp[i] << " ";
		}//end for
		cout << ans << endl;
	}//end while
}
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Info
{
	int no;
	int w;
	int h;
};
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int n;
	while (cin >> n) {
		vector<Info> vec;
		for (int i = 0; i < n; i++) {
			Info p;
			cin >> p.no >> p.w >> p.h;
			vec.push_back(p);
		}
		sort(vec.begin(), vec.end(),
			[](const Info &a, const Info &b)
		{if (a.w == b.w) return a.h < b.h; else return a.w <= b.w; });

		vector<int> dp(n + 1, 0);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			dp[i] = 1;
			for (int j = i - 1; j >= 0; j--) {

				if ((vec[j].h <= vec[i].h  && vec[j].w < vec[i].w) ||
					(vec[j].h == vec[i].h && vec[j].w == vec[i].w)) {
					dp[i] = std::max(dp[i], dp[j] + 1);
				}
			}//end for
			cout << dp[i] << " ";
			ans = std::max(ans, dp[i]);
		}//end for
		cout << ans << endl;
	}//end while
}
