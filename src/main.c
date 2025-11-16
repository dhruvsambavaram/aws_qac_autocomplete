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

    // TODO: read words and insert into trie.
    // Example pseudocode:
    // while ((w = read_word(fp)) != NULL) {
    // normalize_word(w);
    // if (w is not empty) trie_insert(root, w, 1);
    // free(w);
    // }

    fclose(fp);

    // Interactive loop
    char input[512];
    char *results[DEFAULT_K];
    while (1) {
        printf("prefix> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        // strip newline
        input[strcspn(input, "\r\n")] = 0;
        if (strcmp(input, "exit") == 0) break;

        // TODO: call trie_autocomplete and print results
    }

    trie_free(root);
    return 0;
}