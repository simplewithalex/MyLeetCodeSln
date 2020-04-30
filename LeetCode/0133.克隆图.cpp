#include "header.h"

/*

����������ͨͼ��һ���ڵ�����ã����ظ�ͼ���������¡����
ͼ�е�ÿ���ڵ㶼��������ֵ val��Int�������ھӵ��б�list[Node]����
 
   1 ------- 2
   |         |
   |         |
   |         |
   4 ------- 3

*/

// Definition for a Node.
class Node {
public:
	int val;
	vector<Node*> neighbors;

	Node() 
	{
		val = 0;
		neighbors = vector<Node*>();
	}

	Node(int _val) 
	{
		val = _val;
		neighbors = vector<Node*>();
	}

	Node(int _val, vector<Node*> _neighbors) 
	{
		val = _val;
		neighbors = _neighbors;
	}
};

//DFS
class Solution1 {
public:
	unordered_map<Node *, Node *> copies;
	Node * cloneGraph(Node *node) 
	{
		if (!node) return nullptr;
		if (!copies.count(node))
		{
			copies[node] = new Node(node->val);
			for (auto neighbor : node->neighbors)
			{
				copies[node]->neighbors.push_back(cloneGraph(neighbor));
			}
		}
		return copies[node];
	}
};

//BFS
class Solution2 {
public:
	unordered_map<Node *, Node *> copies;
	Node * cloneGraph(Node *node)
	{
		if (!node) return nullptr;
		queue<Node *> q;
		q.push(node);
		copies[node] = new Node(node->val);
		while (!q.empty())
		{
			Node *tempNode = q.front();
			q.pop();
			for (auto neighbor : tempNode->neighbors)
			{
				if (!copies.count(neighbor))
				{
					copies[neighbor] = new Node(neighbor->val);
					q.push(neighbor);
				}
				copies[tempNode]->neighbors.push_back(copies[neighbor]);
			}
		}
		return copies[node];
	}
};
