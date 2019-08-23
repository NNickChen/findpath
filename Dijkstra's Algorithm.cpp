#include<iostream>
#include<map>
#include<vector>
using namespace std;

const int INF=(int)((long)(1<<31)-1);

struct CHILDINFO
{
	string name;
	int costToChild;
};

struct NODEINFO
{
	string fa;
	int costs;
	bool vis;
};

map <string,vector <CHILDINFO> > graph;
map <string,NODEINFO> nodeInfo;

bool find(string &ret)
{
	int smallestCosts=INF;
	string smallestNode;
	map <string,NODEINFO>::iterator end=nodeInfo.end();
    for(map <string,NODEINFO>::iterator i = nodeInfo.begin(); i != end; i++) 
    {
    	string name=i->first;
        int costs=i->second.costs;
        bool vis=i->second.vis;
        if(costs<smallestCosts&&!vis)
        {
        	smallestCosts=costs;
        	smallestNode=name;
        }
    }
	if(smallestNode.empty())
	return false;
	ret=smallestNode;
	return true;
}

void traverse()
{
	map <string,NODEINFO>::iterator end=nodeInfo.end();
    for(map <string,NODEINFO>::iterator i = nodeInfo.begin(); i != end; i++) 
    {
    	string name=i->first;
        int costs=i->second.costs;
        bool vis=i->second.vis;
        cout<<name<<" "<<costs<<" "<<vis<<"\n";
    }
}

int dijs(string location,string object)
{
	string node;
	while(find(node))
	{
		for (int i=0; i < graph[node].size(); i++)
		{
			string name=graph[node][i].name;
			int costToChild=graph[node][i].costToChild;
			nodeInfo[name].costs=min(nodeInfo[name].costs,nodeInfo[node].costs+costToChild);
		}
		nodeInfo[node].vis=true;
	}
	return nodeInfo[object].costs;
}

int main()
{
	string location,object;
	cin>>location>>object;
	while(1)
	{
		string name;
		cin>>name;
		if(name[0]=='0')
		break;
		int childs;
		cin>>childs;
		for (int i = 0; i < childs; ++i)
		{
			CHILDINFO childinfo;
			string child;
			int costToChild;
			cin>>child>>costToChild;
			childinfo.name=child;
			childinfo.costToChild=costToChild;
			graph[name].push_back(childinfo);
		}
		nodeInfo[name].costs=INF;
		nodeInfo[name].vis=false;
	}
	nodeInfo[location].costs=0;
	nodeInfo[object].costs=INF;
	nodeInfo[object].vis=false;
	// traverse();
	int total=dijs(location,object);
	if(total<INF)
	cout<<"You need at least "<<total<<" km to there.\n";
	else cout<<"You can't get there!\n";
	return 0;
}
