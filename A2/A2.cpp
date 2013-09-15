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

/*
 * The purpose of this method is to take in a reference to a sorted vector of strings
 * and a reference to a string to compare and see if the string exists in the vector.
 * 
 * Arguments: const vector<string>& , const string&
 * Return: bool
 */
bool binary_search(const vector<string>& sorted_vec, const string& key){
	size_t mid, left=0;
	size_t right=sorted_vec.size();
	while(left<right){
		mid=left + (right - left) / 2;
		if(key > sorted_vec.at(mid)){
			left = mid +1;
		}
	}
	return false;
}

bool canOpenFile(const string& x){
	ifstream ifs;
	ifs.open(x.c_str());
	bool open = !ifs.fail();
	ifs.close();
	return open;
}

vector<string> storeContent(const string& x){
	vector<string> contents;
	string line;
	ifstream ifs;
	ifs.open(x.c_str());
	while(getline(ifs, line)){
		contents.push_back (line);
	}
	ifs.close()
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
		bool openFile1 = canOpenFile(file1);
		bool openFile2 = canOpenFile(file2);
		if((!openFile1) || (!openFile2)){
			cerr << "Error: was unable to open file!" << endl;
			if(!openFile1){
				cerr << "File : " << file1 << " failed to open" << endl;
			}
			if(!openFile2){
				cerr << "File : " << file2 << " failed to open" << endl;
			}
			input = "";
			algo = "";
			file1 = "";
			file2 = "";
			continue;
		}
		contents1 = storeContent(file1);
		contents2 = storeContent(file2);
		
		printVector(contents2);
		printVector(contents1);

		input = "";
		algo = "";
		file1 = "";
		file2 = "";
	}
	
	return 0;
}
