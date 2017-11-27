#include "head.h"
#include <pthread.h>
#include <unistd.h>

int totalThreadNum = 16;
int total_len;
vector<vector<int>> valid_list;
pthread_mutex_t mutex_4_size;
int finished_size = 0;
vector<vector<string>> paths;

void split(std::string &s, std::string &delim, std::vector <std::string> *ret) {
    size_t last = 0;
    size_t index = s.find_first_of(delim, last);
    while (index != std::string::npos) {
        ret->push_back(s.substr(last, index - last));
        last = index + 1;
        index = s.find_first_of(delim, last);
    }
    if (index - last > 0) {
        ret->push_back(s.substr(last, index - last));
    }
}

vector<vector<int>> valid_triples(string filename, int maxLen=4)
{
    ifstream file;
    file.open(filename, ios::in);

    vector<string> dataset;
    std::string strLine;
    while (getline(file, strLine)) {
        dataset.push_back(strLine);
    }

    vector<vector<int>> valid;
    for(int i=0;i<dataset.size();i++)
    {
        strLine = dataset[i];
        vector <string> line;
        string dot = ",";
        split(strLine, dot, &line);

        int source = stoi(line[0]);
        int target = stoi(line[1]);
        int relation = stoi(line[2]);

        if(BFS(source,target,maxLen)){
            vector<int> triple;
            triple.push_back(source);
            triple.push_back(target);
            triple.push_back(relation);
            valid.push_back(triple);
        }
    }
    return valid;
}



void* thread_cal_path(void* args) {
    int* pid = (int*)args;
    int thread_id = *pid;
    ofstream* out = new ofstream("trainset_with_path"+to_string(thread_id)+".txt");
    cout<< "Thread "<<thread_id<<" start!"<<endl;

    for(int i=thread_id;i<total_len;i+=totalThreadNum)
    {
        int source = valid_list[i][0];
        int target = valid_list[i][1];
        int relation = valid_list[i][2];

        paths[thread_id].clear();
        DFS(source, target, 2, 4, 100, 1, to_string(source),thread_id);
        for(string path:paths[thread_id])
            *out<<i<<","<<source<<","<<target<<","<<relation<<","<<path<<endl;

        pthread_mutex_lock(&mutex_4_size);
        finished_size++;
        pthread_mutex_unlock(&mutex_4_size);
    }
}

void cal_path() {
    pthread_t tids[totalThreadNum];
    int ids[totalThreadNum];

    for(int i = 0; i < totalThreadNum; i++)
    {
        vector<string> path;
        paths.push_back(path);
    }

    for(int i = 0; i < totalThreadNum; i++)
    {
        ids[i] = i;
        int ret = pthread_create(&tids[i], NULL, thread_cal_path, (void *)&ids[i]);//传入的时候必须强制转换为void* 类型，即无类型指针
    }

    while(true)
    {
        pthread_mutex_lock(&mutex_4_size);
        int remain = total_len - finished_size;
        pthread_mutex_unlock(&mutex_4_size);

        sleep(1);
        cout<<remain<<endl;
        if(remain==0)break;

    }
}

int main(){
    string graphFilePath = "graph.txt";
    bool buildSuccess = build_graph(graphFilePath);
    if (!buildSuccess)return 1;

    string weightFilePath = "node_weight.txt";
    build_node_weight(weightFilePath);

    valid_list = valid_triples("trainset.txt");
    total_len = valid_list.size();

    cal_path();

    return 0;
}