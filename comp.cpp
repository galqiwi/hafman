//MALINOVKSII HUFFMAN COMPRESSOR
#include "htree.h"


int main(int argc, char* argv[])  {
	if (argc < 2) {
		return 0;
	}
	if (filesize(argv[1]) == 0) {
		ofstream f(argv[2]);
		f.close();
		return 0;
	}
	HTree t;
	t.set(argv[1]);
	Iobits out(argv[2], true);
	t.printHead(out, t.nodes[t.root]);
	vector<vector<bool>> codes(512, vector<bool>());
	codes_u(codes, t, t.root);
	Iobits in(argv[1], false);
	u_char c;
	int z = 0;
	while (in.readChar(c)) {
		vector<bool>& curr = codes[c];
		for (int i = 0; i < curr.size(); i++) {
			z++;
			out.writeBool(curr[i]);
		}
	}
	out.writeBool(true);
	out.close();
}