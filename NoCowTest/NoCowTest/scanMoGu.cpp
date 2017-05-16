#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
struct Node
{
	Node(int a, int b) :x(a), y(b) {}
	int x;
	int y;
};
#define SIZE 21
int gra[SIZE][SIZE];
int dirx[] = { 0, -1, 1,  0,  0,  -1, -1,  1, 1 };
int diry[] = { 0, 0,  0, -1,  1,  -1,  1, -1, 1 };
int n, m, k;
inline bool check(int x, int y)
{
	return (x < 0 || x >= n || y < 0 || y >= m) ?
		false : true;
}
int scan(int x, int y, vector<Node> &v)
{
	int sum = 0;
	for (int i = 0; i < 9; i++) {
		int a = x + dirx[i];
		int b = y + diry[i];
		if (check(a, b)) {
			if (gra[a][b] > 0) {
				--gra[a][b];
				++sum;
				v.emplace_back(a, b);
			}
		}
	}
	return sum;
}

void recovery(vector<Node> &v)
{
	for (auto &nd : v) {
		++gra[nd.x][nd.y];
	}
}
void print()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << setw(3) << gra[i][j];
		cout << endl;
	}
}
int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	while (cin >> n >> m >> k) {
		memset(gra, 0, sizeof(gra));
		for (int i = 0; i < k; i++) {
			int x, y;
			cin >> x >> y;
			--x; --y;
			++gra[x][y];
		}
		print();
		int x1, y1, x2, y2;
		int ans = 0;
		for (x1 = 0; x1 < n; x1++)
			for (y1 = 0; y1 < m; y1++) {
				vector<Node> v1;
				int c = scan(x1, y1, v1);
				for (x2 = 0; x2 < n; x2++)
					for (y2 = 0; y2 < m; y2++) {
						vector<Node> v2;
						int d = scan(x2, y2, v2);
						ans = std::max(ans, c + d);
						recovery(v2);
					}
				recovery(v1);
			}
		cout << ans << endl;
	}
}