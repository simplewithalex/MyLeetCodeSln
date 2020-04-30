#include "header.h"

/*

ʵ�ֻ�ȡ��һ�����еĺ������㷨��Ҫ���������������������г��ֵ�������һ����������С�
�����������һ����������У��������������г���С�����У����������У���
����ԭ���޸ģ�ֻ����ʹ�ö��ⳣ���ռ䡣

������һЩ���ӣ�����λ������У�����Ӧ���λ���Ҳ��С�
1,2,3 �� 1,3,2
3,2,1 �� 1,2,3
1,1,5 �� 1,5,1

*/

class Solution {
public:
	void nextPermutation(vector<int> &num)
	{
		int len = num.size();
		int index = len - 2;
		while (index >= 0 && num[index] >= num[index + 1]) --index;
		if (index < 0)
		{
			reverse(num.begin(), num.end());
		}
		else
		{
			int i = len - 1;
			while (i >= 0 && num[i] <= num[index]) --i;
			swap(num[index], num[i]);
			reverse(num.begin() + index + 1, num.end());
		}
	}
};
//https://leetcode.wang/leetCode-31-Next-Permutation.html