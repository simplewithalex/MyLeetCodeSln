#include "header.h"

/*

����һ���ǿ��������飬����ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ��������Ρ��ҳ��Ǹ�ֻ������һ�ε�Ԫ�ء�

˵����
����㷨Ӧ�þ�������ʱ�临�Ӷȡ� ����Բ�ʹ�ö���ռ���ʵ����

ʾ�� 1:
����: [2,2,1]
���: 1

ʾ�� 2:
����: [4,1,2,1,2]
���: 4

*/

class Solution {
public:
	int singleNumber(vector<int> &nums) 
	{
		int res = 0;
		int len = nums.size();
		for (int i = 0; i < len; ++i)
		{
			res ^= nums[i];
		}
		return res;
	}
};