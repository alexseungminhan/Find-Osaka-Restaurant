#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include<iostream>
#include<string>
#include <vector>
#include <queue>

using namespace std;

typedef struct node { 
	string name;
	string address;
	int rankingPosition;
	int numberOfReviews;
	vector<string> cuisines;

	node* next; 

} node;

class Linked_list{
	node* head; 
	node* tail; 

public:
	Linked_list();
	void add_list(node* new_node); 
	void print_list(); 

	Linked_list* find_list(string name, int sort,int filter); 
	Linked_list* find_category(string category, int sort, int filter); 
	Linked_list* find_category(string category, int sort);

	Linked_list* sort_by(Linked_list* list,int sort); 

};

#endif __LINKED_LIST_H__
