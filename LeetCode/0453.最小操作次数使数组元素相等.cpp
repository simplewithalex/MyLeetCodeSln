#include "header.h"

/*

453. ��С��������ʹ����Ԫ�����

����һ������Ϊ n ���������飬ÿ�β�������ʹ n - 1 ��Ԫ������ 1
��������������Ԫ����ȵ���С��������

ʾ�� 1��
���룺nums = [1,2,3]
�����3
���ͣ�
ֻ��Ҫ3�β�����ע��ÿ�β�������������Ԫ�ص�ֵ����
[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

ʾ�� 2��
���룺nums = [1,1,1]
�����0

��ʾ��
n == nums.length
1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
�𰸱�֤���� 32-bit ����

*/

class Solution {
public:
	int minMoves(vector<int> &nums) {
		int minNum = *min_element(nums.begin(), nums.end());
		int res = 0;
		for (int n : nums) res += n - minNum;
		return res;
	}
};

