#include "header.h"

/*

546. 移除盒子

给出一些不同颜色的盒子 boxes ，盒子的颜色由不同的正数表示

你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k * k 个积分

返回 你能获得的最大积分和

示例 1：
输入：boxes = [1,3,2,2,2,3,4,3,1]
输出：23
解释：
[1, 3, 2, 2, 2, 3, 4, 3, 1]
----> [1, 3, 3, 4, 3, 1] (3*3=9 分)
----> [1, 3, 3, 3, 1] (1*1=1 分)
----> [1, 1] (3*3=9 分)
----> [] (2*2=4 分)

示例 2：
输入：boxes = [1,1,1]
输出：9

示例 3：
输入：boxes = [1]
输出：1

提示：
1 <= boxes.length <= 100
1 <= boxes[i] <= 100

*/

class Solution {
private:
	vector<vector<vector<int>>> memo;

public:
	int removeBoxes(vector<int> &boxes) {
		int len = boxes.size();
		memo.resize(len, vector<vector<int>>(len, vector<int>(len, -1)));
		return helper(boxes, 0, len - 1, 0);
	}

private:
	int helper(vector<int> &boxes, int l, int r, int k) {
		if (l > r) return 0;
		if (memo[l][r][k] != -1) return memo[l][r][k];
		int res = 0;
		int r1 = r, k1 = k;
		while (r1 > l && boxes[r1] == boxes[r1 - 1]) {
			--r1;
			++k1;
		}
		res = helper(boxes, l, r1 - 1, 0) + (k1 + 1) * (k1 + 1);
		for (int i = l; i < r1; ++i) {
			if (boxes[i] == boxes[r1]) {
				res = max(res, helper(boxes, l, i, k1 + 1) +
					helper(boxes, i + 1, r1 - 1, 0));
			}
		}
		return memo[l][r][k] = res;
	}
};


