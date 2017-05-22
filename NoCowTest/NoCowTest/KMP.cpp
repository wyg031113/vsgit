#include <iostream>
#include <string>
#include <vector>
using namespace std;
void build_pre(const string &pat, vector<int> &pre)
{
	pre.push_back(-1);
	for (int i = 1; i < pat.size(); i++) {
		int j = i - 1;
		while (j != 0) {
			if (pat[pre[j] + 1] == pat[i])
				break;
			j = pre[j];
		}
		pre.push_back(pre[j] + 1);
	}
}
int kmp(const string &str, const string &pat, const vector<int> &pre, int &num)
{
	int i = 1, j = 1;
	while (i < str.size()) {
		if (j == pat.size()) {
			num++;
			j = pre[j-1] + 1;
			if (j == 0) j++;
			continue;
		}
		if (str[i] == pat[j]) {
			i++;
			j++;
		}
		else {
			int k = j - 1;
			while (k != 0) {
				if (pat[pre[k] + 1] == str[i])
					break;
				k = pre[k];
			}
			j = pre[k] + 1 + 1;
			i++;
		}
	}
	if (j == pat.size()) {
		num++;
		return i - j + 1;
	}
	else
		return -1;
}
/*
void show(const vector<int> &v)
{
	for (auto x : v) {
		cout << x << " ";
	}
	cout << endl;
}
*/
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	int T;
	string str, pat;
	cin >> T;
	while (T-- && cin >> pat >> str) {
		str = " " + str;
		pat = " " + pat;
		vector<int> pre;
		build_pre(pat, pre);
		//show(pre);
		int num = 0;
		int index = kmp(str, pat, pre, num);
		cout << num << endl;
		/*if (index == -1) {
			cout <<0<< endl;
		}
		else {
			cout << index << endl;
		}*/
	}
}