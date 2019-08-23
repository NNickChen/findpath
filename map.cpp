#include<iostream>
#include<map>
using namespace std;

map <string,string> nickname;

int main()
{
	int n;
	cin>>n;
	for (int i = 0; i < n; ++i)
	{
		string name,nnickname;
		cin>>name>>nnickname;
		nickname[name]=nnickname;
	}
	// for (int i = 0; i < m; ++i)
	// {
	// 	string name;
	// 	cin>>name;
	// 	cout<<nickname[name]<<endl;
	// }
	map <string,string>::iterator end=nickname.end();
	for (map <string,string>::iterator i = nickname.begin(); i != end; ++i)
	{
		string name,nnickname;
		name=i->first;
		nnickname=i->second;
		cout<<name<<" "<<nnickname<<"\n";
	}
	return 0;
}
