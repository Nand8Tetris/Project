#include<bits/stdc++.h>
using namespace std;

FILE *in,*out;

char keyword[10000][100]={"class","constructor","function","method","field","static","var","int","char","boolean","void","true","false","null","this","let","do","if","else","while","return"};
char symbol[10000][10]={"{","}","(",")","[","]",".",",",";","+","-","*","/","&","|","<",">","=","~"};

char tpname[10000][100]={"","keyword","symbol","integerConstant","StringConstant","identifier"};

void push(string s) {
	
}

void work() {
	char Str[100],*str,ch;
	int type,len;
	while (str=Str,fscanf(in,"%s",Str)!=EOF) {
		if (str[0]=='/'&&str[1]=='/') {
			while (fscanf(in,"%c",&ch),ch!=10&&ch!=13);
			continue;
		}
		if (str[0]=='/'&&str[1]=='*') {
			while (fscanf(in,"%s",str),(len=strlen(str))<2||str[len-2]!='*'||str[len-1]!='/');
			continue;
		}
		
		type=0;
		for (int i=0;*keyword[i];i++)
			if (!strcmp(keyword[i],str))
				type=1;
		for (int i=0;*symbol[i];i++)
			if (!strcmp(symbol[i],str))
				type=2;
		if ('0'<=str[0]&&str[0]<='9')
			type=3;
		if (str[0]=='"') {
			type=4,str++,str[strlen(str)-1]=0;
			continue;
		}
		if (!type) type=5;

		fprintf(out,"<%s> %s </%s>\n",tpname[type],str,tpname[type]);
	}
}

int main(int argc,char **argv) {

	/*if (argc!=3) {
		puts("Wrong format for parameter");
		return 0;
	}

	in=fopen(argv[1],"r");
	out=fopen(argv[2],"w");
	*/
	in=fopen("Main.jack","r");
	out=fopen("outT.xml","w");
	if (!in) {
		printf("can't find %s\n",argv[1]);
		exit(0);
	}

	fprintf(out,"<tokens>\n");
	work();
	fprintf(out,"</tokens>\n");
	return 0;
}
