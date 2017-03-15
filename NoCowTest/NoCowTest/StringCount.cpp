/**
字符串计数:求字典序在s1和s2之间的，长度在len1到len2的字符串的个数，结果mod 1000007。
参照了前几位大牛的代码，并做了稍微的改动。
先举个10进制的例子：
138-->652 的三位数有几个？ (6-1)*10^2 + (5-3)*10^1 + (2-8)*10^0 = 5*100+2*10+(-6)*1 = 514 == 652-138
可以看出，514中不包括138,但是包括514,所以大于138小于652的数就是再去掉一个数(652)==652-1=651
如果是四位数呢？那就是1380-->6520之间的数，6520-1380=5140(这里只可以看出，不包含6520,因为字典序中，
652<6520, 但是包括1380,因为字典序中1380>138, 所以，这个5140就四位数的个数。

同样可以分析，18-->656 中1到四位数，这里会发现，
	1位数的个数n1就是6-1=5(不包含1，而包含6）
	2位数的个数就是n2=n1*10+(5-8) (不包含18,但包含65)
	3位数的个数就是n3=n2*10+(6-0) (这里18不够三位数，补上0，变成180, 这里不包含180而包含656,刚才应该不包含656而包含180)
	4位数的个数就是n4=n3*10+(0-0) (这里两个数都不足四位数，补0为1800->6560, 不包含1800,而包含6560,实际上应该包含1800而不包含6560,但是对计数没有影响)
同样，字母a-z就是26进制,也这么算。

综上：只有s1的长度和s2的长度相等时，才会多加一个s2,否则不会多加，也就不用减1。
以下测试用例: 
a ac 1 2 -->aa, ab -->2
aa ac 2 3 --> ab, aa(a-z), ab(a-z)-->53
牛客网的测试用例不够充分，所以很多情况测不出来。
*/
#include<iostream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;
#define M 1000007
int main() {
#ifdef LOCAL_DEBUG
	freopen("input.txt", "r", stdin);
#endif
	//根据题中给出的例子，这个字符串只包含小写字母，不然答案就不应该是56了
	string s1, s2;
	int len1, len2;
	while (cin >> s1 >> s2 >> len1 >> len2) {
		//只包含小写字母的字符串可以看成26进制的数制
		//将s1和s2补长到len2长度
		int tlen1 = s1.size();
		int tlen2 = s2.size();
		s1.append(len2 - s1.size(), 'a');
		s2.append(len2 - s2.size(), (char)('a'));
		vector<int> array;
		for (int i = 0; i < len2; i++) {
			array.push_back(s2[i] - s1[i]);
		}
		int result = 0;
		for (int j = 0; j < len1 - 1; j++) {
			result = (26 * result + array[j])%M;
		}
		int sum = 0;
		for (int i = len1 - 1; i < len2; i++) {
			result = ((26 * result) % M + array[i]) % M;
			sum = (sum + result) % M;
		}
		if (tlen1 == tlen2)
			sum = (sum - 1 + M) % M;
		cout << sum << endl;
	}
	return 0;
}