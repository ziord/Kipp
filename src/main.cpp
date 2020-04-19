#include "Compression.h"
#include <cstring>
#include <iostream>
using namespace std;
//Kipp -c f1
//Kipp -u f1 f2
int main(int argc, char* argv[]) {
    if (argc >= 3){
        Compression c;
        if (strcmp(argv[1], "-c") == 0){
            c.compress(argv[2]);
        }else if (strcmp(argv[1], "-uc") == 0){
            if (argc != 4)
                c.error("Not in the expected format: Kipp -uc file.kipp file.your_extension");
            c.uncompress(argv[2], argv[3]);
        }
    }
    else{
        cerr<<"Expected formats\n"
              "Compression: Kipp -c f\n"
              "Uncompression: Kipp -uc f1 f2"<<endl;
        cerr<<"f - file to be compressed\n";
        cerr<<"f1 - file to be uncompressed\t f2  - name of output file\n";
        exit(-1);
    }

}