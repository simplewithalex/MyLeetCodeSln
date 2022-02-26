#include "header.h"

/*

217. �����ظ�Ԫ��

����һ���������� nums �������һֵ�������г��� �������� ������ true �����������ÿ��Ԫ�ػ�����ͬ������ false ��

ʾ�� 1��
���룺nums = [1,2,3,1]
�����true

ʾ�� 2��
���룺nums = [1,2,3,4]
�����false

ʾ�� 3��
���룺nums = [1,1,1,3,3,4,3,2,4,2]
�����true

��ʾ��
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

*/

// ����
class Solution1 {
public:
	bool containsDuplicate(vector<int> &nums) {
		sort(nums.begin(), nums.end());
		int len = nums.size();
		for (int i = 0; i < len - 1; ++i) {
			if (nums[i] == nums[i + 1]) return true;
		}
		return false;
	}
};

// ��ϣ��
class Solution2 {
public:
	bool containsDuplicate(vector<int> &nums) {
		unordered_set<int> s;
		for (auto n : nums) {
			if (s.count(n)) return true;
			s.insert(n);
		}
		return false;
	}
};