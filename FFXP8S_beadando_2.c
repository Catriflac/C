#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//gcc -W -Wall -Wextra -pedantic FFXP8S_beadando_2.c -o cprogram
//.\cprogram

char jegyekRaw[300] = "Jegyek input stringje";
char sulyokRaw[300] = "Sulyok input stringje";

int jegyek[100];
int sulyok[100];

char seps[]   = " ,\t\n";
char *token;
int tokenInt;

int isNumber(char token[]);


int main()
{
    printf("Adja meg a jegyeket: ");
    fgets(jegyekRaw, sizeof(jegyekRaw), stdin);  // read jegyekRaw

    token = strtok( jegyekRaw, seps );
    int i = 0;
    int counter = 0;
    while( token != NULL )
    {
        counter++;
        sscanf(token, "%d", &tokenInt);
        if( isNumber(token)  && tokenInt < 6 && tokenInt > 0 )
        {
            //printf( "%d ", tokenInt );
            jegyek[i] = tokenInt;
            token = strtok( NULL, seps );
            i++;
        }
        else{
            printf( "Hibas bemenet mellozese! (%s)\n", token );
            token = strtok( NULL, seps );
            i++;
            counter--;
        }
    }

    printf( "A megadott jegyek:\n" );    
    for (int j = 0; j < i; j++){
        if(jegyek[j] != 0)
        {
            printf("%d ", jegyek[j]);   
        }  
    }
    printf("\n%d", counter);

    return counter;
}

int isNumber(char token[])
{
    for (int i = 0; token[i]!= '\0'; i++)
    {
        if(strstr(token, "."))
            {
            printf("Valos bemenet! Tort resz eldobasa!\n");
            return token[i];
            }
            
        if (isdigit(token[i]) == 0)
            return 0;
    }
    return 1;
}
