#include<bits/stdc++.h>
using namespace std;
int main() {
	int x=system("dir *.cpp > temp.txt");
	ifstream in;
	in.open("temp.txt");
	string s;
	while (in>>s) {
		if (s.size()>=5&&s.substr(s.size()-5,s.size())==".jack") {
			string t=s.substr(0,s.size()-5);
			system(("part1 "+s+""
		}
	}
	return 0;
}
