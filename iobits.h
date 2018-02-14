#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

struct Iobits {
	bool out;
	Iobits(const char* fname, bool out_ = true) {
		closed = false;

		out = out_;
		pointer = 0;
		if (out)
			pointer = 8;
		mem = '0';
		if (out)
			file.open(fname, std::fstream::app | fstream::binary | fstream::out);
		else
			file.open(fname, std::fstream::app | fstream::binary | fstream::in);
	}
	~Iobits() {
		close();
	}
	bool readBool(bool& var) {
		if (pointer == 0) {
			if (! file.get(mem)) 
				return false;
			pointer = 8;
		}

		var = ((u_char)mem >> (pointer-- - 1)) & 0x01;
		return true;
	}

	void writeBool(bool var) {
		mem = (mem << 1) + (var & 0x01);
		pointer--;

		if (pointer == 0) {
			file << mem;
			mem = 0;
			pointer = 8;
		}
	}

	void writeChar(u_char var) {
		for (int i = 0; i < 8; i++) {
			writeBool(((char)((u_char)var >> (7 - i))) & 0x01);
		}
	}

	bool readChar(u_char& var) {
		char old = mem;
		static bool end = false;

		if (! file.get(mem)) {
			if (pointer == 8 && !end)
				end = true;
			else
				return false;
		}
		var = (old << (8 - pointer)) + ((u_char)mem >> (pointer));
		return true;
	}

	void close() {
		if(closed)
			return;
		closed = true;
		if (out) {
			if (pointer != 8) {
				cout << "pointer is still " << pointer << endl;
				mem = mem << pointer;
				bitset<8> toprint = mem;
				cout << "so i just wrote " << toprint << endl;
				file << mem;
			}
		}
		
		file.close();
	}
	bool closed;
	char mem;
	int pointer;
	fstream file;
};