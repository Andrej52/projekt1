/*
  Kostra programu pre 1.projekt IZP 2023/24

  Program hladajúci mestá z databáze pre navigačný systém
  login: xmrazi01   Andrej Mrázik
*/

#define MAX_LENGTH 100
#include <stdio.h>
#include <string.h>
#include <stdbool.h> 

// vracia pôvodný string bez \n (endline) znaku
char *remove_endline(char string[])
{
    int stringLen= strlen(string);
    if (string[stringLen - 1] == 32 || string[stringLen - 1] == 10 )
    {
        string[stringLen - 1] = 0;   
    }
    return string;
}

// vracia  velke pismena na male, ignoruje ostatne znaky
char* to_upper(char input[],char output[])
{
    for (unsigned int i = 0; i < MAX_LENGTH; i++)
    {
        output[i] = 0;
        if (input[i] >= 65 + 32 && input[i] <= 90 +32 )
        {
            output[i]  = input[i] - 32; 
        }
        else
        {
            output[i]  = input[i];  
        }
    }
    return 0;
}

// validacia dat
// overuje či je dlzka max
// overuje aj ci znaky nie su whitespaces
bool data_valid(char input[])
{
    int len = strlen(input);
    if (len > 100) return false;
    for (int i = 0; i < len; i++)
    {
        if ((!(input[i] >= 32 && input[i] <= 126)) && (input[0]== '\n' || input[0] == ' '))  return false; 
    }
    return true;
}

// vracia najdenu zhodu vstupu a riadku
// hlada zhodu vstupu s adresou ako substr
bool found_addres(char input[], char line[])
{
    int len = strlen(input);

    for (int i = 0; i <len ; i++)
    {
        if (input[i] != line[i]) return false;  
    }
    return true;
}

// return value je  sorted enable
// usporiadava znaky ENABLE vystupu
char* sort_en(char enable[])
{
    int len = strlen(enable);
    for (int i = 0; i < len- 1; i++) 
    {
        for (int j = i + 1; j < len; j++) 
        {
            if (enable[i] > enable[j]) 
            {
                char temp = enable[i];
                enable[i] = enable[j];
                enable[j] = temp;   
            }
        }
    }
return enable;
}

// navratova hodnota ENABLE je bez duplikatov znakov 
// odstranuje duplikaty a vracia sorted ENABLE
char *enable_chars(char enable[])
{
    int len = strlen(enable);
 
	for (int i = 0; i < len; i++)
	{
		for(int j = i + 1; j < len; j++)
		{
    		if(enable[i] == enable[j])
    		{
    			for(int k = j; k < len; k++)
    			{
    				enable[k] = enable[k + 1];  
				}
                len--;
				j--;
			}
		}
	}
    char *output = sort_en(enable);
    return output; 
}

// MAIN
int main(int argc, char*argv[]) 
{
    if (argc < 1)
    {
        printf("without arguments \n");
        return -1;
    }

    if (argv[1] == NULL) argv[1] =  "";

    char line[MAX_LENGTH+1] ={};
    char enableChars[MAX_LENGTH] = {};
    char loweredString[MAX_LENGTH+1] = {};
    char loweredArgv[MAX_LENGTH+1] = {};
    char foundcity[MAX_LENGTH+1]= {};
    int cnt = 0;

    to_upper(argv[1],loweredArgv);     
 
    while(fgets(line, sizeof(line), stdin) != NULL)
    {
        if (!data_valid(line))
        {
            printf("line in list of Cities are invalid format \n");
            return -1;
        }

        remove_endline(line);
        to_upper(line,loweredString);

        if (!found_addres(loweredArgv, loweredString))continue;
        
        enableChars[cnt++] = loweredString[strlen(loweredArgv)];

        if (strlen(loweredArgv) == strlen(loweredString))
        {
            strcpy(foundcity,line);
            cnt = 1;
            break;
        }
        if (strlen(enableChars) < 2)
        {
           strcpy(foundcity,line);
        }
    }

    // vypis  vysledkov
    if (cnt > 1)
    {
        printf("Enable: %s\n",enable_chars(enableChars));
    }
    else if (cnt == 1)
    {
        printf("Found: %s\n",foundcity);
    }
    else
    {
        printf("Not found\n"); 
    }
    return 0;
}
