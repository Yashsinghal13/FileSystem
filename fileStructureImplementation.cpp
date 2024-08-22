#include<bits/stdc++.h>
using namespace std;
unordered_map<string,vector<string>> AdjListPrepare(vector<string>&files,unordered_map<string,string>&root)
{
    unordered_map<string,vector<string>>adjList;
    for(auto path:files)
    {
        string file="";
        string parentDirectory="";
        for(int i=0;i<path.size();i++)
        {
            if(path[i]!='/') file+=path[i];
            else
            {
                if(parentDirectory=="")
                {
                    parentDirectory=file;
                    if(root.find(file)==root.end()) root[file]="";
                }
                else
                {
                    adjList[parentDirectory].push_back(file);
                    root[file]=parentDirectory;
                    parentDirectory=file;
                }
                file="";
            }
        }
        root[file]=parentDirectory;
        adjList[parentDirectory].push_back(file);
    }
    return adjList;
}
void printAdjList(unordered_map<string,vector<string>>&adjList,unordered_map<string,string>&root)
{
    for(auto files:adjList)
    {
        cout<<files.first<<": ";
        for(auto subFiles:files.second) cout<<subFiles<<" ";
        cout<<endl;
    }
    for(auto rootfiles:root)
    {
        cout<<rootfiles.first<<":"<<rootfiles.second<<endl;
    }
    
}
vector<string> rootFileExtract(unordered_map<string,string>&root)
{
    vector<string> rootFiles;
    for(auto check:root)
    {
        if(check.second=="")
        {
            rootFiles.push_back(check.first);
        }
    }
    return rootFiles;
}
void dfs(unordered_map<string,vector<string>>&adjList,string startRoot,int count)
{
    for(int i=0;i<count;i++)
    {
        cout<<"-----";
    }
    cout<<startRoot<<endl;
    for(auto file:adjList[startRoot])
    {
        dfs(adjList,file,count+1);
    }
    return ;
}
int main()
{
    vector<string> files={"a/b/c","c/f/g/h","h/k/l","l/m/n","a/d","temp2/temp1","o/p"};
    unordered_map<string,string>root;
    unordered_map<string,vector<string>> adjList=AdjListPrepare(files,root);
    vector<string> rootFiles=rootFileExtract(root);
    for(int i=0;i<rootFiles.size();i++)
    {
        dfs(adjList,rootFiles[i],0);
        cout<<endl;
    }
    
    return 0;
}