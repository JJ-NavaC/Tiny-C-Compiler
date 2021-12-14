#include <iostream>
#include <map>
#include <string>
#include <set>
#include <sstream>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "SintacticAnalyzer.h"
#include "SemanticAnalyzer.h"

using namespace std;

// https://app.diagrams.net/#G1SXGbBbt8RPmqT9iGNhADK2XGB8EmjPOS

int main(){
    LexicalAnalyzer a1;
	SintacticAnalyzer a2;
	SemanticAnalyzer a3;
    string doc = "test-2.txt";
    string* dividedLine;
    dividedLine = new string[20];



	cout << endl << "---------------Lexical Analysis---------------" << endl << endl;
    int aux = 0;
    ifstream file;
    string text;
    int aux1 = 1;
    file.open(doc ,ios::in);
    if(file.fail()){
        cout << "Something wrong :(" << endl;
        exit(1);
    } 
    while(!file.eof()){
        getline(file,text);
        if(text!=""){            
            int aux = 0;
            string line = text;
            istringstream isstream(line);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                dividedLine[aux] = tempStr;
                aux++;
            }
			if(aux>4){
				cout << text << "\t\tline " << aux1++ << "\t\t";
				if(a1.test(text)){
					cout << "Acepted" << endl;
				} else {
					cout << "Rejected" << endl;
				}
			} else if (aux == 1){
				cout << text << "\t\t\t\tline " << aux1++ << "\t\t";
				if(a1.test(text)){
					cout << "Acepted" << endl;
				} else {
					cout << "Rejected" << endl;
				}
			} else {
				cout << text << "\t\t\tline " << aux1++ << "\t\t";
				if(a1.test(text)){
					cout << "Acepted" << endl;
				} else {
					cout << "Rejected" << endl;
				}
			} 			
        }        
    }
    file.close();		
    cout << endl;



	aux1 = 1;
	cout << "---------------Sintactic Analysis---------------" << endl << endl;
	file.open(doc ,ios::in);
    if(file.fail()){
        cout << "Something wrong :(" << endl;
        exit(1);
    } 
    while(!file.eof()){
        getline(file,text);
        if(text!=""){            
            int aux = 0;
            string line = text;
            istringstream isstream(line);
            while(!isstream.eof()){
                string tempStr;
                isstream >> tempStr;
                dividedLine[aux] = tempStr;
                aux++;
            }
            if(aux>4){
			    cout << text << "\t\tline " << aux1++ << "\t\t";
				if(a2.test(text)){
					cout << "Acepted" << endl;
				} else {
					cout << "Rejected" << endl;
				}
			} else if (aux == 1){
				cout << text << "\t\t\t\tline " << aux1++ << "\t\t";
				if(a2.test(text)){
					cout << "Acepted" << endl;
				} else {
					cout << "Rejected" << endl;
				}
			} else {
				cout << text << "\t\t\tline " << aux1++ << "\t\t";
				if(a2.test(text)){
					cout << "Acepted" << endl;
				} else {
					cout << "Rejected" << endl;
				}
			} 			
        }      
    }
    file.close();		
    cout << endl;
    if(a2.getStatus()){
        cout << "Falta completar bloque de llave '{' o '}'" << endl;
    } else {
        aux1 = 1;
	    cout << "---------------Semantic Analysis---------------" << endl << endl;
	    file.open(doc ,ios::in);
        if(file.fail()){
            cout << "Something wrong :(" << endl;
            exit(1);
        } 
        while(!file.eof()){
            getline(file,text);
            if(text!=""){            
                int aux = 0;
                string line = text;
                istringstream isstream(line);
                while(!isstream.eof()){
                    string tempStr;
                    isstream >> tempStr;
                    dividedLine[aux] = tempStr;
                    aux++;
                } 
                cout << text << "\t\t\tline " << aux1++ <<  endl;
                a3.analyze(dividedLine, aux);
            }        
        }
        file.close();
        cout << endl;
        a3.printA();        			
    }   
    return EXIT_SUCCESS;
} 