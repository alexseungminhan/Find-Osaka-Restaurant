#ifndef __FILE_H__
#define __FILE_H__
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include "Linked_list.h"
using namespace std;

class Get_file {
	Linked_list* list; //객체 생성
public:
	Get_file(string file_name); //매개 변수가 있는 생성자
	vector<string> split_data(string line); //멤버 함수

	Linked_list* get_list(); //리스트 주기
};

#endif __FILE_H__
