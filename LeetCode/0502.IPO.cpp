#include "header.h"

/*

502. IPO

���� ���ۣ�LeetCode��������ʼ IPO ��Ϊ���Ը��ߵļ۸񽫹�Ʊ��������Ͷ�ʹ�˾������ ϣ���� IPO ֮ǰ��չһЩ��Ŀ���������ʱ�
������Դ���ޣ���ֻ���� IPO ֮ǰ������ k ����ͬ����Ŀ������ ���� ��������� k ����ͬ��Ŀ��õ�������ʱ��ķ�ʽ

���� n ����Ŀ������ÿ����Ŀ i ��������һ�������� profits[i] ������������Ŀ��Ҫ����С�ʱ� capital[i]

�������ʱ�Ϊ w ���������һ����Ŀʱ���㽫��ô����������󽫱���ӵ�������ʱ���

�ܶ���֮���Ӹ�����Ŀ��ѡ�� ��� k ����ͬ��Ŀ���б��� ��������ʱ�����������տɻ�õ�����ʱ�

�𰸱�֤�� 32 λ�з���������Χ��


ʾ�� 1��
���룺k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
�����4
���ͣ�
������ĳ�ʼ�ʱ�Ϊ 0��������Դ� 0 ����Ŀ��ʼ
����ɺ��㽫��� 1 ������������ʱ�����Ϊ 1
��ʱ�����ѡ��ʼ 1 �Ż� 2 ����Ŀ
������������ѡ��������Ŀ����������Ҫ��� 2 ����Ŀ�Ի�������ʱ�
��ˣ���������󻯵��ʱ���Ϊ 0 + 1 + 3 = 4

ʾ�� 2��
���룺k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
�����6

��ʾ��
1 <= k <= 10^5
0 <= w <= 10^9
n == profits.length
n == capital.length
1 <= n <= 10^5
0 <= profits[i] <= 10^4
0 <= capital[i] <= 10^9

*/

class Solution {
public:
	int findMaximizedCapital(int k, int w, vector<int> &profits,
		vector<int> &capital) {
		int len = profits.size();
		int idx = 0;
		vector<pair<int, int>> v;
		priority_queue<int> pq;
		for (int i = 0; i < len; ++i) v.push_back({ capital[i], profits[i] });
		sort(v.begin(), v.end());
		for (int i = 0; i < k; ++i) {
			while (idx < len && v[idx].first <= w) {
				pq.push(v[idx].second);
				++idx;
			}
			if (!pq.empty()) {
				w += pq.top();
				pq.pop();
			} else {
				break;
			}
		}
		return w;
	}
};

