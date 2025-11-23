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


int trie_autocomplete(TrieNode *root, const char *prefix, char** output, int output_count, int out_put_string_len) {
	int input_str_len = (int)strlen(input_str);
	TrieNode* input_str_node = head;
	for (int c_iter = 0; c_iter < input_str_len; c_iter++)
	{
		input_str_node = input_str_node->m_Children[input_str[c_iter]];
		if (input_str == nullptr)
		{
			return 0;
		}
	}

	// get all possible 26 words under input_str_node
	char max_words[ALPHABET_COUNT][512];
	for (int w_iter = 0; w_iter < ALPHABET_COUNT; w_iter++)
	{
		char* curr_word = max_words[w_iter];
		Snprintf(curr_word, 512, input_str);
		int curr_word_len = input_str_len;
		TrieNode* curr_node = input_str_node->m_Children[w_iter];
		while (curr_node != nullptr && curr_node->m_IsWordEnding == false)
		{
			curr_word[curr_word_len] = curr_node->m_Char;
			curr_word_len++;

			//change curr_node to next most frequent child
			TrieNode* child_node = nullptr;
			int max_child_count = 0;
			for (int c_iter = 0; c_iter < ALPHABET_COUNT; c_iter++)
			{
				if (curr_node->m_Children[c_iter] != nullptr && curr_node->m_Children[c_iter]->m_Count > max_child_count)
				{
					max_child_count = curr_node->m_Children[c_iter]->m_Count;
					child_node = curr_node->m_Children[c_iter];
				}
			}
			curr_node = child_node;
		}
		//close the string
		curr_word[curr_word_len] = '\0';
	}

	// now write the top output_count into result
	int output_index[ALPHABET_COUNT];
	for (int iter = 0; iter < ALPHABET_COUNT; iter++)
	{
		output_index[iter] = -1;
	}

	int word_out_put_count = 0;
	for (int op_iter = 0; op_iter < output_count; op_iter++)
	{
		// next most frequent word
		int max_word_indx = -1;
		int max_word_index_count = 0;
		for (int iter = 0; iter < ALPHABET_COUNT; iter++)
		{
			if (output_index[iter] == -1)
			{
				if (input_str_node->m_Children[iter] != nullptr && input_str_node->m_Children[iter]->m_Count < max_word_index_count)
				{
					max_word_indx = iter;
					output_index[iter] = word_out_put_count;
					word_out_put_count++;
					break;
				}
			}
		}

		if (max_word_indx == -1)
		{
			break;
		}
		else
		{
			Snprintf(output[word_out_put_count - 1], out_put_string_len, max_words[max_word_indx]);
		}
	}

	return word_out_put_count;
}


void trie_free(TrieNode *root) {
// TODO: recursively free all nodes
}