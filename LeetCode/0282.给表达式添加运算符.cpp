#include "header.h"

/*

给定一个仅包含数字 0-9 的字符串 num 和一个目标值整数 target，在 num 的数字之间添加 二元 运算符（不是一元）+、- 或 *，返回所有能够得到 target 的表达式。
注意，返回表达式中的操作数 不应该 包含前导零。

示例 1:
输入: num = "123", target = 6
输出: ["1+2+3", "1*2*3"]
解释: “1*2*3” 和 “1+2+3” 的值都是6

示例 2:
输入: num = "232", target = 8
输出: ["2*3+2", "2+3*2"]
解释: “2*3+2” 和 “2+3*2” 的值都是8

示例 3:
输入: num = "3456237490", target = 9191
输出: []
解释: 表达式 “3456237490” 无法得到 9191

提示：
1 <= num.length <= 10
num 仅含数字
-2^31 <= target <= 2^31 - 1

*/

class Solution {
public:
	vector<string> addOperators(string num, int target) {
		this->target = target;
		string expr;
		backtrack(num, 0, expr, 0, 0);
		return this->res;
	}

private:
	vector<string> res;
	int target = 0;
	void backtrack(const string &num, int idx, string &expr, long long cnt,
		long long lastMulti) {
		int len = num.size();
		if (idx == len) {
			if (cnt == target) res.push_back(expr);
			else return;
		}
		int opIdx = expr.size();
		long long val = 0;
		if (idx > 0) expr.push_back(0);
		for (int j = idx; j < len && (j == idx || num[idx] != '0'); ++j) {
			val = val * 10 + num[j] - '0';
			expr.push_back(num[j]);
			if (idx == 0) {
				backtrack(num, j + 1, expr, val, val);
			} else {
				expr[opIdx] = '+';
				backtrack(num, j + 1, expr, cnt + val, val);
				expr[opIdx] = '-';
				backtrack(num, j + 1, expr, cnt - val, -val);
				expr[opIdx] = '*';
				backtrack(num, j + 1, expr, cnt - lastMulti + lastMulti * val, lastMulti * val);
			}
		}
		expr.resize(opIdx);
	}
};

// https://leetcode.cn/problems/expression-add-operators/solutions/1048321/gei-biao-da-shi-tian-jia-yun-suan-fu-by-2o1s7/
// @author 力扣官方题解