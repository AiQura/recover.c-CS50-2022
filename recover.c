#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // to check  if the user put more than 1 input
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }
    // to check if the user put correct file
    FILE *openedFile = fopen(argv[1], "r");
    if (openedFile == NULL)
    {
        printf("file can not be opened please check the file name and type");
        return 1;
    }

    unsigned char *readBuffer = malloc(512 * sizeof(char));
    // unsigned char readBuffer[512];
    char *filename = malloc(8 * sizeof(char));
    int fileCounter = 0;
    FILE *img = NULL;

    while (fread(readBuffer, 512,sizeof(char),  openedFile)==1)
    {
        // BYTE buffer[] = malloc(512 * sizeof(BYTE));
        // long readFile = fread(buffer, 512, 1, *f);
        //to check the start of a photo
        if (readBuffer[0] == 0xff && readBuffer[1] == 0xd8 && readBuffer[2] == 0xff && (readBuffer[3] & 0xf0) == 0xe0)
        {
            if (!(fileCounter == 0))
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", fileCounter);
            img = fopen(filename, "w");
            fileCounter++;
        }
        if (!(fileCounter == 0))
        {
            fwrite(readBuffer, 512, sizeof(char), img);
        }
    }
    fclose(img);
    fclose(openedFile);
    free(filename);
    free(readBuffer);
    return 0;
}
