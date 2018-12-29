#include<iostream>
#include<fstream>
using namespace std;

ifstream in;
ofstream out,symboltable;
int dep;
string classname;

void output(string s) {
	//for (int i=0;i<dep*2;i++)
	//	out<<' ';
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
	int pos=s.find(' ')+1;
	symboltable<<s.substr(pos,s.find(' ',pos)-pos)<<" ";
	pos=t.find(' ')+1;
	symboltable<<t.substr(pos,t.find(' ',pos)-pos)<<" "<<classname<<endl;

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

	getline(in,s);classname=s.substr(13,s.size()-13*2);
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
int main(int argc,char **argv) {

	if (argc!=2) {
		puts("Wrong format for parameter");
		return 0;
	}

	ifstream p;
	string f=argv[1],g;
	symboltable.open(f+"/table.txt");
	p.open(f+"/list.txt");

	symboltable<<"init function Math"<<endl;
	symboltable<<"abs function Math"<<endl;
	symboltable<<"multiply function Math"<<endl;
	symboltable<<"divide function Math"<<endl;
	symboltable<<"min function Math"<<endl;
	symboltable<<"max function Math"<<endl;
	symboltable<<"sqrt function Math"<<endl;
	
	symboltable<<"new constructor String"<<endl;
	symboltable<<"dispose method String"<<endl;
	symboltable<<"length method String"<<endl;
	symboltable<<"charAt method String"<<endl;
	symboltable<<"setCharAt method String"<<endl;
	symboltable<<"appendChar method String"<<endl;
	symboltable<<"eraseLastChar method String"<<endl;
	symboltable<<"intValue method String"<<endl;
	symboltable<<"setInt method String"<<endl;
	symboltable<<"backspace function String"<<endl;
	symboltable<<"doubleQuote function String"<<endl;
	symboltable<<"newLine function String"<<endl;
	
	symboltable<<"new function Array"<<endl;
	symboltable<<"dispose method Array"<<endl;
	
	symboltable<<"init function Output"<<endl;
	symboltable<<"moveCursor function Output"<<endl;
	symboltable<<"printChar function Output"<<endl;
	symboltable<<"printString function Output"<<endl;
	symboltable<<"printInt function Output"<<endl;
	symboltable<<"println function Output"<<endl;
	symboltable<<"backspace function Output"<<endl;

	symboltable<<"init function Screen"<<endl;
	symboltable<<"clearScreen function Screen"<<endl;
	symboltable<<"setColor function Screen"<<endl;
	symboltable<<"drawPixel function Screen"<<endl;
	symboltable<<"drawLine function Screen"<<endl;
	symboltable<<"drawRectangle function Screen"<<endl;
	symboltable<<"drawCircle function Screen"<<endl;

	symboltable<<"init function Keyboard"<<endl;
	symboltable<<"keyPressed function Keyboard"<<endl;
	symboltable<<"readChar function Keyboard"<<endl;
	symboltable<<"readLine function Keyboard"<<endl;
	symboltable<<"readInt function Keyboard"<<endl;
	
	symboltable<<"init function Memory"<<endl;
	symboltable<<"peek function Memory"<<endl;
	symboltable<<"poke function Memory"<<endl;
	symboltable<<"alloc function Memory"<<endl;
	symboltable<<"deAlloc function Memory"<<endl;
	
	symboltable<<"init function Sys"<<endl;
	symboltable<<"halt function Sys"<<endl;
	symboltable<<"error function Sys"<<endl;
	symboltable<<"wait function Sys"<<endl;

	while (p>>g)
		if (g.size()>5&&g.substr(g.size()-5,5)==".jack") {
			in.open((g.substr(0,g.size()-5)+".xmlT").c_str());
			out.open((g.substr(0,g.size()-5)+".xml").c_str());
			
			getline(in,s);//<tokens>
			getline(in,s);//keyword<class>
			CompileClass(s);
			getline(in,s);//</tokens>
			
			in.close();
			out.close();
		}

	return 0;
}
