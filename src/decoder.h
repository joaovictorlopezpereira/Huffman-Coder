#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Loads the reverse codes table
void load_code_table(const char* file_name, char reverse_codes[256][256]) {
  FILE* file = fopen(file_name, "r");
  if (!file) {
    printf("It was not possible to open the file %s\n.", file_name);
    exit(1);
  }

  char line[512];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '\'' && line[1] != '\0') {
      char ch;
      int frequency;
      char code[256];
      sscanf(line, "'%c' (%d): %s", &ch, &frequency, code);

      // Stores the code and the character in reverse table
      strcpy(reverse_codes[(unsigned char)ch], code);
    }
  }
  fclose(file);
}

// Decodes the codified code using the reverse codes table
void decode_text(const char* encoded_file, const char reverse_codes[256][256], const char* output_file) {
  // Tries to open the encoded file
  FILE* encoded = fopen(encoded_file, "r");
  if (!encoded) {
    printf("It was not possible to open the file %s\n.", encoded_file);
    exit(1);
  }

  // Tries to open the output file
  FILE* output = fopen(output_file, "w");
  if (!output) {
    printf("It was not possible to open the file %s\n.", output_file);
    exit(1);
  }

  char buffer[256] = {0};
  int buffer_index = 0;
  int bit;

  while ((bit = fgetc(encoded)) != EOF) {
    if (bit != '0' && bit != '1') {
      continue; // Ignores invalid characters
    }

    buffer[buffer_index++] = (char)bit;
    buffer[buffer_index] = '\0';

    for (int i = 0; i < 256; i++) {
      if (reverse_codes[i][0] != '\0' && strcmp(buffer, reverse_codes[i]) == 0) {
        fputc((char)i, output);
        buffer_index = 0;
        buffer[0] = '\0';
        break;
      }
    }

    if (buffer_index >= 255) {
      printf("Error: Buffer overflow. Stopping decoding.\n");
      buffer_index = 0;
      buffer[0] = '\0';
      fclose(encoded);
      fclose(output);
      exit(1);
    }
  }

  // Closes both files
  fclose(encoded);
  fclose(output);
}

// Treats the decoding process
void decode_process(const char *encoded_filename, const char *output_filename, const char *table_filename) {

  // Loads the decoding table
  char reverse_codes[256][256] = {0};
  load_code_table(table_filename, reverse_codes);

  // Decodes the text
  decode_text(encoded_filename, reverse_codes, output_filename);
}
