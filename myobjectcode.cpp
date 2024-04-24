#include "myobjectcode.h"

myObjectCode::myObjectCode()
{
    // 初始化寄存器，用"#"表示寄存器为空
    for(int i=0;i<regNum;i++)
    {
        this->reg.push_back("#");
    }
}

void myObjectCode::clearFourCode()
{
    // 清空四元式代码容器
    this->fourCode.clear();
}

void myObjectCode::setFourCode(four _code)
{
    // 将四元式代码添加到容器中
    this->fourCode.push_back(_code);
}

QVector<QString> myObjectCode::generation(QVector<QString> _code)
{
    qDebug() << _code[0];
    this->str.clear();
    this->ansCode.clear();
    n = _code.size();

    // 将输入的中间代码字符串切分为二维数组
    for(int i=0;i<n;i++)
    {
        str.push_back(_code[i].split(" "));
    }

    for(int i=0;i<n;i++){
        int index = indexReg(str[i][3]);
        if(index == inf){
            // 如果寄存器中不存在该变量，选择一个寄存器存储
            index = choseReg(i);
            ansCode.push_back(QString("LD R%1, %2").arg(index).arg(str[i][3]));
        }
        printfAns(i,index);
    }
    return ansCode;
}

int myObjectCode::indexReg(QString ch)
{
    // 查找变量在寄存器中的索引
    for(int i=0;i<this->regNum;i++){
        if(reg[i] == ch) return i;
    }
    return inf;
}

int myObjectCode::existBehind(int id,QString ch)
{
    // 查找变量在之后的四元式中是否存在
    for(int i=id;i<n;i++){
        if(ch == str[i][3] || ch == str[i][5]) return i;
    }
    return inf;
}

int myObjectCode::choseReg(int id)
{
    // 选择要存储的寄存器
    if(top<regNum) return top++;
    int Max = -1,index =0;
    for(int i=0;i<regNum;i++){
        if(existBehind(id,reg[i]) > Max){
            Max = existBehind(id,reg[i]);
            index = i;
        }
    }
    if(reg[index]!='\0' && existBehind(id,reg[index])!=inf){
        ansCode.push_back(QString("ST R%1, %2").arg(index).arg(reg[index]));
        reg[index] = NULL;
    }
    return index;
}

void myObjectCode::printfAns(int id,int index)
{
    // 输出生成的目标代码
    QString tmpAns;
    QString temp = str[id][4];
    if(temp == '+') tmpAns.push_back("ADD ");
    else if (temp == '-')
    {
        tmpAns.push_back("SUB ");
    }else if (temp == '*')
    {
        tmpAns.push_back("MUL ");
    }else if (temp == '/')
    {
        tmpAns.push_back("DIV ");
    }
    tmpAns.push_back(QString("R%1, ").arg(index));
    if(indexReg(str[id][5]) == inf){
        tmpAns.push_back(str[id][5]);
    }else{
        tmpAns.push_back(QString("R%1").arg(indexReg(str[id][5])));
    }
    reg[index] = str[id][0];
    ansCode.push_back(tmpAns);
}
