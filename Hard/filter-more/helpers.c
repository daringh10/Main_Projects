#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //take the average of the RGB of a pixel.
    //Set each RGB to the average

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double blue  = image[i][j].rgbtBlue;
            double red   = image[i][j].rgbtRed;
            double green = image[i][j].rgbtGreen;

            BYTE avg_color = round((red + green + blue) / (double)3);


            image[i][j].rgbtRed = avg_color;
            image[i][j].rgbtGreen = avg_color;
            image[i][j].rgbtBlue = avg_color;


        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    int right = width - 1;
    for(int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][right - j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][right - j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][right - j].rgbtBlue;

        }

    }




    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //get pixel
    //check if the neighboringnpixel is out of bounds
    //if not then add its value to the avg
    //if out of bounds then continue

    RGBTRIPLE temp[height][width];
    for(int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];
            double avg_red = 0;
            double avg_green = 0;
            double avg_blue = 0;
            double total = 0;
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if ( (i+h) < 0 || (i+h) >= height || (j+w) < 0 || (j+w) >= width)
                    {
                        continue;
                    }
                    else
                    {

                        total +=1;
                        RGBTRIPLE *temp_pixel = &temp[i+h][j+w];
                        avg_red += (*temp_pixel).rgbtRed;
                        avg_green += (*temp_pixel).rgbtGreen;
                        avg_blue += (*temp_pixel).rgbtBlue;
                    }
                }
            }

            BYTE avgR = round((avg_red) / (double)total);
            BYTE avgG = round((avg_green) / (double)total);
            BYTE avgB = round((avg_blue) / (double)total);

            (*pixel).rgbtRed = avgR;
            (*pixel).rgbtGreen = avgG;
            (*pixel).rgbtBlue = avgB;





        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    double Gx[3][3] = {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    double Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];
            double Gxavg_red = 0;
            double Gyavg_red = 0;

            double Gxavg_green = 0;
            double Gyavg_green = 0;

            double Gxavg_blue = 0;
            double Gyavg_blue = 0;
            double total = 0;
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if ((i + h) < 0 || (i + h) >= height || (j + w) < 0 || (j + w) >= width)
                    {
                        continue;
                    }
                    else
                    {
                        RGBTRIPLE *temp_pixel = &temp[i + h][j + w];
                        Gxavg_red += (*temp_pixel).rgbtRed * Gx[h + 1][w + 1];
                        Gyavg_red += (*temp_pixel).rgbtRed * Gy[h + 1][w + 1];

                        Gxavg_green += (*temp_pixel).rgbtGreen * Gx[h + 1][w + 1];
                        Gyavg_green += (*temp_pixel).rgbtGreen * Gy[h + 1][w + 1];

                        Gxavg_blue += (*temp_pixel).rgbtBlue * Gx[h + 1][w + 1];
                        Gyavg_blue += (*temp_pixel).rgbtBlue * Gy[h + 1][w + 1 ];

                    }
                }
            }


            double avgR = round(sqrt(pow(Gxavg_red, 2) + pow(Gyavg_red, 2)));
            if (avgR > 255)
            {
                avgR = 255;
            }
            double avgG = round(sqrt(pow(Gxavg_green, 2) + pow(Gyavg_green, 2)));
            if (avgG > 255)
            {
                avgG = 255;
            }
            double avgB = round(sqrt(pow(Gxavg_blue, 2) + pow(Gyavg_blue, 2)));
            if (avgB > 255)
            {
                avgB = 255;
            }


            (*pixel).rgbtRed = avgR;
            (*pixel).rgbtGreen = avgG;
            (*pixel).rgbtBlue = avgB;





        }
    }
    return;
}
