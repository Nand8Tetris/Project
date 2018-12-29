#include<iostream>
#include<fstream>
#include<map>
#include"assert.h"
using namespace std;
#define mp make_pair
#define pb push_back
ifstream in;
ofstream out;

int if_cnt,while_cnt;

string s;

typedef pair<int,int> PR;

//map<string,int>ID;
map<string,int>local,fie,sta,parameter;
map<string,string>vartype,fievartype,functiontable;
string v;
string returntype,functionname,functiontype;
string classname;

bool checkvar(string varname) {
	if (local.count(varname))
		v+="local "+to_string(local[varname]);
	else if (parameter.count(varname))
		v+="argument "+to_string(parameter[varname]);
	else if (fie.count(varname))
		v+="this "+to_string(fie[varname]);
	else if (sta.count(varname))
		v+="static "+to_string(sta[varname]);
	else {
		//assert(functiontable.count(varname));
		return false;
	}
	v+="\n";
	return true;
}
bool CompileExpression();
int CompileExpressionList();
void CompileTerm() {
	//函数调用
	//~ 加上 Term
	//变量
	//常数
	//字符串
	getline(in,s);//<term>
	in>>s;
	if (s=="<symbol>") {
		string op;in>>op;getline(in,s);
		if (op=="(") {
		   CompileExpression();
		   getline(in,s);//<symbol> ) </symbol>
		} else {
			CompileTerm();
			if (op=="~")
				v+="not\n";
			else if (op=="-")
				v+="neg\n";
			else
				assert(false);
		}
	} else if (s=="<integerConstant>") {
		in>>s;
		v+="push constant "+s+"\n";
		getline(in,s);
	} else if (s=="<stringConstant>") {
		getline(in,s);
		s=s.substr(1,s.size()-17-2);
		v+="push constant "+to_string(s.size())+"\n";
		v+="call String.new 1\n";
		for (char ch:s) {
			v+="push constant "+to_string(int(ch))+"\n";
			v+="call String.appendChar 2\n";
		}
	} else if (s=="<identifier>") {
		string o,fr;in>>o;getline(in,s);
		getline(in,s);
		if (s=="<symbol> [ </symbol>") {
			CompileExpression();
			v+="push ";checkvar(o);
			v+="add\n";
			v+="pop pointer 1\n";
			v+="push that 0\n";
			getline(in,s);//<symbol> ] </symbol>
		} else {
			v+="push ";
			if (s=="</term>") {
				checkvar(o);
				return;
			}
			if (s=="<symbol> . </symbol>") {//<symbol> . </symbol>
				fr=o;
				in>>s;in>>o;getline(in,s);
				getline(in,s);//<symbol> ( </symbol>
			} else fr=classname;
			int vars=0;
			if (checkvar(fr)) vars++,fr=vartype[fr];
			else for (int i=0;i<5;i++) v.pop_back();
			vars+=CompileExpressionList();
			v+="call "+fr+"."+o+" "+to_string(vars)+"\n";
			getline(in,s);//<symbol> ) </symbol>
		}
	} else if (s=="<keyword>") {
		in>>s;
		if (s=="null"||s=="false")
			v+="push constant 0\n";
		else if (s=="true")
			v+="push constant 0\n",v+="not\n";
		else if (s=="this")
			v+="push pointer 0\n";
		else if (s=="that")
			v+="push pointer 1\n";
		getline(in,s);
	}
	getline(in,s);//</trem>
}

bool CompileExpression() {
	getline(in,s);//<expression>
	if (s!="<expression>")
		return false;
	CompileTerm();
	in>>s;
	if (s!="</expression>") {
		string op;in>>op;getline(in,s);
		CompileTerm();
		if (op=="+")
			v+="add";
		else if (op=="-")
			v+="sub";
		else if (op=="*")
			v+="call Math.multiply 2";
		else if (op=="/")
			v+="call Math.divide 2";
		else if (op=="&amp;")
			v+="and";
		else if (op=="|")
			v+="or";
		else if (op=="&lt;")
			v+="lt";
		else if (op=="&gt;")
			v+="gt";
		else if (op=="=")
			v+="eq";
		else
			assert(false);
		v+="\n";
		getline(in,s);//</expression>
	} else getline(in,s);
	return true;
}

