#include <cs50.h>
#include <stdio.h>

int main(void)
{
     //Prompts uer to input the height for the pyramid
    int height = 0;
    while(height <= 0 || height >= 9){
        printf("Height: ");
        scanf("%d",&height);
    }




    //This variable represents the amount of space characters to
    //Create on each level of the pyramid.
    int space_dist = height - 1;


    for(int j = 0; j < height;j++){

        //This variable represents the amount of hashtags to print
        //On each level. Inverse relation with the amount of spaces
        int hash_dist = height - space_dist;

        //Prints the spaces
        for(int i = 0; i < space_dist;i++){
            printf(" ");
        }

        //Prints the hashtags
        for(int i = 0; i < hash_dist;i++){
            printf("#");
        }

        //Space for the middle.
        printf("  ");

        //Prints the other side's hashtags.
        //We dont have to print spaces
        for(int i = 0; i < hash_dist;i++){
            printf("#");
        }
        printf("\n");


        //Less spaces as the pyramid goes down.
        space_dist -=1;
    }


}