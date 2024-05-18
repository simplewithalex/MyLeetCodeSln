#include "header.h"

/*

887. ��������

���� k ö��ͬ�ļ�����������ʹ��һ���ӵ� 1 �㵽�� n �㹲�� n ��¥�Ľ�����
��֪����¥�� f������ 0 <= f <= n���κδ� ���� f ��¥�����µļ��������飬�� f ¥�������͵�¥�����µļ����������ơ�
ÿ�β����������ȡһöû����ļ�������������һ¥�� x ���£����� 1 <= x <= n����
����������ˣ���Ͳ����ٴ�ʹ���������ĳö�������º�û��ˤ�飬�������֮��Ĳ����� �ظ�ʹ�� ��ö������

������㲢����Ҫȷ�� f ȷ�е�ֵ �� ��С�������� �Ƕ��٣�

ʾ�� 1��
���룺k = 1, n = 2
�����2
���ͣ�
������ 1 ¥���䡣��������ˣ��϶��ܵó� f = 0
���򣬼����� 2 ¥���䡣��������ˣ��϶��ܵó� f = 1
�����û�飬��ô�϶��ܵó� f = 2
��ˣ�����������������Ҫ�ƶ� 2 ����ȷ�� f �Ƕ���

ʾ�� 2��
���룺k = 2, n = 6
�����3

ʾ�� 3��
���룺k = 3, n = 14
�����4

��ʾ��
1 <= k <= 100
1 <= n <= 10^4

*/


class Solution1 {
private:
	vector<vector<int>> memo;

public:
	int superEggDrop(int k, int n) {
		memo.resize(k + 1, vector<int>(n + 1, -1));
		return helper(k, n);
	}

private:
	int helper(int k, int n) {
		if (k == 1) return n;
		if (n == 0) return 0;
		if (memo[k][n] != -1) return memo[k][n];
		int res = INT_MAX;
		for (int i = 1; i <= n; ++i) {
			res = min(res, max(helper(k, n - i), helper(k - 1, i - 1)) + 1);
		}
		return memo[k][n] = res;
	}
};

// ���ֲ����Ż�
class Solution2 {
private:
	vector<vector<int>> memo;

public:
	int superEggDrop(int k, int n) {
		memo.resize(k + 1, vector<int>(n + 1, -1));
		return helper(k, n);
	}

private:
	int helper(int k, int n) {
		if (k == 1) return n;
		if (n == 0) return 0;
		if (memo[k][n] != -1) return memo[k][n];
		int lo = 1, hi = n;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			int broken = helper(k - 1, mi - 1);
			int nbroken = helper(k, n - mi);
			broken < nbroken ? lo = mi + 1 : hi = mi;
		}
		return memo[k][n] = max(helper(k, n - lo), helper(k - 1, lo - 1)) + 1;
	}
};

/*

�����Ŀ�� LeetCode 458 ������С�� �е�������ʵ������ָ����Щ¥���У��ܹ���֤�ҵ�һ�������λ�� f��
����Ҫ�Ĳ������������Ƕ��١���� f ����������λ�ã����Խ����Ҫ���ܹ���֤��һ���ͬʱ�������١�

*/