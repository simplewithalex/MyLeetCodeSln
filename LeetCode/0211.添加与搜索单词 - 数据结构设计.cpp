#include "header.h"

/*

请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。

实现词典类 WordDictionary ：
WordDictionary() 初始化词典对象
void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；否则，返回  false 。word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母。
 
示例：
输入：
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]

输出：
[null,null,null,null,false,true,true,true]

解释：
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True
  
提示：
1 <= word.length <= 500
addWord 中的 word 由小写英文字母组成
search 中的 word 由 '.' 或小写英文字母组成
最多调用 50000 次 addWord 和 search

*/

class TrieNode {
private:
	int num = 26;
	bool end;
	vector<TrieNode *> v;

public:
	TrieNode() : end(false), v(vector<TrieNode *>(num, nullptr)) {}
	bool containsKey(char ch) { return v[ch - 'a'] != nullptr; }
	TrieNode *get(char ch) { return v[ch - 'a']; }
	void put(char ch, TrieNode *node) { v[ch - 'a'] = node; }
	void setEnd() { end = true; }
	bool isEnd() { return end; }
	int getNum() { return num; }
};

// Trie树问题可参考208题
class WordDictionary {

public:
	WordDictionary() { root = new TrieNode(); }

	void addWord(string word) {
		TrieNode *node = root;
		for (int i = 0; i < word.size(); ++i) {
			char cur = word[i];
			if (!node->containsKey(cur)) {
				node->put(cur, new TrieNode());
			}
			node = node->get(cur);
		}
		node->setEnd();
	}

	bool search(string word) { return dfs(word, 0, root); }

private:
	TrieNode *root;
	bool dfs(const string &word, int idx, TrieNode *node) {
		if (idx == word.size()) return node->isEnd();
		char cur = word[idx];
		if (cur == '.') {
			for (int i = 0; i < node->getNum(); ++i) {
				char c = 'a' + i;
				TrieNode *child = node->get(c);
				if (child != nullptr && dfs(word, idx + 1, child)) return true;
			}
		}
		else if (cur >= 'a' && cur <= 'z') {
			TrieNode *child = node->get(cur);
			return child != nullptr && dfs(word, idx + 1, child);
		}
		return false;
	}
};

/**
* Your WordDictionary object will be instantiated and called as such:
* WordDictionary* obj = new WordDictionary();
* obj->addWord(word);
* bool param_2 = obj->search(word);
*/
