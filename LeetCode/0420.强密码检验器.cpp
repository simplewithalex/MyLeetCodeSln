#include "header.h"

/*

420. ǿ���������

�����������������뱻��Ϊ��ǿ���룺

������ 6 �������� 20 ���ַ����
��������һ��Сд��ĸ������һ����д��ĸ��������һ������
���������������ظ��ַ�(���� "Baaabb0" ��������, ���� "Baaba0" ��ǿ����)
����һ���ַ���password�����ؽ�password�޸ĵ�����ǿ����������Ҫ�������޸Ĳ�������� password �Ѿ���ǿ���룬�򷵻� 0

��һ���޸Ĳ����У�����ԣ�
����һ���ַ��� password���� password ��ɾ��һ���ַ���������һ���ַ����滻 password �е�ĳ���ַ�

ʾ�� 1��
���룺password = "a"
�����5

ʾ�� 2��
���룺password = "aA1"
�����3

ʾ�� 3��
���룺password = "1337C0d3"
�����0

��ʾ��
1 <= password.length <= 50
password ����ĸ�����֡��� '.' ���߸�̾�� '!' ���

*/

class Solution {
public:
	int strongPasswordChecker(string password) {
		int A = 0, B = 0, C = 0;
		for (char c : password) {
			if (c >= 'a' && c <= 'z') A = 1;
			else if (c >= '0' && c <= '9') B = 1;
			else if (c >= 'A' && c <= 'Z') C = 1;
		}
		int m = A + B + C;
		int len = password.size();
		if (len < 6) {
			return max(6 - len, 3 - m);
		} else if (len <= 20) {
			int rep = 0;
			int i = 0;
			while (i < len) {
				int j = i;
				while (j < len && password[j] == password[i]) ++j;
				int cnt = j - i;
				if (cnt >= 3) rep += cnt / 3;
				i = j;
			}
			return max(rep, 3 - m);
		} else {
			int rep = 0;
			vector<int> remainders(3);
			int i = 0;
			while (i < len) {
				int j = i;
				while (j < len && password[j] == password[i]) ++j;
				int cnt = j - i;
				if (cnt >= 3) {
					rep += cnt / 3;
					++remainders[cnt % 3];
				}
				i = j;
			}
			int base = len - 20, cur = base;
			for (int i = 0; i < 3; ++i) {
				if (i == 2) remainders[i] = rep;
				if (remainders[i] && cur) {
					int del = min(remainders[i] * (i + 1), cur);
					cur -= del;
					rep -= del / (i + 1);
				}
			}
			return base + max(rep, 3 - m);
		}
	}
};
// https://leetcode.cn/problems/strong-password-checker/solutions/1387891/by-ac_oier-unp5/comments/2272696
// @author https://leetcode.cn/u/nice-pike0sm/

