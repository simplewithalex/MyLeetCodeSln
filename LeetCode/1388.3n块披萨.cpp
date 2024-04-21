#include "header.h"

/*

1388. 3n ������

����һ������������ 3n �鲻ͬ��С�Ĳ�����ɣ�������������������Ҫ�������¹�������������

����ѡ ���� һ������
Alice ������ѡ����ѡ���������ʱ�뷽�����һ������
Bob ������ѡ����ѡ�������˳ʱ�뷽�����һ������
�ظ���������ֱ��û������ʣ��

ÿһ�������Ĵ�С��˳ʱ�뷽����ѭ������ slices ��ʾ
���㷵������Ի�õ�������С�ܺ͵����ֵ

ʾ�� 1��
���룺slices = [1,2,3,4,5,6]
�����10
���ͣ�ѡ���СΪ 4 ��������Alice �� Bob �ֱ���ѡ��СΪ 3 �� 5 ��������
Ȼ����ѡ���СΪ 6 ��������Alice �� Bob �ֱ���ѡ��СΪ 2 �� 1 ��������
���õ������ܴ�СΪ 4 + 6 = 10


ʾ�� 2��
���룺slices = [8,9,8,6,1,1]
�����16
���ͣ����ֶ�ѡ��СΪ 8 ��������
�����ѡ���СΪ 9 ����������������Ǿͻ�ѡ���СΪ 8 ��������
�������������ܺͲ������ġ�


��ʾ��
1 <= slices.length <= 500
slices.length % 3 == 0
1 <= slices[i] <= 1000

*/


// ��ҽ�����չ��
// ����¼
class Solution1 {
private:
	vector<vector<int>> memo;

public:
	int maxSizeSlices(vector<int> &slices) {
		int m = slices.size();
		int n = m / 3;
		memo.resize(m + 1, vector<int>(n + 1, -1));
		int res1 = helper(slices, 1, m - 1, n);
		// ע�����μ������벻ͬ��memo����Ҫ���
		memo.clear();
		memo.resize(m + 1, vector<int>(n + 1, -1));
		int res2 = helper(slices, 2, m, n);
		return max(res1, res2);
	}

private:
	int helper(vector<int> &slices, int start, int idx, int c) {
		if (c == 0 || idx < start) return 0;
		if (memo[idx][c] != -1) return memo[idx][c];
		return memo[idx][c] =
			max(helper(slices, start, idx - 2, c - 1) + slices[idx - 1],
				helper(slices, start, idx - 1, c));
	}
};

// �Ե׶��ϵĶ�̬�滮
class Solution2 {
public:
	int maxSizeSlices(vector<int> &slices) {
		int len = slices.size();
		int res1 = calculate(slices, 1, len - 1);
		int res2 = calculate(slices, 2, len);
		return max(res1, res2);
	}

private:
	int calculate(vector<int> &slices, int start, int end) {
		int m = slices.size(), n = m / 3;
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		dp[start - 1][0] = 0, dp[start][0] = 0;
		dp[start - 1][1] = 0, dp[start][1] = slices[start - 1];
		for (int i = start + 1; i <= end; ++i) {
			dp[i][0] = 0;
			for (int j = 1; j <= n; ++j) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 2][j - 1] + slices[i - 1]);
			}
		}
		return dp[end][n];
	}
};

// https://leetcode.cn/problems/pizza-with-3n-slices/solutions/177086/3n-kuai-pi-sa-by-leetcode-solution/
// @author LeetCode�ٷ����


