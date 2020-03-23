#include "header.h"

/*

����һ���ǿ��������飬����ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ����������Ρ��ҳ��Ǹ�ֻ������һ�ε�Ԫ�ء�

˵����

����㷨Ӧ�þ�������ʱ�临�Ӷȡ� ����Բ�ʹ�ö���ռ���ʵ����

ʾ�� 1:
����: [2,2,3,2]
���: 3

ʾ�� 2:
����: [0,1,0,1,0,1,99]
���: 99

*/

class Solution {
public:
	int singleNumber(vector<int> &nums)
	{
		int res = 0;
		for (int i = 0; i < 32; ++i)
		{
			int sum = 0;
			for (auto n : nums)
			{
				if ((n >> i) & 1) sum += 1;
			}
			res |= (sum % 3) << i;
		}
		return res;
	}
};