#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include<iostream>
#include<string>
#include <vector>
#include <queue>

using namespace std;

typedef struct node { //restaurant node
	string name;
	string address;
	int rankingPosition;
	int numberOfReviews;
	vector<string> cuisines;
	//cuisines include each restaurants' categories

	node* next; 

} node;

class Linked_list{
	node* head; 
	node* tail; 

public:
	Linked_list();
	void add_list(node* new_node); //add node to linked list
	void print_list(); //print entire linked list

	Linked_list* find_list(string name, int sort1,int sort2,int filter); //find list by name
	//:param filter: search list by name or category
	Linked_list* find_category(string category, int sort1, int sort2, int filter); //find list by category
	Linked_list* find_category(string category, int sort1, int sort2); //fucntion overloading

	Linked_list* sort_by(Linked_list* list,int sort1, int sort2); 
	//sort list 
	//:param sort1: search by descending or ascending order
	//:param sort2: search by ranking or number of reviews

	Linked_list* resverse_list(Linked_list* list); //reverse linked list in order

};

#endif __LINKED_LIST_H__
