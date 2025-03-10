
# Huffman-Coder

## Description

A text encoding and decoding system utilizing Huffman coding for efficient compression and decompression using a binary tree structure.

-----
## How to Encode and Decode

You first need to compile the project. Make sure ``gcc`` is installed on your system, then compile the project by running:

``gcc main.c -o huffman.exe``

You can choose a different name for the output file instead of ``huffman.exe``, but for the sake of simplicity, we will refer to it as ``huffman.exe`` throughout this document.

### Encoding Process

To encode a text file, use the following command:

``huffman.exe encode <input-file> <encoded-file> <table-file>``

- ``<input-file>``: The path to the text file you want to encode.
- ``<encoded-file>``: The path where the encoded output will be saved. This file will contain the compressed data.
- ``<table-file>``: The path to the Huffman encoding table. This file contains the mapping of characters to their respective Huffman codes, and is necessary for decoding.

### Example:

``huffman.exe encode text.txt encoded.txt table.txt``

In this example, ``text.txt`` is the file to be encoded, ``encoded.txt`` will store the encoded output, and ``table.txt`` will contain the Huffman encoding table.


### Decoding Process

To decode an encoded file, use the following command:

``huffman.exe decode <encoded-file> <decoded-file> <table-file>``

- ``<encoded-file>``: The path to the encoded file that you want to decode.
- ``<decoded-file>``: The path where the decoded output will be saved. This file will contain the original text after decoding.
- ``<table-file>``: The Huffman encoding table used during the encoding process. It is required to correctly decode the data.

### Example:

``huffman.exe decode encoded.txt decoded.txt table.txt``

In this example, ``encoded.txt`` is the file containing the encoded data, ``decoded.txt`` will store the original text after decoding, and ``table.txt`` is the Huffman encoding table used during encoding.

### Important Notes

Make sure the ``<table-file>`` used for decoding is the exact same table that was generated during the encoding process. If the table is different or missing, the decoding will fail or produce incorrect results. The encoded file is a compressed representation of the original text, and the decoding process restores it back to its original form.

By following these steps, you can efficiently encode and decode text files using the Huffman coding algorithm.

-----
## Running the Tests

To run the tests available in ``test-encoding``, you can run the encoding test with the following command:

``huffman.exe encode text.txt encoded.txt table.txt``

The ``encoded.txt`` and ``table.txt`` files do not need to exist beforehand, as they will be generated as output by the program.

To verify the correctness of the encoding process, you can run the decoding test available in ``test-decoding``:

``huffman.exe decode encoded.txt decoded.txt table.txt``

Make sure that ``encoded.txt`` and ``table.txt`` are the output files generated from the same encoding run. The ``decoded.txt`` file will be the result of the decoding process, and it should match the original ``text.txt`` file if the encoding and decoding processes work correctly.
