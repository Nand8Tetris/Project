#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;

ifstream in;
ofstream out;

string s,name;

void readline() {
	string z;
	in>>z;in>>z;in>>z;
}



int main(int argc, char const *argv[])
{
	in.open(argv[1]);
	out.open(argv[2]);
	in>>s;
	readline();
	in>>s;in>>name;in>>s;
	readline();
	while (in>>s,s!="</class>") {
		
		in>>s;
	}

	return 0;
}