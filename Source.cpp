#include <iostream>
#include <queue>
#include "File.h"
#include "Linked_list.h"
using namespace std;

int main() {
	Get_file* file = new Get_file("osaka_tripadvisor.csv");
	Linked_list* osaka_list = file->get_list(); //file의 리스트를 가져와서 osaka_list에 넣기

	Linked_list* result = new Linked_list; //검색결과를 저장할 링크드 리스트 result

	cout << "\033[31m--------Tripadvisor's Top 500 Osaka Restaurant--------\033[0m" << endl;

	

	int sort2 ;
	cout << "sort by 0.no sort 1. ranking 2.number of reviews" << endl;
	cout << "\033[36msort by:\033[0m";
	cin >> sort2;

	int sort1=0;
	if (sort2 != 0) {
		cout << "sort by  1. ascending order 2.descending order" << endl;
		cout << "\033[36msort by:\033[0m";
		
		cin >> sort1;
	}

	cout << "filter: 0. no filter 1.vegan option 2.vegeterian friendly 3. gluten free" << endl;
	cout << "\033[36mfilter:\033[0m";

	int filter;
	cin >> filter;

	cout << "Search: 0.search all 1. find by name 2. find by category" << endl;
	cout << "\033[36mfind by:\033[0m";

	int select;
	cin >> select;

	if (select == 0) {
		result = osaka_list->sort_by(osaka_list, sort1, sort2);
		result->print_list();
	}

	if (select == 1) {
		cout << "\033[36mname:\033[0m";
		string name;
		cin >> name;
		result = osaka_list->find_list(name,sort1,sort2,filter);
		result->print_list();
	}
	if (select == 2) {
		cout << "\033[36mcategory:\033[0m";
		string category;
		cin >> category;
		result = osaka_list->find_category(category,sort1,sort2,filter);
		result->print_list();
	}

}