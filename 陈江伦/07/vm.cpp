#include<bits/stdc++.h>
using namespace std;
//SP Õ»¶¥
//LCL local
//ARG argument
//THIS
//THAT
int main() {
	freopen("SimpleFunction.vm","r",stdin);
	freopen("SimpleFunction.asm","w",stdout);

	char c=getchar();
	string op;
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
		} else {
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
		}
		c=getchar();
	}
	
	return 0;
}
