#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include "File.h"

using namespace std;

Get_file::Get_file(string file_name) {
	list = new Linked_list();
	string data;
	fstream fs; 

	fs.open(file_name, ios::in);
	
	for(int i=0; i<501; i++){
		getline(fs, data, '\n'); 
		if (i == 0) continue;

		vector<string> ans = split_data(data);

		if (ans.size() > 0) {
			node* new_node = new node();
			new_node->name = ans[0];
			new_node->address = ans[1];
	
			new_node->rankingPosition = stoi(ans[2]);
			new_node->numberOfReviews = stoi(ans[5]);
			
			for (int j = 8;j < ans.size();j++) {

				if (ans[j] != "") {
					new_node->cuisines.push_back(ans[j]);
					//cuisines include the restaurants' categories
				}
			}

			list->add_list(new_node);

		}

	}
}

vector<string> Get_file::split_data(string line) {

	vector<string> split_list;
	istringstream tokenStream(line);

	int cnt = 0;

	while (true) {
		string temp;
		getline(tokenStream, temp, ',');
		if (cnt < 15) split_list.push_back(temp);
		else break; 
		cnt++;
	}
	return split_list;
}

Linked_list* Get_file::get_list() {
	return list; 
}
