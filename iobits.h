#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

int filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

struct Iobits {
	int char_i;
	bool out;
	Iobits(const char* fname, bool out_ = true) {
		char_i = 0;
		closed = false;

		out = out_;
		pointer = 0;
		if (out)
			pointer = 8;
		mem = '0';
		if (out)
			file.open(fname, fstream::binary | fstream::out);
		else
			file.open(fname, fstream::binary | fstream::in);
	}
	~Iobits() {
		close();
	}
	bool readBool(bool& var, int len = -1) {
		if (pointer == 0) {
			if (! file.get(mem)) {
				char_i++; 
				return false;
			} else {
				char_i++;
			}
			pointer = 8;
		}
		if (len != -1 && len == char_i) {
			int d = ( (((u_char)mem << (8 -  pointer))) & 0xFF - (u_char)0x80 );
			//cout << (bitset<8>)d << endl;
			if (d == 0) {
				return false;
			}
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
			char_i++;
			if (pointer == 8 && !end)
				end = true;
			else
				return false;
		} else {
			char_i++;
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