// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tester.h"
void isTrue(bool test);
void showValue(char test);

node *head;
int wordCount=0;
int main(void)
{
   head=malloc(sizeof(node));
    createNode(head);

    node *spice=malloc(sizeof(node));
    spice->letter='B';

    printf("%i\n",wordCount);

    isTrue(spice->isWord);
    showValue(head->letter);
    showValue(spice->letter);

}
void showValue(char test)
{
    if (test)
    {
        printf("this is your number: %c\n", test);
    }
    else
    {
        printf("No value\n");
    }
}
void isTrue(bool test)
{
    if (test)
    {
        printf("It is true\n");
    }
    else
    {
        printf("it is false\n");
    }
}
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //a place holder the trie is being traversed
   node *cursor;
   cursor=head;
   //the node to be added upon traversing the trie


   //each indicie corresponds to a letter in the alphabet and '
    int index;

    FILE *dictPtr = fopen(dictionary,"r");
    if (!dictPtr)
    {
        fprintf(stderr, "File does not exist!\n");
        return false;
    }
   //for every dictionary word iterate through the trie
    for (char c = fgetc(dictPtr); c!=EOF; c = fgetc(dictPtr))
    {
        //if not the end of the word
        if (c != '\n')
        {
            index = getIndex(c);
            //if the letter doesn't exist create a new node
            if (cursor -> children[index] == NULL)
            {
                createNode(cursor -> children[index]);
                cursor=cursor -> children[index];
            }
            else    //continue to the next child
            {
                cursor = cursor -> children[index];
            }
        }
        else //if it is the end of the word
        {
            cursor->isWord=true;
            cursor = head;
            wordCount++;
        }
    }
    return false;
}

//Return index of a character
int getIndex(char c)
{
    if (c == '\'')
        return 26;
    else if (c >= 'a' && c <= 'z')
        return c - 'a';
    else if (c >='A' && c<= 'Z')
        return c - 'A';
    //if non alphabetical character
    return -1;
}

void unloadHelper(node *pointer[])
{
    for( int i=0; i<27; i++)
    {
        if(pointer[i] != NULL)
        unloadHelper(pointer[i]->children);
    }
}

//Returns pointer to the initial value of the list
void createNode(node *cursor)
{
    node *pointer;
    pointer=malloc(sizeof(node));
    node newNode;
    pointer=&newNode;
    pointer->isWord = true;
    pointer->letter='A';
    for (int i = 0; i < 27; i++)
    {
        pointer->children[i] = NULL;
    }
    *cursor=*pointer;
}
