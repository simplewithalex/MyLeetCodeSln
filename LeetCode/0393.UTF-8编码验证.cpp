#include "header.h"

/*

393. UTF-8 ������֤

����һ����ʾ���ݵ��������� data ���������Ƿ�Ϊ��Ч�� UTF-8 ����

UTF-8 �е�һ���ַ����ܵĳ���Ϊ 1 �� 4 �ֽڣ���ѭ���µĹ���

���� 1 �ֽ� ���ַ����ֽڵĵ�һλ��Ϊ 0 ������ 7 λΪ������ŵ� unicode ��
���� n �ֽ� ���ַ� (n > 1)����һ���ֽڵ�ǰ n λ����Ϊ1���� n+1 λ��Ϊ 0 �������ֽڵ�ǰ��λһ����Ϊ 10 ��ʣ�µ�û���ἰ�Ķ�����λ��ȫ��Ϊ������ŵ� unicode ��
���� UTF-8 ����Ĺ�����ʽ��


      Number of Bytes  |        UTF-8 octet sequence
				       |              (binary)
   --------------------+---------------------------------------------
		    1          | 0xxxxxxx
		    2          | 110xxxxx 10xxxxxx
		    3          | 1110xxxx 10xxxxxx 10xxxxxx
		    4          | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
x ��ʾ��������ʽ��һλ�������� 0 �� 1

ע�⣺�������������顣ֻ��ÿ�������� ��� 8 ����Чλ �����洢���ݡ�����ζ��ÿ������ֻ��ʾ 1 �ֽڵ�����


ʾ�� 1��
���룺data = [197,130,1]
�����true
���ͣ����ݱ�ʾ�ֽ�����:11000101 10000010 00000001��
������Ч�� utf-8 ���룬Ϊһ�� 2 �ֽ��ַ�������һ�� 1 �ֽ��ַ���

ʾ�� 2��
���룺data = [235,140,4]
�����false
���ͣ����ݱ�ʾ 8 λ������: 11101011 10001100 00000100.
ǰ 3 λ���� 1 ���� 4 λΪ 0 ��ʾ����һ�� 3 �ֽ��ַ���
��һ���ֽ��ǿ�ͷΪ 10 �������ֽڣ�������ȷ�ġ�
���ڶ��������ֽڲ��� 10 ��ͷ�������ǲ����Ϲ���ġ�

��ʾ:
1 <= data.length <= 2 * 10^4
0 <= data[i] <= 255

*/

class Solution {
public:
	bool validUtf8(vector<int> &data) {
		int len = data.size();
		int idx = 0;
		while (idx < len) {
			int temp = data[idx], j = 7;
			while (j >= 0 && ((temp >> j) & 1)) --j;
			int cnt = 7 - j;
			if (cnt == 1 || cnt > 4) return false;
			if (idx + cnt > len) return false;
			for (int k = idx + 1; k < idx + cnt; ++k) {
				if (((data[k] >> 7) & 1) && !((data[k] >> 6) & 1)) continue;
				return false;
			}
			if (cnt == 0) ++idx;
			else idx += cnt;
		}
		return true;
	}
};

