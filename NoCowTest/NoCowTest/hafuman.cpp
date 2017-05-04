#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
using namespace std;
struct Element
{
	Element(char a = 0, int b = 0, Element *L = NULL, Element *R = NULL) :
		c(a), n(b), left(L), right(R) {}
	char c;
	int n;
	Element *left;
	Element *right;
};
struct Ele_Cmp
{
	bool operator()(const Element *a, Element *b)
	{
		return a->n > b->n;
	}
};

void dfs(Element *root, map<char, int> &mp, int &sum, int deep)
{
	if (root == NULL)
		return;
	if (root->left == NULL && root->right == NULL) {
		sum += mp[root->c] * deep;
	}
	dfs(root->left, mp, sum, deep + 1);
	dfs(root->right, mp, sum, deep + 1);
	delete root;
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	string str;
	while (cin >> str) {
		map<char, int> mp;
		for (auto s : str) {
			++mp[s];
		}
		priority_queue<Element *, vector<Element*>, Ele_Cmp> Q;
		for (auto &ite : mp) {
			Q.push(new Element(ite.first, ite.second));
		}
		while (Q.size() > 1) {
			Element *a = Q.top();
			Q.pop();
			Element *b = Q.top();
			Q.pop();
			Element *c = new Element(0, a->n + b->n, a, b);
			Q.push(c);
		}
		int sum = 0;
		dfs(Q.top(), mp, sum, 0);
		cout << sum << endl;
	}
	return 0;
}