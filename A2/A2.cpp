#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::cin;
using std::cerr;
using std::vector;

bool binary_search(const vector<string>& sorted_vec, const string& key){
	size_t mid, left=0;
	size_t right=sorted_vec.size();
	while(left<right){
		mid=left + (right - left) / 2;
		if(key > sorted_vec.at(mid)){
			left = mid +1;
		}
	}
}

vector<string> storeContent(string x){
	vector<string> contents;
	string line;
	ifstream ifs;
	ifs.open(x.c_str());
	if(ifs.fail()){
		cerr << "Error: Are you sure you're using the correct format?" << endl;
		cout << x << " failed to open." << endl;
		vector<string> failed;
		failed.push_back ("failed");
		return failed;
	}
	else{
		while(getline(ifs, line)){
			contents.push_back (line);
		}
	}
	return contents;
}

void printVector(vector<string> vec){
	for(int i=0; i<vec.size(); i++){
		cout << vec.at(i) << " " << endl;
	}
}

int main(){
	string input, algo, file1, file2;
	vector<string> contents1, contents2;
	ifstream ifs1, ifs2;
	cout << endl << "Please enter slow or fast followed by a space, your first ";
	cout << "file followed by a space, then your second file." << endl;
	cout << "Example:" << endl;
	cout << "slow file1 file2" << endl << endl;
	while(getline(cin, input)){
		if(input == "exit"){
			break;
		}
		int spaceCounter = 0;
		bool error = false;
		for(int i=0; i<input.length(); i++){
			if(input.at(i) == ' '){
				spaceCounter++;
				i++;
			}
			if(input.at(i) == ' '){
				cerr << "Error: Please make sure you are using the correct format"
					<< endl;
				error = true;
				break;
			}
			if(spaceCounter == 1){
				file1 += input.at(i);
			}
			else if(spaceCounter == 2){
				file2 += input.at(i);	
			}
			else{
				algo += input.at(i);
			}
		}	
		if(error){
			continue;
		}
		contents1 = storeContent(file1);
		contents2 = storeContent(file2);
		if((contents1[0] == "failed") || (contents2[0] == "failed")){
			input = "";
			algo = "";
			file1 = "";
			file2 = "";
			continue;
		}
		printVector(contents2);
		printVector(contents1);

		input = "";
		algo = "";
		file1 = "";
		file2 = "";
	}
	
	return 0;
}
