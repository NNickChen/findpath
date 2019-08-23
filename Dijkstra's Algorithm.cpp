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
			// nodeInfo[name].costs=min(nodeInfo[name].costs,nodeInfo[node].costs+costToChild);
			if(nodeInfo[node].costs+costToChild<nodeInfo[name].costs)
			{
				nodeInfo[name].costs=nodeInfo[node].costs+costToChild;
				nodeInfo[name].fa=node;
			}
		}
		nodeInfo[node].vis=true;
	}
	return nodeInfo[object].costs;
}

void printpath(string object)
{
	if(nodeInfo[object].fa.empty())
	{
		cout<<object;
		if(!graph[object].empty())
		cout<<"->";
		return;
	}
	printpath(nodeInfo[object].fa);
	cout<<object;
	if(!graph[object].empty())
	cout<<"->";
	return;
}

int main(int argc, const char *argv[])
{
	string location,object,unit;
	cin>>location>>object>>unit;
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
	// traverse();b
	int total=dijs(location,object);
	if(total<INF)
	{
		cout<<"You need at least "<<total<<" "<<unit<<((total==1)?" ":"s ")<<"to get there.\n";
		if(argc>1)
		{
			string parameter=argv[1];
			if(parameter=="-p")
			printpath(object);
		}
	}
	else cout<<"You can't get there!\n";
	return 0;
}
