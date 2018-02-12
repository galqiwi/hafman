#include "iobits.h"

int main() {

	int k = 0;

	Iobits w("in.txt", true);
	w.writeBool(false);
	w.writeChar('a');
	for (int i = 0; i < 10; i++)
		w.writeBool(i % 2 == 0);
	w.close();

	Iobits f("in.txt", false);
	u_char a;
	bool b;
	for (int i = 0; i < 24; i++) {
		f.readBool(b);
		cout << b;
		if (++k % 8 == 0)
			cout << endl;
	}
	cout << endl;
	while(f.readChar(a)) {
		cout << (int)a << endl;
	}
}