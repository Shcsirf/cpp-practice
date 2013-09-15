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
		if(sorted_vec.at(mid).compare(key) < 0){
			left = mid +1;
		}
		if(sorted_vec.at(mid).compare(key) > 0){
			right = mid;
		}
		if(sorted_vec.at(mid).compare(key) == 0){
			return true;
		}
	}
	return false;
}

/*
 * This method checks to see if file can be openned.
 *
 * Arguments: String fileName
 * Return: bool
 */
bool canOpenFile(const string& x){
	ifstream ifs;
	ifs.open(x.c_str());
	bool open = !ifs.fail();
	ifs.close();
	return open;
}

/*
 * This method stores content from a file into a vector.
 *
 * Arguments: const string$ fileName
 * Return: vector<string>
 */
vector<string> storeContent(const string& x){
	vector<string> contents;
	string line;
	ifstream ifs;
	ifs.open(x.c_str());
	while(getline(ifs, line)){
		contents.push_back (line);
	}
	ifs.close();
	return contents;
}

/*
 * This method prints out the contents of a variable.
 *
 * Argument: vector<string> vec
 */
void printVector(vector<string> vec){
	for(int i=0; i<vec.size(); i++){
		cout << vec.at(i) << " " << endl;
	}
}

/*
 * This method clears out the strings used in the main method.
 *
 * Argument: string input, string algo, string file1, string file2
 */
void clearStrings(string& input, string& algo, string& file1, string& file2){
	input = "";
	algo = "";
	file1 = "";
	file2 = "";
}

/*
 * The purpose of this program is to allow the user to choose between
 * a slow and fast search method and compare contents of two different
 * files. The result is a printed report of the comparison.
 */
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
			clearStrings(input, algo, file1, file2);
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
			clearStrings(input, algo, file1, file2);	
			continue;
		}
		contents1 = storeContent(file1);
		contents2 = storeContent(file2);
		
		if(algo == "slow"){
			for(int i=0; i < contents1.size(); i++){
				bool yes;
				for(int j=0; j < contents2.size(); j++){
					if(contents1.at(i).compare(contents2.at(j)) == 0){
						yes = true;
						break;
					}
					else{
						yes = false;
					}
				}
				if(yes){
					cout << "YES: " << contents1.at(i) << endl;
				}
				else{
					cout << " NO: " << contents1.at(i) << endl;
				}
			}
		}
		else if(algo == "fast"){
			sort(contents2.begin(), contents2.end());
			for(int i = 0; i < contents1.size(); i++){
				bool yes = binary_search(contents2, contents1.at(i));
				if(yes){
					cout << "YES: " << contents1.at(i) << endl;
				}
				else{
					cout << " NO: " << contents1.at(i) << endl;
				}
			}
		}
		else{
			cerr << "Please make sure you enter slow or fast and follow the " << endl
				<< "correct format:" << endl << "slow file1 file2"<< endl;
			clearStrings(input, algo, file1, file2);
			continue;
		}
		clearStrings(input, algo, file1, file2);
	}
	return 0;
}
