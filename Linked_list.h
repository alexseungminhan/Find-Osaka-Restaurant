#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include<iostream>
#include<string>
#include <vector>
#include <queue>

using namespace std;

typedef struct node { //식당 노드 생성
	string name;
	string address;
	int rankingPosition;
	int numberOfReviews;
	vector<string> cuisines;

	node* next; //링크드 리스트 형식

} node;

class Linked_list{
	node* head; //헤드
	node* tail; //테일

public:
	Linked_list();
	void add_list(node* new_node); //링크드 리스트 연결하기
	void print_list(); //만들어진 링크드 리스트 출력

	Linked_list* find_list(string name, int sort,int filter); //이름으로 찾기
	Linked_list* find_category(string category, int sort, int filter); //카테고리로 찾기
	Linked_list* find_category(string category, int sort);

	Linked_list* sort_by(Linked_list* list,int sort); //정렬하기

};

#endif __LINKED_LIST_H__
