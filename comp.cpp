#include "htree.h"


int main() {
	HTree t;
	t.set("in");
	Iobits out("archive.hman", true);
	t.printHead(out, t.nodes[t.root]);
	vector<vector<bool>> codes(512, vector<bool>());
	codes_u(codes, t, t.root);
	Iobits in("in", false);
	u_char c;
	int z = 0;
	while (in.readChar(c)) {
		vector<bool>& curr = codes[c];
		for (int i = 0; i < curr.size(); i++) {
			z++;
			out.writeBool(curr[i]);
		}
	}
	cout << z << " - comp" << endl;
	out.close();
}