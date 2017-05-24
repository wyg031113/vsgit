#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Palindrome {
public:
	int getLongestPalindrome(string A, int n) {
		// write code here
		
		vector<char> str;
		for (int i = 0; i < n; i++) {
			str.push_back('#');
			str.push_back(A[i]);
		}
		str.push_back('#');
		n = str.size();
		int pos = 0;
		int maxR = 0;
		int ans = 0;
		vector<int> vec(n, 0);
		for (int i = 0; i < n; i++) {
			if (i <= maxR) {
				vec[i] = min(maxR - i, vec[2 * pos - i]);
			}
			while (i - vec[i] - 1 >= 0 && i + vec[i] + 1 < n) {
				if (str[i - vec[i] - 1] == str[i + vec[i] + 1])
					++vec[i];
				else
					break;
			}
			if (i+vec[i]>maxR) {
				maxR = i + vec[i];
				pos = i;
			}
			ans = max(ans, vec[i]);

		}
		return ans;
	}
};

#ifdef LOCAL
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	string A;
	int len;
	while (cin >> A >> len) {
		Palindrome pa;
		int maxlen = pa.getLongestPalindrome(A, len);
		cout << maxlen << endl;
	}
}
#endif
