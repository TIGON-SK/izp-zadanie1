// gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter
//./keyfilter
// test:./test_keyfilter.sh
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_CITY_COUNT 42
#define MAX_CITY_NAME_LEN 101

void appendChar(char *str, char newChar)
{
    int len = strlen(str);
    str[len] = newChar;
    str[len + 1] = '\0';
}
char *trim(char *s)
{
    char *ptr;
    if (!s)
        return NULL; // handle NULL string
    if (!*s)
        return s; // handle empty string
    for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr)
        ;
    ptr[1] = '\0';
    return s;
}

int containsAlphabetic(const char *str)
{
    while (*str)
    {
        if (isalpha(*str))
        {
            return 1;
        }
        str++;
    }
    return 0;
}
void bubbleSort(char *str)
{
    int length = strlen(str);
    int i, j;
    char temp;

    for (i = 0; i < length - 1; i++)
    {
        for (j = 0; j < length - i - 1; j++)
        {
            if (str[j] > str[j + 1])
            {
                // Swap characters
                temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    char addresses[MAX_CITY_COUNT][MAX_CITY_NAME_LEN];

    for (int i = 2; i < argc; i++)
    {
        strcat(argv[1], argv[i]);
        strcat(argv[1], " ");
    }

    int cityCount = 0;
    while (scanf("%101[^\n]\n", addresses[cityCount]) != EOF)
    {
        cityCount++;
    }

    fprintf(stderr, "Addresses[0]= %s\n", addresses[0]);

    // CONVERT ADDRESSES TO UPPERCASE
    for (int i = 0; i < cityCount; i++)
    {
        for (int j = 0; j < (int)strlen(addresses[i]); j++)
        {
            addresses[i][j] = toupper(addresses[i][j]);
        }
    }

    char possibleResult[MAX_CITY_NAME_LEN] = {};
    // IF NO ARGUMENT PASSED
    if (argc == 1)
    {
        for (int k = 0; k < cityCount; k++)
        {
            int tempCount = 0;
            for (int j = 0; j < (int)strlen(possibleResult); j++)
            {
                // CHECK IF LETTER ALREADY IN POSSIBLE RESULT
                if (possibleResult[j] == addresses[k][0])
                {
                    tempCount++;
                }
            }
            // ADDING LETTER TO POSSIBLE RESULT
            if (tempCount < 1)
            {
                appendChar(possibleResult, addresses[k][0]);
            }
        }
        bubbleSort(possibleResult);
        printf("Enable: %s", possibleResult);
        exit(0);
    }

    int inputLength = (int)strlen(argv[1]);
    // CHANGE USE INPUT TO UPPERCASE
    for (int i = 0; i < inputLength; i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    };

    int notFound = 0;
    int currentPosision = 0;
    int count = 0;
    for (int i = 0; i < cityCount; i++)
    {

        if (strcmp(trim(addresses[i]), trim(argv[1])) == 0)
        {
            printf("Found: %s", argv[1]);
            exit(0);
        }
        else
        {
        }
    }

    for (int i = 0; i < cityCount; i++)
    {
        count = 0;
        currentPosision = 0;
        notFound = 0;
        while (count < (int)strlen(argv[1]))
        {
            if (currentPosision == (int)strlen(argv[1]))
            {

                break;
            }
            if (argv[1][currentPosision] == addresses[i][currentPosision])
            {

                currentPosision++;
            }
            else
            {
                notFound++;
                break;
            }
            count++;
        }

        if (notFound == 0 && addresses[i][currentPosision] != '\0')
        {
            int countOfLetters = 0;
            for (int h = 0; h < inputLength; h++)
            {
                if (possibleResult[h] == addresses[i][currentPosision])
                {
                    countOfLetters++;
                }
            }
            if (countOfLetters == 0)
            {
                appendChar(possibleResult, addresses[i][currentPosision]);
            }
        }
    }

    if (possibleResult[0] == '\0' && notFound == 1)
    {
        printf("Not found\n");
        exit(0);
    }
    bubbleSort(possibleResult);
    printf("Enable: %s", possibleResult);

    return 0;
}