int CompileExpressionList() {
	int vars=0;
	getline(in,s);
	while (CompileExpression()) {
		++vars;
		getline(in,s);
		if (s=="</expressionList>")
			break;
	}
	return vars;
}
void CompileStatements(string stop) {
	string trash;
	while (in>>s,getline(in,trash),s!=stop) {
		if (s=="<letStatement>") {
			getline(in,s);//<keyword> let </keyword>
	
			in>>s;string varname;in>>varname;getline(in,s);

			getline(in,s);
			bool isarray=false;
			if (s=="<symbol> [ </symbol>") {
				isarray=true;
				CompileExpression();
				v+="push ";
				checkvar(varname);
				v+="add\n";
				getline(in,s);//<symbol> ] </symbol>
				getline(in,s);//<symbol> = </symbol>
			}
			CompileExpression();
			if (isarray) {
				v+="pop temp 0\n";
				v+="pop pointer 1\n";
				v+="push temp 0\n";
				v+="pop that 0\n";
			} else {
				v+="pop ";
				checkvar(varname);
			}
			getline(in,s);//<symbol> ; </symbol>
			getline(in,s);//</letStatement>
		} else if (s=="<doStatement>") {
			getline(in,s);//<keyword> do </keyword>
			in>>s;string o,fr;in>>o;getline(in,s);//<identifier> 类名称
			getline(in,s);
			if (s=="<symbol> . </symbol>") {//<symbol> . </symbol>
				fr=o;
				in>>s;in>>o;getline(in,s);
				getline(in,s);//<symbol> ( </symbol>
			} else fr=classname;
			int vars=0;
			v+="push ";
			//string zz=functiontable[fr+"."+o];
			if (checkvar(fr))
				fr=vartype[fr],vars++;
			else
				if (functiontable[fr+"."+o]=="method")
					v+="pointer 0\n",fr=classname,vars++;
				else
					for (int i=0;i<5;i++) v.pop_back();
			vars+=CompileExpressionList();
			v+="call "+fr+"."+o+" "+to_string(vars)+"\n";
			getline(in,s);//<symbol> ) </symbol>
			getline(in,s);//<symbol> ; </symbol>
			getline(in,s);//</doStatement>
			v+="pop temp 0\n";
		} else if (s=="<ifStatement>") {
			getline(in,s);//<keyword> if </keyword>
			getline(in,s);//<symbol> ( </symbol>

			CompileExpression();
			int ifcnt=if_cnt++;
			v+="if-goto IF_TRUE"+to_string(ifcnt)+"\n";
			v+="goto IF_FALSE"+to_string(ifcnt)+"\n";
			v+="label IF_TRUE"+to_string(ifcnt)+"\n";
			getline(in,s);//<symbol> ) </symbol>
			getline(in,s);//<symbol> { </symbol>
			getline(in,s);//<statements>
			CompileStatements("</statements>");
			getline(in,s);//<symbol> } </symbol>
			getline(in,s);
			if (s=="<keyword> else </keyword>") {
				v+="goto IF_END"+to_string(ifcnt)+"\n";
				v+="label IF_FALSE"+to_string(ifcnt)+"\n";
				getline(in,s);//<symbol> { </symbol>
				getline(in,s);//<statements>
				CompileStatements("</statements>");
				getline(in,s);//<symbol> } </symbol>
				getline(in,s);//</ifStatement>
				v+="label IF_END"+to_string(ifcnt)+"\n";
			} else v+="label IF_FALSE"+to_string(ifcnt)+"\n";
		} else if (s=="<whileStatement>") {
			int whilecnt=while_cnt++;
			getline(in,s);//<keyword> while </keyword>
			getline(in,s);//<symbol> ( </symbol>
			v+="label WHILE_EXP"+to_string(whilecnt)+"\n";
			CompileExpression();
			v+="not\n";
			v+="if-goto WHILE_END"+to_string(whilecnt)+"\n";
			getline(in,s);//<symbol> ) </symbol>
			getline(in,s);//<symbol> { </symbol>
			CompileStatements("</statements>");
			v+="goto WHILE_EXP"+to_string(whilecnt)+"\n";
			v+="label WHILE_END"+to_string(whilecnt)+"\n";
			getline(in,s);//<symbol> } </symbol>
			getline(in,s);//</whileStatement>
		} else if (s=="<returnStatement>") {
			getline(in,s);//<keyword> return </keyword>
			if (returntype=="void")
				v+="push constant 0\n";
			else
				CompileExpression();
			v+="return\n";
			getline(in,s);//<symbol> } </symbol>
			getline(in,s);//</returnStatement>
		}
		else
			if (s!="<statements>")
				assert(false);
	}
}

