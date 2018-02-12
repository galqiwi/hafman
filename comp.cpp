#include "htree.h"

void codes_u(vector<vector<bool>>& codes, HTree& t, int i) {
	cout << i  << "!" << endl;
	if (t.nodes[i]->r == 0)
		return;
	int ri = t.nodes[i]->r->id + (t.nodes[i]->r->r == 0 ? 0:256);
	int li = t.nodes[i]->l->id + (t.nodes[i]->l->r == 0 ? 0:256);
	codes[ri] = codes[i];
	codes[li] = codes[i];
	codes[ri].push_back(true);
	codes[li].push_back(false);
	codes_u(codes, t, ri);
	codes_u(codes, t, li);
}	

int main() {
	//Iobits r("in.txt", false);
	//u_char c = 'a';
	//r.readChar(c);
	//cout << c << endl;
	HTree t;
	t.set("in.txt");
	Iobits out("archive.hman");
	t.printHead(out);
	//out.writeBool(true);
	out.close();
	vector<vector<bool>> codes(512, vector<bool>());
	codes_u(codes, t, t.root);

	for (int i = 0; i < 512; i++)
		if (! codes[i].empty()) {
			vector<bool>& curr = codes[i];
			cout << i << ": ";
			for (int k = 0; k < curr.size(); k++)
				cout << curr[k];
			cout << endl;
		}
}