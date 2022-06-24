#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }
    string key = argv[1];
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }

    //got duplicate code from stackoverflow
    //source https://stackoverflow.com/questions/8199403/how-to-check-if-an-array-has-any-duplicates
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            exit(1);
        }
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                exit(1);
            }
        }
    }




    string p = get_string("plaintext: ");
    char c[strlen(p)];
    strcpy(c, p);

    for (int i = 0; i < strlen(p); i++)
    {
        if (!isalpha(p[i]))
        {
            c[i] = p[i];
            continue;
        }
        bool upperCase = false;
        if (isupper(p[i]))
        {
            upperCase = true;
        }
        char temp_char = tolower(p[i]);

        char letter = key[temp_char - 97];
        if (upperCase)
        {
            letter = toupper(letter);
        }
        else
        {
            letter = tolower(letter);
        }
        c[i] = letter;

    }

    printf("ciphertext: %s\n", c);



}