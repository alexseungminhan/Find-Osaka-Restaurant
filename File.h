#ifndef __FILE_H__
#define __FILE_H__
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include "Linked_list.h"
using namespace std;

class Get_file {
	Linked_list* list; 
public:
	Get_file(string file_name); 
	//get csv file
	//:param string file_name: file name
	vector<string> split_data(string line); 
	//splits data from the file per cell
	//:param string line: one individual row from csv file data

	Linked_list* get_list(); 
};

#endif __FILE_H__
