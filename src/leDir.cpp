#include<iostream>
#include<string>
#include<stdio.h>
#include<sstream>
#include<vector>

using namespace std;

vector<string> split(string str, char delimiter);

/*int main(int argc, char* argv[])
{
	string diretorio = argv[1];
	vector<string> sep = split(diretorio,'/');
	int i = 0;
	string s = sep[i];
	while(s != "")
	{
		cout << s << endl;
		s = sep[++i];
	};
	return 0;
}*/

vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while(getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	};

	return internal;
}
