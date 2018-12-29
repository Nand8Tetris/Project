#include<bits/stdc++.h>
using namespace std;
//SP Õ»¶¥
//LCL local
//ARG argument
//THIS
//THAT
map<string,int>argu;
void pushD() {
	puts("@SP");
	puts("A=M");
	puts("M=D");
	puts("@SP");
	puts("M=M+1");
}
int main() {
	freopen("FibonacciElement.vm","r",stdin);
	freopen("FibonacciElement.asm","w",stdout);
	char c=getchar();
	string op;
	int cnt=0;
	string name;
	puts("@256");
	puts("D=A");
	puts("@0");
	puts("M=D");
	while (c!=-1) {
		if (c=='/') {
			while (c!=10&&c!=13) c=getchar();
			c=getchar();
			continue;
		}
		if (c<'a'||'z'<c) {
			c=getchar();
			continue;
		}
		cin>>op;
		op=c+op;
		if (op=="push"||op=="pop") {
			string s;cin>>s;
			int id;cin>>id;
			printf("@%d\n",id);
			puts("D=A");
			if (s=="constant") {
			} else {
				if (s=="argument")
					puts("@ARG");
				if (s=="local")
					puts("@LCL");
				if (s=="static") {
					puts("@16");
					goto nxt;
				}
				if (s=="this")
					puts("@THIS");
				if (s=="that")
					puts("@THAT");
				if (s=="pointer") {
					puts("@3");
					goto nxt;
				}
				if (s=="temp") {
					puts("@5");
					goto nxt;
				}
				puts("A=M");
			nxt:;
				if (op=="push") {
					puts("A=A+D");
					puts("D=M");
				} else {
					puts("D=A+D");
				}
			}
			if (op=="push") {
				puts("@SP");
				puts("A=M");
				puts("M=D");
				puts("@SP");
				puts("M=M+1");
			} else {
				puts("@R5");
				puts("M=D");
				puts("@SP");
				puts("M=M-1");
				puts("A=M");
				puts("D=M");
				puts("@R5");
				puts("A=M");
				puts("M=D");
			}
		} else if (op=="neg"||op=="not") {
			puts("@SP");
			puts("A=M");
			puts("A=A-1");
			if (op=="neg")
				puts("M=-M");
			if (op=="not")
				puts("M=!M");
		} else if (op=="add"||op=="sub"||op=="and"||op=="or"||op=="eq"||op=="gt"||op=="lt") {
			puts("@SP");
			puts("M=M-1");
			puts("A=M");
			puts("D=M");
			puts("@SP");
			puts("M=M-1");
			puts("A=M");
			if (op=="add")
				puts("M=M+D");
			if (op=="sub")
				puts("M=M-D");
			if (op=="and")
				puts("M=M&D");
			if (op=="or")
				puts("M=M|D");
			if (op=="eq"||op=="gt"||op=="lt") {
				static int cnt;
				puts("D=M-D");
				puts("M=-1");
				printf("@jump%d\n",++cnt);
				if (op=="eq")
					puts("D;JEQ");
				if (op=="gt")
					puts("D;JGT");
				if (op=="lt")
					puts("D;JLT");
				puts("@SP");
				puts("A=M");
				puts("M=0");
				printf("(jump%d)\n",cnt);
			}
			puts("@SP");
			puts("M=M+1");
		} else if (op=="label") {
			string s;cin>>s;
			printf("(%s.%s)\n",name.c_str(),s.c_str());
		} else if (op=="goto") {
			string s;cin>>s;
			printf("@%s.%s\n",name.c_str(),s.c_str());
			puts("0;JEQ");
		} else if (op=="if-goto") {
			string s;cin>>s;
			puts("@SP");
			puts("M=M-1");
			puts("A=M");
			puts("D=M");
			printf("@%s.%s\n",name.c_str(),s.c_str());
			puts("D;JNE");
		} else if (op=="function") {
			string s;cin>>s;
			printf("(%s)\n",s.c_str());
			cin>>argu[s];
			for (int i=0;i<argu[s];i++)
				puts("D=0"),pushD();
			name=s;
		} else if (op=="call") {
			++cnt;
			printf("@return%d\n",cnt);
			puts("D=A");
			pushD();

			puts("@LCL");
			puts("D=M");
			pushD();

			puts("@ARG");
			puts("D=M");
			pushD();

			puts("@THIS");
			puts("D=M");
			pushD();

			puts("@THAT");
			puts("D=M");
			pushD();

			puts("@SP");
			puts("D=M");
			puts("@LCL");
			puts("M=D");
			puts("@ARG");
			puts("M=D");
			string s;cin>>s;
			int k;for (cin>>k,k+=5;k;k--) puts("M=M-1");

			printf("@%s\n",s.c_str());
			puts("0;JEQ");

			printf("(return%d)\n",cnt);
		} else if (op=="return") {
			puts("@LCL");
			puts("D=M");
			puts("@R5");
			puts("M=D");
			
			puts("@LCL");
			puts("A=M");
			for (int i=0;i<5;i++) puts("A=A-1");
			puts("D=M");
			puts("@R6");
			puts("M=D");
			
			puts("@SP");
			puts("M=M-1");
			puts("A=M");
			puts("D=M");
			puts("@ARG");
			puts("A=M");
			puts("M=D");

			puts("D=A+1");
			puts("@SP");
			puts("M=D");

			puts("@R5");
			puts("M=M-1");
			puts("A=M");
			puts("D=M");
			puts("@THAT");
			puts("M=D");

			puts("@R5");
			puts("M=M-1");
			puts("A=M");
			puts("D=M");
			puts("@THIS");
			puts("M=D");

			puts("@R5");
			puts("M=M-1");
			puts("A=M");
			puts("D=M");
			puts("@ARG");
			puts("M=D");

			puts("@R5");
			puts("M=M-1");
			puts("A=M");
			puts("D=M");
			puts("@LCL");
			puts("M=D");
			
			puts("@R6");
			puts("A=M");

			puts("0;JEQ");
		}
		c=getchar();
	}
	
	return 0;
}
