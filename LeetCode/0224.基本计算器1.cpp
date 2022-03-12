#include "header.h"

/*

给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
注意:不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。

示例 1：
输入：s = "1 + 1"
输出：2

示例 2：
输入：s = " 2-1 + 2 "
输出：3

示例 3：
输入：s = "(1+(4+5+2)-3)+(6+8)"
输出：23


提示：
1 <= s.length <= 3 * 10^5
s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
s 表示一个有效的表达式
'+' 不能用作一元运算(例如， "+1" 和 "+(2 + 3)" 无效)
'-' 可以用作一元运算(即 "-1" 和 "-(2 + 3)" 是有效的)
输入中不存在两个连续的操作符
每个数字和运行的计算将适合于一个有符号的 32位 整数

*/

// 双栈方法（通用）
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
					} else {
						ops.pop();
						break;
					}
				}
			} else if (isdigit(c)) {
				int curNum = 0;
				int j = i;
				while (j < len&&isdigit(s[j])) curNum = curNum * 10 + (s[j++] - '0');
				nums.push(curNum);
				i = j - 1;
			} else if (c == '+' || c == '-') {
				if (i > 0 && s[i - 1] == '(') nums.push(0);
				while (!ops.empty() && ops.top() != '(') calc(nums, ops);
				ops.push(c);
			}
		}
		while (!ops.empty()) calc(nums, ops);
		return nums.top();
	}

private:
	void calc(stack<int> &nums, stack<char> &ops) {
		if (nums.size() < 2 || ops.empty()) return;
		int b = nums.top();
		nums.pop();
		int a = nums.top();
		nums.pop();
		char op = ops.top();
		ops.pop();
		nums.push(op == '+' ? a + b : a - b);
	}
};
// https://leetcode-cn.com/problems/basic-calculator/solution/shuang-zhan-jie-jue-tong-yong-biao-da-sh-olym/

// 使用一个栈
class Solution2 {
public:
	int calculate(string s) {
		stack<char> ops;
		int sign = 1;
		ops.push(sign);
		int len = s.size();
		int res = 0;
		for (int i = 0; i < len; ++i) {
			if (s[i] == '+') { sign = ops.top(); }
			else if (s[i] == '-') { sign = -ops.top(); }
			else if (s[i] == '(') { ops.push(sign); }
			else if (s[i] == ')') { ops.pop(); }
			else if (isdigit(s[i])) {
				int curNum = 0;
				int j = i;
				while (j < len&&isdigit(s[j])) {
					curNum = curNum * 10 + (s[j++] - '0');
				}
				i = j - 1;
				res += sign*curNum;
			}
		}
		return res;
	}
};
// LeetCode官方题解：https://leetcode-cn.com/problems/basic-calculator/solution/ji-ben-ji-suan-qi-by-leetcode-solution-jvir/