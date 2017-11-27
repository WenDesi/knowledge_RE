#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

#define NODES_TOTAL 45428
#define Max_Len 500
#define NEGATIVE_SAMPLE_RELATION_ID 26
#define MAX_TRY_TIMES 2000

extern int graph[NODES_TOTAL][Max_Len];
extern vector<int> tongji;
extern double node_weight[NODES_TOTAL];
extern vector<vector<string>> paths;

bool build_graph(string filepath);
void build_node_weight(string filepath);
void split(std::string& s, std::string& delim,std::vector< std::string >* ret);
unsigned int DFS(int source, int target, unsigned int minLen, unsigned int maxLen, unsigned int maxPathSize, unsigned int depth, string prefix, int thread_id);
bool BFS(int source,int target,int max_length);
