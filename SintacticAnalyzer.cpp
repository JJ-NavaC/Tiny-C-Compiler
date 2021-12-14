#include "SintacticAnalyzer.h"
#include <iostream>

SintacticAnalyzer::SintacticAnalyzer(){	
	  q0 = 0;
	  q1 = 1;
	  q2 = 2;
	  q3 = 3;
	  q4 = 4;
    q5 = 5;
	  q6 = 6;
	  q7 = 7;
	  q8 = 8;
    q9 = 9;
    q10 = 10;
    q11 = 11;
    q12 = 12;
    q13 = 13;
    q14 = 14;

	  init = q0;
	  finalStates.insert(q5);
    finalStates.insert(q12);
    finalStates.insert(q13);
    finalStates.insert(q14);
    
    // q0 a q1
    for(int i=48; i<=57; i++){
      delta[q0][(char)i]=q1;
    } // 0-9
    for(int i=65; i<=90; i++){
      delta[q0][(char)i]=q1;
    } // MAYUSCULAS
    for(int i=97; i<=122; i++){
      delta[q0][(char)i]=q1;
    } // minusculas

    // q1 a q1
    for(int i=48; i<=57; i++){
      delta[q1][(char)i]=q1;
    } // 0-9
    for(int i=65; i<=90; i++){
      delta[q1][(char)i]=q1;
    } // MAYUSCULAS
    for(int i=97; i<=122; i++){
      delta[q1][(char)i]=q1;
    } // minusculas

    // q1 a q2
    delta[q1][(char)32]=q2;

    // q2 a q2
    for(int i=48; i<=57; i++){
      delta[q2][(char)i]=q2;
    } // 0-9
    for(int i=65; i<=90; i++){
      delta[q2][(char)i]=q2;
    } // MAYUSCULAS
    for(int i=97; i<=122; i++){
      delta[q2][(char)i]=q2;
    } // minusculas
    delta[q2]['(']=q2;
    delta[q2][')']=q2;
    delta[q2][(char)32]=q2;

    // q2 a q3
    delta[q2]['=']=q3;
    delta[q2][',']=q3;

    // q3 a q2
    delta[q3][(char)32]=q2;

    // q2 a q4
    delta[q2]['+']=q4;
    delta[q2]['-']=q4;
    delta[q2]['*']=q4;
    delta[q2]['/']=q4;

    // q4 a q2
    delta[q4][(char)32]=q2;

    // q2 a q5
    delta[q2][';']=q5;

    // q0 a q13
    delta[q0]['{']=q13;

    // q0 a q14
    delta[q0]['}']=q14;

    // q0 a q6
    delta[q0]['i']=q6;

    // q6 a q7
    delta[q6]['n']=q7;

    // q7 a q8
    delta[q7]['t']=q8;

    // q8 a q9
    delta[q8][(char)32]=q9;

    // q9 a q9
    for(int i=48; i<=57; i++){
      delta[q9][(char)i]=q9;
    } // 0-9
    for(int i=65; i<=90; i++){
      delta[q9][(char)i]=q9;
    } // MAYUSCULAS
    for(int i=97; i<=122; i++){
      delta[q9][(char)i]=q9;
    } // minusculas
    delta[q9]['(']=q9;
    delta[q9]['=']=q9;
    delta[q9][(char)32]=q9;

    // q9 a q10
    delta[q9][',']=q10;

    // q10 a q9
    delta[q10][(char)32]=q9;

    // q9 a q11
    //delta[q9][(char)32]=q11;

    // q11 a q11
    delta[q11]['=']=q11;

    // q11 a q9
    delta[q11][(char)32]=q9;

    // q9 a q12
    delta[q9][')']=q12;
    delta[q9][';']=q12;

    // q12 a q12
    delta[q12][';']=q12;
}

void SintacticAnalyzer::print(){
for (map<unsigned,event>::iterator it=delta.begin(); it!=delta.end(); ++it){		
		for (map<char,unsigned>::iterator it_1 = it->second.begin(); it_1!=it->second.end(); ++it_1){
      cout << "[" << it->first;
			cout << ","<< it_1->first << "]: " << it_1->second << endl;
		}
	}
    cout << endl << "Final [ ";
	for (const auto& a : finalStates) {
		cout << a << " ";
	}	
	cout << " ]" << endl;
}

unsigned SintacticAnalyzer::transition(unsigned currentState, char event, map<unsigned, map<char, unsigned>> delta){	
	map<unsigned, map<char, unsigned>>::iterator it = delta.begin();
	unsigned aux = 0;
	for (it=delta.begin(); it!=delta.end(); ++it){
		if(currentState == it->first){
			for (map<char,unsigned>::iterator it_1 = it->second.begin(); it_1!=it->second.end(); ++it_1){
				if(event == it_1->first){
					aux = it_1->second;					
				}
			}
		}	
	}
	return aux;
}

map<unsigned, map<char, unsigned>> SintacticAnalyzer::Delta(){
	return delta;
}

bool SintacticAnalyzer::test(string word){
	bool flag = false;
	unsigned aux = init;
	if(word.length()>0){
		for(unsigned i=0; i < word.length(); i++){
      if(word[i]=='{'){
        key_1++;
        key = true;
      }
      if(word[i]=='}'){
        key_2++;
        key = false;
      }
      aux = transition(aux, word[i], delta);
      if(aux==0){
        return false;
      }      
		}	
        for (const auto& a : finalStates) {
            if(aux==a){
			    flag = true;
		    }		
        }			
		if(flag){
			return true;
		} {
			return false;
		}
	} else {	
		return true;
	}
}

bool SintacticAnalyzer::getStatus(){
  if((key_1==key_2)and(!key)){
    return false;
  } else {
    return true;
  }
}