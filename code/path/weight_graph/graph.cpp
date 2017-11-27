#include "head.h"

int graph[NODES_TOTAL][Max_Len];
double node_weight[NODES_TOTAL];

void init_graph()
{
    for(int i=0;i<NODES_TOTAL;i++)
        for(int j=0;j<Max_Len;j++)
            graph[i][j] = -1;
}

void build_node_weight(string filepath)
{
    ifstream file;
    file.open(filepath,ios::in);

    std::string strLine;
    int i=0;
    string dot=",";
    while(getline(file,strLine)) {
        vector<string> line;
        split(strLine, dot, &line);
        int node = stoi(line[0]);
        double weight = stod(line[1]);
        node_weight[node] = weight;
    }
}

bool build_graph(string filepath)
{
    init_graph();

    ifstream file;
    file.open(filepath,ios::in);

    if(!file.is_open())
    {
        cout << "cant open " << filepath << ", please check" <<endl;
        return false;
    }



    std::string strLine;
    int i=0;
    string dot=",";
    while(getline(file,strLine))
    {
        vector<string> line;
        split(strLine,dot,&line);

        for(int j=0;j<line.size()&&j<Max_Len;j++){
            int nnode = stoi(line[j]);
            graph[i][j] = nnode;
        }
        graph[i][Max_Len-1]=-1;

        i += 1;
    }

    return true;
}
