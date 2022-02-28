// Hexdump.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#include "hexdump.h"


int main(int argc, char* argv[])
{
    int pathEnd, temp;
    const char* possibleArguments[] = { RAM, LINE, OUT };
    int argumentsLen = 2;
    char newpath[120];
    int lineDelimiter = VALUES_INLINE;
    /* For Every Byte in 'printBuffer' there are 2 bytes of hexadecimal digits
    and 1 space, and every given amount a NEWLINE and Another 1 for NULL TERMINATOR*/
    //char actualPrintBuffer[PRINT_BUFFER_SIZE*3 + PRINT_BUFFER_SIZE / VALUES_INLINE + 1];
    int printBufferSize = PRINT_BUFFER_SIZE;
    char* printBuffer = NULL;
    char* actualPrintBuffer = NULL;
    size_t bytesRead;

    /* If No Arguments were given*/
    if (argc == 1)
    {
        printf("%s", NO_ARGUMENTS_TEXT);
        exit(1);
    }
    /* If Only 1 Arguments is given*/
    if (argc == 2)
    {
        /* Check if first argument given is "-help"*/
        if (strcmp(argv[1], HELP) == 0)
        {
            printf("%s", HELP_TEXT);
            exit(1);
        }
        else if (!argv[1][0] == '"' && !argv[1][strlen(argv[1]) - 1] == '"')
        {
            printf("%s", SYNTAX_WRONG);
            exit(1);
        }
    }

    /*find where path is located*/
    if ((pathEnd = indexFirstArgument(argv, argc, possibleArguments, argumentsLen)) == -1)
    {
        pathEnd = argc - 1;
    }
    else
        pathEnd--;

    /* Retrive File Descriptor After Connecting Arguments Into One Path*/
    FILE* fp = fopen(getPath(argv, 1, pathEnd, newpath), "rb");

 //   printf("%s\n", strerror(errno));
    /* OPEN FILE, HANDLE ERRORS */
    if (fp == NULL)
    {
        printf("Error Opening File! (%s)\n", newpath);
        exit(1);
    }

    /* GET ARGUMENTS */
    temp = indexFirstArgument(argv, argc, possibleArguments, argumentsLen);
    while (temp != -1)
    {
        if (strcmp(argv[temp], LINE) == 0)
        {
            if (isNumericString(argv[temp + 1]) == FALSE)
            {
                printf("%s", ARGUMENT_WRONG_TEXT);
                exit(1);
            }
            lineDelimiter = atoi(argv[temp + 1]);
        }

        if (strcmp(argv[temp], RAM) == 0)
        {
            if (isNumericString(argv[temp + 1]) == 0)
            {
                printf("%s", ARGUMENT_WRONG_TEXT);
                exit(1);
            }
            printBufferSize = atoi(argv[temp + 1]);
        }
        if (indexFirstArgument(argv + temp, argc - temp, possibleArguments, argumentsLen) == -1)
            temp = -1;
        else
            temp += indexFirstArgument(argv + temp, argc - temp, possibleArguments, argumentsLen);
    }

    /* Allocate Memory For Print Buffer*/
    allocate((void**)&printBuffer, printBufferSize * sizeof(char));
    allocate((void**)&actualPrintBuffer, printBufferSize * sizeof(char) * 5);




    while (!feof(fp))
    {
        bytesRead = fread(printBuffer, sizeof(char), printBufferSize - printBufferSize % lineDelimiter, fp);
        printf("%s", hexform(printBuffer, bytesRead, actualPrintBuffer, lineDelimiter));
    }

    printf("\n");
    return 0;
}


int indexFirstArgument(char* argv[], int argc, const char* possibleArguments[], int argumentsLen)
{
    int i, j;
    if (argc == 1)
        return -1;
    else
    {
        for (i = 1; i < argc; i++)
        {
            if (i + 1 < argc) {
                for (j = 0; j < argumentsLen; j++)
                    if (strcmp(argv[i], possibleArguments[j]) == 0) return i;
            }
        }
        return -1;
    }
}

char* getPath(char* argv[], int start, int end, char* dest)
{
    int index;
    int strindex = 0;

    for (index = start; index <= end; index++)
    {
        strcpy(dest + strindex, argv[index]);
        strindex += strlen(argv[index]);
        if (index + 1 <= end)
        {
            dest[strindex] = ' ';
            strindex++;
        }
    }
    dest[strindex] = '\0';
    return dest;
}

char* hexform(char buffer[], int bytesRead, char dest[], int lineDelimiter)
{
    int i, j, bytesPrinted = 0;
    for (i = 0, j = 0; i < bytesRead; i++)
    {
        sprintf(dest + j, "%02X ", buffer[i]);
        j += 3;
        bytesPrinted++;
        if (bytesPrinted % lineDelimiter == 0)
        {
            sprintf(dest + j, "\n");
            j += 1;
        }
    }
    sprintf(dest + j, "\0");
    return dest;
}

int getLineDelimeter(char* argv[], int argc, int* lineDelimeter)
{
    int i, j;
    int returnValue = DEFAULT;
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], LINE) == 0)
        {
            if (i + 1 < argc)
            {
                if (isAlphaString(argv[i + 1]))
                {
                    *lineDelimeter = atoi(argv[i + 1]);
                    return i;
                }
            }
        }
    }
}

int isAlphaString(char* str)
{
    int i;
    int isAlpha = TRUE;
    for (i = 0; i < strlen(str); i++)
        isAlpha = isalpha(str[i]) && TRUE;
    return isAlpha;
}

int isNumericString(char* str)
{
    int i;
    int isNumeric = TRUE;
    for (i = 0; i < strlen(str); i++)
        isNumeric = isdigit(str[i]) && TRUE;
    return isNumeric;
}

void allocate(void** dest, int bytes)
{
    *dest = malloc(bytes);
    if (*dest == NULL)
    {
        printf("%s", MEMORY_ALLOCATION_FAILED);
        exit(1);
    }
}

void allocate(void** dest, int numberOfElements, int SizeInBytes)
{
    *dest = calloc(numberOfElements, SizeInBytes);
    if (*dest == NULL)
    {
        printf("%s", MEMORY_ALLOCATION_FAILED);
        exit(1);
    }
}