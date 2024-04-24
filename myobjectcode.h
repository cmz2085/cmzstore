#ifndef MYOBJECTCODE_H
#define MYOBJECTCODE_H

#include <mycodegeneration.h>
#include <QStringList>

class myObjectCode
{
public:
    myObjectCode();
    void clearFourCode();
    void setFourCode(four _code);
    QVector<QString> generation(QVector<QString> _code);
    int indexReg(QString ch);
    int existBehind(int id,QString ch);
    int choseReg(int id);
    void printfAns(int id,int index);
public:
    QVector<four> fourCode;
private:
    const int inf = 0x3f3f3f;
    QVector<QStringList> str; // 记得清零
    const int regNum = 2;
    QVector<QString> reg;
    int top = 0;
    int n;
    QVector<QString> ansCode; //最终代码 记得清零
};

#endif // MYOBJECTCODE_H
