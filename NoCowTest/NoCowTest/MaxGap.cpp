#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class MaxGap {
public:
	int findMaxGap(vector<int> A, int n) {
		// write code here
		/*vector<int> left;
		vector<int> right;
		left.push_back(A[0]);
		right.push_back(A[n - 1]);
		for (int i = 1; i <= n - 1; i++) {
			left.push_back(max(left[i - 1], A[i]));
		}
		for (int i = n - 2; i >= 0; i--) {
			right.push_back(max(right[n - i - 2], A[i]));
		}
		int ans = 0;
		for (int k = 0; k <= n - 2; k++)
			ans = max(ans, abs(left[k] - right[n - k - 2]));
		return ans;*/
		return *std::max_element(A.begin(), A.end()) - std::min(A[0], A[n - 1]);
	}
};
#ifdef LOCAL
int main()
{
	MaxGap mg;
	vector<int> A = { 28,75,38,44,66,1 };
	cout << mg.findMaxGap(A, A.size()) << endl;
	return 0;
}
#endif