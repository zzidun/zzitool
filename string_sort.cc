#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ratio>

#define STRING_SORT_LINE_LENGTH 105
#define STRING_SORT_CHARSET_SIZE 128

typedef enum {
    READIN = 0,
    WAIT,
} string_input_status_t;

typedef struct tag_trie_node{
    int32_t cnt;
    struct tag_trie_node *son[STRING_SORT_CHARSET_SIZE];
} trie_node_t;

void trie_insert(trie_node_t *root, char *str, int32_t length)
{
    trie_node_t *now = root;
    for (int32_t i = 0; i < length; ++i) {
        char si = str[i];
        if (now->son[si] == nullptr) {
            now->son[si] = (trie_node_t *)malloc(sizeof(trie_node_t));
            memset(now->son[si], 0, sizeof(trie_node_t));
        }
        now = now->son[si];
    }
    now->cnt = 1;
    return;
}

void trie_free(trie_node_t *root)
{
    for (int32_t i = 0; i < STRING_SORT_CHARSET_SIZE; ++i) {
        if (root->son[i] != nullptr) {
            trie_free(root->son[i]);
        }
    }

    free(root);
    return;
}

void string_sort_build(trie_node_t *root)
{
    string_input_status_t status = WAIT;

    int32_t now_length = 0;
    char now = 0;
    char buffer[STRING_SORT_LINE_LENGTH];

    while (true) {
        scanf("%c", &now);

        switch (status) {
            case READIN: {
                buffer[now_length++] = now;

                if (now == '\n') {
                    trie_insert(root, buffer, now_length-1);
                    status = WAIT;
                } else if (now_length == STRING_SORT_LINE_LENGTH) {
                    status = WAIT;
                }
            }
            break;
            case WAIT: {
                if (now == '\n') {
                    return;
                } else {
                    status = READIN;
                    now_length = 0;
                    buffer[now_length++] = now;
                }
            }
            break;
        }
    }
}

void string_sort_dfs(trie_node_t *root, char * const buffer, int32_t length)
{
    if (root->cnt == 1) {
        for (int32_t i = 0; i < length; ++i) {
            putchar(buffer[i]);
        }
        putchar('\n');
    }

    for (int32_t i = 0; i < STRING_SORT_CHARSET_SIZE; ++i) {
        if (root->son[i] != nullptr) {
            buffer[length] = i;
            string_sort_dfs(root->son[i], buffer, length+1);
        }
    }
}

int main(int args, char *argv[])
{
    trie_node_t *root = (trie_node_t *)malloc(sizeof(trie_node_t));

    string_sort_build(root);

    char buffer[STRING_SORT_LINE_LENGTH];
    string_sort_dfs(root, buffer, 0);

    trie_free(root);

    return 0;
}