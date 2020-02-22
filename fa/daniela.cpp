#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool A (int i);
bool B (int i);
bool C (int i);
string word;

bool start(int i){
	char n = word[i];
	cout << 'S' << n <<'\n';
	i++;
	if (n == 'a') return A(i) || B(i);
	return 0;
}

bool A (int i){
	char n = word[i];
	cout << 'A' << n <<'\n';
	if (n == 'b') return start(++i);
	return 0;
}

bool B (int i){
	char n = word[i];
	cout << 'B' << n <<'\n';
	if (n == 'a') return C(++i);
	return 0;
}

bool C (int i){
	char n = word[i];
	cout << 'C' << n <<'\n';
	if (n == 'a') return 1;
	if (n == 'b') return start(++i);
	return 0;
}

int main(){

	ifstream cin ("t1.in");
    ofstream cout ("t1.out");

	cin >> word;
	cout << start(0);
	

	return 0;
}