#ifndef TRIE_H
#define TRIE_H


#include <stdio.h>


#define ALPHABET_SIZE 26
#define MAX_WORD_LEN 256


// TODO: You may replace this struct with a more memory efficient design.
typedef struct TrieNode {
bool is_word;
// store frequency if you want ranking
unsigned int freq;
struct TrieNode *children[ALPHABET_SIZE];
} TrieNode;


// Create a new trie node
TrieNode *trie_create_node(void);


// Insert a word into the trie (optionally with frequency)
void trie_insert(TrieNode *root, const char *word, unsigned int freq);


// Returns true if the word exists
bool trie_search(TrieNode *root, const char *word);


// Given a prefix, gather up to `k` completions. The caller provides `results` array
// `results` must be an array of `char *` of length at least k; the function will
// allocate strings for each result which the caller must free.
int trie_autocomplete(TrieNode *root, const char *prefix, char **results, int k);


// Free the entire trie
void trie_free(TrieNode *root);


#endif // TRIE_H