#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int S_TriCountAllocCount = 0;

TrieNode *trie_create_node(void) {
	TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
	if (node != NULL)
	{
		S_TriCountAllocCount++;

		node->m_Char = input_char;
		node->m_Count = 0;
		node->m_Parent = nullptr;
		for (int c_iter = 0; c_iter < ALPHABET_COUNT; c_iter++)
		{
			node->m_Children[c_iter] = nullptr;
		}
	}
	return node;
}


TrieNode* ModifyOrAddChildNode(TrieNode* parent, char input_char, int freq)
{
	TrieNode* child_node = nullptr;
	if (parent->m_Children[input_char] == nullptr)
	{
		child_node = CreateTrieNode(input_char);
		parent->m_Children[input_char] = child_node;
	}
	else
	{
		child_node = parent->m_Children[input_char];
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
		curr_parent_node = ModifyOrAddChildNode(curr_parent_node, input_word[c_iter], count);
		if (curr_parent_node == nullptr)
		{
			return false;
		}
	}
	curr_parent_node->m_IsWordEnding = true;
	return true;
}


bool trie_search(TrieNode *root, const char *word) {
// TODO: implement search; return true if is_word at end
return false; // replace
}


int trie_autocomplete(TrieNode *root, const char *prefix, char** output, int output_count, int out_put_string_len) {
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