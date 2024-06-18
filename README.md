You can learn more about BWT here: https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform

This project focuses on implementing the Burrows-Wheeler Transformation (BWT) in C to achieve efficient data compression. BWT rearranges the input text into runs of similar characters, making it more amenable to further compression techniques like Run-Length Encoding (RLE) and Huffman coding.
Objectives

    Implement BWT: Transform the input text using the Burrows-Wheeler Transformation.
    Compression: Apply additional compression techniques (e.g., RLE, Huffman coding) on the BWT output.
    Decompression: Reverse the compression and BWT to reconstruct the original text.

Features

    BWT Transformation: Efficiently implement the Burrows-Wheeler transform.
    Compression Algorithms: Integrate RLE and Huffman coding for enhanced compression.
    File I/O: Handle input and output operations for reading the original text and writing the compressed data.

Technical Requirements

    Language: C
    Compiler: GCC or similar
    Libraries: Standard C libraries (stdlib.h, stdio.h, string.h)

Deliverables

    Source Code: Well-documented C files.
    Executable: Compiled program for compression and decompression.
    Documentation: README file with instructions and sample test cases.

This project will provide a complete implementation of the Burrows-Wheeler Transformation for efficient data compression and decompression in C.
 **Setup**
 
  **for encryption (compression) :**
    simply run encrypt file with three parameters 1. file name of file to encrypt 2. output file name 3. 0 ( represent its encrypting)
    exmaple: **(for linux)**
        **./encrypt file_to_encrypt output_file 0**

  **for decryption (decompression):**
    simply run encrypt file with three parameters 1. file name of file to decrypt 2. output file name 3. 1 ( represent its decrypting)
    exmaple: **(for linux)**
        **./encrypt file_to_encrypt output_file 1**

