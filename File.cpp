#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include "File.h"

using namespace std;

Get_file::Get_file(string file_name) { //매개 변수가 있는 생성자 구현
	list = new Linked_list();
	string data;
	fstream fs; //입출력스트림 객체 fs 생성

	fs.open(file_name, ios::in);
	//입출력 둘다 되는 fstream으로 해서 입력위해 ios::in해줘야 함.
	//ostream fs로 했으면 ios::in할 필요가 없다.

	//while (!fs.eof())
	for(int i=0; i<501; i++){
		getline(fs, data, '\n'); //row 단위로 자르기
		if (i == 0) continue;
		//첫 row는 항목 구분 칸이라 제외
		//cout << data << endl;

		vector<string> ans = split_data(data);//row안에서 셀 단위로 자르기

		if (ans.size() > 0) {
			node* new_node = new node();
			new_node->name = ans[0];
			new_node->address = ans[1];
	
			new_node->rankingPosition = stoi(ans[2]);
			new_node->numberOfReviews = stoi(ans[5]);
			
			for (int j = 8;j < ans.size();j++) {

				if (ans[j] != "") {
					new_node->cuisines.push_back(ans[j]);
					//cout << "name = " << ans[j] << endl;
				}
			}

			list->add_list(new_node);

		}

	}
}

vector<string> Get_file::split_data(string line) {
	//cvs 파일 셀마다의 구분은 기본적으로 ,로 내장.

	vector<string> split_list;
	istringstream tokenStream(line);
	//istringsteam 객체인 tokenStream을 만들고 line을 넣어라

	int cnt = 0;

	while (true) {
		string temp;
		getline(tokenStream, temp, ',');//,니까 cell기준으로 자르라
		if (cnt < 15) split_list.push_back(temp);
		//, 기준으로 name을 temp에 저장해놓고, 그 다음 push_back, 다음으로 넘어가기
		else break; //16번째 칸 넘어가면 끝내기
		cnt++;//빈칸인 애들도 빈칸으로 넣어줘야하니까 한 row마다 15칸씩 있음.
	}
	//vector<string> split_list = split(line, ',');
	return split_list;
}

Linked_list* Get_file::get_list() {
	return list; //리스트 리턴
}