#include "iobits.h"
#include <vector>

struct Node {
	Node *r, *l, *parent;
	u_char id;
	Node(u_char id = 0): r(0), l(0), parent(0), id(id) {}
	~Node() {
	}
};

Node* merge(Node* a, Node* b) {
	Node* out = new Node();
	out->r = b;
	out->l = a;
	a->parent = out;
	b->parent = out;
	return out;
}

int findmin(vector<int>v, int ignore) {
	int outv = 1e9;
	int out = -1;
	for (int i = 0; i < 512; i++) {
		if (outv > v[i] && i != ignore && v[i] != 0) {
			outv = v[i];
			out = i;
		}
	}
	return out;
}

Node* recset(Iobits& file, int& p, vector<Node*>& nodes, Node* last) {
	bool b;
	file.readBool(b);
	if (b) {
		//cout << 2 << endl;
		//while (true);
		u_char c;
		file.readChar(c);
		cout << c << " done!" << endl;
		nodes[c]->parent = last;
		return nodes[c];
	} else {
		//cout << p << endl;
		nodes[p] = new Node();
		nodes[p]->parent = last;
		//cout << last << endl;
		int oldp = p;
		Node* currn = nodes[p];
		p++;
		nodes[oldp]->l = recset(file, p, nodes, currn);
		nodes[oldp]->r = recset(file, p, nodes, currn);
		return currn;
	}
}

struct HTree {
	int root;
	vector<Node*> nodes;
	HTree() {
		nodes = vector<Node*>(512, 0);
		for (int i = 0; i < 256; i++)
			nodes[i] = new Node();
	}
	~HTree() {
		for(int i = 0; i < 512; i++)
			if(nodes[i] != 0)
				delete nodes[i];
	}
	void set_(Iobits& file) {
		root = 256;
		int p = 256;
		
		recset(file, p, nodes, 0);
		cout << "done!" << endl;
		for(int i = 0; i < 512; i++)
			if (nodes[i] == 0)
				nodes[i] = new Node();
		for(int i = 0; i < 512; i++)
			if(nodes[i] != 0)
				nodes[i]->id = (u_char)i;
	}
	void print() {
		for (int i = 0; i < 512; i++) {
			//cout << i << endl;
			if (nodes[i]->parent != 0)
				cout << (int)nodes[i]->id << "->" << (int)nodes[i]->parent->id << endl;
			}
	}
	void set(const char* file) {
		vector<int> v(512, 0);
		Iobits f(file, false);
		u_char c;
		//cout << 1 << endl;
		while (f.readChar(c)) {
			//cout << (int)c << endl;
			v[(int)c]++;
		}
		int p = 256;
		root = -1;
		while (true) {
			int fmin = findmin(v, -1);
			int smin = findmin(v, fmin);
			if (smin == -1) {
				root = fmin;
				break;
			}
			v[p] = v[fmin] + v[smin];
			nodes[p] = merge(nodes[fmin], nodes[smin]);
			p++;
			v[fmin] = 1e9;
			v[smin] = 1e9;
		}

		for(int i = p; i < 512; i++)
			nodes[i] = new Node();

		for(int i = 0; i < 512; i++)
			if(nodes[i] != 0)
				nodes[i]->id = (u_char)i;
		f.close();

		/*
		
		*/
	}
	void printHead(Iobits& file, Node* curr) {
		if (curr->r == 0) {
			file.writeBool(true);
			file.writeChar(curr->id);
		} else {
			file.writeBool(false);
			printHead(file, curr->r);
			printHead(file, curr->l);
		}
	}
};


void codes_u(vector<vector<bool>>& codes, HTree& t, int i) {
	//cout << i << " " << t.nodes[i]->r << " " << t.nodes[i]->l << endl;
	//cout << i  << "!" << endl;
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