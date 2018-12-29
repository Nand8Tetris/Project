#include<iostream>
#include<fstream>
using namespace std;

ifstream in;
ofstream out;
int dep;

string stack[100001];
int top;

void output(string s) {
	for (int i=0;i<dep*2;i++)
		out<<' ';
	out<<s;
	out<<endl;
}

void outputterm(string s) {
	output("<term>");
	output("  "+s);
	output("</term>");
}

map<string,pair<int,string> >TP;

void work() {
	TP["constructor"]=TP["function"]=tp["method"]="subroutineDec";
	TP["static"]=TP["field"]="classVarDec";
	TP["class"]="class";
	string s,t,v;
	int x,y;
	int cur=0;//cur=0 no cur=1: parameter cur=2: expression
	int key=0;//key=0 class key=1 
	while (getline(in,s)) {
		for (x=0;s[x]!='>';x++);
		for (y=x+1;s[y]!='<';y++);
		t=s.substr(0,x);
		v=s.substr(x+1,y-x-1);
		if (t=="keyword") {
			if (TP.count(v)) {
				stack[dep]=v;
				output(TP[v]);
				dep++;
			}
			output(v);
		}
		if (t=="symbol") {
			output(s);

		}
		if (t=="integerConstant") {
			outputterm(s);
		}
		if (t=="StringConstant") {
			outputterm(s);
		}
		if (t=="identifier") {
			outputterm(s);
		}
	}
}

int main(int argc,char **argv) {

	if (argc!=3) {
		puts("Wrong format for parameter");
		return 0;
	}

	in.open(argv[1]);
	out.open(argv[2]);
	
	//in.open("MainT.xml");
	//out.open("Mainout.xml");

	work();

	return 0;
}
