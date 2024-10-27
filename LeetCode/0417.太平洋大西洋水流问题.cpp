#include "header.h"

/*

417. ̫ƽ�������ˮ������

��һ�� m �� n �ľ��ε��죬�� ̫ƽ�� �� ������ ���ڡ� ��̫ƽ�� ���ڴ�½����߽���ϱ߽磬�� �������� ���ڴ�½���ұ߽���±߽�

��������ָ��һ�������ɷ��ε�Ԫ����ɵ����񡣸���һ�� m x n ���������� heights �� heights[r][c] ��ʾ���� (r, c) �ϵ�Ԫ�� ���ں�ƽ��ĸ߶�

������ˮ�϶࣬������ڵ�Ԫ��ĸ߶� С�ڻ���� ��ǰ��Ԫ��ĸ߶ȣ���ˮ����ֱ���򱱡��ϡ��������������ڵ�Ԫ��ˮ���ԴӺ��󸽽����κε�Ԫ�����뺣��

������������ result �� 2D �б� ������ result[i] = [ri, ci] ��ʾ��ˮ�ӵ�Ԫ�� (ri, ci) ���� �ȿ�����̫ƽ��Ҳ�����������

ʾ�� 1��
����: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
���: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

ʾ�� 2��
����: heights = [[2,1],[1,2]]
���: [[0,0],[0,1],[1,0],[1,1]]

��ʾ��
m == heights.length
n == heights[r].length
1 <= m, n <= 200
0 <= heights[r][c] <= 10^5

*/


const int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

// BFS
class Solution1 {
public:
	vector<vector<int>> heights;
	void bfs(int row, int col, vector<vector<char>> &visited) {
		if (visited[row][col]) return;
		int rows = heights.size(), cols = heights[0].size();
		visited[row][col] = true;
		queue<vector<int>> q;
		q.push({ row, col });
		while (!q.empty()) {
			vector<int> tmp = q.front();
			q.pop();
			int row = tmp[0], col = tmp[1];
			for (int i = 0; i < 4; ++i) {
				int newRow = row + dirs[i][0], newCol = col + dirs[i][1];
				if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
					heights[newRow][newCol] >= heights[row][col] &&
					!visited[newRow][newCol]) {
					visited[newRow][newCol] = true;
					q.push({ newRow, newCol });
				}
			}
		}
	}
	vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
		this->heights = heights;
		int rows = heights.size(), cols = heights[0].size();
		vector<vector<char>> pacific(rows, vector<char>(cols, false));
		vector<vector<char>> atlantic(rows, vector<char>(cols, false));
		for (int i = 0; i < rows; ++i) {
			bfs(i, 0, pacific);
		}
		for (int j = 0; j < cols; ++j) {
			bfs(0, j, pacific);
		}
		for (int i = 0; i < rows; ++i) {
			bfs(i, cols - 1, atlantic);
		}
		for (int j = 0; j < cols; ++j) {
			bfs(rows - 1, j, atlantic);
		}
		vector<vector<int>> result;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (pacific[i][j] && atlantic[i][j]) {
					result.push_back({ i, j });
				}
			}
		}
		return result;
	}
};


// DFS
class Solution2 {
public:
	vector<vector<int>> heights;
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
		this->heights = heights;
		int rows = heights.size(), cols = heights[0].size();
		vector<vector<char>> pacific(rows, vector<char>(cols, false));
		vector<vector<char>> atlantic(rows, vector<char>(cols, false));
		for (int i = 0; i < rows; ++i) {
			dfs(i, 0, pacific);
		}
		for (int j = 0; j < cols; ++j) {
			dfs(0, j, pacific);
		}
		for (int i = 0; i < rows; ++i) {
			dfs(i, cols - 1, atlantic);
		}
		for (int j = 0; j < cols; ++j) {
			dfs(rows - 1, j, atlantic);
		}
		vector<vector<int>> result;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (pacific[i][j] && atlantic[i][j]) {
					result.push_back({ i, j });
				}
			}
		}
		return result;
	}
	void dfs(int row, int col, vector<vector<char>>& visted) {
		int rows = visted.size();
		int cols = visted[0].size();
		if (visted[row][col]) return;
		visted[row][col] = true;
		for (int i = 0; i < 4; ++i) {
			int newRow = row + dirs[i][0], newCol = col + dirs[i][1];
			if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
				heights[newRow][newCol] >= heights[row][col]) {
				dfs(newRow, newCol, visted);
			}
		}
	}
};

