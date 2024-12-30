#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_tree.h"
#include "encoder.h"
#include "decoder.h"

int main(int argc, char *argv[]) {
  // Verifies if all the parameters were given as input
  if (argc < 5) {
    printf("Correct usage: %s <mode (encode/decode)> <input_file> <output_file> <table_file>\n", argv[0]);
    exit(1);
  }

  char* mode = argv[1]; // "encode" or "decode"
  char* input_filename = argv[2];
  char* output_filename = argv[3];
  char* table_filename = argv[4];

  if (strcmp(mode, "encode") == 0) {
    encode_process(input_filename, output_filename, table_filename);
  }
  else if (strcmp(mode, "decode") == 0) {
    decode_process(input_filename, output_filename, table_filename);
  }
  else {
    printf("Invalid mode. Use 'encode' or 'decode'.\n");
    exit(1);
  }
  printf("Operation successfully completed!\n");
  return 0;
}