#include "helpers.h"
#include "math.h"

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            int sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            int sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
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
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    // 各ピクセルをoriginal二コピー
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
                    int newI = i + k;
                    int newJ = j + l;

                    // 新しいピクセルの位置が有効かどうかチェック
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
            image[i][j].rgbtRed = round((float)redValue / pxCount);
            image[i][j].rgbtGreen = round((float)greenValue / pxCount);
            image[i][j].rgbtBlue = round((float)blueValue / pxCount);
        }
    }
    return;
}
