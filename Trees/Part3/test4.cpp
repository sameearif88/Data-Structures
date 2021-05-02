#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
using namespace std;

#include "exp_tree.cpp"

string getTreeString(shared_ptr<node> currNode, int padding)
{
    if (currNode == NULL)
        return "";
    padding += 10;
    string returnString = "";
    returnString += getTreeString(currNode->right, padding);
    returnString += '_';
    for (int i = 10; i < padding; i++)
        returnString += ' ';
    returnString += currNode->op;
    returnString += '_';
    returnString += getTreeString(currNode->left, padding);
    return returnString;
}

int checkBuilding(string exprs[], string treeStrings[], string optTreeStrings[], int length)
{
    cout << "Test 4.1 - Building the Expression Tree\n";

    int marks = 0;

    cout << "Test 4.1.1 - optimal set to false: ";

    bool optimal = false;
    ExpTree tree("", optimal);
    bool isCorrect = true;
    for (int i = 0; i < length; ++i)
    {
        tree.buildTree(exprs[i], optimal);
        isCorrect = isCorrect && (treeStrings[i] == getTreeString(tree.getRoot(), 0));
    }
    if (isCorrect)
    {
        marks += 7;
        cout << "Passed\n";
    }
    else
    {
        cout << "Failed\n";
    }

    cout << "Test 4.1.2 - optimal set to true: ";

    optimal = true;
    isCorrect = true;
    for (int i = 0; i < length; ++i)
    {
        tree.buildTree(exprs[i], optimal);
        isCorrect = isCorrect && (optTreeStrings[i] == getTreeString(tree.getRoot(), 0));
    }
    if (isCorrect)
    {
        marks += 3;
        cout << "Passed\n";
    }
    else
    {
        cout << "Failed\n";
    }

    cout << "Total Points: " << marks << "/10\n\n";

    return marks;
}

double getVal(char alphabet, vector<Variable> variables)
{
    return variables[alphabet - 'a'].value;
}

int checkCalculation(string exprs[], int length)
{
    cout << "Test 4.2 - Calculating Value\n";

    srand(time(NULL));

    char var_name = 'a';
    vector<Variable> variables;
    for (int i = 0; i < 26; i++)
        variables.push_back(Variable(var_name++, rand() % 1000));
    // for (int i = 0; i < 26; i++)
    // {
    //     cout << variables[i].name << ": " << variables[i].value << endl;
    // }

    double answers[] = {
        -99,
        getVal('x', variables),
        5.0,
        (getVal('b', variables)+4.0)/(getVal('a', variables)*2.0),
        (getVal('a', variables)*(getVal('b', variables)+2.0))/(7.0-(getVal('c', variables)/getVal('d', variables))),
        (getVal('x', variables)*2.0)+(9.0/(1.0+3.0)),
        5.0+((9.0/(1+((5.0-4)*3)))*getVal('a', variables)),
        (((((getVal('a', variables)+5)+getVal('b', variables))+getVal('a', variables))-6)-1)+getVal('d', variables),
        ((((6*getVal('a', variables))/getVal('c', variables))+5.0)+getVal('e', variables))-((2*4.0)*((0*getVal('d', variables))*3.0)),
        ((getVal('a', variables)+9)*(getVal('a', variables)/(5+4)))/(0.0+getVal('b', variables)+(getVal('b', variables)*(getVal('a', variables)+4)))
    };

    int marks = 0;

    cout << "Test 4.2.1: ";

    bool optimal = false;
    ExpTree tree("", optimal);
    bool isCorrect = true;
    for (int i = 0; i < length; ++i)
    {
        tree.buildTree(exprs[i], optimal);
        isCorrect = isCorrect && (answers[i] == tree.calculate(variables));
    }
    if (isCorrect)
    {
        marks += 10;
        cout << "Passed\n";
    }
    else
    {
        cout << "Failed\n";
    }

    cout << "Total Points: " << marks << "/10\n\n";

    return marks;
}

