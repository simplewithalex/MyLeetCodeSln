#include "header.h"

/*

396. ��ת����

����һ������Ϊ n ���������� nums

���� arrk ������ nums ˳ʱ����ת k ��λ�ú�����飬���Ƕ��� nums �� ��ת���� F Ϊ��
F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1]
���� F(0), F(1), ..., F(n-1)�е����ֵ

���ɵĲ��������ô𰸷��� 32 λ ����

ʾ�� 1:
����: nums = [4,3,2,6]
���: 26
����:
F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
���� F(0), F(1), F(2), F(3) �е����ֵ�� F(3) = 26

ʾ�� 2:
����: nums = [100]
���: 0


��ʾ:
n == nums.length
1 <= n <= 10^5
-100 <= nums[i] <= 100

*/

class Solution {
public:
	int maxRotateFunction(vector<int> &nums) {
		int f = 0, len = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		for (int i = 0; i < len; ++i) f += i * nums[i];
		int ans = f;
		for (int i = len - 1; i >= 0; --i) {
			f += sum - len * nums[i];
			ans = max(ans, f);
		}
		return ans;
	}
};
// https://leetcode.cn/problems/rotate-function/solutions/1437641/xuan-zhuan-shu-zu-by-leetcode-solution-s0wd/
// @author LeetCode�ٷ����

