#include "header.h"

/*

给定无向连通图中一个节点的引用，返回该图的深拷贝（克隆）。
图中的每个节点都包含它的值 val（Int）和其邻居的列表（list[Node]）。
 
   1 ------- 2
   |         |
   |         |
   |         |
   4 ------- 3

*/


//Definition for undirected graph.
struct UndirectedGraphNode {
    int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
	unordered_map< UndirectedGraphNode *, UndirectedGraphNode *> copies;
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
	{
		if (!node)
		{
			return nullptr;
		}
		if (!copies.count(node))
		{
			copies[node] = new UndirectedGraphNode(node->label);
			for (auto neighbor : node->neighbors)
			{
				copies[node]->neighbors.push_back(cloneGraph(neighbor));
			}
		}
		return copies[node];
	}
};
