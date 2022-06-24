#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long main_l;
    long check_length;
    int length = 0;

    //Gets Input
    main_l = get_long("Input: ");
    check_length = main_l;

    //Checks to see if length is good
    while (check_length != 0)
    {
        length += 1;
        check_length /= 10;
    }
    if (length != 16 && length != 15 && length != 13)
    {
        printf("INVALID\n");
        exit(0);
    }

    //Main variables
    int card_man_num = 0;
    long l2 = main_l;
    int temp_sum1 = 0;
    int temp_sum2 = 0;

    int digit = 0;
    bool isVisa = false;
    for (int i = 0; i < length; i++)
    {
        digit = l2 % 10;
        l2 = l2 / 10;

        //Check for first 2 digits.
        if (length - i == 2)
        {
            card_man_num += digit;
        }
        if (length - i == 1)
        {
            if (digit == 4)
            {
                isVisa = true;
            }
            card_man_num += digit * 10;
        }

        if (i % 2 == 0)
        {
            temp_sum2 += digit;
        }
        else
        {
            digit = digit * 2;
            if (digit  >= 10)
            {
                temp_sum1 += digit % 10;
                temp_sum1 += 1;
            }
            else
            {
                temp_sum1 += (digit);
            }

        }
    }

    if ((temp_sum1 + temp_sum2) % 10 != 0)
    {

        printf("INVALID\n");
        exit(0);
    }

    if (isVisa)
    {
        printf("VISA\n");
        exit(0);
    }

    //For checking what card manufac.
    switch (card_man_num)
    {
        case (34):
            printf("AMEX\n");
            break;
        case (37):
            printf("AMEX\n");
            break;
        case (51):
            printf("MASTERCARD\n");
            break;
        case (52):
            printf("MASTERCARD\n");
            break;
        case (53):
            printf("MASTERCARD\n");
            break;
        case (54):
            printf("MASTERCARD\n");
            break;
        case (55):
            printf("MASTERCARD\n");
            break;

        default:
            printf("INVALID\n");
            break;
    }
}