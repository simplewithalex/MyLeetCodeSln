#include "header.h"

/*

427. �����Ĳ���

����һ�� n * n ���� grid ������������ 0 �� 1 ��ɡ��������Ĳ�����ʾ�þ��� grid
����Ҫ�����ܱ�ʾ���� grid �� �Ĳ��� �ĸ����

�Ĳ������ݽṹ�У�ÿ���ڲ��ڵ�ֻ���ĸ��ӽڵ�
���⣬ÿ���ڵ㶼���������ԣ�
val������Ҷ�ӽ��������������ֵ��1 ��Ӧ True��0 ��Ӧ False��
ע�⣬�� isLeaf Ϊ False ʱ������԰� True ���� False ��ֵ���ڵ㣬����ֵ���ᱻ������� ����

isLeaf: ������ڵ���һ��Ҷ�ӽ��ʱΪ True��������� 4 ���ӽڵ���Ϊ False

class Node {
public boolean val;
public boolean isLeaf;
public Node topLeft;
public Node topRight;
public Node bottomLeft;
public Node bottomRight;
}

���ǿ��԰����²���Ϊ��ά���򹹽��Ĳ�����
�����ǰ�����ֵ��ͬ������ȫΪ 0 ����ȫΪ 1������ isLeaf ��Ϊ True ���� val ��Ϊ������Ӧ��ֵ�������ĸ��ӽڵ㶼��Ϊ Null Ȼ��ֹͣ
�����ǰ�����ֵ��ͬ���� isLeaf ��Ϊ False�� �� val ��Ϊ����ֵ��Ȼ������ͼ��ʾ������ǰ���񻮷�Ϊ�ĸ�������
ʹ���ʵ���������ݹ�ÿ���ӽڵ�

�Ĳ�����ʽ��
�㲻��Ҫ�Ķ����������������⡣ֻ�е������˽������ʽʱ�Ż������������Ϊʹ�ò���������Ĳ��������л���ʽ������ null ��ʾ·����ֹ���������治���ڽڵ�
��������������л��ǳ����ơ�Ψһ�������ǽڵ����б���ʽ��ʾ [isLeaf, val]
��� isLeaf ���� val ��ֵΪ True �����ʾ�����б� [isLeaf, val] �е�ֵΪ 1 ����� isLeaf ���� val ��ֵΪ False �����ʾֵΪ 0

ʾ�� 1��
���룺grid = [[0,1],[1,0]]
�����[[0,1],[1,0],[1,1],[1,1],[1,0]]
���ͣ���ʾ���Ľ������£�
��ע�⣬�������Ĳ�����ͼʾ�У�0 ��ʾ false��1 ��ʾ True

ʾ�� 2��
���룺grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
�����[[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
���ͣ������е�����ֵ������ͬ�����ǽ����񻮷�Ϊ�ĸ�������
topLeft��bottomLeft �� bottomRight ��������ͬ��ֵ
topRight ���в�ͬ��ֵ��������ǽ����ٷ�Ϊ 4 ������������ÿ�������񶼾�����ͬ��ֵ
��������ͼ��ʾ��


��ʾ��
n == grid.length == grid[i].length
n == 2^x ���� 0 <= x <= 6

*/

// Definition for a QuadTree node.
class Node {
public:
	bool val;
	bool isLeaf;
	Node *topLeft;
	Node *topRight;
	Node *bottomLeft;
	Node *bottomRight;

	Node() {
		val = false;
		isLeaf = false;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight,
		Node *_bottomLeft, Node *_bottomRight) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = _topLeft;
		topRight = _topRight;
		bottomLeft = _bottomLeft;
		bottomRight = _bottomRight;
	}
};

class Solution1 {
public:
	Node *construct(vector<vector<int>> &grid) {
		return helper(grid, 0, grid.size(), 0, grid.size());
	}
	Node *helper(vector<vector<int>> &grid, int r0, int r1, int c0, int c1) {
		for (int i = r0; i < r1; ++i) {
			for (int j = c0; j < c1; ++j) {
				if (grid[i][j] != grid[r0][c0]) {
					return new Node(
						true, false,
						helper(grid, r0, (r0 + r1) / 2, c0, (c0 + c1) / 2),
						helper(grid, r0, (r0 + r1) / 2, (c0 + c1) / 2, c1),
						helper(grid, (r0 + r1) / 2, r1, c0, (c0 + c1) / 2),
						helper(grid, (r0 + r1) / 2, r1, (c0 + c1) / 2, c1));
				}
			}
		}
		return new Node(grid[r0][c0], true);
	}
};


// ��άǰ׺��
class Solution2 {
public:
	vector<vector<int>> sum;
	Node *construct(vector<vector<int>> &grid) {
		int len = grid.size();
		sum.resize(len + 1, vector<int>(len + 1));
		for (int i = 1; i <= len; ++i) {
			for (int j = 1; j <= len; ++j) {
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] +
					grid[i - 1][j - 1];
			}
		}
		return helper(grid, 0, 0, len, len);
	}
	int getSum(int r0, int c0, int r1, int c1) {
		return sum[r1][c1] - sum[r1][c0] - sum[r0][c1] + sum[r0][c0];
	}
	Node *helper(vector<vector<int>> &grid, int r0, int c0, int r1, int c1) {
		int total = getSum(r0, c0, r1, c1);
		if (total == 0) return new Node(false, true);
		if (total == (r1 - r0) * (c1 - c0)) return new Node(true, true);
		return new Node(true, false,
			helper(grid, r0, c0, (r0 + r1) / 2, (c0 + c1) / 2),
			helper(grid, r0, (c0 + c1) / 2, (r0 + r1) / 2, c1),
			helper(grid, (r0 + r1) / 2, c0, r1, (c0 + c1) / 2),
			helper(grid, (r0 + r1) / 2, (c0 + c1) / 2, r1, c1));
	}
};

