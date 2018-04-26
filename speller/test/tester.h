// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

typedef struct NODE
{
    bool isWord;
    char letter;
    struct NODE *children[27];
}
node;

int getIndex(char c);
void createNode(node *cursor);
void unloadHelper(node *pointer[]);

#endif // DICTIONARY_H
