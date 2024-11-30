#include "header.h"

/*

402. �Ƶ� K λ����

����һ�����ַ�����ʾ�ķǸ����� num ��һ������ k ���Ƴ�������е� k λ���֣�ʹ��ʣ�µ�������С��

�������ַ�����ʽ���������С�����֡�


ʾ�� 1 ��
���룺num = "1432219", k = 3
�����"1219"
���ͣ��Ƴ����������� 4, 3, �� 2 �γ�һ���µ���С������ 1219

ʾ�� 2 ��
���룺num = "10200", k = 1
�����"200"
���ͣ��Ƶ���λ�� 1 ʣ�µ�����Ϊ 200
ע������������κ�ǰ����

ʾ�� 3 ��
���룺num = "10", k = 2
�����"0"
���ͣ���ԭ�����Ƴ����е����֣�ʣ��Ϊ�վ��� 0 

��ʾ��
1 <= k <= num.length <= 10^5
num ��������λ���֣�0 - 9�����
���� 0 ����֮�⣬num �����κ�ǰ����

*/

class Solution {
public:
	string removeKdigits(string num, int k) {
		vector<char> stk;
		int len = num.size();
		for (char c : num) {
			while (k && !stk.empty() && stk.back() > c) {
				stk.pop_back();
				--k;
			}
			stk.push_back(c);
		}
		while (k--) stk.pop_back();
		string ans;
		bool isLeadZero = true;
		for (char c : stk) {
			if (isLeadZero && c == '0') continue;
			isLeadZero = false;
			ans.append(1, c);
		}
		return ans == "" ? "0" : ans;
	}
};


	