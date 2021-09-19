#include "header.h"

/*

n�ʺ������о�������ν�n���ʺ������n��n�������ϣ�����ʹ�ʺ�˴�֮�䲻���໥������
����һ������ n ������ n �ʺ����ⲻͬ�Ľ��������������

ʾ�� 1��
���룺n = 4
�����2
���ͣ�����ͼ��ʾ��4 �ʺ��������������ͬ�Ľⷨ��

ʾ�� 2��
���룺n = 1
�����1

��ʾ��
1 <= n <= 9
�ʺ�˴˲����໥������Ҳ����˵���κ������ʺ󶼲��ܴ���ͬһ�����С����л�б���ϡ�

*/

// �ο� 0051.N�ʺ�1
class Solution1 {
public:
	int totalNQueens(int n) {
		int res = 0;
		std::vector<char> flag(5 * n - 2, 0);
		solveNQueens(res, flag, 0, n);
		return res;
	}
private:
	void solveNQueens(int &res, std::vector<char> &flag, int row, int n) {
		if (row == n) {
			++res;
			return;
		}
		for (int col = 0; col < n; ++col) {
			if (flag[col] || flag[row + col + n] || flag[4 * n - 2 + col - row]) continue;
			flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 1;
			solveNQueens(res, flag, row + 1, n);
			flag[col] = flag[n + row + col] = flag[4 * n - 2 + col - row] = 0;
		}
	}
};

// �Ż�Ϊλ���㷽��
class Solution2 {
public:
	int totalNQueens(int n) {
		int res = 0;
		solveNQueens(res, 0, 0, 0, 0, n);
		return res;
	}
private:
	// ����ÿһ�д����Ҷ�Ӧ����λ�Ĵ��ҵ��󣬷�������
	void solveNQueens(int &res, int columns, int diagonals1, int diagonals2, int row, int n) {
		if (row == n) {
			++res;
			return;
		}
		int availablePosition = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));
		while (availablePosition) {
			int position = availablePosition&(-availablePosition);
			availablePosition = availablePosition&(availablePosition - 1);
			solveNQueens(res, columns | position, (diagonals1 | position) << 1, (diagonals2 | position) >> 1, row + 1, n);
		}
	}
};
// https://leetcode-cn.com/problems/n-queens-ii/solution/nhuang-hou-ii-by-leetcode-solution/
// ͬ������������ 0051.N�ʺ�1
