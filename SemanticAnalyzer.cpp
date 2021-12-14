#include "SemanticAnalyzer.h"

using namespace std;

SemanticAnalyzer::SemanticAnalyzer(){
    rWords.insert("int");
    rWords.insert("main");
    rWords.insert("main(void)");
    rWords.insert("void");
    rWords.insert("return");

    simbolTable.insert("=");
    simbolTable.insert("+");
    simbolTable.insert("-");
    simbolTable.insert("*");
    simbolTable.insert("/");

    delimiters.insert("{");
    delimiters.insert("}");
    delimiters.insert("(");
    delimiters.insert(")");
    delimiters.insert(";");
    delimiters.insert(",");  
    
    
    /* varNames["op1"] = 36;
    varNames["op2"] = 12;
    varNames["suma"] = 0;
    varNames["resta"] = 0;
    varNames["mult"] = 0;
    varNames["div"] = 0;
    varNames["total"] = 0; */
}

void SemanticAnalyzer::analyze(string* words, int length){    
    int pos = 0;  
    string aux = "";
    if((words[pos]=="{") or (words[pos]=="}")){
        return;
    } else if(words[pos]=="int"){   
        bool exist = false;
        bool exist2 = false;
        bool exist3 = false;
        pos++;
        if(words[pos]=="main(void)"){
            while(pos < length){
                pos++;                
            }
           return;
        } 
        while(pos < length){             
            string::iterator it=words[pos].end();                                                           
            it = it-4;                                                                                           
            string aux (1, *it);
            if(aux=="("){
                words[pos].erase(it, it+4);
                for(auto &a: funcNames){
                    if (words[pos]==a){
                         exist2 = true;
                    } 
                }           
                if(!exist2){
                    funcNames.insert(words[pos]);
                }
                pos++;
                while(pos < length){                                       
                    string::iterator it=words[pos].end();                                                           
                    it--;                                                                                           
                    string aux (1, *it); 
                    if (aux==","){
                        words[pos].pop_back();
                    }       
                    if (aux==";"){
                        words[pos].pop_back();
                        words[pos].pop_back();
                    }   
                    for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                        if(words[pos]==it1->first){
                           exist = true;
                        }
                    }
                    if(!exist){
                        varNames[words[pos]] = 0;
                    }
                    pos++;
                }
            } else if(words[pos+1]!="="){   
                string::iterator it=words[pos].end();                                                           
                it--;                                                                                           
                string aux (1, *it); 
                if ((aux == ";") or (aux==",")){
                    words[pos].pop_back();
                }                                                                                                       
                for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                    if(words[pos]==it1->first){
                       exist = true;
                    }
                }
                if(!exist){
                    varNames[words[pos]] = 0;
                }
                pos++;
            } else {
                pos++;
                while(pos < length){                     
                    int auxValue;
                    string::iterator it=words[pos+1].end();                                                           
                    it--;                                                                                           
                    string aux (1, *it);
                    if ((aux == ";") or (aux==",")){
                        words[pos+1].pop_back();
                    }
                    for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                        if(words[pos-1]==it1->first){
                           exist = true;
                        }
                        if(words[pos+1]==it1->first){
                           exist2 = true;
                           auxValue = it1->second;
                        }
                    }
                    if(!exist){
                        if(!exist2){
                            istringstream (words[pos+1]) >> auxValue;
                        } 
                        varNames[words[pos-1]] = auxValue;
                    } else {
                        varNames.erase(words[pos-1]);
                        if(!exist2){
                             istringstream (words[pos+1]) >> auxValue;
                        }                       
                        varNames[words[pos-1]] = auxValue;
                    }
                    pos = pos + 3;
                }
            }
        }       
    } else if(words[pos]=="return"){        
        return;
    } else {       
        string auxV;
        int auxO1, auxO2;
        bool dVar = false;
        bool eOp1 = false;
        bool eOp2 = false;
        bool rec = false;
        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
            if(words[pos] == it1->first){
                auxV = it1->first;
                dVar = true;
            }
        }
        if(dVar){
            varNames.erase(auxV);            
            pos++;            
            if(words[pos-1]!="total"){
                pos++;
                if((words[pos+1]=="+")or(words[pos+1]=="-")or(words[pos+1]=="*")or(words[pos+1]=="/")){ 
                    while(pos < length){                        
                        if(!rec){
                            string op = words[pos+1];
                            string::iterator it=words[pos+2].end();                                                           // Obtiene el ultimo caracter de la cadena
                            it--;                                                                                           // Obtiene el ultimo caracter de la cadena
                            string aux (1, *it);
                            if(aux==";"){
                                words[pos+2].pop_back();
                            }
                            for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                                if(words[pos] == it1->first){
                                    eOp1 = true;
                                    auxO1 = it1->second;
                                }
                                if(words[pos+2] == it1->first){
                                    eOp2 = true;
                                    auxO2 = it1->second;
                                }
                            }                        
                            if(op=="+"){
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 + auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 + auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 + auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 + auxO2;
                                    }
                                }
                                rec = true;
                            } else if(op=="-"){
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 - auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 - auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 - auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 - auxO2;
                                    }
                                }
                                rec = true;
                            }
                            else if(op=="*"){
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 * auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 * auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 * auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 * auxO2;
                                    }
                                }
                                rec = true;
                            } else if(op=="/"){
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 / auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 / auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 / auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 / auxO2;
                                    }
                                }
                                rec = true;
                            }             
                        } else {                          
                            string op = words[pos+1];
                            eOp1 = false;
                            eOp2 = false;
                            string::iterator it=words[pos+2].end();                                                           // Obtiene el ultimo caracter de la cadena
                            it--;                                                                                           // Obtiene el ultimo caracter de la cadena
                            string aux (1, *it);
                            if(aux==";"){
                                words[pos+2].pop_back();
                            }
                            for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                                if(auxV == it1->first){
                                    eOp1 = true;
                                    auxO1 = it1->second;
                                }
                                if(words[pos+2] == it1->first){
                                    eOp2 = true;
                                    auxO2 = it1->second;
                                }
                            }                                                    
                            if(op=="+"){
                                varNames.erase(auxV);
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 + auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 + auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 + auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 + auxO2;
                                    }
                                }
                            } else if(op=="-"){
                                varNames.erase(auxV);
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 - auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 - auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 - auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 - auxO2;
                                    }
                                }
                            }
                            else if(op=="*"){
                                varNames.erase(auxV);
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 * auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 * auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 * auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 * auxO2;
                                    }
                                }
                            } else if(op=="/"){
                                varNames.erase(auxV);
                                if(eOp1){
                                    if(eOp2){
                                        varNames[auxV] = auxO1 / auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 / auxO2;
                                    }
                                } else {
                                    istringstream (words[pos]) >> auxO1;
                                    if(eOp2){
                                        varNames[auxV] = auxO1 / auxO2;
                                    } else {
                                        istringstream (words[pos+2]) >> auxO2;
                                        varNames[auxV] = auxO1 / auxO2;
                                    }
                                }
                            } 
                        }
                        pos = pos + 2; 
                    }                          
                } else {
                    string::iterator it=words[pos].end();                                                           
                    it--;                                                                                           
                    string aux (1, *it);
                    if((aux==",")or(aux==";")){
                        words[pos].pop_back();
                    }
                    for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                        if(words[pos] == it1->first){
                            eOp1 = true;
                            auxO1 = it1->second;
                        }
                    }
                    if(eOp1){
                        varNames[auxV] = auxO1;
                    } else {
                        istringstream (words[pos]) >> auxO1;
                    }
                    varNames[auxV] = auxO1;
                }
            } else if((words[pos]=="=")and(words[pos-1]=="total")){                                
                pos++;
                            
                size_t id = words[pos].find("(");
                string p2 = words[pos].substr(id);
                p2.erase(0,1);               
                string::iterator it=words[pos].end();                                                           
                it = it-4;                                                                                           
                string aux_0 (1, *it);   
                it--;
                string aux_1 (1, *it);                 
                string::iterator en=words[pos].end();                
                if(aux_0=="("){
                    it++; 
                    words[pos].erase(it,en);                    
                    string::iterator it=p2.end();                                                           
                    it--;                                                                                           
                    string aux (1, *it);
                    if((aux==",")or(aux==";")){
                        p2.pop_back();
                    }        
                    words[pos+1].pop_back();
                    words[pos+1].pop_back(); 
                    if (words[pos]=="suma"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 + auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 + auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 + auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 + auxO2;
                            }
                        }                 
                    } else if(words[pos]=="rest"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 - auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 - auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 - auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 - auxO2;
                            }
                        }
                    } else if(words[pos]=="mult"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 * auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 * auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 * auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 * auxO2;
                            }
                        }                       
                    } else if(words[pos]=="div"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 / auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 / auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 / auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 / auxO2;
                            }
                        }                      
                    }
                    pos++; 
                } else if(aux_1=="("){
                    words[pos].erase(it,en);                    
                    string::iterator it=p2.end();                                                           
                    it--;                                                                                           
                    string aux (1, *it);
                    if((aux==",")or(aux==";")){
                        p2.pop_back();
                    }        
                    words[pos+1].pop_back();
                    words[pos+1].pop_back(); 
                    if (words[pos]=="suma"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 + auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 + auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 + auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 + auxO2;
                            }
                        }                 
                    } else if(words[pos]=="rest"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 - auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 - auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 - auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 - auxO2;
                            }
                        }
                    } else if(words[pos]=="mult"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 * auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 * auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 * auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 * auxO2;
                            }
                        }                       
                    } else if(words[pos]=="div"){
                        for (map<string,int>::iterator it1=varNames.begin(); it1!=varNames.end(); ++it1){
                            if(p2 == it1->first){
                                eOp1 = true;
                                auxO1 = it1->second;
                            }                            
                            if(words[pos+1] == it1->first){
                                eOp2 = true;
                                auxO2 = it1->second;
                            }
                        }  
                        if(eOp1){
                            if(eOp2){
                                varNames[auxV] = auxO1 / auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 / auxO2;
                            }
                        } else {
                            istringstream (p2) >> auxO1;
                            if(eOp2){
                                varNames[auxV] = auxO1 / auxO2;
                            } else {
                                istringstream (words[pos+1]) >> auxO2;
                                varNames[auxV] = auxO1 / auxO2;
                            }
                        }                      
                    }
                    pos++;
                }             
            }   
        }
    }
}

void SemanticAnalyzer::printA(){
    cout << "Variables:" << endl;
    for (map<string,int>::iterator it=varNames.begin(); it!=varNames.end(); ++it){
        cout << it->first << "\t" << it->second << endl;
    }
    cout << endl << "Functions:" << endl;
    for(auto &a: funcNames){
        cout << a << endl;
    }
}