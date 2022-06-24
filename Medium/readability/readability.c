#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1 ;
        }
    }

    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            words += 1;
        }
    }
    words += 1;

    return words;
}

int count_sentences(string text)
{
    int s = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            s += 1;
        }
    }


    return s;
}
//read each word and on each word:
//add strlen(word) to letters.
//when a period is seen, then S +=1;
int main(void)
{
    double L = 0;
    double S = 0;
    double W = 0;

    string text = get_string("Text: ");
    L = count_letters(text);



    W = count_words(text);



    S = count_sentences(text);



    L = (L / W) * 100;
    S = (S / W) * 100;

    double index = 0.0588 * L - 0.296 * S - 15.8;
    int i = floor(round(index));

    if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (i >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (i));
    }

}

