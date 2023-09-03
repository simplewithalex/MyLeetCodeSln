#include "header.h"

/*

410. �ָ���������ֵ

����һ���Ǹ��������� nums ��һ������ m, ����Ҫ���������ֳ� m ���ǿյ�����������
���һ���㷨ʹ���� m ����������Ժ͵����ֵ��С

ʾ�� 1��
���룺nums = [7,2,5,10,8], m = 2
�����18
���ͣ�
һ�������ַ����� nums �ָ�Ϊ 2 ��������
������õķ�ʽ�ǽ����Ϊ [7,2,5] �� [10,8]
��Ϊ��ʱ��������������Եĺ͵����ֵΪ18���������������С

ʾ�� 2��
���룺nums = [1,2,3,4,5], m = 2
�����9

ʾ�� 3��
���룺nums = [1,4,4], m = 3
�����4

��ʾ��
1 <= nums.length <= 1000
0 <= nums[i] <= 10^6
1 <= m <= min(50, nums.length)

*/

// ����¼
class Solution1 {
public:
	int splitArray(vector<int> &nums, int k) {
		int len = nums.size();
		vector<vector<long long>> memo(len + 1, vector<long long>(k + 1, -1));
		vector<long long> preSum(len + 1, 0);
		for (int i = 1; i <= len; ++i) {
			preSum[i] = preSum[i - 1] + nums[i - 1];
		}
		return helper(len, k, preSum, memo);
	}

private:
	int helper(int i, int j, vector<long long> &preSum,
		vector<vector<long long>> &memo) {
		if (memo[i][j] != -1) return memo[i][j];
		if (j == 0) return i > 0 ? INT_MAX : 0;
		int minSum = INT_MAX;
		for (int k = j - 1; k < i; ++k) {
			int cur = max(helper(k, j - 1, preSum, memo),
				(int)(preSum[i] - preSum[k]));
			minSum = min(minSum, cur);
		}
		return memo[i][j] = minSum;
	}
};
// https://leetcode.cn/problems/split-array-largest-sum/solutions/345417/fen-ge-shu-zu-de-zui-da-zhi-by-leetcode-solution/
// @author https://leetcode.cn/u/leetcode-solution/



// ��̬�滮
class Solution2 {
public:
	int splitArray(vector<int> &nums, int k) {
		int len = nums.size();
		vector<vector<long long>> dp(len + 1,
			vector<long long>(k + 1, LLONG_MAX));

		vector<long long> preSum(len + 1, 0);
		for (int i = 1; i <= len; ++i) {
			preSum[i] = preSum[i - 1] + nums[i - 1];
		}

		dp[0][0] = 0;
		for (int i = 1; i <= len; ++i) {
			for (int j = 1; j <= k; ++j) {
				for (int p = j - 1; p < i; ++p) {
					dp[i][j] =
						min(dp[i][j], max(dp[p][j - 1], preSum[i] - preSum[p]));
				}
			}
		}
		return dp[len][k];
	}
};


// ���ֲ���
class Solution3 {
public:
	int splitArray(vector<int> &nums, int k) {
		int maxNum = INT_MIN, sum = 0;
		for (const auto &num : nums) {
			maxNum = max(maxNum, num);
			sum += num;
		}
		int lo = maxNum, hi = sum;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			int splits = split(nums, mi);
			splits > k ? lo = mi + 1 : hi = mi;
		}
		return lo;
	}

private:
	int split(vector<int> &nums, int tarInterSum) {
		int splits = 1;
		int curInterSum = 0;
		for (const auto &num : nums) {
			if (curInterSum + num > tarInterSum) {
				curInterSum = 0;
				++splits;
			}
			curInterSum += num;
		}
		return splits;
	}
};
// https://leetcode.cn/problems/split-array-largest-sum/solutions/242909/er-fen-cha-zhao-by-liweiwei1419-4/
// @authors https://leetcode.cn/u/liweiwei1419/

