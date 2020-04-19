# Kipp

A lightweight text based file compressor and decompressor  written in C++ based on the Huffman coding algorithm.

## Usage
- Build the project.
- For compression of file:
   Run `Kipp -c name_of_file_to_be_compressed.ext`
- For decompression/uncompression of `Kipp`ed files:
    Run `Kipp -uc name_of_file_to_be_uncompressed.kipp` `name_of_output_file.ext`

### Note
`Kipp` only works for text based files (.txt, .py, .C, etc.).
This version of `Kipp` currently compresses only one file at a time.
    
