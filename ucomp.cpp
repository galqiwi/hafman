#include "htree.h"
#include <algorithm>



int main(int argc, char* argv[])  {
	if (argc < 2) {
		return 0;
	}

	Iobits in(argv[1], false);
	int size = filesize(argv[1]);
	HTree t;
	t.set_(in);
	
	Node* curr = t.nodes[256];
	bool b;
	Iobits out(argv[2]);
	u_char c;
	int i = 0;
	while (in.readBool(b, size)) {
		//cout << b << endl;
		i++;
		if (b) {
			curr = curr->l;
		} else {
			curr = curr->r;
		}
		if(curr->r == 0) {
			out.writeChar(curr->id);
			curr = t.nodes[256];
		}
	}
	cout << i << " - ucomp" << endl;
}