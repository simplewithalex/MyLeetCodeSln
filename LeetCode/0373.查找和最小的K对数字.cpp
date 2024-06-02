#include "header.h"

/*

373. ���Һ���С�� K ������

���������Էǵݼ�˳�����е��������� nums1 �� nums2���Լ�һ������ k

����һ��ֵ (u,v)�����е�һ��Ԫ������ nums1���ڶ���Ԫ������ nums2

���ҵ�����С�� k ������ (u1,v1)��(u2,v2)  ...  (uk,vk)

ʾ�� 1:
����: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
���: [1,2],[1,4],[1,6]
����: ���������е�ǰ 3 ������
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

ʾ�� 2:
����: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
���: [1,1],[1,1]
����: ���������е�ǰ 2 ������
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

��ʾ:
1 <= nums1.length, nums2.length <= 10^5
-10^9 <= nums1[i], nums2[i] <= 10^9
nums1 �� nums2 ��Ϊ ��������
1 <= k <= 10^4
k <= nums1.length * nums2.length

*/

// ��·�鲢
class Solution1 {
private:
	static vector<int> nums1_cpy;
	static vector<int> nums2_cpy;

public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2,
		int k) {
		nums1_cpy = nums1;
		nums2_cpy = nums2;
		int flag = true;
		int len1 = nums1_cpy.size(), len2 = nums2_cpy.size();
		if (len1 > len2) {
			swap(len1, len2);
			swap(nums1_cpy, nums2_cpy);
			flag = false;
		}
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp) *> pq(cmp);
		vector<vector<int>> ans;
		for (int i = 0; i < min(len1, k); ++i) pq.push({ i, 0 });
		while (!pq.empty() && ans.size() < k) {
			const auto tmp = pq.top();
			pq.pop();
			flag ? ans.push_back({ nums1_cpy[tmp.first], nums2_cpy[tmp.second] })
				: ans.push_back({ nums2_cpy[tmp.second], nums1_cpy[tmp.first] });
			if (tmp.second + 1 < len2) pq.push({ tmp.first, tmp.second + 1 });
		}
		return ans;
	}

private:
	static bool cmp(const pair<int, int> &p1, const pair<int, int> &p2) {
		return nums1_cpy[p1.first] + nums2_cpy[p1.second] >
			nums1_cpy[p2.first] + nums2_cpy[p2.second];
	}
};

vector<int> Solution1::nums1_cpy;
vector<int> Solution1::nums2_cpy;

// ���ֲ���
class Solution2 {
public:
	vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2,
		int k) {
		vector<vector<int>> ans;
		int len1 = nums1.size(), len2 = nums2.size();
		int lo = nums1[0] + nums2[0], hi = nums1[len1 - 1] + nums2[len2 - 1];
		while (lo < hi) {
			int mi = lo + (hi - lo) / 2;
			if (check(mi, k, nums1, nums2)) hi = mi;
			else lo = mi + 1;
		}
		// ��ɶ��ֲ��Һ����Ժ� <= target ���������ܴ��ڵ��� k ��
		// �����Ժ� < target ��������С�� k ��
		int target = lo;
		for (int i = 0; i < len1; ++i) {
			for (int j = 0; j < len2; ++j)
				if (nums1[i] + nums2[j] < target) ans.push_back({ nums1[i], nums2[j] });
				else break;
		}
		// ��ʣ��������ҵ����Ժ� = target ������ֱ����ȫ k ��
		for (int i = 0; i < len1 && ans.size() < k; ++i) {
			int a = nums1[i], b = target - a;
			// ���¹��̶��ֲ��������е�Ŀ��ֵ�����Ŀ��ֵ�ж���ظ�ֵ�����ҵ����������Ҳ����
			int lo = 0, hi = len2 - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo) / 2;
				nums2[mi] >= b ? hi = mi : lo = mi + 1;
			}
			if (nums2[lo] != b) continue;
			int ic = lo;
			lo = 0, hi = len2 - 1;
			while (lo < hi) {
				int mi = lo + (hi - lo + 1) / 2;
				nums2[mi] <= b ? lo = mi : hi = mi - 1;
			}
			int id = lo;
			for (int j = ic; j <= id && ans.size() < k; ++j) ans.push_back({ a, b });
		}
		return ans;
	}

private:
	bool check(int target, int k, const vector<int> &nums1,
		const vector<int> &nums2) {
		int ans = 0;
		for (int i = 0; i < nums1.size() && ans < k; ++i) {
			for (int j = 0; j < nums2.size() && ans < k; ++j) {
				if (nums1[i] + nums2[j] <= target) ++ans;
				else break;
			}
		}
		return ans >= k;
	}
};
