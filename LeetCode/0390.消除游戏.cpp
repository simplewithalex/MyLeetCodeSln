#include "header.h"

/*

390. ������Ϸ

�б� arr ���ڷ�Χ [1, n] �е�����������ɣ������ϸ������������� arr Ӧ�������㷨��
�����ң�ɾ����һ�����֣�Ȼ��ÿ��һ������ɾ��һ����ֱ�������б�ĩβ
�ظ�����Ĳ��裬������Ǵ��ҵ���Ҳ���ǣ�ɾ�����Ҳ�����֣�Ȼ��ʣ�µ�����ÿ��һ��ɾ��һ��
�����ظ��������������Һʹ��ҵ�������У�ֱ��ֻʣ��һ������
�������� n ������ arr ���ʣ�µ�����

ʾ�� 1��
���룺n = 9
�����6
���ͣ�
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
arr = [2, 4, 6, 8]
arr = [2, 6]
arr = [6]

ʾ�� 2��
���룺n = 1
�����1

��ʾ��
1 <= n <= 10^9

*/

class Solution {
public:
	int lastRemaining(int n) {
		return n == 1 ? 1 : 2 * (n / 2 + 1 - lastRemaining(n / 2));
	}
};
// https://leetcode.cn/problems/elimination-game/solutions/1187589/gong-shui-san-xie-yue-se-fu-huan-yun-yon-x60m/
// @author https://leetcode.cn/u/ac_oier/

