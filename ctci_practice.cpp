#include <iostream>
#include <vector>
#include <array>
#include <unordered_set>
#include <math.h>
#include <cmath>
#include <tuple>
#include <fstream>
#include <algorithm>

using namespace std;

vector<int> build_table(string s);

//global variables
array<int,8> a1 = {1,2,3,4,5,7,8,34};

//binary search 
void binary_search(int low, int high, int target) {

	if(high - low == 1) {
		if(a1[high] == target || a1[low] == target) {
			cout << "found!" << endl;
			return;
		}
		else  {
			cout << "not found" << endl;
			return;
		}
	} 

	if(high - low == 0) {
		cout << "not found" << endl;
		return;
	}
	int med = (low+high/2);
	
	if(a1[med] >= target)
		binary_search(low,med,target);
	else 
		binary_search(med+1,high,target);
}

//see if any two integers in input vector's difference is k
int count_diff(vector<int> input, int k) {
	unordered_set<int> s;
	int sum = 0;
	for(int i=0; i<input.size(); i++) 
		s.insert(input[i]);

	for(int i=0; i<input.size(); i++) {
		unordered_set<int>::iterator it = s.find(input[i] + k);
		if(it != s.end()) 
			sum++;
	}
	return sum;
}

//find all solutions to a^3 + b^3 = c^3 + d^3 for a,b,c,d between 1,1000 
//my implementation assums a,b,c,d have to be unique
void cube_sums() {

	ofstream ofile;
	ofile.open("cube_sums.txt");
	vector<tuple<int,int,int> > cubes;
	for(int i=1; i<1000; i++) {
		for(int j=i+1; j<1000; j++) {
			cubes.push_back(make_tuple(pow(i,3) + pow(j,3),i,j));
		}
	}

	int sum = 0;
	for(int i=0; i<cubes.size(); i++) {
		for(int j=i+1; j<cubes.size(); j++) {
			int x = get<0>(cubes[i]);
			int y = get<0>(cubes[j]);
			if(get<0>(cubes[i]) == get<0>(cubes[j])) {
				sum++;
				ofile << get<1>(cubes[i]) << "," << get<2>(cubes[i]) << ","  << get<1>(cubes[j]) << ","  << get<2>(cubes[j]) << endl;
			}
		}
	}
	ofile.close();
	cout << "sum: " << sum << endl;

} 

//see if a string contains only unique chars
void is_unique1(string s) {
	int arr[26] = {0};

	for(char c : s) {
		c = tolower(c);
		arr[c-'a']++;
		if(arr[c-'a'] > 1) {
			cout << "not unique" << endl;
			return;
		}
	}
	cout << "unique" << endl;
}

//see if a string contains only unique chars without using DS's
void is_unique2(string s) {
	for(int i=0; i<s.length(); i++) {
		for(int j=i+1; j<s.length(); j++) {
			if(tolower(s[i]) == tolower(s[j])) {
				cout << "not unique" << endl;
				return;
			}
		}
	}
	cout << "unique" << endl;
}

//decide whether two strings are permutations of eachother
bool check_permutation(string s1, string s2) {
	if(s1.length() != s2.length()) {
		//cout << "not a perm" << endl;
		return false;
	}

	int arr1[26] = {0};
	int arr2[26] = {0};

	for(int i=0; i<s1.size(); i++) { 
		arr1[tolower(s1[i])-'a']++;
		arr2[tolower(s2[i])-'a']++;
	}

	for(int i=0; i<26; i++) {
		if(arr1[i] != arr2[i]) {
			//cout << "not perm" << endl;
			return false;
		}
	}

	//cout << "is perm" << endl;
	return true;
}

//convert string into valid url (replace all spaces with %20)
//my implementation attempts to do this in place (no other strings or DS's)
string URLify(char * s, int len) {
	len += 3;
	for(int i=0; i<len; i++) {
		if(s[i] == ' ') {
			for(int k=len-1; k>=i+3; k--) {
				s[k] = s[k-2];
			}
			s[i] = '%';
			s[i+1] = '2';
			s[i+2] = '0';
		}
	}
	return s;
}

//check whether a permutation of string s 
//is a palindrome.
void palindrome_permutation(string s) {
	const int alphabet_len = 26;
	vector<int> letters(alphabet_len,0);

	for(char c : s) {
		if(tolower(c)-'a' >= 0)
			letters[tolower(c)-'a']++;  
	}

	int odds = 0;

	for(int i=0; i<alphabet_len; i++) {
		if(letters[i]%2 != 0)
			odds++;
		if(odds > 1) {
			cout << "s is not a palindrome permutation" << endl;
			return;
		}
	}
	cout << "s is a palindrome permutation" << endl;
}


//check if we can get to s2 by removing a char
//adding a char, or replacing a char


void one_away(string s1, string s2) {

	int alphabet_len = 26;


	int s1_len = s1.length();
	int s2_len = s2.length();
	if(abs(s1_len - s2_len) > 1) {
		cout << "more than one away" << endl;
		return;
	}

	if(check_permutation(s1,s2)) {
		cout << "zero away" << endl;
		return;
	}

	vector<int> table = build_table(s1);
	for(char c : s2) {
		int index = tolower(c) - 'a';
		if(table[index] == 0)
			table[index]++;
		else
			table[index]--;
	}
	//debugging output
	cout << "|";
	for(int i=0; i<alphabet_len; i++) {
		cout << table[i] << "|";
	}

	int table_sum = 0;

	for(int i=0; i<alphabet_len; i++)
		table_sum += table[i]; 

	if(table_sum <= 2) 
		cout << "one away" << endl;
	else
		cout << "more than one away" << endl;
}

//helper function for one_away
vector<int> build_table(string s) {
	int alphabet_len = 26;
	vector<int> table(alphabet_len,0);

	for(char c : s) 
		table[c-'a']++;

	return table;
}

int main() {
	vector<int> v1;
	vector<int> v2;
	v1.push_back(1);
	v1.push_back(7);
	v1.push_back(5);
	v1.push_back(9);
	v1.push_back(2);
	v1.push_back(12);
	v1.push_back(3);

	/*cout << count_diff(v1,2) << endl;
	
	int target = 4;
	cout << "searching for " << target << ".. ";
	binary_search(0,7,target);
	
	cube_sums();

	is_unique1("Abcdefghijklmnopqrstuvwxyz");
	is_unique2("AbcdefghijklmnopqrstuvwxyzA");

	cout << check_permutation("abcd","aacd");
	char str[] = "hell ooo ooo o     ";

	cout << URLify(str,14);

	palindrome_permutation("Tact Coa");*/

	one_away("pale","bake");

}