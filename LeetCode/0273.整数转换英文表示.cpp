#include "header.h"

/*

将非负整数 num 转换为其对应的英文表示

示例 1：
输入：num = 123
输出："One Hundred Twenty Three"

示例 2：
输入：num = 12345
输出："Twelve Thousand Three Hundred Forty Five"

示例 3：
输入：num = 1234567
输出："One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

提示：
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