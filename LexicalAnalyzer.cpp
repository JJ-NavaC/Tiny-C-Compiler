#include "LexicalAnalyzer.h"
#include <iostream>

LexicalAnalyzer::LexicalAnalyzer(){	
	q0 = 0;
	q1 = 1;	
	init = q0;
	finalState = q1;	

  delta[q0]['(']=q1;
  delta[q0][')']=q1;
  delta[q0]['{']=q1;
  delta[q0]['}']=q1;
  delta[q0][';']=q1;
  delta[q0]['=']=q1;
  delta[q0]['+']=q1;
  delta[q0]['-']=q1;
  delta[q0]['*']=q1;
  delta[q0]['/']=q1;
  delta[q0][(char)32]=q1;

  for(int i=48; i<=57; i++){
    delta[q0][(char)i]=q1;
  }
  for(int i=65; i<=90; i++){
    delta[q0][(char)i]=q1;
  }
  for(int i=97; i<=122; i++){
    delta[q0][(char)i]=q1;
  }

  delta[q1]['(']=q1;
  delta[q1][')']=q1;
  delta[q1]['{']=q1;
  delta[q1]['}']=q1;
  delta[q1][';']=q1;
  delta[q1]['=']=q1;
  delta[q1]['+']=q1;
  delta[q1]['-']=q1;
  delta[q1]['*']=q1;
  delta[q1]['/']=q1;
  delta[q1][(char)32]=q1;

  for(int i=48; i<=57; i++){
    delta[q1][(char)i]=q1;
  }
  for(int i=65; i<=90; i++){
    delta[q1][(char)i]=q1;
  }
  for(int i=97; i<=122; i++){
    delta[q1][(char)i]=q1;
  }

}

void LexicalAnalyzer::print(){
for (map<unsigned,event>::iterator it=delta.begin(); it!=delta.end(); ++it){		
		for (map<char,unsigned>::iterator it_1 = it->second.begin(); it_1!=it->second.end(); ++it_1){
      cout << "[" << it->first;
			cout << ","<< it_1->first << "]: " << it_1->second << endl;
		}
	}
	
	cout << endl << "Final [ "<< finalState << " ]" << endl;
}

unsigned LexicalAnalyzer::transition(unsigned currentState, char event, map<unsigned, map<char, unsigned>> delta){	
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

map<unsigned, map<char, unsigned>> LexicalAnalyzer::Delta(){
	return delta;
}

bool LexicalAnalyzer::test(string word){
	bool flag = false;
	unsigned aux = init;
	if(word.length()>0){
		for(unsigned i=0; i < word.length(); i++){
			aux = transition(aux, word[i], delta);
		}		
		if(aux==finalState){
			flag = true;
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
