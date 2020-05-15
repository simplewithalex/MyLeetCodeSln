#include "header.h"

/*

给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

示例 1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2:
输入: nums = [1], k = 1
输出: [1]

说明：
你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。

*/

//快速划分方法
class Solution1 {
public:
	vector<int> topKFrequent(vector<int> &nums, int k)
	{
		unordered_map<int, int> m;
		for (auto num : nums) ++m[num];
		vector<pair<int, int>> data(m.begin(), m.end());
		int len = data.size();
		int lo = 0, hi = len - 1;
		int index = partition(data, lo, hi);
		while (index != k - 1)
		{
			if (index > k - 1)
			{
				hi = index - 1;
				index = partition(data, lo, hi);
			}
			else
			{
				lo = index + 1;
				index = partition(data, lo, hi);
			}
		}
		vector<int> res(k);
		for (int i = 0; i <= index; ++i)
		{
			res[i] = data[i].first;
		}
		return res;
	}
	int partition(vector<pair<int, int>> &data, int lo, int hi)
	{
		swap(data[lo], data[lo + rand() % (hi - lo + 1)]);
		pair<int, int> pivot = data[lo];
		while (lo < hi)
		{
			while (lo < hi)
			{
				if (data[hi].second < pivot.second) --hi;
				else
				{
					data[lo++] = data[hi];
					break;
				}
			}
			while (lo < hi)
			{
				if (data[lo].second > pivot.second) ++lo;
				else
				{
					data[hi--] = data[lo];
					break;
				}
			}
		}
		data[lo] = pivot;
		return lo;
	}
};

//桶排序法
class Solution2 {
public:
	vector<int> topKFrequent(vector<int> &nums, int k)
	{
		int len = nums.size();
		unordered_map<int, int> m;
		for (auto num : nums) ++m[num];
		//桶排序，桶数组的下标含义为频率，其中频率最多出现的次数只可能是nums数组长度
		vector<vector<int>> freqBucket(len + 1);
		for (auto it = m.begin(); it != m.end(); ++it)
		{
			freqBucket[it->second].push_back(it->first);
		}
		vector<int> res;
		for (int i = len; i >= 0 && res.size() < k; --i)
		{
			if (!freqBucket[i].empty()) res.insert(res.end(), freqBucket[i].begin(), freqBucket[i].end());
		}
		//数组元素数量可能会多于k
		//res.resize(k);
		return res;
	}
};