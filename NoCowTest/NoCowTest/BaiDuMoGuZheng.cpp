#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define SIZE 21
double mp[SIZE][SIZE];
int N, M, K;
double get_paths(int n, int m)
{
	int i, j;
	mp[0][0] = 1;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			if (mp[i][j] == -1) {
				mp[i][j] = 0;
				continue;
			}
			if (i - 1 >= 0 && mp[i - 1][j] != -1)
				mp[i][j] += mp[i - 1][j] * (j+1>=m ? 1 : 0.5);
			if (j - 1 >= 0 && mp[i][j - 1] != -1)
				mp[i][j] += mp[i][j - 1] *(i+1>=n ? 1 : 0.5);
		}
	return mp[n - 1][m - 1];
}
int main()
{
#ifdef LOCAL_DEBUG
	freopen("input.txt", "r", stdin);
#endif
	while (cin >> N >> M >> K) {
		int x, y;
		memset(mp, 0, sizeof(mp));
		for (int i = 0; i < K; i++) {
			scanf("%d%d", &x, &y);
			mp[x-1][y-1] = -1;
		}
		
		printf("%.2f\n", get_paths(N, M));
	}
	return 0;
}