#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Linked_list.h"
using namespace std;

Linked_list::Linked_list() :head(nullptr), tail(nullptr){}

void Linked_list::add_list(node* new_node) {
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		tail->next = new_node;
		tail = new_node;
	}

}

void Linked_list::print_list() {
	cout << "\033[31m--------Search Result--------\033[0m" << endl;

	node* cur = head;

	int cnt = 1;

	if (head == nullptr) cout << "empty list" << endl;
	else {
		while (cur != nullptr) {
			cout << "\033[37m"<<cnt<<"\033[O" << "-----------------" << endl;
			cout << "\033[35mName:\033[O" << cur->name << endl;
			cout << "\033[33mAddress:\033[O"<< cur->address << endl;
			cout << "\033[32mRanking:\033[O" << cur->rankingPosition << endl;
			cnt++;
			cur = cur->next;
		}
		cout<< "\033[37m \033[O" << endl;
		
	}
}

Linked_list* Linked_list::find_list(string name, int sort1,int sort2, int filter) {
	node* cur = head;

	Linked_list* new_linked_list = new Linked_list; 

	string filter_name[3] = {"vegen option", "vegeterian friendly", "gluten free"};

	if (filter > 0) new_linked_list = find_category(filter_name[filter - 1], sort1,sort2);

	string lower_name = ""; //lower-casing param name
	for (int i = 0; i < name.size();i++) {
		if (name[i] >= 65 && name[i] <= 90) lower_name += (name[i] + 32);
		else lower_name += name[i];
	}

	if (head == nullptr) {
		cout << "\033[31mNo Result\033[0m" << endl;
		return nullptr;
	}
	
	while (cur != nullptr) {
		string lower_cur = ""; //lower-casing restaurants' names
		for (int i = 0; i < cur->name.size();i++) {
			if (cur->name[i] >= 65 && cur->name[i] <= 90) lower_cur += (cur->name[i] + 32);
			else lower_cur += cur->name[i];
		}
		if (lower_cur.find(lower_name) != string::npos) {
			node* new_node = new node;
			new_node->name=cur->name;
			new_node->address = cur->address;
			new_node->rankingPosition = cur->rankingPosition;
			new_node->next = nullptr;

			new_linked_list->add_list(new_node);//add matching node to new_linked_list
		}
		cur = cur->next; 
	}
	
	sort_by(new_linked_list,sort1, sort2); 
	return new_linked_list; 
}

Linked_list* Linked_list::find_category(string category, int sort1, int sort2) {
	node* cur = head;

	Linked_list* new_linked_list = new Linked_list;

	string lower_name = "";

	for (int i = 0; i < category.size();i++) { //lower-casing param category
		if (category[i] >= 65 && category[i] <= 90) lower_name += (category[i] + 32);
		else lower_name += category[i];
	}

	if (head == nullptr) {
		cout << "\033[31mNo Result\033[0m" << endl;
		return nullptr;
	}

	while (cur != nullptr) {
		for (int i = 0; i < cur->cuisines.size();i++) {//lower-casing restaurants' categories
			string lower_cur = "";
			for (int j = 0; j < cur->cuisines[i].size();j++) {
				if (cur->cuisines[i][j] >= 65 && cur->cuisines[i][j] <= 90) lower_cur += (cur->cuisines[i][j] + 32);
				else lower_cur += cur->cuisines[i][j];
			}
			if (lower_cur.find(lower_name) != string::npos) {
				node* new_node = new node;
				new_node->name = cur->name;
				new_node->address = cur->address;
				new_node->rankingPosition = cur->rankingPosition;
				new_node->next = nullptr;

				new_linked_list->add_list(new_node);//add matching node to new_linked_list
				break;
			}

		}
		cur = cur->next;
	}
	new_linked_list = sort_by(new_linked_list,sort1, sort2);
	return new_linked_list;
}

Linked_list* Linked_list::find_category(string category, int sort1,int sort2,int filter) {
	//function overloading
	Linked_list* new_linked_list = find_category(category,sort1,sort2);
	if (filter == 0) return new_linked_list;
	//return if filter was not selected
	string filter_name[3] = { "vegan option", "vegeterian friendly", "gluten free" };
	new_linked_list->find_category(filter_name[filter-1], sort1, sort2);
	/*
	"vegan option", "vegeterian friendly", "gluten free" filters are all included in vector<string> cuisine
 	search through find_category once more using filter keywords
	*/
	return new_linked_list;
}

Linked_list* Linked_list::resverse_list(Linked_list* list) {

	Linked_list *new_linked_list1 = new Linked_list();
	
	node* cur = list -> head;
	
	while (cur != nullptr) {
		node* temp = new node;
		temp->name = cur->name;
		temp->address = cur->address;
		temp->cuisines = cur->cuisines;
		temp->rankingPosition = cur->rankingPosition;
		temp->numberOfReviews = cur->numberOfReviews;


		temp->next = new_linked_list1->head;
		new_linked_list1->head = temp;
		cur = cur->next;
	}

	return new_linked_list1;
}

Linked_list* Linked_list::sort_by(Linked_list* list,int sort1, int sort2) {
	
	node* prev = nullptr;
	node* cur = head;
	
	for (node* cur = list->head; cur != nullptr; ) {
		bool che = true;
		node* prev2 = nullptr;
		int order[3] = { 0, cur->rankingPosition,cur->numberOfReviews };
		for (node* cur2 = list->head;cur2 != cur;cur2 = cur2->next) {
			int order2[3] = { 0, cur2->rankingPosition,cur2->numberOfReviews };
			
			if (order2[sort2] > order[sort2]) {
				
				if(prev!=nullptr)prev->next = cur->next;
				if(prev2!=nullptr)prev2->next = cur;
				if(cur!= nullptr)cur->next = cur2;
				
				che = false;
				if (cur2 == head) head = cur;
				if (cur == tail) tail = prev;
				break;
				
			}
			
			prev2 = cur2;
		}
	
		if(che)prev = cur;
		if(che == false)cur = prev->next;
		else  cur = cur->next;
		
	}
	if (sort1 == 1) return list; //ascending order
	else return resverse_list(list); //descending order

}






