#include "header.h"

/*

���Ǹ����� num ת��Ϊ���Ӧ��Ӣ�ı�ʾ

ʾ�� 1��
���룺num = 123
�����"One Hundred Twenty Three"

ʾ�� 2��
���룺num = 12345
�����"Twelve Thousand Three Hundred Forty Five"

ʾ�� 3��
���룺num = 1234567
�����"One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

��ʾ��
0 <= num <= 2^31 - 1

*/

class Solution {
private:
	vector<string> num2str_small{"Zero", "One", "Two", "Three", "Four",
		                         "Five", "Six", "Seven", "Eight", "Nine",
		                         "Ten", "Eleven", "Twelve", "Thirteen",
		                         "Fourteen", "Fifteen", "Sixteen", "Seventeen",
		                         "Eighteen", "Nineteen"};
	vector<string> num2str_medium{"", "", "Twenty", "Thirty", "Forty", "Fifty",
		                          "Sixty", "Seventy", "Eighty", "Ninety"};
	vector<string> num2str_large{"Billion", "Million", "Thousand", ""};
	string num2str(int x) {
		string cur;
		if (x >= 100) {
			cur += num2str_small[x / 100] + " Hundred ";
			x %= 100;
		}
		if (x >= 20) {
			cur += num2str_medium[x / 10] + " ";
			x %= 10;
		}
		if (x != 0) cur += num2str_small[x] + " ";
		return cur;
	}

public:
	string numberToWords(int num) {
		if (num == 0) return num2str_small[0];
		string ans;
		for (int i = 1E9, j = 0; i >= 1; i /= 1000, ++j) {
			if (num < i) continue;
			ans.append(num2str(num / i) + num2str_large[j] + " ");
			num %= i;
		}
		while (ans.back() == ' ') ans.pop_back();
		return ans;
	}
};
// https://leetcode.cn/problems/integer-to-english-words/solutions/1040978/gong-shui-san-xie-zi-fu-chuan-da-mo-ni-b-0my6/
// @author https://leetcode.cn/u/ac_oier/