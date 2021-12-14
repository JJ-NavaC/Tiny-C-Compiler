#ifndef SemanticAnalyzer_h
#define SemanticAnalyzer_h

#include <stddef.h>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
     
using namespace std;

class SemanticAnalyzer {
    set <string> rWords; // int, main, void
    set <string> simbolTable; // =, +, -, *, /;
    set <string> delimiters; // {, }, (, ), ;, coma ,
    map <string,int> varNames; // nombre de variables declaradas durante el codigo 
    set <string> funcNames; // nombre de funciones declaradas durante el codigo 
public:
    SemanticAnalyzer();
    void analyze(string*,int);

    void printA();
};

#endif