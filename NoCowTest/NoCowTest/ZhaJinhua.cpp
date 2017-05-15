#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
string puke = "234567891JQKA";
bool parse_puke(const string &s, vector<int> &v)
{
	for (int i = 0; i < s.size(); i++) {
		int k = puke.find(s[i]);
		if (k == string::npos)
			return false;
		if (k == 8 && (s.size() < i+2 || s[i + 1] != '0'))
			return false;
		v.push_back(k);
		if (k == 8)
			i++;
	}
	if (v.size() != 3)
		return false;
	return true;
}
int get_type_sort(vector<int> &v)
{
	int t = 4;
	sort(v.begin(), v.end());
	if (v[0] == v[1] && v[1] == v[2])
		t = 1;
	if (v[0] + 1 == v[1] && v[1] + 1 == v[2])
		t = 2;
	if (v[0] == v[1] || v[1] == v[2])
		t = 3;
	

	if (t == 3) {
		if (v[0] == v[1])
			swap(v[0], v[2]);
	}
	return t;
}
int cmp_same_type(const vector<int> &v1, const vector<int> &v2, int t)
{
	int i;

	for (i = 2; i >= 0; i--)
		if (v1[i] != v2[i])
			break;
	if (i < 0)
		return 0;
	if (v1[i] < v2[i])
		return -1;
	else
		return 1;
}
int cmp_puke(vector<int> &v1, vector<int> &v2)
{
	int t1 = get_type_sort(v1);
	int t2 = get_type_sort(v2);
	if (t1 < t2)
		return 1;
	else if (t2 < t1)
		return -1;
	return cmp_same_type(v1, v2, t1);
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	string s1, s2;
	while (cin >> s1 >> s2) {
		vector<int> v1, v2;
		bool b1 = parse_puke(s1, v1);
		bool b2 = parse_puke(s2, v2);
		if (!b1 || !b2) {
			cout << "-2" << endl;
			continue;
		}
		
		int ans = cmp_puke(v1, v2);
		cout << ans << endl;
	}
}