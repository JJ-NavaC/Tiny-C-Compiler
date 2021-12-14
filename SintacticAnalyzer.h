#ifndef SintacticAnalyzer_h
#define SintacticAnalyzer_h

#include <stddef.h>
#include <string>
#include <set>
#include <map>

using namespace std;

class SintacticAnalyzer {
    unsigned q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14;
    set<unsigned> finalStates;
    unsigned init;
	
	typedef map<char, unsigned> event;
	typedef map<unsigned, event> state;	
	
	state delta;

	int key_1=0;
	int key_2=0;
	bool key = false;
	

public:
	SintacticAnalyzer();
	
	bool test(string);
	
	void print();
	
	unsigned transition(unsigned, char, map<unsigned, map<char, unsigned>>);
	
	map<unsigned, map<char, unsigned>> Delta();

	bool getStatus();

};

#endif
