#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Encodes the text from ASCII to Huffman coding
void encode_text(FILE *input_file, const char codes[256][256], const char *output_file) {
  FILE *output = fopen(output_file, "w");

  if (!output) {
    printf("It was not possible to open the file %s.\n.", output_file);
    exit(1);
  }

  rewind(input_file);
  int c = fgetc(input_file);
  while (c != EOF) {
    if (codes[c][0] != '\0') {
      fprintf(output, "%s", codes[c]);
    }
    c = fgetc(input_file);
  }
  fclose(output);
}

// Saves the coding table in a file
void save_code_table(const char codes[256][256], const int frequencies[256], const char *output_file) {
  FILE* file = fopen(output_file, "w");
  if (!file) {
    printf("It was not possible to open the file %s.\n.", output_file);
    exit(1);
  }

  fprintf(file, "Huffman encoding:\n");
  for (int i = 0; i < 256; i++) {
    if (frequencies[i] > 0) {
      fprintf(file, "'%c' (%d): %s\n", (char)i, frequencies[i], codes[i]);
    }
  }
  fclose(file);
}

// Treats the encoding process
void encode_process(const char *input_filename, const char *output_filename, const char *table_filename) {
  // Tries to open the input file
  FILE *file = fopen(input_filename, "r");
  if (file == NULL) {
    printf("It was not possible to open the file %s.\n", input_filename);
    exit(1);
  }

  // Initializes an array with the frequencies of the 256 ASCII characters.
  int frequencies[256] = {0};
  int c = fgetc(file);
  while (c != EOF) {
    frequencies[c] += 1;
    c = fgetc(file);
  }

  // Builds the Huffman tree
  node *root = build_huffman_tree(frequencies);

  // Computes the best codes for each character
  char codes[256][256];
  char code[256];
  generate_codes(root, code, 0, codes);

  // Encodes the text
  encode_text(file, codes, output_filename);
  save_code_table(codes, frequencies, table_filename);

  // Closes the file and frees the tree
  fclose(file);
  free_tree(root);
}
