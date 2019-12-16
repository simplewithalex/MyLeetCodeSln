#include "header.h"

/*

����һ������ nums����дһ������������ 0 �ƶ��������ĩβ��ͬʱ���ַ���Ԫ�ص����˳��

ʾ��:
����: [0,1,0,3,12]
���: [1,3,12,0,0]

˵��:
������ԭ�����ϲ��������ܿ�����������顣
�������ٲ���������

*/

class Solution1 {
public:
	void moveZeroes(vector<int> &nums)
	{
		if (nums.empty()) return;
		int len = nums.size();
		int lastZero = 0;
		for (int cur = 0; cur < len; ++cur)
		{
			if (nums[cur] != 0)
				nums[lastZero++] = nums[cur];
		}
		for (int i = lastZero; i < len; ++i)
		{
			nums[i] = 0;
		}
	}
};

//����Ԫ�رȽ϶������ȽϺõĽⷨ
//���磺[0��0��0������0��1]
class Solution2 {
public:
	void moveZeroes(vector<int> &nums)
	{
		if (nums.empty()) return;
		int len = nums.size();
		for (int lastZero = 0, cur = 0; cur < len; ++cur)
		{
			if (nums[cur] != 0) swap(nums[lastZero++], nums[cur]);
		}
	}
};