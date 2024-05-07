#include "header.h"

/*

368. ��������Ӽ�

����һ���� ���ظ� ��������ɵļ��� nums�������ҳ��������������������Ӽ� answer���Ӽ���ÿһԪ�ض� (answer[i], answer[j]) ��Ӧ�����㣺
answer[i] % answer[j] == 0 ����
answer[j] % answer[i] == 0
������ڶ����Ч���Ӽ������������κ�һ������

ʾ�� 1��
���룺nums = [1,2,3]
�����[1,2]
���ͣ�[1,3] Ҳ�ᱻ��Ϊ��ȷ��

ʾ�� 2��
���룺nums = [1,2,4,8]
�����[1,2,4,8]

��ʾ��
1 <= nums.length <= 1000
1 <= nums[i] <= 2 * 10^9
nums �е��������� ������ͬ

*/


class Solution {
private:
	vector<int> memo;

public:
	vector<int> largestDivisibleSubset(vector<int> &nums) {
		int len = nums.size();
		memo.resize(len + 1, -1);
		sort(nums.begin(), nums.end());
		int maxLen = 1, handle = 1;
		for (int i = 1; i <= len; ++i) {
			int tempLen = helper(nums, i);
			if (tempLen > maxLen) {
				maxLen = tempLen;
				handle = i;
			}
		}
		vector<int> ans;
		for (int i = handle, curVal = nums[i - 1]; i >= 1; --i) {
			if (memo[i] == maxLen && curVal % nums[i - 1] == 0) {
				ans.push_back(nums[i - 1]);
				curVal = nums[i - 1];
				--maxLen;
			}
		}
		return ans;
	}

private:
	int helper(vector<int> &nums, int idx) {
		if (memo[idx] != -1) return memo[idx];
		int maxLen = 1;
		for (int j = 1; j < idx; ++j) {
			if (nums[idx - 1] % nums[j - 1] == 0) {
				maxLen = max(maxLen, helper(nums, j) + 1);
			}
		}
		return memo[idx] = maxLen;
	}
};
