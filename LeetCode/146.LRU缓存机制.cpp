#include "header.h"

/*

运用你所掌握的数据结构，设计和实现一个LRU (最近最少使用) 缓存机制。它应该支持以下操作:获取数据 get 和 写入数据 put 。
获取数据 get(key) - 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
写入数据 put(key, value) - 如果密钥不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据之前删除最近最少使用的数据值，从而为新的数据值留出空间。
进阶:
你是否可以在 O(1) 时间复杂度内完成这两种操作？

示例:
LRUCache cache = new LRUCache(2/缓存容量/);
cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // 返回  1
cache.put(3, 3);    // 该操作会使得密钥 2 作废
cache.get(2);       // 返回 -1 (未找到)
cache.put(4, 4);    // 该操作会使得密钥 1 作废
cache.get(1);       // 返回 -1 (未找到)
cache.get(3);       // 返回  3
cache.get(4);       // 返回  4

*/


class LRUCache {
public:
	LRUCache(int capacity) :cap(capacity) {}
	int get(int key) 
	{
		auto it = m.find(key);
		if (it == m.end()) return -1;
		update(it);
		return it->second.first;
	}
	void put(int key, int value) 
	{
		auto it = m.find(key);
		if (it != m.end()) update(it);
		else
		{
			if (m.size() == cap)
			{
				m.erase(dLink.back());
				dLink.pop_back();
			}
			dLink.push_front(key);
		}
		m[key] = { value, dLink.begin() };
	}
private:
	list<int> dLink;
	//m中的结构为<key,pair<value,key在链表中的位置>>
	unordered_map<int, pair<int, list<int>::iterator>> m;
	int cap;
	void update(unordered_map<int, pair<int, list<int>::iterator>>::iterator it)
	{
		int key = it->first;
		dLink.erase(it->second.second);
		dLink.push_front(key);
		it->second.second = dLink.begin();
	}
};

