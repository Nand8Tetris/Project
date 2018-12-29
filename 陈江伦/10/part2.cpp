#include<iostream>
#include<fstream>
using namespace std;

ifstream in;
ofstream out;
int dep;

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

string s;

void CompileVarDec(string id,string t) {
	output("<"+id+">");
	dep++;
	output(t);
	while (getline(in,s),output(s),s!="<symbol> ; </symbol>");
	dep--;
	output("</"+id+">");
}

void CompileParameterList() {
	getline(in,s);
	output(s);//左括号

	output("<parameterList>");
	dep++;

	while (getline(in,s),s!="<symbol> ) </symbol>")
		output(s);

	dep--;
	output("</parameterList>");

	output(s);//右括号
}

void CompileExpression();
void CompileExpressionList();
void CompileTerm(bool &ispre) {

	getline(in,s);
	if (s.substr(0,8)=="<symbol>"&&s[9]==')')
		return;
	if (!ispre) {
		output("<expression>");
		dep++;
		ispre=true;
	}
	output("<term>");
	dep++;
	
	output(s);
	
	if (s=="<symbol> - </symbol>"||s=="<symbol> ~ </symbol>") {
		CompileTerm(ispre);
	} else if (s.substr(0,8)=="<symbol>"&&s[9]=='(') {
		CompileExpression();
		output(s);
		getline(in,s);
	} else {
		getline(in,s);
		if (s.substr(0,8)=="<symbol>"&&s[9]=='.') {
			output(s);
			getline(in,s);
			output(s);
			getline(in,s);
		}
		if (s.substr(0,8)=="<symbol>"&&(s[9]=='('||s[9]=='[')) {
			output(s);
			if (s[9]=='(')
				CompileExpressionList();
			else {
				CompileExpression();
				output(s);
			}
			getline(in,s);
		}
	}

	dep--;
	output("</term>");
}

void CompileExpression() {//读到)或者;或者]或者=或者，停止，并输出)或者]或者,或者=或者;
	bool ispre=false;

	while (1) {
		CompileTerm(ispre);
		if (s.substr(0,8)=="<symbol>"&&(/*s[9]=='='||*/s[9]==','||s[9]==')'||s[9]==']'||s[9]==';'))
			break;
		output(s);
	}

	if (ispre) {
		dep--;
		output("</expression>");
	}
}

void CompileExpressionList() {//读到)或者;或者)停止，并输出)或者;
	output("<expressionList>");
	dep++;
	while (1) {
		CompileExpression();
		if (s!="<symbol> , </symbol>") break;
		output(s);
	}
	dep--;
	output("</expressionList>");
	
	output(s);
}

void CompileDo(string t) {
	output("<doStatement>");
	dep++;

	output(t);

	while (getline(in,s)) {
		output(s);
		if (s=="<symbol> ( </symbol>") break;
	}

	CompileExpressionList();

	getline(in,s);
	output(s);//;

	dep--;
	output("</doStatement>");
}

void CompileLet(string t) {
	output("<letStatement>");
	dep++;

	output(t);

	getline(in,s);
	output(s);//identifier

	getline(in,s);
	if (s=="<symbol> [ </symbol>") {
		output(s);
		CompileExpression();
		output(s);
		getline(in,s);
	}

	output(s);//<symbol> = </symbol>

	CompileExpression();
	output(s);

	dep--;
	output("</letStatement>");
}

void CompileReturn(string t,bool isvoid) {
	output("<returnStatement>");
	dep++;

	output(t);

	if (isvoid)
		getline(in,s),output(s);//;
	else {
		CompileExpression();
		output(s);
	}

	dep--;
	output("</returnStatement>");
}

void CompileIf(string,bool);
void CompileWhile(string,bool);
void CompileElse(string,bool);
void CompileStatements(bool isvoid,bool isbegin) {//遇到}结束,并输出}
	bool lastif=false;
	while (getline(in,s)) {
		if (lastif&&s!="<keyword> else </keyword>") {
			dep--;
			output("</ifStatement>");
		}
		if (!isbegin&&s!="<keyword> var </keyword>")
			isbegin=true,output("<statements>"),dep++;
		lastif=false;
		if (s=="<symbol> } </symbol>") {
			dep--;
			output("</statements>");
			output(s);
			break;
		}
		if (s=="<symbol> { </symbol>") {
			output(s);
			isbegin=true,output("<statements>"),dep++;
		}
		if (s=="<keyword> var </keyword>")
			CompileVarDec("varDec",s);
		else if (s=="<keyword> let </keyword>")
			CompileLet(s);
		else if (s=="<keyword> do </keyword>")
			CompileDo(s);
		else if (s=="<keyword> if </keyword>")
			CompileIf(s,isvoid),lastif=true;
		else if (s=="<keyword> while </keyword>")
			CompileWhile(s,isvoid);
		else if (s=="<keyword> return </keyword>")
			CompileReturn(s,isvoid);		
		else if (s=="<keyword> else </keyword>") {
			CompileElse(s,isvoid);
			dep--;
			output("</ifStatement>");
		}
	}
}

void CompileSubroutine(string t) {
	output("<subroutineDec>");
	dep++;
	output(t);
	
	getline(in,s);
	output(s);//函数类型
	bool isvoid=s.substr(10,4)=="void";
	getline(in,s);
	output(s);//函数名

	CompileParameterList();

	output("<subroutineBody>");
	dep++;

	getline(in,s);
	output(s);//{

	CompileStatements(isvoid,false);

	dep--;
	output("</subroutineBody>");

	dep--;
	output("</subroutineDec>");
}

void CompileWhile(string t,bool isvoid) {
	output("<whileStatement>");
	dep++;

	output(t);

	getline(in,s);
	output(s);//(

	CompileExpression();
	output(s);

	CompileStatements(isvoid,true);

	dep--;
	output("</whileStatement>");
}

void CompileIf(string t,bool isvoid) {//延迟输出if结束符
	output("<ifStatement>");
	dep++;

	output(t);//while

	getline(in,s);//(
	output(s);

	CompileExpression();
	output(s);

	CompileStatements(isvoid,true);

	//dep--;
	//output("</ifStatement>");
}

void CompileElse(string t,bool isvoid) {
	output(t);

	CompileStatements(isvoid,true);
}

void CompileClass(string t) {
	output("<class>");
	dep++;
	output(t);//<keyword> class </keyword>

	getline(in,s);
	output(s);//<identifier> <identifier>

	getline(in,s);
	output(s);//<symbol> { </symbol>

	while (1) {
		getline(in,s);
		if (s=="<symbol> } </symbol>") {
			output(s);
			break;
		}
		if (s=="<keyword> field </keyword>"||s=="<keyword> static </keyword>")
			CompileVarDec("classVarDec",s);
		else if (s=="<keyword> constructor </keyword>"||s=="<keyword> function </keyword>"||s=="<keyword> method </keyword>")
			CompileSubroutine(s);
	}

	dep--;
	output("</class>");
}
#include "assert.h"
int main(int argc,char **argv) {

	if (argc!=3) {
		puts("Wrong format for parameter");
		return 0;
	}
	assert(0);
	in.open(argv[1]);
	out.open(argv[2]);
	
	//in.open("Square/MainT.xml");
	//out.open("Square/out.xml");

	getline(in,s);//<tokens>
	getline(in,s);//keyword<class>
	CompileClass(s);
	getline(in,s);//</tokens>

	return 0;
}
