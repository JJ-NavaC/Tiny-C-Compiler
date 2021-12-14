#ifndef LexicalAnalyzer_h
#define LexicalAnalyzer_h

#include <stddef.h>
#include <string>
#include <set>
#include <map>

using namespace std;

class LexicalAnalyzer {
	unsigned q0, q1;
	unsigned finalState;
	unsigned init;
	
	typedef map<char, unsigned> event;
	typedef map<unsigned, event> state;	
	
	state delta;
	

public:
	LexicalAnalyzer();
	
	bool test(string);
	
	void print();
	
	unsigned transition(unsigned, char, map<unsigned, map<char, unsigned>>);
	
	map<unsigned, map<char, unsigned>> Delta();

};

#endif