int checkInfix(string exprs[], string infix_exprs[], int length)
{
    cout << "Test 4.3 - Infix Notation with Parentheses\n";

    int marks = 0;

    cout << "Test 4.3.1: ";

    bool optimal = false;
    ExpTree tree("", optimal);
    bool isCorrect = true;
    for (int i = 0; i < length; ++i)
    {
        tree.buildTree(exprs[i], optimal);
        isCorrect = isCorrect && (infix_exprs[i] == tree.getInfix());
    }
    if (isCorrect)
    {
        marks += 10;
        cout << "Passed\n";
    }
    else
    {
        cout << "Failed\n";
    }

    cout << "Total Points: " << marks << "/10\n\n";

    return marks;
}

int main()
{

    cout << "Test 4 - Expression Tree\n\n";

    int marks = 0;

    string exprs[] = {
        "",
        "x",
        "5",
        "b4+a2*/",
        "ab2+*7cd/-/",
        "x2*913+/+",
        "59154-3*+/a*+",
        "a5+b+a+6-1-d+",
        "6a*c/5+e+24*0d*3**-",
        "a9+a54+/*bba4+*+/"
    };
    string treeStrings[] = {
        "",
        "_x_",
        "_5_",
        "_                    2__          *__                    a__/__                    4__          +__                    b_",
        "_                              d__                    /__                              c__          -__                    7__/__                              2__                    +__                              b__          *__                    a_",
        "_                              3__                    +__                              1__          /__                    9__+__                    2__          *__                    x_",
        "_                    a__          *__                                                  3__                                        *__                                                            4__                                                  -__                                                            5__                              +__                                        1__                    /__                              9__+__          5_",
        "_          d__+__                    1__          -__                              6__                    -__                                        a__                              +__                                                  b__                                        +__                                                            5__                                                  +__                                                            a_",
        "_                              3__                    *__                                        d__                              *__                                        0__          *__                              4__                    *__                              2__-__                    e__          +__                              5__                    +__                                        c__                              /__                                                  a__                                        *__                                                  6_",
        "_                                        4__                              +__                                        a__                    *__                              b__          +__                    b__/__                                        4__                              +__                                        5__                    /__                              a__          *__                              9__                    +__                              a_"
    };
    string optTreeStrings[] = {
        "",
        "_x_",
        "_5_",
        "_                    2__          *__                    a__/__                    4__          +__                    b_",
        "_                              d__                    /__                              c__          -__                    7__/__                              2__                    +__                              b__          *__                    a_",
        "_          2__+__                    2__          *__                    x_",
        "_                    a__          *__                    2__+__          5_",
        "_          d__+__                    1__          -__                              6__                    -__                                        a__                              +__                                                  b__                                        +__                                                            5__                                                  +__                                                            a_",
        "_                              3__                    *__                                        d__                              *__                                        0__          *__                    8__-__                    e__          +__                              5__                    +__                                        c__                              /__                                                  a__                                        *__                                                  6_",
        "_                                        4__                              +__                                        a__                    *__                              b__          +__                    b__/__                              9__                    /__                              a__          *__                              9__                    +__                              a_"
    };
    string infix_exprs[] = {
        "",
        "x",
        "5",
        "(b+4)/(a*2)",
        "(a*(b+2))/(7-(c/d))",
        "(x*2)+(9/(1+3))",
        "5+((9/(1+((5-4)*3)))*a)",
        "(((((a+5)+b)+a)-6)-1)+d",
        "((((6*a)/c)+5)+e)-((2*4)*((0*d)*3))",
        "((a+9)*(a/(5+4)))/(b+(b*(a+4)))"
    };

    marks += checkBuilding(exprs, treeStrings, optTreeStrings, 10);

    marks += checkCalculation(exprs, 10);

    marks += checkInfix(exprs, infix_exprs, 10);

    cout << "Total Marks: " << marks << "/30\n";
    if (marks >= 30)
        cout << "Yayy! You did it! :')" << endl;

    return 0;
}
