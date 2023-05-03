#include "header.h"

/*

����һ����������citations������ citations[i] ��ʾ�о��ߵĵ� i ƪ���ı����õĴ�����citations �Ѿ������������С����㲢���ظ��о��ߵ� h ָ����
hָ���Ķ��壺h���������ô�������high citations����һ��������Ա�� h ָ����ָ���������ģ�n ƪ�����У��ܹ��� h ƪ���ķֱ����������� h �Ρ�
������Ʋ�ʵ�ֶ���ʱ�临�Ӷȵ��㷨��������⡣

ʾ�� 1��
���룺citations = [0,1,3,5,6]
�����3
���ͣ����������ʾ�о����ܹ��� 5 ƪ���ģ�ÿƪ������Ӧ�ı������� 0, 1, 3, 5, 6 �Ρ�
�����о����� 3 ƪ����ÿƪ ���� �������� 3 �Σ�������ƪ����ÿƪ������ ������ 3 �Σ��������� h ָ���� 3

ʾ�� 2��
���룺citations = [1,2,100]
�����2

��ʾ��
n == citations.length
1 <= n <= 10^5
0 <= citations[i] <= 1000
citations ����������

*/

class Solution {
public:
	int hIndex(vector<int> &citations) {
		int len = citations.size();
		if (citations[len - 1] == 0) return 0;
		int lo = 0, hi = len - 1;
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			citations[mi] < len - mi ? lo = mi + 1 : hi = mi;
		}
		return len - lo;
	}
};
// https://leetcode.cn/problems/h-index-ii/solutions/20185/jian-er-zhi-zhi-er-fen-cha-zhao-by-liweiwei1419-2/
// @author https://leetcode.cn/u/liweiwei1419/