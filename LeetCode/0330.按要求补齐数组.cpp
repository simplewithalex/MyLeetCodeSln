#include "header.h"

/*

330. ��Ҫ��������

����һ�������������������nums����һ�������� n
�� [1, n] ������ѡȡ��������ֲ��䵽 nums �У�ʹ�� [1, n] �����ڵ��κ����ֶ������� nums ��ĳ�������ֵĺ�����ʾ
�뷵����������Ҫ���������Ҫ��������ָ���

ʾ�� 1:
����: nums = [1,3], n = 6
���: 1
����:
���� nums �����е���� [1], [3], [1,3]�����Եó� 1, 3, 4��
����������ǽ� 2 ��ӵ� nums �У� ��ϱ�Ϊ: [1], [2], [3], [1,3], [2,3], [1,2,3]��
��Ϳ��Ա�ʾ���� 1, 2, 3, 4, 5, 6���ܹ����� [1, 6] ���������е�����
��������������Ҫ���һ�����֡�

ʾ�� 2:
����: nums = [1,5,10], n = 20
���: 2
����: ������Ҫ��� [2,4]��

ʾ�� 3:
����: nums = [1,2,2], n = 5
���: 0

��ʾ��
1 <= nums.length <= 1000
1 <= nums[i] <= 10^4
nums ����������
1 <= n <= 2^31 - 1

*/

class Solution {
public:
	int minPatches(vector<int> &nums, int n) {
		long long total = 0;
		int count = 0;
		int index = 0;
		while (total < n) {
			if (index < nums.size() && nums[index] - 1 <= total) {
				total += nums[index++];
			} else {
				total += total + 1;
				++count;
			}
		}
		return count;
	}
};
// https://leetcode.cn/problems/patching-array/solutions/539098/an-yao-qiu-bu-qi-shu-zu-tan-xin-suan-fa-b4bwr/
// @author https://leetcode.cn/u/sdwwld/
