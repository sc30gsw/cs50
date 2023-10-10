// Implements a dictionary's functionality
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

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

bool check(const char *word)
{
    hashValue = hash(word);

    node *cursor = table[hashValue];

    // リンクされたリストを確認
    while (cursor != 0)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }

        cursor = cursor -> next;
    }

    return false;
}


unsigned int hash(const char *word)
{
    // 調べている単語のASCⅡ値の合計
    unsigned long total = 0;

    for (int i = 0; i < strlen(word); i ++)
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
        return false;
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

unsigned int size(void)
{
    if (wordCount > 0)
    {
        return wordCount;
    }
    return 0;
}

bool unload(void)
{
    for (int i = 0; i < N; i ++)
    {
        // リンクされたリストの先頭にカーソルを設定
        node *cursor = table[i];

        // カーソルがNULLでない場合、メモリをフリーにする
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        if (cursor != NULL)
        {
            return false;
        }
    }

    return true;
}
