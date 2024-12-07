#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

float similar_text(char word1[], char word2[]);

int main(void)
{
    FILE *filePtr;
    char fileText[100];
    char inputText[100];
    float mainConf = 0.0f;
    char predictionWord[101];

    filePtr = fopen("../word.txt", "r");

    if (NULL == filePtr) {
        printf("Dosya açılamadı.\n");
        return EXIT_FAILURE;
    }

    printf("Search:");
    scanf("%s", inputText);

    while (fscanf(filePtr, "%s", fileText) != EOF)
    {
        float conf = similar_text(inputText, fileText);

        if (conf > mainConf)
        {
            mainConf = conf;
            strcpy(predictionWord, fileText);
        }
    }

    if (mainConf != 0)
    {
        printf("Did you mean? %s %.2f\n", predictionWord, mainConf);
    }
    else
    {
        printf("No matching");
    }

    fclose(filePtr);
    return 0;
}

// word1 kullanıcı girdisi, word2 doğru kelime
float similar_text(char word1[], char word2[])
{
    for (int i = 0; i < strlen(word1); i++)
    {
        // Her bir harf için küçültme işlemi
        word1[i] = tolower(word1[i]);
    }

    float oneConf = 0.0f;
    float wordConf = 0.0f;

    if (strlen(word2) > 0) {
        // Her bir harf için conf değeri
        oneConf = 1.0 / strlen(word2); // NOLINT(*-narrowing-conversions)
    }

    for (int i = 0; i < strlen(word1); i++)
    {
        if (word1[i] == word2[i])
        {
            wordConf += oneConf;
        }
    }
    return wordConf;
}
