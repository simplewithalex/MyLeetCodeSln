#include "header.h"

/*

给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数
如果小数部分为循环小数，则将循环的部分括在括号内
如果存在多个答案，只需返回 任意一个
对于所有给定的输入，保证 答案字符串的长度小于 10^4

示例 1：
输入：numerator = 1, denominator = 2
输出："0.5"

示例 2：
输入：numerator = 2, denominator = 1
输出："2"

示例 3：
输入：numerator = 2, denominator = 3
输出："0.(6)"

示例 4：
输入：numerator = 4, denominator = 333
输出："0.(012)"

示例 5：
输入：numerator = 1, denominator = 5
输出："0.2"

提示：
-2^31 <= numerator, denominator <= 2^31 - 1
denominator != 0

*/

class Solution {
public:
	string fractionToDecimal(int numerator, int denominator) {
		if (numerator == 0) return "0";
		string decimal;
		if ((numerator > 0) ^ (denominator > 0)) decimal.append("-");
		// 本题目INT_MIN不太好处理，统一转为长整型
		long long dividend = abs((long long)numerator);
		long long divisor = abs((long long)denominator);
		long long remainder = dividend%divisor;
		decimal.append(to_string(dividend / divisor));
		if (remainder == 0) return decimal;
		decimal.append(".");
		unordered_map<long long, int> m;
		while (remainder != 0) {
			if (m.count(remainder) != 0) {
				decimal.insert(m[remainder], "(");
				decimal.append(")");
				break;
			}
			m[remainder] = decimal.size();
			remainder *= 10;
			decimal.append(to_string(remainder / divisor));
			remainder %= divisor;
		}
		return decimal;
	}
};