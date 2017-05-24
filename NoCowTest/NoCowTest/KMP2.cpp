#include <iostream>
#include <vector>
#include <string>
using namespace std;
class StringPattern {
public:
	void getNext(const string &pat, vector<int> &next) {
		next.clear();
		int lenb = pat.size();
		int j = -1;
		next.push_back(-1);
		for (int i = 1; i < lenb; i++) {
			while (j != -1 && pat[j + 1] != pat[i]) {
				j = next[j];
			}
			if (pat[j + 1] == pat[i])
				j++;
			next.push_back(j);
		}
	}
	int kmp(const string &A, const string &B, const vector<int> &next)
	{
		int j = -1;
		for (int i = 0; i < A.size(); i++) {
			while (j != -1 && A[i] != B[j + 1])
				j = next[j];
			if (A[i] == B[j + 1])
				++j;
			if (j + 1 == B.size())
				return i - j;
		}
		return -1;
	}
	int findAppearance(string A, int lena, string B, int lenb) {
		// write code here
		vector<int> next;
		getNext(B, next);
		return kmp(A, B, next);
	}
};
#ifdef LOCAL
int main()
{
	string A = "abcabcabcdefg";
	string B = "abcabcd";
	StringPattern sp;
	cout << sp.findAppearance(A, A.size(), B, B.size()) << endl;
}
#endif