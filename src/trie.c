#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static int S_TriCountAllocCount = 0;

TrieNode *trie_create_node(void) {
	TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
	if (node != NULL)
	{
		S_TriCountAllocCount++;

		node->m_Char = '\0';
		node->m_Freq = 0;
		node->m_IsWordEnding = false;
		node->m_Parent = NULL;
		for (int c_iter = 0; c_iter < ALPHABET_COUNT; c_iter++)
		{
			node->m_Children[c_iter] = NULL;
		}
	}
	return node;
}


TrieNode* modify_or_add_child_node(TrieNode* parent, char input_char, int freq)
{
	// Convert character to array index (a-z -> 0-25)
	int index = input_char - 'a';
	if (index < 0 || index >= ALPHABET_COUNT) {
		return NULL;
	}
	
	TrieNode* child_node = NULL;
	if (parent->m_Children[index] == NULL)
	{
		child_node = trie_create_node();
		if (child_node) {
			child_node->m_Char = input_char;
			parent->m_Children[index] = child_node;
			child_node->m_Parent = parent;
		}
	}
	else
	{
		child_node = parent->m_Children[index];
	}
	// update count on the node
	if (child_node)
	{
		child_node->m_Freq += freq;
	}
	return child_node;
}


bool trie_insert(TrieNode *root, const char * input_word, unsigned int freq) {
	int input_word_char_count = (int)strlen(input_word);
	TrieNode* curr_parent_node = root;
	for (int c_iter = 0; c_iter < input_word_char_count; c_iter++)
	{
		curr_parent_node = modify_or_add_child_node(curr_parent_node, input_word[c_iter], freq);
		if (curr_parent_node == NULL)
		{
			return false;
		}
	}
	curr_parent_node->m_IsWordEnding = true;
	// Set the frequency on the final node
	curr_parent_node->m_Freq = freq;
	return true;
}


// Helper structure to store word-frequency pairs
typedef struct {
	char word[MAX_WORD_LEN];
	unsigned int freq;
} WordFreq;

// Helper function to collect all words starting from a node
static void collect_words(TrieNode* node, char* buffer, int buffer_len, WordFreq* words, int* word_count, int max_words) {
	if (node == NULL || *word_count >= max_words) {
		return;
	}
	
	// If this node marks the end of a word, add it to the list
	if (node->m_IsWordEnding) {
		if (*word_count < max_words) {
			strncpy(words[*word_count].word, buffer, MAX_WORD_LEN - 1);
			words[*word_count].word[MAX_WORD_LEN - 1] = '\0';
			words[*word_count].freq = node->m_Freq;
			(*word_count)++;
		}
	}
	
	// Recursively traverse all children
	for (int i = 0; i < ALPHABET_COUNT; i++) {
		if (node->m_Children[i] != NULL) {
			int new_len = buffer_len;
			if (new_len < MAX_WORD_LEN - 1) {
				buffer[new_len] = node->m_Children[i]->m_Char;
				new_len++;
				buffer[new_len] = '\0';
				collect_words(node->m_Children[i], buffer, new_len, words, word_count, max_words);
				buffer[buffer_len] = '\0'; // Restore buffer
			}
		}
	}
}

// Comparison function for sorting by frequency (descending)
static int compare_word_freq(const void* a, const void* b) {
	WordFreq* wa = (WordFreq*)a;
	WordFreq* wb = (WordFreq*)b;
	if (wa->freq > wb->freq) return -1;
	if (wa->freq < wb->freq) return 1;
	return 0;
}

int trie_autocomplete(TrieNode *root, const char *prefix, char** output, int output_count, int out_put_string_len) {
	int input_str_len = (int)strlen(prefix);
	TrieNode* prefix_node = root;
	
	// Navigate to the prefix node
	for (int c_iter = 0; c_iter < input_str_len; c_iter++)
	{
		int index = prefix[c_iter] - 'a';
		if (index < 0 || index >= ALPHABET_COUNT) {
			return 0;
		}
		prefix_node = prefix_node->m_Children[index];
		if (prefix_node == NULL)
		{
			return 0;
		}
	}

	// Collect all words starting with the prefix
	// Use a reasonable limit to avoid excessive memory usage
	const int max_collect = 10000;
	WordFreq* words = (WordFreq*)malloc(max_collect * sizeof(WordFreq));
	if (words == NULL) {
		return 0;
	}
	
	int word_count = 0;
	char buffer[MAX_WORD_LEN];
	strncpy(buffer, prefix, MAX_WORD_LEN - 1);
	buffer[MAX_WORD_LEN - 1] = '\0';
	
	// Collect all words from the subtree (including the prefix itself if it's a word)
	collect_words(prefix_node, buffer, input_str_len, words, &word_count, max_collect);
	
	// Sort by frequency (descending)
	qsort(words, word_count, sizeof(WordFreq), compare_word_freq);
	
	// Return the top output_count results
	int result_count = (word_count < output_count) ? word_count : output_count;
	for (int i = 0; i < result_count; i++) {
		strncpy(output[i], words[i].word, out_put_string_len - 1);
		output[i][out_put_string_len - 1] = '\0';
	}
	
	free(words);
	return result_count;
}


void trie_free(TrieNode *root) {
   // recursively call and free memoory
	if (root)
	{
		for (int c_iter = 0; c_iter < ALPHABET_COUNT; c_iter++)
		{
			TrieNode* child_node = root->m_Children[c_iter];
			if (child_node != NULL)
				trie_free(child_node);
		}
		free(root);
	}
}
