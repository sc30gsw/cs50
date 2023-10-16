#include "helpers.h"
#include "math.h"

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            int average = round((red + green + blue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width / 2; j ++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    // 各ピクセルをoriginalにコピー
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            original[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int redValue = 0;
            int greenValue = 0;
            int blueValue = 0;
            int pxCount = 0;

            // 各ピクセルに対する3☓3のグリッドをループ
            for (int k = -1; k <= 1; k ++)
            {
                for (int l = -1; l <= 1; l ++)
                {
                    int newI = i +k;
                    int newJ = j +l;

                    // 新しいピクセルの位置が有効かどうかをチェック
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        redValue += original[newI][newJ].rgbtRed;
                        greenValue += original[newI][newJ].rgbtGreen;
                        blueValue += original[newI][newJ].rgbtBlue;
                        pxCount ++;
                    }
                }
            }
        
        // ピクセルの色を近くのピクセルの平均とする
        image[i][j].rgbtRed = round((float) redValue / pxCount);
        image[i][j].rgbtGreen = round((float) greenValue / pxCount);
        image[i][j].rgbtBlue = round((float) blueValue / pxCount);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    // 各ピクセルをoriginalにコピー
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            original[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // 各ピクセルに対する3☓3のグリッドをループ
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int gxRed = 0;
            int gxGreen = 0;
            int gxBlue = 0;

            int gyRed = 0;
            int gyGreen = 0;
            int gyBlue = 0;

            for (int k = -1; k <= 1; k ++)
            {
                for (int l = -1; l <= 1; l ++)
                {
                    int newI = i + k;
                    int newJ = j + l;

                    // 新しいピクセルの位置が有効かどうかをチェック
                    if (newI < 0 || newI >= height || newJ < 0 || newJ >= width)
                    {
                        continue;
                    }

                    gxRed += original[newI][newJ].rgbtRed * gx[k + 1][l + 1];
                    gxGreen += original[newI][newJ].rgbtGreen * gx[k + 1][l + 1];
                    gxBlue += original[newI][newJ].rgbtBlue * gx[k + 1][l + 1];

                    gyRed += original[newI][newJ].rgbtRed * gy[k + 1][l + 1];
                    gyGreen += original[newI][newJ].rgbtGreen * gy[k + 1][l + 1];
                    gyBlue += original[newI][newJ].rgbtBlue * gy[k + 1][l + 1];
                }
            }

            int red = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
            int green = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
            int blue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));

            image[i][j].rgbtRed = red > 255 ? 255 : red;
            image[i][j].rgbtGreen = green > 255 ? 255 : green;
            image[i][j].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }
    return;
}
