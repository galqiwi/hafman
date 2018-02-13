#include <iostream>
#include <fstream>

using namespace std;

struct Iobits {
	bool out;
	Iobits(const char* fname, bool out_ = true) {
		closed = false;
		//cout << out_ << "init" << endl;
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

		var = (mem >> (pointer-- - 1)) & 0x01;
		return true;
	}

	void writeBool(bool var) {
		cerr << "just wrote " << var << endl;
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
		//cout << "1" << endl;
		for (int i = 0; i < 8; i++) {
			writeBool(((char)(var >> (7 - i))) & 0x01);
		}
		//cout << "2" << endl;
	}

	bool readChar(u_char& var) {
		//cout << mem << " " << pointer << endl;
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
		if(closed)
			return;
		closed = true;
		//cout << out << endl;
		if (out) {
			//cout << this << endl;
			//cout << pointer << endl;
			if (pointer != 8) {
				cout << "pointer is still " << pointer << endl;
				cout << "so i just wrote " << (int)mem << endl;
				mem = mem << pointer;
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