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

		/*
		for (int i = 0; i < 512; i++)
			if (v[i] != 0)
				cout << (int)nodes[i]->id << ": " << v[i] << endl;
		*/
	}
	void printHead(Iobits& file, int i) {
		Node* curr = nodes[i];
		if (curr->r == 0) {
			file.writeBool(true);
			file.writeChar(curr->id);
		} else {
			file.writeBool(false);
		}
	}
};