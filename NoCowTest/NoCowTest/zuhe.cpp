#include <iostream>
#include <list>
using namespace std;
list<int> ls;
int n = 5;
int m = 3;
void dfs(int k)
{
	if (ls.size() > m)
		return;
	if (k==n) {
		for (auto x : ls)
			cout << x << " ";
		cout << endl;
		return;
	}
	
	dfs(k + 1);
	//for (int j = k; j < n; j++) {
		ls.push_back(k);
		dfs(k+1);
		ls.pop_back();
//	}
}
int main()
{
	while(cin >> n >> m)
	dfs(0);
	return 0;
}