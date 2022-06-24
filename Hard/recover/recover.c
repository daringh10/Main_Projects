#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <cs50.h>
//open raw file
//iterate through each 512 block,
//if it starts with jpeg stuff then new imamge
//else its a cont of last image


#define BLOCK_SIZE 512


typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r"); //open the card.raw
    if (raw_file == NULL)
    {
        return 1;
    }
    BYTE buffer[BLOCK_SIZE]; // buffer to read in 512 bytes at a time from card.raw
    bool isNewJPEG = false;
    bool inImage = false;
    int count = -1;
    FILE *img;
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //Checks first 3 bits to see if JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            //Checks 4th bit to see if last 4 bits are eq to 0xe
            if ((buffer[3] >> 4) & 0xe)
            {
                //Is JPEG
                count += 1; // count for jpg number
                inImage = true;
                isNewJPEG = true;

            }

        }

        if (inImage)
        {
            //If it is a JPEG
            if (isNewJPEG)
            {
                char *filename = malloc(4); //Set 4 bytes for file name
                sprintf(filename, "%03i.jpg", count); //Creata a custom string
                img = fopen(filename, "w"); //create the jpg

                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img); //write 512 "bytes" into img from buffer
                isNewJPEG = false;
            }

            else
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }

    }
    fclose(raw_file);
    fclose(img);
}