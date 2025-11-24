#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

#define DEFAULT_K 10

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <words_file> [k]\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int k = (argc >= 3) ? atoi(argv[2]) : DEFAULT_K;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    TrieNode *root = trie_create_node();
    if (!root) {
        fprintf(stderr, "Failed to allocate trie root\n");
        fclose(fp);
        return 1;
    }

    // Read words from TSV file and insert into trie (only words with count > 10)
    char line[512];
    int words_loaded = 0;
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        // Parse word and count (tab-separated)
        char *word = line;
        char *tab_pos = strchr(line, '\t');
        if (!tab_pos) continue; // Skip malformed lines
        
        *tab_pos = '\0'; // Split the line
        unsigned int count = (unsigned int)atoi(tab_pos + 1);
        
        // Only insert words with count > 5 and wordlen > 4
        if (count > 5 && strlen(word) > 4) {
            // Normalize word to lowercase
            for (int i = 0; word[i]; i++) {
                if (word[i] >= 'A' && word[i] <= 'Z') {
                    word[i] = word[i] - 'A' + 'a';
                }
            }
            
            if (trie_insert(root, word, count)) {
                words_loaded++;
            }
        }
    }
    
    printf("Loaded %d words into trie\n", words_loaded);
    fclose(fp);

    // Interactive loop
    char input[512];
    char *results[k];
    const int max_result_len = MAX_WORD_LEN;
    
    // Allocate memory for results
    for (int i = 0; i < k; i++) {
        results[i] = (char *)malloc(max_result_len);
        if (!results[i]) {
            fprintf(stderr, "Failed to allocate memory for results\n");
            trie_free(root);
            return 1;
        }
    }
    
    while (1) {
        printf("prefix> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        // strip newline
        input[strcspn(input, "\r\n")] = 0;
        if (strcmp(input, "exit") == 0) break;
        
        // Normalize input to lowercase
        for (int i = 0; input[i]; i++) {
            if (input[i] >= 'A' && input[i] <= 'Z') {
                input[i] = input[i] - 'A' + 'a';
            }
        }

        // Call trie_autocomplete and print results
        int num_results = trie_autocomplete(root, input, results, k, max_result_len);
        
        if (num_results > 0) {
            for (int i = 0; i < num_results; i++) {
                printf("%s\n", results[i]);
            }
        } else {
            printf("No completions found\n");
        }
    }
    
    // Free results memory
    for (int i = 0; i < k; i++) {
        free(results[i]);
    }

    trie_free(root);
    return 0;
}
