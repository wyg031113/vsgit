#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <string.h>
using namespace std;
#define N 5005

//int mp[N][N];
map<int, vector<int>> mp;
int girls[N];
bool vis[N];
int dist[N];
int n, m;
#define INF (0x0FFFFFFF)
struct Node
{
	Node(int vex = 0, int dist = 0) :v(vex), d(dist) {}
	int v;
	int d;
};
bool operator<(const Node &a, const Node &b)
{
	return a.d > b.d;
}
void dijkstra()
{
	priority_queue<Node> Q;
	Q.emplace(1, girls[1]);
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
		vis[i] = false;
	}
	dist[1] = girls[1];
	while (!Q.empty()) {
		Node nd = Q.top();
		Q.pop();
		if (vis[nd.v]) continue;
		vis[nd.v] = true;
		for (int j = 0; j < mp[nd.v].size() ; j++) {
			int i = mp[nd.v][j];
			if (!vis[i] && dist[nd.v]   < dist[i] - girls[i]) {
				dist[i] = dist[nd.v] + girls[i];
				Q.push(Node(i, dist[i]));
			}
		}
	}
	cout << dist[n] << endl;
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	while (cin >> n >> m) {
		mp.clear();
		int i;
		for (i = 1; i <= n; i++)
			cin >> girls[i];
		for (int i = 1; i <= m; i++) {
			int x, y;
			cin >> x >> y;
			mp[x].push_back(y);// [y] = 1;
			mp[y].push_back(x);// [x] = 1;
		}
		dijkstra();
	}
	return 0;
}