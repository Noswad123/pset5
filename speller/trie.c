// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

//the initial position of the node array
node *head;
node *cursor;
//a place holder the trie is being traversed
int wordCount = 0;
int myWords=0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *follower;         //debuggin tool
    cursor=head;
    int index = 0;
    // check each character
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        follower=cursor;
        index = getIndex(word[i]);
        if(cursor ->children[index]==NULL)
        {
            return false;
        }
        else
        {
            cursor = cursor -> children[index];
        }
    }

         //check if final position is at end of the word
        if (cursor -> isWord == true )
        {
           myWords++;
            return true;
        }
        else
        {
            return false;
        }

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    node *follower;
    cursor=malloc(sizeof(node));
   head = createNode(cursor);
   //each indicie corresponds to a letter in the alphabet and '
    int index;

    FILE *dictPtr = fopen(dictionary,"r");
    if (!dictPtr)
    {
        fprintf(stderr, "File does not exist!\n");
        unload();
        return false;
    }
   //for every dictionary word iterate through the trie
    for (char c = fgetc(dictPtr); c != EOF; c = fgetc(dictPtr))
    {
        follower=cursor;
            //if not the end of the word
        if (c >= 39)
        {
            index = getIndex(c);
            if (index>=0 && index<=26)
            {
            //if the letter doesn't exist create a new node
                if (cursor -> children[index] == NULL)
                {
                    cursor->children[index] = malloc(sizeof(node));
                    cursor -> children[index] = createNode(cursor -> children[index]);
                }

                   //continue to the next child
                    cursor = cursor -> children[index];

            }
        }
        else //if it is the end of the word
        {
            cursor->isWord = true;
            cursor = head;
            wordCount++;
        }
    }
    fclose(dictPtr);
    return true;
}

//Return index of a character
int getIndex(char c)
{
    if (c == '\'')
        return 26;
    else if (c >= 'a' && c <= 'z')
        return c - 'a';
    else
        return c - 'A';
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    cursor=head;
    unloadHelper(cursor);
    return true;
}

void unloadHelper(node *pointer)
{
    for( int i=0; i<27; i++)
   {
        if(pointer->children[i] != NULL)
        {
             unloadHelper(pointer->children[i]);
        }
   }
   free(pointer);
}

//Returns pointer to the initial value of the list
node* createNode(node *newNode)
{

   for (int i = 0; i < 27; i++)
    {
        newNode->children[i] = NULL;
    }
   return newNode;
}