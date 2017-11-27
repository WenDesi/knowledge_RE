#include "head.h"
#include <vector>

bool BFS(int source,int target,int max_length)
{
	vector<int> pre;
	vector<int> next;
	pre.push_back(source);

	bool crawled_node[NODES_TOTAL];
    for(int i=0;i<NODES_TOTAL;i++)crawled_node[i] = false;
	crawled_node[source] = true;

    for(int length = 1;length <= max_length;length++)
    {
    	for(int node: pre)
    	{
    	 
    		for(int i=0;graph[node][i]!=-1;i++)
    		{
				if(node==target)
				{
					if(length!=1){return true;}
					else continue;
				}
    			if(crawled_node[graph[node][i]])continue;
    			next.push_back(graph[node][i]);
    			crawled_node[graph[node][i]] = true;
    		}
    	}

    	pre.clear();
    	pre.swap(next);
    }

    return false;
}