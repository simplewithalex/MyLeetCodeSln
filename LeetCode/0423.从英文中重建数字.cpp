#include "header.h"

/*

423. ��Ӣ�����ؽ�����

����һ���ַ��� s �����а�����ĸ˳����ҵ���Ӣ�ĵ��ʱ�ʾ���������֣�0-9��
�� ���� ����ԭʼ������

ʾ�� 1��
���룺s = "owoztneoer"
�����"012"

ʾ�� 2��
���룺s = "fviefuro"
�����"45"

��ʾ��
1 <= s.length <= 10^5
s[i] Ϊ ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"] ��Щ�ַ�֮һ
s ��֤��һ��������ĿҪ����ַ���

*/

class Solution {
public:
	vector<string> ss{ "zero", "one", "two",   "three", "four",
		"five", "six", "seven", "eight", "nine" };
	vector<int> priority{ 0, 8, 6, 3, 2, 7, 5, 9, 4, 1 };
	string originalDigits(string s) {
		int len = s.size();
		int cnts[26] = {};
		for (int i = 0; i < len; ++i) ++cnts[s[i] - 'a'];
		string ans;
		for (int p : priority) {
			int k = INT_MAX;
			for (char c : ss[p]) k = min(k, cnts[c - 'a']);
			for (char c : ss[p]) cnts[c - 'a'] -= k;
			while (k-- > 0) ans += (p + '0');
		}
		sort(ans.begin(), ans.end());
		return ans;
	}
};
// https://leetcode.cn/problems/reconstruct-original-digits-from-english/solutions/1118849/gong-shui-san-xie-nao-jin-ji-zhuan-wan-m-vg7a/
// @author https://leetcode.cn/u/ac_oier/


