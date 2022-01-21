#include "header.h"

/*

����һ����ά�����һ�����ʣ��ҳ��õ����Ƿ�����������С�
���ʱ��밴����ĸ˳��ͨ�����ڵĵ�Ԫ���ڵ���ĸ���ɣ����С����ڡ���Ԫ������Щˮƽ���ڻ�ֱ���ڵĵ�Ԫ��
ͬһ����Ԫ���ڵ���ĸ�������ظ�ʹ�á�

ʾ��:
board =
[
 ['A','B','C','E'],
 ['S','F','C','S'],
 ['A','D','E','E']
]

���� word = "ABCCED", ���� true.
���� word = "SEE", ���� true.
���� word = "ABCB", ���� false.

*/

class Solution {
public:
	bool exist(vector<vector<char>> &board, string word)
	{
		for (int i = 0; i < board.size(); ++i)
		{
			for (int j = 0; j < board[0].size(); ++j)
			{
				if (backTrack(board, i, j, word, 0))
					return true;
			}
		}
		return false;
	}
	bool backTrack(vector<vector<char>> &board, int i, int j, string &word, int index)
	{
		if (index == word.size()) return true;
		if (i>board.size() - 1 || i < 0 || j<0 || j>board[0].size() - 1 || board[i][j] != word[index])
			return false;
		board[i][j] = '*';
		bool result = backTrack(board, i - 1, j, word, index + 1) ||
			backTrack(board, i + 1, j, word, index + 1) ||
			backTrack(board, i, j - 1, word, index + 1) ||
			backTrack(board, i, j + 1, word, index + 1);
		board[i][j] = word[index];
		return result;
	}
};