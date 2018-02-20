#include<fstream>
#include<iostream>
#include<bitset>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) 
		return 0;
	fstream in(argv[1]);
	char c;
	while (in.get(c)) {
		cout << (bitset<8>) c << endl;
	}
}