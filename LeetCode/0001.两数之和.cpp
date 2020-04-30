#include "header.h"

/*

����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ�����������������������ǵ������±ꡣ

����Լ���ÿ������ֻ���Ӧһ���𰸡�
�㲻���ظ�����������ͬһ��Ԫ�ء�

ʾ��:

���� nums = [2, 7, 11, 15], target = 9
��Ϊ nums[0] + nums[1] = 2 + 7 = 9
���Է��� [0, 1]

*/

class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target)
	{
		int len = numbers.size();
		if (len < 2) return {};
		unordered_map<int, int> m;
		for (int i = 0; i<len; ++i)
		{
			int temp = target - numbers[i];
			if (!m.count(temp))
				m[numbers[i]] = i;
			else
				return{ m[temp], i };
		}
		return {};
	}
};