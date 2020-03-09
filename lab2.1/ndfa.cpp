#include <iostream>
#include <fstream>
#include<iomanip>
#include<string>

using namespace std;

ifstream fin ("ndfa.in");
ofstream fout ("ndfa.out");

int inp[100][5], trans[100][5], lengthOut = 1, start = 0, nos;

int convState(int a){
	
	return 1<<a;
}

int readGrammar(int n){
	int s, t, f, l = 0;
	for(int i = 0; i < n; i++){
    	fin >> s >> t >> f; 
    	if(f > l) l = f;
    	inp[s][t] = convState(f) | inp[s][t]; // state(f) | inp[s][t];
    }
    return l;
}

void printInp(int n){
	for(int i = 0; i < n; i++){
		// fout << inp[i][1] << ' ' << inp[i][2] << '\n';
		// cout<<nos;
		for (int j = 1; j <= nos; j++)
		{
			fout << inp[i][j] << ' ';
		}
    	fout << '\n';
    }
    fout << '\n';
}

bool checkTransE(int s, int n){
	bool ret = 0;
	for (int i = 0; i < n; i++){
		if (trans[i][0] == s) ret = 1;
	}
	// cout << "\nret " << ret;
	return ret;
}   

void makeTransition(int stateNr){

	if(stateNr == 0) trans[0][0] = convState(start);
	if(!trans[stateNr][0]) return;

	int order = 0, num = trans[stateNr][0];

	while (num){
		if (num % 2) {
			for (int j = 1; j <= nos; j++){
				trans[stateNr][j] = trans[stateNr][j] | inp[order][j]; // trans[stateNr][1] |
			}
		}
		num >>= 1;
		order ++;
	}

	for (int j = 1; j <= nos; j++){
		int asta1 = trans[stateNr][j];
		if((asta1) && !(checkTransE(asta1, lengthOut))){
		trans[lengthOut++][0] = asta1;
		}
	}
	
	int next = stateNr;

	makeTransition(++next);
}

void printTransition(int n){
	// fout << trans[i][0] << ' ' << trans[i][1] << ' ' << trans[i][2] << '\n';
	for(int i = 0; i < n; i++){
		for (int j = 1; j <= nos; j++){
			fout << trans[i][j] << '\t';
		}
    	fout << '\n';
    }
}

void printFancy(int n){
	fout << "\n\tS\t\ta\t\tb\t\tc\n\n";
	for(int i = 0; i < n; i++){
    	// fout << trans[i][0] << '\t' << trans[i][1] << '\t' << trans[i][2] << '\n';

    	for (int j = 0; j <= nos; j++)
    	{
    		int order = 0, num = trans[i][j];
    		string toPrint = "";
			while (num){
				if (num % 2) {
					toPrint = toPrint +  "q" + char(order+48);  
					// fout << 'q' << order;
				}
				num >>= 1;
				order ++;
			}
			fout << setw(7)<< toPrint;
    	}
    	fout << '\n';
    	
	}


}

int main(){

    int n, lengthIn;
    fin >> n;

    lengthIn = readGrammar(n) +1;
    fin >> nos >> start;
    printInp(lengthIn);

    
    

    makeTransition(0);
    // makeTransition(1);
	// cout<< convState(start);

    printTransition(lengthOut);
    printFancy(lengthOut);

    return 0;

}