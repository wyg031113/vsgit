#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
struct Score
{
	long p;
	long c;
};

int main()
{
#ifdef LOCAL
	freopen("input.txt", "r", stdin);
#endif
	unsigned long long  n, r, avg, sum = 0;
	while (cin >> n >> r >> avg) {
		Score sc;
		vector<Score> vec;
		for (int i = 0; i < n; i++) {
			cin >> sc.p >> sc.c;
			vec.push_back(sc);
			sum += sc.p;
		}
		sort(vec.begin(), vec.end(), [](const Score &a, const Score &b)->bool
		{
			return a.c < b.c;
		});
		long long diff = avg * n - sum;
		long long cost = 0;
		for (int i = 0; i < vec.size() && diff > 0; i++) {
			long long  k = r - vec[i].p;
			if (k == 0)
				continue;
			k = std::min(k, diff);
			cost += k * vec[i].c;
			diff -= k;

		}
		cout << cost << endl;
	}
	return 0;
}
/*

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct score_hour
{
    long score;
    long hour;
};
// for sort
bool cmp(score_hour a, score_hour b)
{
    return a.hour < b.hour;
}
int main(){
    long long  n, r, avg;
    while(cin >> n >> r >> avg){
        vector<score_hour> vec;
        long long sum = 0;
        for (long long i = 0; i < n; i++){
            score_hour t;
            cin >> t.score >> t.hour;
            sum += t.score;
            vec.push_back(t);
        }
        
        sort(vec.begin(), vec.end(), [](const score_hour &a, const score_hour &b)
             {
                 return a.hour < b.hour;
             });
        long long need_points = n *avg - sum;
        long long need_hours = 0;
        for (long long  i = 0; i < vec.size() && need_points > 0; i++){
            if (vec[i].score < r){
                long long  tmp = r - vec[i].score;
                long long  k = std::min(tmp, need_points);
                if(k == 0) continue;
                need_hours += k * vec[i].hour;
                need_points -= k;
            }
        }
        std::cout << need_hours << endl;
    }
    return 0;
}

*/