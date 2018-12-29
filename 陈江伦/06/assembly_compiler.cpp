#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<bitset>
#include<assert.h>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

template<typename T>inline bool upmin(T &x,T y) { return y<x?x=y,1:0; }
template<typename T>inline bool upmax(T &x,T y) { return x<y?x=y,1:0; }

typedef unsigned int u32;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double lod;
typedef pair<int,int> PR;
typedef vector<int> VI;

const lod pi=acos(-1);
const int oo=1<<30;
const LL OO=1LL<<62;
const int mod=1e9+7;

char c;
int line,var=16;
string command[1<<20];
map<string,int>label;

bool isstatement(char c) {
	return c=='@'||isalpha(c)||isdigit(c)||c=='='||c==';'||c=='('||c==')'||c=='_'||c==':'||c=='$'||c=='!'||c=='+'||c=='-'||c=='&'||c=='|'||c=='.';
}

string advance() {
	string command;
	while (isstatement(c)) {
		command.pb(c);
		c=getchar();
	}
	return command;
}

bool hasMoreCommands() {
	while (!isstatement(c)) {
		if (c==-1)
			return false;
		if (c=='/')
			while (c!=10&&c!=13)
				c=getchar();
		c=getchar();
	}
	return true;
}

enum commandtype{A,C,L};

commandtype commandType(string command) {
	if (command[0]=='@') return A;
	if (command[0]=='(') return L;
	return C;
}

void printbinary(int x,int d) {
	while (d)
		putchar(((x>>--d)&1)+'0');
}

int main()
{
	string name;
	cin>>name;
	freopen((name+".asm").c_str(),"r",stdin);
	freopen((name+".hack").c_str(),"w",stdout);
	c=getchar();
	label["SP"]=0;
	label["LCL"]=1;
	label["ARG"]=2;
	label["THIS"]=3;
	label["THAT"]=4;
	for (int i=0;i<16;i++)
		label["R"+to_string(i)]=i;
	label["SCREEN"]=16384;
	label["KBD"]=24576;
	//first step
	int lines=0;
	while (hasMoreCommands()) {
		string cur=advance();
		commandtype op=commandType(cur);
		++lines;
		if (op==L) {
			cur=cur.substr(1,cur.size()-2);
			if (label.count(cur))
				return fprintf(stderr,"line %d repeat label %s",lines,cur.c_str()),0;
			label[cur]=line;
		} else command[line++]=cur;
	}
	//second step
	for (int i=0;i<line;i++) {
		commandtype op=commandType(command[i]);
		if (op==A) {
			putchar('0');
			string cur=command[i].substr(1,command[i].size()-1);
			if (isdigit(cur[0])) {
				for (int j=1;j<cur.size();j++)
					if (!isdigit(cur[j]))
						return fprintf(stderr,"variable can't begin with digit"),0;
				printbinary(atoi(cur.c_str()),15);
			} else {
				if (label.find(cur)==label.end())
					label[cur]=var++;
				printbinary(label[cur],15);
			}
			putchar(10);
		} else {
			string dest,comp=command[i],jump;
			for (int j=0;j<comp.size();j++)
				if (comp[j]=='=')
					dest=comp.substr(0,j),comp=comp.substr(j+1,comp.size()-j-1);
			for (int j=0;j<comp.size();j++)
				if (comp[j]==';')
					jump=comp.substr(j+1,comp.size()-j-1),comp=comp.substr(0,j);
			string out="111";

			if (comp=="0") out+="0101010"; 
			else if (comp=="1") out+="0111111"; 
			else if (comp=="-1") out+="0111010"; 
			else if (comp=="D") out+="0001100"; 
			else if (comp=="A") out+="0110000"; 
			else if (comp=="!D") out+="0001101"; 
			else if (comp=="!A") out+="0110001"; 
			else if (comp=="-D") out+="0001111"; 
			else if (comp=="-A") out+="0110011"; 
			else if (comp=="D+1") out+="0011111"; 
			else if (comp=="A+1") out+="0110111"; 
			else if (comp=="D-1") out+="0001110"; 
			else if (comp=="A-1") out+="0110010"; 
			else if (comp=="D+A") out+="0000010"; 
			else if (comp=="D-A") out+="0010011"; 
			else if (comp=="A-D") out+="0000111"; 
			else if (comp=="D&A") out+="0000000"; 
			else if (comp=="D|A") out+="0010101"; 
			else if (comp=="M") out+="1110000"; 
			else if (comp=="!M") out+="1110001"; 
			else if (comp=="-M") out+="1110011"; 
			else if (comp=="M+1") out+="1110111"; 
			else if (comp=="M-1") out+="1110010"; 
			else if (comp=="D+M") out+="1000010"; 
			else if (comp=="D-M") out+="1010011"; 
			else if (comp=="M-D") out+="1000111"; 
			else if (comp=="D&M") out+="1000000"; 
			else if (comp=="D|M") out+="1010101"; 
			else return fprintf(stderr,"WA %s",comp.c_str()),0;

			if (dest=="") out+="000";
			else if (dest=="M") out+="001";
			else if (dest=="D") out+="010";
			else if (dest=="MD") out+="011";
			else if (dest=="A") out+="100";
			else if (dest=="AM") out+="101";
			else if (dest=="AD") out+="110";
			else if (dest=="AMD") out+="111";
			else return fprintf(stderr,"WA %s",dest.c_str()),0;
			
			if (jump=="") out+="000";
			else if (jump=="JGT") out+="001";
			else if (jump=="JEQ") out+="010";
			else if (jump=="JGE") out+="011";
			else if (jump=="JLT") out+="100";
			else if (jump=="JNE") out+="101";
			else if (jump=="JLE") out+="110";
			else if (jump=="JMP") out+="111";
			else return fprintf(stderr,"WA %s",jump.c_str()),0;
			
			cout<<out<<endl;
		}
	}
	return 0;
}
