#include "header.h"

/*

实现一个 Trie (前缀树)，包含 insert, search, 和 startsWith 这三个操作。

示例:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // 返回 true
trie.search("app");     // 返回 false
trie.startsWith("app"); // 返回 true
trie.insert("app");
trie.search("app");     // 返回 true

说明:

你可以假设所有的输入都是由小写字母 a-z 构成的。
保证所有输入均为非空字符串。


Your Trie object will be instantiated and called as such:

Trie *obj = new Trie();
obj->insert(word);
bool param_2 = obj->search(word);
bool param_3 = obj->startsWith(prefix);

*/

class TrieNode
{
private:
	int num = 26;
	bool end;
	vector<TrieNode *> v;
public:
	TrieNode()
		:end(false), v(vector<TrieNode *>(num, nullptr)){}
	bool containsKey(char ch)
	{
		return v[ch - 'a'] != nullptr;
	}
	TrieNode * get(char ch)
	{
		return v[ch - 'a'];
	}
	void put(char ch, TrieNode *node)
	{
		v[ch - 'a'] = node;
	}
	void setEnd()
	{
		end = true;
	}
	bool isEnd()
	{
		return end;
	}
};

class Trie {
private:
	TrieNode *root;
	TrieNode *searchPrefix(string word)
	{
		TrieNode *node = root;
		for (int i = 0; i < word.size(); ++i)
		{
			char cur = word[i];
			if (node->containsKey(cur))
			{
				node = node->get(cur);
			}
			else
			{
				return nullptr;
			}
		}
		return node;
	}
public:
	/** Initialize your data structure here. */
	Trie()
	{
		root = new TrieNode();
	}
	/** Inserts a word into the trie. */
	void insert(string word)
	{
		TrieNode *node = root;
		for (int i = 0; i < word.size(); ++i)
		{
			char cur = word[i];
			if (!node->containsKey(cur))
			{
				node->put(cur, new TrieNode());
			}
			node = node->get(cur);
		}
		node->setEnd();
	}
	/** Returns if the word is in the trie. */
	bool search(string word)
	{
		TrieNode *node = searchPrefix(word);
		return (node != nullptr) && (node->isEnd());
	}
	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix)
	{
		TrieNode *node = searchPrefix(prefix);
		return node != nullptr;
	}
};
//https://leetcode-cn.com/problems/implement-trie-prefix-tree/solution/shi-xian-trie-qian-zhui-shu-by-leetcode/

