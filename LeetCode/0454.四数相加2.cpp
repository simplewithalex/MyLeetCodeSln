#include "header.h"

/*

454. ������� II

�����ĸ��������� nums1��nums2��nums3 �� nums4 �����鳤�ȶ��� n ����������ж��ٸ�Ԫ�� (i, j, k, l) �����㣺
0 <= i, j, k, l < n
nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

ʾ�� 1��
���룺nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
�����2
���ͣ�
����Ԫ�����£�
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

ʾ�� 2��
���룺nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
�����1

��ʾ��
n == nums1.length
n == nums2.length
n == nums3.length
n == nums4.length
1 <= n <= 200
-2^28 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2^28

*/

class Solution {
public:
	int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
		vector<int> &nums4) {
		unordered_map<int, int> cnt;
		for (int n1 : nums1) {
			for (int n2 : nums2) {
				++cnt[n1 + n2];
			}
		}
		int ans = 0;
		for (int n3 : nums3) {
			for (int n4 : nums4) {
				ans += cnt[-n3 - n4];
			}
		}
		return ans;
	}
};
