#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
#define N 9
int P[N][N];

void get_input()
{
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			scanf("%d", &P[i][j]);
}
void show_P()
{
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf("%d%c", P[i][j], j == N - 1 ? '\n' : ' ');
	}
}
bool check(int x, int y)
{
	int i, j;
	set<int> s;
	for (i = 0; i < N; i++) { //check row
		if (P[x][i] == 0)
			continue;
		if ( s.find(P[x][i]) != s.end())
			return false;
		else
			s.insert(P[x][i]);
	}

	s.clear();
	for (i = 0; i < N; i++) { //check column
		if (P[i][y] == 0)
			continue;
		if (s.find(P[i][y]) != s.end())
			return false;
		else
			s.insert(P[i][y]);
	}

	s.clear();
	int tx = x / 3 * 3;
	int ty = y / 3 * 3;
	for(i = tx; i < tx + 3; i++)
		for (j = ty; j < ty + 3; j++) {
			if (P[i][j] == 0)
				continue;
			if (s.find(P[i][j]) != s.end())
				return false;
			else
				s.insert(P[i][j]);
		}
	return true;
}
bool stop = false;
void dfs(int x, int y)
{
	//show_P();
	//printf("\n");
	//printf("%d %d\n", x, y);
	if (x == N - 1 && y == N) {
		show_P();
		stop = true;
		return;
	}
	if (y >= N) {
		x++;
		y = 0;
	}
	if (P[x][y] != 0)
		dfs(x, y + 1);
	else {
		for (int i = 1; i <= 9 && ! stop; i++) {
			P[x][y] = i;
			if (check(x, y))
				dfs(x, y + 1);
		}
		P[x][y] = 0;
	}
	
}
int main()
{
#ifdef LOCAL_DEBUG
	freopen("input.txt", "r", stdin);
#endif
	get_input();
	//show_P();
	dfs(0, 0);
}