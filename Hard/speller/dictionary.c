// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 11881376;
const unsigned int factor1 = 456976;
const unsigned int factor2 = 17576;
const unsigned int factor3 = 676;
const unsigned int factor4 = 26;


//global for size;
int size_of_dict = 0;
bool loaded = false;
char dict_name[LENGTH];


// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

        node *temp = table[hash(word)];
        while(temp!=NULL)
        {
            if (strcasecmp(temp->word,word) == 0)
            {
                return true;
            }
            temp = temp->next;
        }

    return false;
}

//Ex: acorn
//Hash function:
// toupper -> ACE -> [65,67,69]
// (17576 * word[0] - 65) + word[1] + word[2] + word[3]

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if(strlen(word) == 1)
    {
        return (factor1 * (toupper(word[0]) - 'A'));
    }
    else if (strlen(word) == 2)
    {
        return (factor1 * (toupper(word[0]) - 'A')) + ( factor2 * (toupper(word[1]) - 'A'));
    }
    else if (strlen(word) == 3)
    {
        return (factor1 * (toupper(word[0]) - 'A')) + ( factor2 * (toupper(word[1]) - 'A')) + ( factor3 * (toupper(word[2]) - 'A'));
    }
    else if (strlen(word) == 4)
    {
         return (factor1 * (toupper(word[0]) - 'A')) + ( factor2 * (toupper(word[1]) - 'A')) + ( factor3 * (toupper(word[2]) - 'A')) + (factor4 * toupper(word[3]) - 'A');
    }

    else if (strlen(word) >= 5)
    {
         return (factor1 * (toupper(word[0]) - 'A')) + ( factor2 * (toupper(word[1]) - 'A')) + ( factor3 * (toupper(word[2]) - 'A')) + (factor4 * toupper(word[3]) - 'A') + (toupper(word[4]) - 'A');
    }


    return 0;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    strcpy(dict_name,dictionary);
    FILE *file;
    file = fopen(dictionary,"r");
    char str[LENGTH + 1];
    while (fscanf(file, "%s", str) != EOF)
    {
        size_of_dict +=1;
        node *n = malloc(sizeof(node));

        strcpy(n->word,str);
        n->next = NULL;

        unsigned int bucket = hash(n->word);
        //printf("wordlen: %lu  Word:%s  Bucket:%d\n",strlen(str),n->word,bucket);

        if(table[bucket] != NULL)
        {
            node *temp = table[bucket];
            while(temp->next!= NULL)
            {
                temp = temp->next;
            }
            temp->next = n;
        }
        else
        {
            table[bucket] = n;
        }


    }

    fclose(file);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(loaded)
    {
        return size_of_dict;
    }
    return 0;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    node *temp1 = NULL;
    node *temp2 = NULL;
    for (int i = 0; i < N; i++)
    {
        temp2 = table[i];
        while (temp2 != NULL)
        {
            temp1 = temp2;
            temp2 = temp2->next;
            free(temp1);
        }
    }
    return true;
}