void CompileSubroutine() {
	if_cnt=0;
	while_cnt=0;
	local.clear();parameter.clear();vartype=fievartype;
	in>>s;in>>functiontype;getline(in,s);
	in>>s;in>>returntype;getline(in,s);
	in>>s;in>>functionname;getline(in,s);
	if (functiontype=="constructor") {
		v+="push constant "+to_string(fie.size())+"\n";
		v+="call Memory.alloc 1\n";
		v+="pop pointer 0\n";
	}
	if (functiontype=="method") {
		v+="push argument 0\n";
		v+="pop pointer 0\n";
	}
	
	if (functiontype=="method")
		parameter["this"]=0;
	
	getline(in,s);//<symbol> ( </symbol>
	in>>s;//<parameterList>
	while (in>>s,s!="</parameterList>")
		if (s=="<keyword>"||s=="<identifier>") {
			getline(in,s);
			in>>s;in>>s;parameter[s]=parameter.size()-1;getline(in,s);
		}
	in>>s;getline(in,s);//<symbol> ) </symbol>

	getline(in,s);//<subroutineBody>
	getline(in,s);//<symbol> { </symbol>
	while (getline(in,s),s=="<varDec>") {
		getline(in,s);//<keyword> var </keyword>
		in>>s;string tp;in>>tp;getline(in,s);
		in>>s;in>>s;local[s]=local.size()-1;vartype[s]=tp;
		getline(in,s);
		while (getline(in,s),s=="<symbol> , </symbol>") {
			in>>s;in>>s;local[s]=local.size()-1;getline(in,s);
		}//<symbol> ; </symbol>
		getline(in,s);//</varDec>
	}//<statements>
	CompileStatements("</statements>");
	getline(in,s);//<symbol> } </symbol>
	getline(in,s);//</subroutineBody>
}

void CompileClass(string t) {

	in>>s;in>>classname;getline(in,s);//<identifier> name </identifier>
	getline(in,s);//<symbol> { </symbol>
	
	while (1) {
		getline(in,s);
		if (s=="<symbol> } </symbol>")
			break;
		if (s=="<keyword> static </keyword>") {
			in>>s;string tp;in>>tp;getline(in,s);
			in>>s;in>>s;sta[s]=sta.size()-1;fievartype[s]=tp;getline(in,s);
			getline(in,s);
		} else if (s=="<keyword> field </keyword>") {
			in>>s;string tp;in>>tp;getline(in,s);
			in>>s;in>>s;fie[s]=fie.size()-1;fievartype[s]=tp;getline(in,s);
			while (getline(in,s),s!="<symbol> ; </symbol>")
				in>>s,in>>s,fie[s]=fie.size()-1,getline(in,s);
		} else if (s=="<subroutineDec>") {
			v.clear();
			CompileSubroutine();
			out<<"function "<<classname<<"."<<functionname<<" "<<local.size()<<endl;
			out<<v;
			in>>s;//</subroutineDec>
		}
	}
}

int main(int argc,char **argv) {
	/*ID["boolean"]=0;
	ID["int"]=1;
	ID["char"]=2;
	ID["String"]=3;
	ID["Array"]=4;*/

	/*if (argc!=2) {
		puts("Wrong format for parameter");
		return 0;
		}*/

	ifstream p,q;
	string f=argv[1],g,gg,ggg;
	p.open(f+"/list.txt");
	q.open(f+"/table.txt");
	while (q>>g) {
		q>>gg,q>>ggg;
		functiontable[ggg+"."+g]=gg;
	}
	//for (auto zz:functiontable)
	//	fprintf(stderr,"%s %s\n",zz.first.c_str(),zz.second.c_str());
	while (p>>g)
		if (g.size()>5&&g.substr(g.size()-5,5)==".jack") {
			fie.clear();
			sta.clear();
			fievartype.clear();
			in.open((g.substr(0,g.size()-5)+".xml").c_str());
			out.open((g.substr(0,g.size()-5)+".vm").c_str());
			
			//in.open("Square/MainT.xml");
			//out.open("Square/out.xml");
			
			getline(in,s);//<class>
			getline(in,s);//<keyword> class </keyword>
			
			CompileClass(s);
			in.close();
			out.close();
		}
	return 0;
}
