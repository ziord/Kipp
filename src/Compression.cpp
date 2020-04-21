#include "Compression.h"
#include <sys/stat.h>

void Compression::error(string msg){
    cerr<<msg<<endl;
    exit(EXIT_FAILURE);
}

streamsize file_size(string fn){
    struct stat buffer;
    int status = stat(fn.c_str(), &buffer);
    return status == 0 ? buffer.st_size : -1;
}

void Compression::compress(string fn) {
	string nfn = fn + ".kipp";
	ifstream in(fn.c_str(), (ios::in | ios::binary));  //input
	ofstream b_out(nfn.c_str(), (ios::out | ios::binary)); //ouput -- write to
	Counter cc(in); //allow Counter do its thing
	HTree htree(cc); //create a tree using initialized Counter obj

	b_out << (magicmarker);
	htree.writeEncodingTable(b_out);  //write the encoding table to output header
	in.clear(); in.seekg(0, ios::beg); //clear input stream, reset to beginning of file
	
	BitOutputStream bstream(b_out);  //create a bitoutputsream obj
	char ch;
	while (in.get(ch))
		bstream.writeBits(htree.getCode(ch & 0xff)); //write bits to output -- use a mask to prevent the high bits from being interpreted as a sign bit
	bstream.writeBits(htree.getCode(HTree::END_)); //sentinel
	in.close();
	cout<<"Compression of " <<fn<<" completed."<<endl;
    streamsize of_size = file_size(fn);
    streamsize cf_size = file_size(nfn);
    double cp_rate = (static_cast<double>(of_size - cf_size) / static_cast<double>(cf_size)) * 100;
    cout<<"Original file size: "<<of_size<<" bytes."<<endl;
    cout<<"Compressed file size: "<<cf_size<<" bytes."<<endl;
    cout<<"Compression rate: "<<cp_rate<<"%"<<endl;
}

void Compression::uncompress(string fn, string fn2) {
    size_t found = fn.find(".kipp");
    if (found >= string::npos){
        error("Cannot uncompress :( -- Not a kipp file!");
    }
	ifstream b_in(fn.c_str(), (ios::in | ios::binary));
	ofstream out(fn2.c_str(), (ios::out | ios::binary));
	Counter cc;
	HTree htree;
	unsigned long long marker_;
	b_in >> marker_;
	if (marker_ != magicmarker){
	    error("Cannot uncompress :( -- Not a kipp file!");
	}
	htree.readEncodingTable(b_in);
	BitInputStream bistream(b_in);
	int bit = 0;
	int ch;
	vector<int> bits;
	for (;;) {
		bit = bistream.readBit();
		bits.push_back(bit);
		ch = htree.getChar(bits);
		if (ch == HTree::UND_) {
			continue;
		}else if (ch == HTree::ERR_) {
			error("error occurred while decoding file " + fn);
		}else if (ch == HTree::END_){
		    break;
		}else{
            out.put(static_cast<char>(ch));
            bits.resize(0);
		}
	}
	b_in.close();
	out.close();
	cout << "\nDone!\n";
	cout <<fn << " Uncompressed successfully\n";
	cout <<"Decompressed file size: "<<file_size(fn2)<<" bytes."<<endl;
}