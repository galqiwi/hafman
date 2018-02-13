#include "htree.h"
#include <algorithm>

int main() {
	Iobits in("archive.hman", false);
	//bool b;
	u_char c;
	/*
	while (in.readBool(b)) {
		if (b) {
			in.readChar(c);
			cout << b << " " << c << endl;
		} else {
			cout << b << endl;
		}
	}
	*/
	HTree t;
	t.set_(in);
	//t.print();
	Node* curr = t.nodes[256];
	bool b;
	Iobits out("out");
	int i = 0;
	while (in.readBool(b)) {
		i++;
		//cout << 1 << endl;
		if (b) {
			curr = curr->l;
		} else {
			curr = curr->r;
		}
		//cout << 2 << endl;
		if(curr->r == 0) {
			out.writeChar(curr->id);
			curr = t.nodes[256];
		}
		//cout << 3 << endl;
	}
	cout << i << " - ucomp" << endl;
}