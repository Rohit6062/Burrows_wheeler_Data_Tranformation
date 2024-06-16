This project is demonstration of Borrows wheeler Data Transformation which is a string transformation algorithm which helps in making string more compressable.

You can learn more about it here: https://en.wikipedia.org/wiki/Burrows%E2%80%93Wheeler_transform

Here We first transform give data file into bwd form and then use one of two methods to compress it and create a compressed file.
( effective ness of this methods depends on data )
Methods after BWD Transformation
**1) count of continous occuring same element + HUffman
2) link-list method + Huffman**

 **Setup**
 
  **for encryption (compression) :**
    simply run encrypt file with three parameters 1. file name of file to encrypt 2. output file name 3. 0 ( represent its encrypting)
    exmaple: **(for linux)**
        **./encrypt file_to_encrypt output_file 0**

  **for decryption (decompression):**
    simply run encrypt file with three parameters 1. file name of file to decrypt 2. output file name 3. 1 ( represent its decrypting)
    exmaple: **(for linux)**
        **./encrypt file_to_encrypt output_file 1**

