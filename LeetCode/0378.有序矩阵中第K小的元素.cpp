#include "header.h"
/*

378. ��������е� K С��Ԫ��

����һ�� n x n ���� matrix ������ÿ�к�ÿ��Ԫ�ؾ������������ҵ������е� k С��Ԫ��
��ע�⣬���� ����� �ĵ� k СԪ�أ������ǵ� k �� ��ͬ ��Ԫ��

������ҵ�һ���ڴ渴�Ӷ����� O(n^2) �Ľ������

ʾ�� 1��
���룺matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
�����13
���ͣ������е�Ԫ��Ϊ [1,5,9,10,11,12,13,13,15]���� 8 СԪ���� 13

ʾ�� 2��
���룺matrix = [[-5]], k = 1
�����-5

��ʾ��
n == matrix.length
n == matrix[i].length
1 <= n <= 300
-10^9 <= matrix[i][j] <= 10^9
��Ŀ���� ��֤ matrix �е������к��ж��� �ǵݼ�˳�� ����
1 <= k <= n^2

���ף�
���ܷ���һ���㶨���ڴ�(�� O(1) �ڴ渴�Ӷ�)������������?
������ O(n) ��ʱ�临�Ӷ��½�����������?�����������������˵����̫��ǰ�ˣ�������ᷢ���Ķ���ƪ���£� this paper ������Ȥ

*/

class Solution {
public:
	int kthSmallest(vector<vector<int>> &matrix, int k) {
		int len = matrix.size();
		int lo = matrix[0][0];
		int hi = matrix[len - 1][len - 1];
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			check(matrix, mi, k, len) ? hi = mi : lo = mi + 1;
		}
		return lo;
	}

private:
	bool check(vector<vector<int>> &matrix, int mi, int k, int len) {
		int i = len - 1, j = 0;
		int num = 0;
		while (i >= 0 && j < len) {
			if (matrix[i][j] <= mi) {
				num += i + 1;
				++j;
			} else {
				--i;
			}
		}
		return num >= k;
	}
};

