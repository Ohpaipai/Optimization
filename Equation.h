#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
class Linklist;

class ListVariables{
public:
	ListVariables() :name(""), exponential(0),Vnext(NULL){};
	ListVariables(std::string _name,double _exp) :name(_name), exponential(_exp), Vnext(NULL) {};
	
	
private:
	std::string name;
	double exponential;
	ListVariables *Vnext;
	friend class Linklist;
};

class ListNode {

public:

	ListNode() :coefficient(0), MathName(""),variables(),Lnext(NULL){};
	ListNode(double _coe) : coefficient(_coe), MathName(""),variables(), Lnext(NULL){};
	ListNode(std::string _mathname) : coefficient(1), MathName(_mathname), variables(), Lnext(NULL) {};
	ListNode(double _coe, std::string _mathname) : coefficient(_coe), MathName(_mathname), variables(), Lnext(NULL) {};
private: 
	double coefficient;
	std::string MathName;
	ListVariables variables;
	ListNode *Lnext;
	friend class Linklist;
};


class Linklist {
private:
	int size;                
	ListNode *Lfirst;   
	ListVariables *Vfirst;
public:
	Linklist() :size(0),Lfirst(NULL),Vfirst(NULL){};
	void PrintList();           
	void Push_front(std::string _name, double _exp);
	void Push_front(double _coe);
	void Push_back(int x);      
	void Delete(int x);        
	void Clear();               
	void Reverse();            
};