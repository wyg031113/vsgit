#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;
#define N 302
#define M 102
int C[M];
double P[N][M];
double dp[M][N];
int main()
{
	int n, m;
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	while (cin >> n >> m) {
		for (int i = 1; i <= m; i++)
			cin >> C[i];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> P[i][j];

		memset(dp, 0, sizeof(dp));
		for (int j = 0; j <=m; j++)
			dp[j][C[j]] = 1;

		for(int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (C[j] != 0) {
					dp[j][0] = dp[j][0] + dp[j][1] * P[i][j];
					for (int k = 1; k <= C[j]; k++) {
						dp[j][k] = dp[j][k + 1] * P[i][j] + dp[j][k] * (1 - P[i][j]);
					}
				}
			}
		double E = 0;
		int sum = 0;
		for (int i = 1; i <= m; i++) {
			sum += C[i];
			for (int j = 0; j <= C[i]; j++) {
				E += dp[i][j] * j;
			}
		}
		E = sum - E;
		cout << setiosflags(ios::fixed)<<setprecision(1) << E << endl;
	}
	return 0;
}