#include "header.h"

/*

377. ����ܺ� IV

����һ���� ��ͬ ������ɵ����� nums����һ��Ŀ������ target
����� nums ���ҳ��������ܺ�Ϊ target ��Ԫ����ϵĸ���

��Ŀ���ݱ�֤�𰸷��� 32 λ������Χ

ʾ�� 1��
���룺nums = [1,2,3], target = 4
�����7
���ͣ�
���п��ܵ����Ϊ��
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
��ע�⣬˳��ͬ�����б�������ͬ�����

ʾ�� 2��
���룺nums = [9], target = 3
�����0

��ʾ��
1 <= nums.length <= 200
1 <= nums[i] <= 1000
nums �е�����Ԫ�� ������ͬ
1 <= target <= 1000

���ף���������������к��и����ᷢ��ʲô�������������ֱ仯��������������֣���Ҫ����Ŀ�������Щ����������

*/

class Solution {
private:
	vector<int> memo;

public:
	int combinationSum4(vector<int> &nums, int target) {
		memo.resize(target + 1, -1);
		return helper(nums, target);
	}

private:
	int helper(vector<int> &nums, int t) {
		if (t == 0) return 1;
		if (memo[t] != -1) return memo[t];
		int res = 0;
		for (int n : nums) {
			if (n <= t) res += helper(nums, t - n);
		}
		return memo[t] = res;
	}
};
