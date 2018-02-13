#include "htree.h"


int main() {
	//Iobits r("in.txt", false);
	//u_char c = 'a';
	//r.readChar(c);
	//cout << c << endl;
	HTree t;
	t.set("in.txt");
	Iobits out("archive.hman", true);
	t.printHead(out, t.nodes[t.root]);
	t.print();
	//out.writeBool(true);
	//cout << 238 << endl;
	vector<vector<bool>> codes(512, vector<bool>());
	codes_u(codes, t, t.root);
	Iobits in("in.txt", false);
	u_char c;
	
	while (in.readChar(c)) {
		//cout << c << endl;
		vector<bool>& curr = codes[c];
		for (int i = 0; i < curr.size(); i++) {
			out.writeBool(curr[i]);
		}
	}

	out.close();

	for (int i = 0; i < 512; i++)
		if (! codes[i].empty()) {
			vector<bool>& curr = codes[i];
			cout << i << ": ";
			for (int k = 0; k < curr.size(); k++)
				cout << curr[k];
			cout << endl;
		}
	
}