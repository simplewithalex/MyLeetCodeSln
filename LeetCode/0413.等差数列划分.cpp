#include "header.h"

/*

413. �Ȳ����л���

���һ����������������Ԫ�أ�����������������Ԫ��֮����ͬ����Ƹ�����Ϊ�Ȳ�����
���磬[1,3,5,7,9]��[7,7,7,7] �� [3,-1,-5,-9] ���ǵȲ�����
����һ����������nums����������nums������Ϊ�Ȳ���������������

������ �������е�һ����������

ʾ�� 1��
���룺nums = [1,2,3,4]
�����3
���ͣ�nums ���������ӵȲ����飺[1, 2, 3]��[2, 3, 4] �� [1,2,3,4] ����

ʾ�� 2��
���룺nums = [1]
�����0

��ʾ��
1 <= nums.length <= 5000
-1000 <= nums[i] <= 1000

*/

class Solution {
private:
	vector<int> memo;

public:
	int numberOfArithmeticSlices(vector<int> &nums) {
		int len = nums.size();
		memo.resize(len, -1);
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			ans += helper(nums, i);
		}
		return ans;
	}

private:
	int helper(vector<int> &nums, int idx) {
		if (idx < 2) return 0;
		if (memo[idx] != -1) return memo[idx];
		int ans = 0;
		if (nums[idx] - nums[idx - 1] == nums[idx - 1] - nums[idx - 2]) {
			ans = 1 + helper(nums, idx - 1);
		}
		return memo[idx] = ans;
	}
};
