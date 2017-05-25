#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class MonoSum {
public:
	void merge_sort(vector<int> &A, int L, int R)
	{
		if (R - L <= 0)
			return;
		int mid = (L + R) >> 1;
		merge_sort(A, L, mid);
		merge_sort(A, mid + 1, R);
		vector<int> vx;
		int i = L;
		int j = mid + 1;
		int tsum = 0;
		while (i <= mid && j <= R) {
			
			if (A[i] <= A[j]) {
				tsum += A[i];
				vx.push_back(A[i++]);
			}
			else {
				vx.push_back(A[j]);
				sum += tsum;
				j++;
			}
			
		}
		while (i <= mid) {
			vx.push_back(A[i++]);
		}
		if(j<=R)
			sum += tsum *(R-j+1);
		while (j <= R) {
			vx.push_back(A[j++]);
		}
		std::copy(vx.begin(), vx.end(), A.begin() + L);
	}
	int calcMonoSum(vector<int> A, int n) {
		// write code here

		sum = 0;
		merge_sort(A, 0, n - 1);
		return sum;
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (A[j] <= A[i])
					ans += A[j];
			}
		}
		return ans;
	}
	int sum;
};

#ifdef LOCAL
int main()
{
	vector<int> vec = { 1,5,3,2,6,4 };
	MonoSum ms;
	cout << ms.calcMonoSum(vec, vec.size()) << endl;
}
#endif