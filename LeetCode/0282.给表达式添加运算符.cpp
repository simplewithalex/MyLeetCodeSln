#include "header.h"

/*

����һ������������ 0-9 ���ַ��� num ��һ��Ŀ��ֵ���� target���� num ������֮����� ��Ԫ �����������һԪ��+��- �� *�����������ܹ��õ� target �ı��ʽ��
ע�⣬���ر��ʽ�еĲ����� ��Ӧ�� ����ǰ���㡣

ʾ�� 1:
����: num = "123", target = 6
���: ["1+2+3", "1*2*3"]
����: ��1*2*3�� �� ��1+2+3�� ��ֵ����6

ʾ�� 2:
����: num = "232", target = 8
���: ["2*3+2", "2+3*2"]
����: ��2*3+2�� �� ��2+3*2�� ��ֵ����8

ʾ�� 3:
����: num = "3456237490", target = 9191
���: []
����: ���ʽ ��3456237490�� �޷��õ� 9191

��ʾ��
1 <= num.length <= 10
num ��������
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
// @author ���۹ٷ����