#include "header.h"

/*

472. 连接词

给你一个不含重复单词的字符串数组 words，请你找出并返回 words 中的所有连接词

连接词定义为：一个完全由给定数组中的至少两个较短单词（不一定是不同的两个单词）组成的字符串

示例 1：
输入：words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
输出：["catsdogcats","dogcatsdog","ratcatdogcat"]
解释："catsdogcats" 由 "cats", "dog" 和 "cats" 组成;
"dogcatsdog" 由 "dog", "cats" 和 "dog" 组成;
"ratcatdogcat" 由 "rat", "cat", "dog" 和 "cat" 组成

示例 2：
输入：words = ["cat","dog","catdog"]
输出：["catdog"]

提示：
1 <= words.length <= 10^4
1 <= words[i].length <= 30
words[i] 仅由小写英文字母组成
words 中的所有字符串都是 唯一 的
1 <= sum(words[i].length) <= 10^5

*/

class Solution1 {
private:
	vector<char> memo;
	unordered_set<string> dict;

public:
	vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
		sort(words.begin(), words.end(), [](const string &a, const string &b) {
			return a.size() < b.size();
		});
		vector<string> ans;
		for (const string &word : words) {
			if (word.empty()) continue;
			int len = word.size();
			memo.resize(len + 1, -1);
			memo.clear();
			if (helper(word, len)) ans.push_back(word);
			dict.insert(word);
		}
		return ans;
	}

private:
	bool helper(const string &s, int i) {
		if (i == 0) return true;
		if (memo[i] != -1) return memo[i];
		for (int j = 0; j < i; ++j) {
			if (dict.count(s.substr(j, i - j)) && helper(s, j)) {
				return memo[i] = true;
			}
		}
		return memo[i] = false;
	}
};


// 前缀树
struct TrieNode {
	bool isWord;
	vector<TrieNode *> children;
	TrieNode() : isWord(false), children(26, nullptr) {}
};

class Solution2 {
private:
	TrieNode *root;

public:
	vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
		sort(words.begin(), words.end(), [](const string &a, const string &b) {
			return a.size() < b.size();
		});
		root = new TrieNode();
		vector<string> ans;
		for (const string &word : words) {
			if (!word.empty()) {
				if (helper(word, 0)) ans.push_back(word);
				else insert(word);
			}
		}
		return ans;
	}

private:
	bool helper(const string &word, int start) {
		if (start == word.size()) return true;
		TrieNode *cur = root;
		while (start < word.size()) {
			cur = cur->children[word[start] - 'a'];
			if (!cur) return false;
			if (cur->isWord && helper(word, start + 1)) return true;
			++start;
		}
		return false;
	}
	void insert(const string &word) {
		TrieNode *cur = root;
		for (const auto &c : word) {
			char i = c - 'a';
			if (!cur->children[i]) {
				cur->children[i] = new TrieNode();
			}
			cur = cur->children[i];
		}
		cur->isWord = true;
	}
};
