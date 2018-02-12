#include <iostream>
#include <fstream>

using namespace std;

struct Iobits {
	bool out;
	Iobits(const char* fname, bool out = true) {
		this->out = out;
		pointer = 0;
		if (out)
			pointer = 8;
		mem = '0';
		file.open(fname, std::fstream::app | fstream::binary | (out ? fstream::out:fstream::in));
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

		var = (mem >> (pointer-- - 1)) & 0x01;
		return true;
	}

	void writeBool(bool var) {
		mem = (mem << 1) + (var & 0x01);
		pointer--;
		//cout << "p:" << pointer << " " << (int)mem << endl;

		if (pointer == 0) {
			//cout << (int)mem << endl;
			file << mem;
			mem = 0;
			pointer = 8;
		}
	}

	void writeChar(u_char var) {
		for (int i = 0; i < 8; i++) {
			writeBool(((char)(var >> (7 - i))) & 0x01);
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
		var = (old << (8 - pointer)) + (mem >> (pointer));
		return true;
	}

	void close() {
		
		if (out) {
			if (pointer != 8)
				mem = mem << pointer;
				file << mem;
		}
		
		file.close();
	}

	char mem;
	int pointer;
	fstream file;
};