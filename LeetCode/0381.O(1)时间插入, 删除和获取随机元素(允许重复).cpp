#include "header.h"

/*

381. O(1) 时间插入、删除和获取随机元素 - 允许重复

RandomizedCollection 是一种包含数字集合(可能是重复的)的数据结构。它应该支持插入和删除特定元素，以及删除随机元素。

实现 RandomizedCollection 类:
RandomizedCollection()初始化空的 RandomizedCollection 对象
bool insert(int val) 将一个 val 项插入到集合中，即使该项已经存在。如果该项不存在，则返回 true ，否则返回 false
bool remove(int val) 如果存在，从集合中移除一个 val 项。如果该项存在，则返回 true，否则返回 false。注意，如果val在集合中出现多次，我们只删除其中一个
int getRandom() 从当前的多个元素集合中返回一个随机元素。每个元素被返回的概率与集合中包含的相同值的数量线性相关

您必须实现类的函数，使每个函数的 平均 时间复杂度为 O(1)

注意：生成测试用例时，只有在 RandomizedCollection 中至少有一项时，才会调用 getRandom

示例 1:
输入
["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
[[], [1], [1], [2], [], [1], []]
输出
[null, true, false, true, 2, true, 1]
解释
RandomizedCollection collection = new RandomizedCollection();// 初始化一个空的集合
collection.insert(1);   // 返回 true，因为集合不包含 1
// 将 1 插入到集合中
collection.insert(1);   // 返回 false，因为集合包含 1
// 将另一个 1 插入到集合中。集合现在包含 [1,1]
collection.insert(2);   // 返回 true，因为集合不包含 2
// 将 2 插入到集合中。集合现在包含 [1,1,2]
collection.getRandom(); // getRandom 应当:
// 有 2/3 的概率返回 1,
// 1/3 的概率返回 2
collection.remove(1);   // 返回 true，因为集合包含 1
// 从集合中移除 1。集合现在包含 [1,2]
collection.getRandom(); // getRandom 应该返回 1 或 2，两者的可能性相同

提示:
-2^31 <= val <= 2^31 - 1
insert, remove 和 getRandom 最多总共被调用 2 * 10^5 次
当调用 getRandom 时，数据结构中至少有一个元素

*/

class RandomizedCollection1 {
private:
	unordered_map<int, unordered_set<int>> idx;
	vector<int> nums;

public:
	RandomizedCollection1() {}

	bool insert(int val) {
		nums.push_back(val);
		idx[val].insert(nums.size() - 1);
		return idx[val].size() == 1;
	}

	bool remove(int val) {
		if (!idx.count(val)) return false;
		int i = *(idx[val].begin());
		nums[i] = nums.back();
		idx[val].erase(i);
		if (i < nums.size() - 1) {
			idx[nums[i]].erase(nums.size() - 1);
			idx[nums[i]].insert(i);
		}
		if (idx[val].empty()) idx.erase(val);
		nums.pop_back();
		return true;
	}

	int getRandom() { return nums[rand() % nums.size()]; }
};

/**
* Your RandomizedCollection object will be instantiated and called as such:
* RandomizedCollection* obj = new RandomizedCollection();
* bool param_1 = obj->insert(val);
* bool param_2 = obj->remove(val);
* int param_3 = obj->getRandom();
*/

// 使用 C++ unordered_multimap
class RandomizedCollection2 {
private:
	unordered_multimap<int, int> idx;
	vector<unordered_multimap<int, int>::iterator> nums;

public:
	RandomizedCollection2() {}

	bool insert(int val) {
		bool ret = !idx.count(val);
		nums.push_back(idx.insert({ val, nums.size() }));
		return ret;
	}

	bool remove(int val) {
		auto it = idx.find(val);
		if (it == idx.end()) return false;
		nums.back()->second = it->second;
		nums[it->second] = nums.back();
		nums.pop_back();
		idx.erase(it);
		return true;
	}

	int getRandom() { return nums[rand() % nums.size()]->first; }
};
// https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/solutions/467892/c-unordered_multimapjie-fa-by-vclip/
// https://leetcode.cn/u/vclip/

/**
* Your RandomizedCollection object will be instantiated and called as such:
* RandomizedCollection* obj = new RandomizedCollection();
* bool param_1 = obj->insert(val);
* bool param_2 = obj->remove(val);
* int param_3 = obj->getRandom();
*/

