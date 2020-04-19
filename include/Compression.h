#ifndef COMPRESSION_H
#define COMPRESSION_H
#include "HuffTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#include <string>

#define magicmarker  0xface8200

class Compression {

public:
	explicit Compression()= default;
	void compress(string fn);
	void uncompress(string fn, string fn2);
	void error(string);
};
#endif // !COMPRESSION_H
