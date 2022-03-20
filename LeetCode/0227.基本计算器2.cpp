#include "header.h"

/*

给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
整数除法仅保留整数部分。
你可以假设给定的表达式总是有效的。所有中间结果将在 [-2^31, 2^31 - 1] 的范围内。

注意：不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。

示例 1：
输入：s = "3+2*2"
输出：7

示例 2：
输入：s = " 3/2 "
输出：1

示例 3：
输入：s = " 3+5 / 2 "
输出：5

提示：
1 <= s.length <= 3 * 10^5
s 由整数和算符 ('+', '-', '*', '/') 组成，中间由一些空格隔开
s 表示一个 有效表达式
表达式中的所有整数都是非负整数，且在范围 [0, 2^31 - 1] 内
题目数据保证答案是一个 32-bit 整数

*/

// 根据 0224. 基本计算器1 双栈通用解法扩展
class Solution1 {
public:
	int calculate(string s) {
		stack<int> nums;
		stack<char> ops;
		int len = s.size();
		nums.push(0);
		for (int i = 0; i < len; ++i) {
			char c = s[i];
			if (c == '(') {
				ops.push('(');
			} else if (c == ')') {
				while (!ops.empty()) {
					if (ops.top() != '(') {
						calc(nums, ops);
					}
					else {
						ops.pop();
						break;
					}
				}
			} else if (isdigit(c)) {
				int curNum = 0;
				int j = i;
				while (j < len && isdigit(s[j])) curNum = curNum * 10 + (s[j++] - '0');
				nums.push(curNum);
				i = j - 1;
			} else {
				if (isspace(c)) continue;
				if (i > 0 && s[i - 1] == '(') nums.push(0);
				while (!ops.empty() && ops.top() != '(') {
					char prev = ops.top();
					if (prioMap[prev] >= prioMap[c]) calc(nums, ops);
					else break;
				}
				ops.push(c);
			}
		}
		while (!ops.empty()) calc(nums, ops);
		return nums.top();
	}

private:
	unordered_map<char, int> prioMap{ { '-', 1 },{ '+', 1 },{ '*', 2 },{ '/', 2 } };
	void calc(stack<int> &nums, stack<char> &ops) {
		if (nums.size() < 2 || ops.empty()) return;
		int b = nums.top();
		nums.pop();
		int a = nums.top();
		nums.pop();
		char op = ops.top();
		ops.pop();
		int ans = 0;
		switch (op) {
		case '+':
			ans = a + b;
			break;
		case '-':
			ans = a - b;
			break;
		case '*':
			ans = a * b;
			break;
		case '/':
			ans = a / b;
			break;
		default:
			break;
		}
		nums.push(ans);
	}
};

// 使用一个栈
class Solution2 {
public:
	int calculate(string s) {
		stack<int> stk;
		char preOps = '+';
		int len = s.size();
		int num = 0;
		for (int i = 0; i < len; ++i) {
			if (isdigit(s[i])) {
				int j = i;
				while (j < len&&isdigit(s[j])) num = num * 10 + (s[j++] - '0');
				i = j - 1;
			}
			if (!isdigit(s[i]) && s[i] != ' ' || i == len - 1) {
				switch (preOps) {
				case '+':
					stk.push(num);
					break;
				case '-':
					stk.push(-num);
					break;
				case '*':
					stk.top() *= num;
					break;
				case '/':
					stk.top() /= num;
				default:
					break;
				}
				preOps = s[i];
				num = 0;
			}
		}
		int res = 0;
		while (!stk.empty()) {
			res += stk.top();
			stk.pop();
		}
		return res;
	}
};