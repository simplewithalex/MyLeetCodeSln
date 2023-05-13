#include "header.h"

/*

���ݰٶȰٿƣ�������Ϸ��Ӣ����ѧ��Լ�����ζ١������� 1970 �귢����ϸ���Զ�����
����һ������ m �� n �����ӵ���壬ÿһ�����Ӷ����Կ�����һ��ϸ����ÿ��ϸ��������һ����ʼ״̬��
1 ��Ϊ ��ϸ����live������ 0 ��Ϊ ��ϸ����dead����ÿ��ϸ������˸�����λ�ã�ˮƽ����ֱ���Խ��ߣ���ϸ������ѭ�����������涨�ɣ�

�����ϸ����Χ�˸�λ�õĻ�ϸ�����������������λ�û�ϸ��������
�����ϸ����Χ�˸�λ����������������ϸ�������λ�û�ϸ����Ȼ��
�����ϸ����Χ�˸�λ���г���������ϸ�������λ�û�ϸ��������
�����ϸ����Χ������������ϸ�������λ����ϸ�����

��һ��״̬��ͨ������������ͬʱӦ���ڵ�ǰ״̬�µ�ÿ��ϸ�����γɵģ�����ϸ���ĳ�����������ͬʱ�����ġ����� m x n ������� board �ĵ�ǰ״̬��������һ��״̬��

ʾ�� 1��
���룺board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
�����[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]

ʾ�� 2��
���룺board = [[1,1],[1,0]]
�����[[1,1],[1,1]]

��ʾ��
m == board.length
n == board[i].length
1 <= m, n <= 25
board[i][j] Ϊ 0 �� 1

���ף�
�����ʹ��ԭ���㷨�����������ע�⣬��������и�����Ҫͬʱ�����£��㲻���ȸ���ĳЩ���ӣ�Ȼ��ʹ�����ǵĸ��º��ֵ�ٸ����������ӡ�
�����У�����ʹ�ö�ά��������ʾ��塣ԭ���ϣ���������޵ģ�������ϸ����ռ�����߽�ʱ��������⡣�㽫��ν����Щ���⣿

*/

class Solution {
public:
	void gameOfLife(vector<vector<int>> &board) {
		int rows = board.size(), cols = board[0].size();
		vector<char> dx{ 0, 0, 1, 1, 1, -1, -1, -1 };
		vector<char> dy{ 1, -1, 1, -1, 0, 1, -1, 0 };
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				int curX = 0, curY = 0;
				int live = 0;
				for (int k = 0; k < 8; ++k) {
					curX = i + dx[k], curY = j + dy[k];
					if (curX < 0 || curX == rows || curY < 0 || curY == cols) continue;
					if (board[curX][curY] == 1 || board[curX][curY] == 2) ++live;
				}
				if (board[i][j] == 0) {
					if (live == 3) board[i][j] = -1;
				} else {
					if (live < 2 || live > 3) board[i][j] = 2;
				}
			}
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (board[i][j] == 2) board[i][j] = 0;
				if (board[i][j] == -1) board[i][j] = 1;
			}
		}
	}
};
// https://leetcode.cn/problems/game-of-life/solutions/139404/ju-zhen-wen-ti-tong-yong-jie-fa-by-freshrookie/
// @author https://leetcode.cn/u/freshrookie/