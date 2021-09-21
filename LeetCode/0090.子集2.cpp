#include "header.h"

/*

����һ���������� nums�����п��ܰ����ظ�Ԫ�أ����㷵�ظ��������п��ܵ��Ӽ����ݼ�����
�⼯���ܰ����ظ����Ӽ������صĽ⼯�У��Ӽ����԰�����˳�����С�

ʾ�� 1��
���룺nums = [1,2,2]
�����[[],[1],[1,2],[1,2,2],[2],[2,2]]

ʾ�� 2��
���룺nums = [0]
�����[[],[0]]

��ʾ��
1 <= nums.length <= 10
-10 <= nums[i] <= 10

*/

class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int> &nums) {
		vector<vector<int>> res;
		vector<int> vec;
		sort(nums.begin(), nums.end());
		backTrack(res, vec, nums, 0);
		return res;
	}
private:
	void backTrack(vector<vector<int>> &res, vector<int> &vec, vector<int> &nums, int start)
	{
		res.push_back(vec);
		int len = nums.size();
		for (int i = start; i < len; ++i)
		{
			if (i > start&&nums[i] == nums[i - 1]) continue;
			vec.push_back(nums[i]);
			backTrack(res, vec, nums, i + 1);
			vec.pop_back();
		}
	}
};