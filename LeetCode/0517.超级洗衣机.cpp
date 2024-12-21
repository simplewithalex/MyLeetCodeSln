#include "header.h"

/*

517. ����ϴ�»�

������ n ̨����ϴ�»�����ͬһ���ϡ���ʼ��ʱ��ÿ̨ϴ�»��ڿ�����һ�������·���Ҳ�����ǿյ�

��ÿһ�������У������ѡ������ m (1 <= m <= n) ̨ϴ�»������ͬʱ��ÿ̨ϴ�»���һ���·��͵����ڵ�һ̨ϴ�»�

����һ���������� machines �����������ÿ̨ϴ�»��е������������������������ϴ�»���ʣ�µ������������ȵ� ���ٵĲ�������

�������ʹÿ̨ϴ�»��������������ȣ��򷵻� -1

ʾ�� 1��
���룺machines = [1,0,5]
�����3
���ͣ�
��һ��:    1     0 <-- 5    =>    1     1     4
�ڶ���:    1 <-- 1 <-- 4    =>    2     1     3
������:    2     1 <-- 3    =>    2     2     2

ʾ�� 2��
���룺machines = [0,3,0]
�����2
���ͣ�
��һ��:    0 <-- 3     0    =>    1     2     0
�ڶ���:    1     2 --> 0    =>    1     1     1

ʾ�� 3��
���룺machines = [0,2,0]
�����-1
���ͣ�
����������������ϴ�»�ͬʱʣ����ͬ����������

��ʾ��
n == machines.length
1 <= n <= 10^4
0 <= machines[i] <= 10^5

*/


class Solution {
public:
	int findMinMoves(vector<int> &machines) {
		int len = machines.size();
		int sum = accumulate(machines.begin(), machines.end(), 0);
		if (sum % len) return -1;
		int t = sum / len;
		int ls = 0, rs = sum;
		int ans = 0;
		for (int i = 0; i < len; ++i) {
			rs -= machines[i];
			int a = max(0, t * i - ls);
			int b = max(0, t * (len - 1 - i) - rs);
			ans = max(ans, a + b);
			ls += machines[i];
		}
		return ans;
	}
};

