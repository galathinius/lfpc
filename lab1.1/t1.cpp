#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool A (int i);
bool B (int i);
bool C (int i);
string word;

bool start(){
	char n = word[0];
	// cout << 'S' << n <<'\n';
	if (n == 'd') return A(1);
	return 0;
}

bool A (int i){
	char n = word[i];
	// cout << 'A' << n <<'\n';
	if (n == 'a') return B(++i);
	if (n == 'b') return A(++i);
	return 0;
}

bool B (int i){
	char n = word[i];
	// cout << 'B' << n <<'\n';
	if (n == 'a') return B(++i);
	if (n == 'b') return C(++i);
	if ((n == 'd') & ( !word[++i] )) return 1;
	return 0;
}

bool C (int i){
	char n = word[i];
	// cout << 'C' << n <<'\n';
	if (n == 'c') return B(++i);
	return 0;
}

int main(){

	ifstream cin ("t1.in");
    ofstream cout ("t1.out");

	cin >> word;
	cout << start();
	

	return 0;
}