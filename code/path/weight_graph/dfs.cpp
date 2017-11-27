#include "head.h"
#include <algorithm>

bool cmp(const pair<int,double> &a, const pair<int,double> &b)
{
    return a.first < b.first;
}

unsigned int DFS(int source, int target, unsigned int minLen, unsigned int maxLen, unsigned int maxPathSize, unsigned int depth, string prefix, int thread_id)
{
    if(depth>maxLen)return 0;
    if(maxPathSize<=0)return 0;

    // get next node
    vector<int> next;
    for(int i=0;graph[source][i]!=-1;i++){
        if(graph[source][i]==target){
            if(depth!=1){
                string path = prefix+","+to_string(graph[source][i]);
                paths[thread_id].push_back(path);
                maxPathSize -= 1;
            }
        }
        else {
            next.push_back(graph[source][i]);
        }
    }

    // assign weight
    double total_weight = 0.0;
    for(int node:next)total_weight += node_weight[node];

    vector<pair<int,double>> node_pairs;
    for(int node:next){
        pair<int,double> node_pair(node,node_weight[node]);
        node_pairs.push_back(node_pair);
    }

    // sort
    sort(node_pairs.begin(), node_pairs.end(), cmp);

    for(int i=0;i<node_pairs.size();i++)
    {
        int node = node_pairs[i].first;
        double weight = node_pairs[i].second/total_weight;

        unsigned int max_path = (unsigned int)((double)maxPathSize * weight);
        maxPathSize -= max_path;
        total_weight -= node_pairs[i].second;
        unsigned int remain_path = DFS(node,target,minLen,maxLen,max_path,depth+1,prefix+","+to_string(node),thread_id);
        maxPathSize += remain_path;
    }
    return maxPathSize;
}