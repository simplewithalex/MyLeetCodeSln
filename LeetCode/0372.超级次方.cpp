#include "header.h"

/*

��������Ǽ��� ab �� 1337 ȡģ��a ��һ����������b ��һ���ǳ�����������һ���������ʽ����


ʾ�� 1��
���룺a = 2, b = [3]
�����8

ʾ�� 2��
���룺a = 2, b = [1,0]
�����1024

ʾ�� 3��
���룺a = 1, b = [4,3,3,8,5,2]
�����1

ʾ�� 4��
���룺a = 2147483647, b = [2,0,0]
�����1198

��ʾ��
1 <= a <= 2^31 - 1
1 <= b.length <= 2000
0 <= b[i] <= 9
b ����ǰ�� 0

*/


class Solution {
private:
	int MOD = 1337;

public:
	int superPow(int a, vector<int>& b) { return helper(a, b, b.size() - 1); }

private:
	int helper(int a, vector<int>& b, int idx) {
		if (idx == -1) return 1;
		return (quickPow(helper(a, b, idx - 1), 10) * quickPow(a, b[idx])) % MOD;
	}
	int quickPow(int a, int b) {
		a %= MOD;
		int res = 1;
		while (b) {
			if (b & 1) res = (res * a) % MOD;
			a = (a * a) % MOD;
			b >>= 1;
		}
		return res;
	}
};
// https://leetcode.cn/problems/super-pow/solutions/1139068/gong-shui-san-xie-di-gui-kuai-su-mi-ying-yx1j/
// @author https://leetcode.cn/u/ac_oier/

