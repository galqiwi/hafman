#include "htree.h"
#include <algorithm>

int main() {
	Iobits in("archive.hman", false);

	HTree t;
	t.set_(in);
	
	Node* curr = t.nodes[256];
	bool b;
	Iobits out("out");
	u_char c;
	int i = 0;
	while (in.readBool(b)) {
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