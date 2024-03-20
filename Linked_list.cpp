#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Linked_list.h"
using namespace std;

Linked_list::Linked_list() :head(nullptr), tail(nullptr){}
//head, tail 초기화

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

Linked_list* Linked_list::find_list(string name, int sort, int filter) {
	node* cur = head;

	Linked_list* new_linked_list = new Linked_list; 
	//검색 후 저장해놓을 링크드 리스트 'new_linked_list'

	string filter_name[3] = {"vegen option", "vegeterian friendly", "gluten free"};

	if (filter > 0) new_linked_list = find_category(filter_name[filter - 1], sort);
	//no filter가 아닌 다른 수를 입력했을 시 필터 카테고리 탐색

	string lower_name = ""; //입력 받은 문자의 소문자화 작업
	for (int i = 0; i < name.size();i++) {
		if (name[i] >= 65 && name[i] <= 90) lower_name += (name[i] + 32);
		else lower_name += name[i];
	}

	if (head == nullptr) {
		cout << "\033[31mNo Result\033[0m" << endl;
		return nullptr;
	}
	
	while (cur != nullptr) {
		string lower_cur = ""; //식당 이름의 소문자화 작업
		for (int i = 0; i < cur->name.size();i++) {
			if (cur->name[i] >= 65 && cur->name[i] <= 90) lower_cur += (cur->name[i] + 32);
			else lower_cur += cur->name[i];
		}
		if (lower_cur.find(lower_name) != string::npos) {
			//일치하는 이름을 찾았으면 새로운 노드에 저장해주기
			node* new_node = new node;
			new_node->name=cur->name;
			new_node->address = cur->address;
			new_node->rankingPosition = cur->rankingPosition;
			new_node->next = nullptr;//새로운 노드의 next를 nullptr로 해줘서 공간 빼주기

			new_linked_list->add_list(new_node);//리턴할 링크드 리스트에 만들어준 노드 추가
		}
		cur = cur->next; //다음 노드로 넘어가기
	}
	
	sort_by(new_linked_list, sort); // 필터/이름 검색 완료 했으면 정렬하기
	return new_linked_list; //리턴하기
}

Linked_list* Linked_list::find_category(string category, int sort) {
	node* cur = head;

	Linked_list* new_linked_list = new Linked_list;

	string lower_name = "";

	for (int i = 0; i < category.size();i++) { //입력받은 카테고리의 소문자화 작업
		if (category[i] >= 65 && category[i] <= 90) lower_name += (category[i] + 32);
		else lower_name += category[i];
	}

	if (head == nullptr) {
		cout << "\033[31mNo Result\033[0m" << endl;
		return nullptr;
	}

	while (cur != nullptr) {
		for (int i = 0; i < cur->cuisines.size();i++) {//식당 카테고리의 소문자화 작업
			string lower_cur = "";
			for (int j = 0; j < cur->cuisines[i].size();j++) {
				if (cur->cuisines[i][j] >= 65 && cur->cuisines[i][j] <= 90) lower_cur += (cur->cuisines[i][j] + 32);
				else lower_cur += cur->cuisines[i][j];
			}
			if (lower_cur.find(lower_name) != string::npos) {
				//일치하는 카테고리명이 있으면 새로운 노드 만들고 넣어주기
				node* new_node = new node;
				new_node->name = cur->name;
				new_node->address = cur->address;
				new_node->rankingPosition = cur->rankingPosition;
				new_node->next = nullptr;

				new_linked_list->add_list(new_node);
				break;
			}

		}
		cur = cur->next;
	}
	new_linked_list = sort_by(new_linked_list, sort);
	return new_linked_list;
}

Linked_list* Linked_list::find_category(string category, int sort,int filter) {
	//함수 오버로딩 이용, 처음에는 매개변수 3개를 모두 입력받는다.
	Linked_list* new_linked_list = find_category(category,sort);
	//find_category 함수 이용해 1차 탐색
	if (filter == 0) return new_linked_list;
	//필터 적용안했으면 그대로 리턴
	string filter_name[3] = { "vegan option", "vegeterian friendly", "gluten free" };
	new_linked_list->find_category(filter_name[filter-1], sort);
	//어차피 비건 유뮤, 글루텐 프리 유무, 식당 카테고리 모두
	//식당 노드의 vector<string> cuisine에 저장되어있으니 동일하게 string 탐색

	return new_linked_list;
}

Linked_list* Linked_list::sort_by(Linked_list* list, int sort) {
	
	node* prev = nullptr;
	node* cur = head;
	
	for (node* cur = list->head; cur != nullptr; ) {
		bool che = true;
		node* prev2 = nullptr;
		int order[3] = { 0, cur->rankingPosition,cur->numberOfReviews };
		for (node* cur2 = list->head;cur2 != cur;cur2 = cur2->next) {
			int order2[3] = { 0, cur2->rankingPosition,cur2->numberOfReviews };
			
			if (order2[sort] > order[sort]) {
				
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
	return list;

}




