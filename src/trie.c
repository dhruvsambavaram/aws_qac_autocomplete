#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


TrieNode *trie_create_node(void) {
// TODO: allocate and initialize a node
return NULL; // replace
}


void trie_insert(TrieNode *root, const char *word, unsigned int freq) {
// TODO: implement insertion. update freq if node already marked as word.
}


bool trie_search(TrieNode *root, const char *word) {
// TODO: implement search; return true if is_word at end
return false; // replace
}


int trie_autocomplete(TrieNode *root, const char *prefix, char **results, int k) {
// TODO:
// 1. Walk to prefix node
// 2. From there, traverse subtree and collect full words into results (allocate copies)
// 3. Stop when you reach k results
// Return number of results collected
return 0; // replace
}


void trie_free(TrieNode *root) {
// TODO: recursively free all nodes
}