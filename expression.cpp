#include "expression.h"

Expression::Expression(QString t) : text(t.remove(' ')) {

}

QString Expression::getText() const {
    return text;
}

QString Expression::toString() const {
    return "'" + text + "'";
}

bool isExpression(const QString& i){
    return i.at(0)=='\'' && i.at(i.length()-1)=='\'';
}

bool isChar(QChar a) {
    if (a.isLetterOrNumber())
        return true;
    else return false;
}

bool isPartOperand(QChar a, QString s, int i){
    if(a=='-' && (i==0 || isOperator(QString(s[i-1]))))
        return true;
    else if(a=='$')
        return true;
    else if(a=='.'){
        return true;
    }
    return false;
}

int order(QString op) {
    if(op=="+" || op=="-")
        return 1;
    else if(op=="*" || "/")
        return 2;
    else
        return 0;
}

bool isHigher(QString a, QString b) {
    if(order(a)>=order(b)) return true;
    else return false;
}

QString parseExpression(const QString& s){
    QString infix = s;
    qDebug()<<infix;
    QString postfix = "";
    QStack<QString> stack;
    for(int i = 0; i < infix.length(); i++) {
        qDebug()<<infix[i];
        bool isLongOperator = false;
        //we check if it's an operator composed by more than 1 QChar
        QString opTemp = "";
        int k=i;
        while(infix[k]!='(' && k-i<5 && k<infix.length()){
            opTemp.append(infix[k]);
            k++;
        }
        qDebug()<<"longOperator : "<<opTemp;
        if(isOperator(opTemp)){
            qDebug()<<"operator !!";
            isLongOperator=true;
        }
        //if operand
        if(!isLongOperator && (isChar(infix[i]) || isPartOperand(infix[i], infix, i))) {
            postfix.append(infix[i]);
            qDebug()<<"appending "<<infix[i];
        }
        //if operator
        else if(isOperator(QString(infix[i])) || isLongOperator || infix[i]=='(' || infix[i]==')') {
            QString op = QString(infix[i]);
            if(isLongOperator)
                op=opTemp;
            postfix.append(' ');
            //if stack is empty
            if(stack.isEmpty()) {
                stack.push(op);
            }
            //if stack not empty
            else if(!stack.isEmpty()) {

                //if (
                if(infix[i]=='(') {
                   stack.push(op);
                   }
                //if ) is encountered pop till ( to postfix
                else if(infix[i]==')') {

                    while(!stack.isEmpty() && *(stack.end()-1)!="(") {
                        qDebug()<<"loop";
                        postfix.append(*(stack.end()-1));
                        stack.pop();
                    }
                stack.pop();
                }
                else {
                    //pop until tos has lesser precedence or tos is null.
                    while(!stack.isEmpty() && isHigher(*(stack.end()-1),op) && *(stack.end()-1)!="(") {
                        qDebug()<<*(stack.end()-1);
                        if(*(stack.end()-1)!="(" && *(stack.end()-1)!=")"){//not appending ( and )
                            postfix.append(*(stack.end()-1));
                            postfix.append(' ');
                        }
                        stack.pop_back();
                    }

                    if(stack.isEmpty() || !(isHigher(*(stack.end()-1),op)) || *(stack.end()-1)=="(")
                        stack.push(op);
                    }
            }
            if(isLongOperator){
                qDebug()<<"op length : "<<op.length();
                i+=op.length();
                i--;
            }
        }
        if(infix[i]==',')
            postfix.append(' ');

        qDebug()<<"stack :"<<stack;
    }

        while(!stack.isEmpty()) {
            QStack<QString>::iterator tos = stack.end() - 1;
            postfix.append(' ');
            if(*tos!="(" && *tos!=")"){
                postfix.append(*tos);
            }
            stack.pop();
        }
    qDebug()<<postfix;
    return postfix;
}
