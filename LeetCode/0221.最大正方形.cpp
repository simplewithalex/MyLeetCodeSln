#include "header.h"

/*

��һ���� 0 �� 1 ��ɵĶ�ά�����ڣ��ҵ�ֻ���� 1 ����������Σ��������������

ʾ��:

����:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

���: 4

��ʾ��
m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] Ϊ '0' �� '1'

*/

// ��������
// C++ TLE, Java AC
class Solution1 {
public:
	int maximalSquare(vector<vector<char>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		int maxEdgeLen = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (matrix[i][j] == '1') {
					int tempLen = 1;
					bool flag = true;
					while (i + tempLen < rows && j + tempLen < cols && flag) {
						for (int k = 0; k <= tempLen; ++k) {
							if (matrix[i + tempLen][j + k] == '0' || matrix[i + k][j + tempLen] == '0') {
								flag = false;
								break;
							}
						}
						if (flag) ++tempLen;
					}
					maxEdgeLen = max(maxEdgeLen, tempLen);
				}
			}
		}
		return maxEdgeLen * maxEdgeLen;
	}
};
/**
* ���������е�ÿ��Ԫ�أ�ÿ������1���򽫸�Ԫ����Ϊ�����ε����Ͻǣ�
*
* ȷ�������ε����ϽǺ󣬸������Ͻ����ڵ��к��м�����ܵ���������εı߳��������εķ�Χ���ܳ����������������������
* ÿ�����·�����һ���Լ����ҷ�����һ�У��ж��������к����Ƿ���������Ԫ�ض��� 1��
*
*/


// ��̬�滮
class Solution2 {
public:
	int maximalSquare(vector<vector<char>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
		int maxEdgeLen = 0;
		for (int i = 1; i <= rows; ++i)
		{
			for (int j = 1; j <= cols; ++j)
			{
				if (matrix[i - 1][j - 1] == '1')
				{
					dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
					maxEdgeLen = max(maxEdgeLen, dp[i][j]);
				}
			}
		}
		return maxEdgeLen*maxEdgeLen;
	}
};

// �Ż�Ϊһά��̬�滮����
// �з������鸴��
class Solution3 {
public:
	int maximalSquare(vector<vector<char>> &matrix)
	{
		if (matrix.empty() || matrix[0].empty()) return 0;
		int rows = matrix.size(), cols = matrix[0].size();
		vector<int> dp(cols + 1);
		int maxEdgeLen = 0;
		int prev = 0;
		for (int i = 1; i <= rows; ++i)
		{
			for (int j = 1; j <= cols; ++j)
			{
				int temp = dp[j];
				if (matrix[i - 1][j - 1] == '1')
				{
					dp[j] = min(min(dp[j - 1], dp[j]), prev) + 1;
					maxEdgeLen = max(maxEdgeLen, dp[j]);
				}
				else
				{
					dp[j] = 0;
				}
				prev = temp;
			}
		}
		return maxEdgeLen*maxEdgeLen;
	}
};