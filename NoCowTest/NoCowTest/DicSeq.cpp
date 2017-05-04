#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void reverse(string &str, int L)
{
	for (int i = L; i <= (L + str.size()-1) / 2; ++i)
		swap(str[i], str[str.size() - (i - L + 1)]);
}
void perm(string &str)
{
	while (true) {
		cout << str << endl << endl;
		int i = str.size() - 1;
		int j = 0;
		while (i>0) {
			if (str[i] > str[i - 1])
				break;
			i--;
		}
		i--;
		if (i < 0) break;
		for (j = str.size() - 1; j > i && str[j] <= str[i]; j--)
			;
		swap(str[i], str[j]);
		reverse(str, i + 1);
	}
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	string str;
	while (cin >> str) {
		sort(str.begin(), str.end());
		perm(str);
	}
	return 0;
}