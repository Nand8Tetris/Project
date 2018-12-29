#include<bits/stdc++.h>
using namespace std;

FILE *in,*out;

char keyword[10000][100]={"class","constructor","function","method","field","static","var","int","char","boolean","void","true","false","null","this","let","do","if","else","while","return"};
char symbol[10000][10]={"{","}","(",")","[","]",".",",",";","+","-","*","/","&","|","<",">","=","~"};

char tpname[10000][100]={"","keyword","symbol","integerConstant","StringConstant","identifier"};

bool issymbol(char c) {
	for (int i=0;*symbol[i];i++)
		if (*symbol[i]==c)
			return true;
	return false;
}

bool iskeyword(char *s) {
	for (int i=0;*keyword[i];i++)
		if (!strcmp(s,keyword[i]))
			return true;
	return false;
}

void work() {
	char c,*t,*p;char str[100];int len;
	static char text[1000001],*T=text;
	while (fscanf(in,"%s",str)!=EOF) {
		len=strlen(str);
		if (len>1&&str[0]=='/'&&str[1]=='/')
			while (fscanf(in,"%c",&c),c!=10&&c!=13);
		else
			if (len>1&&str[0]=='/'&&str[1]=='*')
				while (fscanf(in,"%s",str),(len=strlen(str))<2||str[len-2]!='*'||str[len-1]!='/');
			else {
				for (t=str;*t;*T++=*t++);
				*T++=' ';
			}
	}
	for (t=p=text;*p;p++)
		if (*p==' '||*p=='"'||issymbol(*p)) {
			char g=*p;*p=0;
			if (t!=p) {
				string o=iskeyword(t)?"keyword":(isdigit(*t)?"integerConstant":"identifier");
				fprintf(out,"<%s> %s </%s>\n",o.c_str(),t,o.c_str());
			}
			if (g==' ');
			else if (g=='"') {
				fprintf(out,"<stringConstant> ");
				while (*++p!='"') fprintf(out,"%c",*p);*p=0;
				fprintf(out," </stringConstant>\n");
			} else {
				fprintf(out,"<symbol> ");
				if (g=='<') fprintf(out,"&lt;");
				else if (g=='>') fprintf(out,"&gt;");
				else if (g=='&') fprintf(out,"&amp;");
				else fprintf(out,"%c",g);
				fprintf(out," </symbol>\n");
			}
			t=p+1;
		}
}

int main(int argc,char **argv) {

	if (argc!=3) {
		puts("Wrong format for parameter");
		return 0;
	}

	in=fopen(argv[1],"r");
	out=fopen(argv[2],"w");
	//in=fopen("Main.jack","r");
	//out=fopen("outT.xml","w");
	if (!in) {
		printf("can't find %s\n",argv[1]);
		exit(0);
	}

	fprintf(out,"<tokens>\n");
	work();
	fprintf(out,"</tokens>\n");
	return 0;
}
