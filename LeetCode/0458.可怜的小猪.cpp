#include "header.h"

/*

458. ������С��

�� buckets ͰҺ�壬���� ������һͰ ���ж�ҩ������װ�Ķ���ˮ�����Ǵ���ۿ�������һ����
Ϊ��Ū�����ֻˮͰ���ж�ҩ�������ιһЩ��ȣ�ͨ���۲����Ƿ���������жϡ�
���ҵ��ǣ���ֻ�� minutesToTest ����ʱ����ȷ����ͰҺ�����ж��ġ�

ι��Ĺ������£�
ѡ�����ɻ������ι����
��������С��ͬʱ��������������Ͱ�е�ˮ�����Ҹù��̲���Ҫʱ�䣻
С�����ˮ�󣬱����� minutesToDie ���ӵ���ȴʱ�䡣�����ʱ�����ֻ�ܹ۲죬�����������ι��
���� minutesToDie ���Ӻ����кȵ���ҩ��������ȥ���������������������
�ظ���һ���̣�ֱ��ʱ�����ꣻ
����Ͱ����Ŀ buckets��minutesToDie �� minutesToTest�������ڹ涨ʱ�����ж��ĸ�Ͱ�ж��������С����


ʾ�� 1��
���룺buckets = 1000, minutesToDie = 15, minutesToTest = 60
�����5

ʾ�� 2��
���룺buckets = 4, minutesToDie = 15, minutesToTest = 15
�����2

ʾ�� 3��
���룺buckets = 4, minutesToDie = 15, minutesToTest = 30
�����2

��ʾ��
1 <= buckets <= 1000
1 <= minutesToDie <= minutesToTest <= 100

*/

class Solution {
private:
	vector<vector<int>> memo;

public:
	int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
		int j = minutesToTest / minutesToDie;
		int i = 0;
		memo.resize(buckets + 1, vector<int>(j + 1, -1));
		while (helper(i, j) < buckets) ++i;
		return i;
	}

private:
	int helper(int i, int j) {
		if (i == 0 || j == 0) return 1;
		if (memo[i][j] != -1) return memo[i][j];
		int res = 0;
		for (int k = 0; k <= i; ++k) {
			res += helper(k, j - 1) * comb(i, k);
		}
		return memo[i][j] = res;
	}
	int comb(int i, int j) {
		int n = 1, m = 1;
		for (int k = 0; k < j; ++k) {
			n *= (i - k);
			m *= (k + 1);
		}
		return n / m;
	}
};