#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in the tree
typedef struct node {
  char character;
  int frequency;
  struct node *left;
  struct node *right;
} node;

// Creates a node
node* create_node(char character, int frequency) {
  node* n = (node *)malloc(sizeof(node));
  n->character = character;
  n->frequency = frequency;
  n->left      = NULL;
  n->right     = NULL;
  return n;
}

// Finds the two nodes with the least frequency
void two_nodes_with_least_freq(node* nodes[], int size, int* first, int* second) {
  *first = -1;
  *second = -1;

  for (int i = 0; i < size; i++) {
    // Checks the remaining nodes if the node is null
    if (nodes[i] == NULL) {
      continue;
    }
    // Updates first and second if a node with a smaller frequency than first was found
    if (*first == -1 || nodes[i]->frequency < nodes[*first]->frequency){
      *second = *first;
      *first = i;
    }
    // Updates second if a node with a smaller frequency than second was found
    else if (*second == -1 || nodes[i]->frequency < nodes[*second]->frequency) {
      *second = i;
    }
  }
}

// Builds the Huffman tree
node* build_huffman_tree(int frequencies[]) {
  // Initializes all nodes as null
  node* nodes[256] = {NULL};
  int size = 0;

  // Creates a node for every character with frequency above 0
  for (int i = 0; i < 256; i++) {
    if (frequencies[i] > 0) {
      nodes[size++] = create_node((char)i, frequencies[i]);
    }
  }

  // Builds the tree
  while (size > 1){
    int first, second;

    // Builds the nodes made up from the two nodes with the least frequency
    two_nodes_with_least_freq(nodes, size, &first, &second);
    node* left = nodes[first];
    node* right = nodes[second];
    node* parent = create_node('\0', left->frequency + right->frequency);
    parent->left = left;
    parent->right = right;

    // Substitutes the two nodes by the parent
    nodes[first] = parent;
    nodes[second] = nodes[size-1];
    size -= 1;
  }

  // Returns the root
  return nodes[0];
}

// Generates the codes recursively
void generate_codes(node* root, char* code, int depth, char codes[256][256]) {
  if (!root->left && !root->right) {
    code[depth] = '\0'; // ends code
    strcpy(codes[(unsigned char)root->character], code);
    return;
  }
  if (root->left) {
    code[depth] = '0';
    generate_codes(root->left, code, depth + 1, codes);
  }
  if (root->right) {
    code[depth] = '1';
    generate_codes(root->right, code, depth + 1, codes);
  }
}

// Frees the memory consumed by the tree structure
void free_tree(node* root) {
  if (root == NULL) {
    return;
  }
  free_tree(root->left);
  free_tree(root->right);
  free(root);
}
