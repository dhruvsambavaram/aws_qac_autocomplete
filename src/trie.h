#ifndef TRIE_H
#define TRIE_H


#include <stdio.h>


#define ALPHABET_COUNT 26
#define MAX_WORD_LEN 256


// TODO: You may replace this struct with a more memory efficient design.
typedef struct TrieNode {
	char      m_Char;
	int       m_Freq;
	bool      m_IsWordEnding;
	TrieNode* m_Children[ALPHABET_COUNT];
	TrieNode* m_Parent;
};


// Create a new trie node
TrieNode *trie_create_node(void);


// Insert a word into the trie (optionally with frequency)
bool trie_insert(TrieNode *root, const char * input_word, unsigned int freq);


// Given a prefix, gather up to `k` completions. The caller provides `results` array
// `results` must be an array of `char *` of length at least k; the function will
// allocate strings for each result which the caller must free.
int trie_autocomplete(TrieNode *root, const char *prefix, char** output, int output_count, int out_put_string_len);


// Free the entire trie
void trie_free(TrieNode *root);


#endif // TRIE_H