#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
      printf("Could not open file\n");
      return 1;
    }

    BYTE buffer[512];

    int countImage = 0;

    FILE *output = NULL;

    // char型で8メモリを確保
    char *filename = malloc(8 * sizeof(char));

    // 512バイト分読み取る
    while (fread(buffer, sizeof(char), 512, input))
    {
      // バイトの開始がJPEGかどうかチェック
      if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
      {
        // ファイル名を作成
        snprintf(filename, 8, "%03i.jpg", countImage);

        output = fopen(filename, "w");

        countImage ++;
      }

      if (output != NULL)
      {
        fwrite(buffer, sizeof(char), 512, output);
      }
    }

    // mallocに割り当てたメモリを解放
    free(filename);
    // すべてのファイルを閉じる
    if(output != NULL)
    {
      fclose(output);
    }
    fclose(input);

    return 0;
}
