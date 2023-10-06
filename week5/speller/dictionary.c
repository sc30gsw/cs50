// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 26;

node *table[N];

unsigned int wordCount;
unsigned int hashValue;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}


unsigned int hash(const char *word)
{
    // 調べている単語のASCⅡ値の合計
    unsigned long total = 0;

    for (int i = 0; i < strlen(total); i ++)
    {
        total += tolower(word[i]);
    }

    return total % N;
}

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Unable to open dictionary\n");
    }

    char word[LENGTH + 1];

    // EOFまでの文字列の辞書をスキャン
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // ノードからwordにコピー
        strcpy(n->word, word);
        hashValue = hash(word);
        n->next = table[hashValue];
        table[hashValue] = n;
        wordCount ++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
