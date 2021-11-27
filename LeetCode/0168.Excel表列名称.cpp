#include "header.h"

/*

给你一个整数 columnNumber ，返回它在Excel表中相对应的列名称。

例如：

A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...

示例 1：
输入：columnNumber = 1
输出："A"

示例 2：
输入：columnNumber = 28
输出："AB"

示例 3：
输入：columnNumber = 701
输出："ZY"

示例 4：
输入：columnNumber = 2147483647
输出："FXSHRXW"

提示：
1 <= columnNumber <= 2^31 - 1

*/

class Solution {
public:
	string convertToTitle(int columnNumber) {
		const int base = 26;
		string res;
		while (columnNumber > 0) {
			--columnNumber;
			res.append(1, 'A' + columnNumber % base);
			columnNumber /= base;
		}
		reverse(res.begin(), res.end());
		return res;
	}
};
/*
columnNumber % 26 的结果中 0 - Z , 1 - A , 2 - B, ... , 25 - Y
显然应该是0 - A, ..., 25 - Z 更好, 所以进行columnNumber - 1 偏移操作
*/