#include "header.h"

/*

456. 132 ģʽ

����һ���������� nums �������й��� n ������
132 ģʽ�������� ���������� nums[i]��nums[j] �� nums[k] ��ɣ���ͬʱ���㣺i < j < k �� nums[i] < nums[k] < nums[j]
��� nums �д��� 132 ģʽ�������� ������ true �����򣬷��� false

ʾ�� 1��
���룺nums = [1,2,3,4]
�����false
���ͣ������в����� 132 ģʽ��������

ʾ�� 2��
���룺nums = [3,1,4,2]
�����true
���ͣ��������� 1 �� 132 ģʽ�������У� [1, 4, 2]

ʾ�� 3��
���룺nums = [-1,3,2,0]
�����true
���ͣ��������� 3 �� 132 ģʽ�ĵ������У�[-1, 3, 2]��[-1, 3, 0] �� [-1, 2, 0]

��ʾ��
n == nums.length
1 <= n <= 2 * 10^5
-10^9 <= nums[i] <= 10^9

*/

class Solution {
public:
	bool find132pattern(vector<int>& nums) {
		stack<int> st;
		int len = nums.size();
		int k = INT_MIN;
		for (int i = len - 1; i >= 0; --i) {
			if (nums[i] < k) return true;
			while (!st.empty() && st.top() < nums[i]) {
				k = st.top();
				st.pop();
			}
			st.push(nums[i]);
		}
		return false;
	}
};

