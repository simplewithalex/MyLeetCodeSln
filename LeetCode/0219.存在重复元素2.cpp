#include "header.h"

/*

219. �����ظ�Ԫ�� II

����һ���������� nums ��һ������ k ���ж��������Ƿ�������� ��ͬ������ i �� j ������ nums[i] == nums[j] �� abs(i - j) <= k ��
������ڣ����� true �����򣬷��� false ��

ʾ�� 1��
���룺nums = [1,2,3,1], k = 3
�����true

ʾ�� 2��
���룺nums = [1,0,1,1], k = 1
�����true

ʾ�� 3��
���룺nums = [1,2,3,1,2,3], k = 2
�����false

��ʾ��
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
0 <= k <= 10^5

*/

class Solution {
public:
	bool containsNearbyDuplicate(vector<int> &nums, int k) {
		unordered_set<int> s;
		for (int i = 0; i < nums.size(); ++i) {
			if (s.count(nums[i])) return true;
			s.insert(nums[i]);
			if (s.size() == k + 1) s.erase(nums[i - k]);
		}
		return false;
	}
};
// �����Ϊ���Ƿ���ڳ��Ȳ������� k + 1 �Ĵ��ڣ�ʹ����������ͬԪ��