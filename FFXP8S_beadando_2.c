#include <stdio.h>
#include <ctype.h>
#include <string.h>

//gcc -W -Wall -Wextra -pedantic FFXP8S_beadando_2.c -o cprogram
//.\cprogram

char jegyekRaw[] = "Jegyek input stringje";
char sulyokRaw[] = "Sulyok input stringje";

int jegyek[300];
int sulyok[300];

int i = 0;
char seps[]   = " ,\t\n";
char *token;
int tokenInt;

int main( void )
{
    printf("Adja meg a jegyeket: ");
    fgets(jegyekRaw, sizeof(jegyekRaw), stdin);  // read jegyekRaw

    printf( "A megadott jegyek:\n" );
    token = strtok( jegyekRaw, seps );
    
    while( token != NULL )
    {
        sscanf(token, "%d", &tokenInt);
        if(tokenInt > 0 && tokenInt <6)
        {
            printf( " %d\n", tokenInt );
            jegyek[i] = tokenInt;
            token = strtok( NULL, seps );
            i++;
        }
        else{
            printf( "Hibas bemenet mellozese! (%s)\n", token );
        }
    }
    printf("%d\n", jegyek[3]);


    printf("Adja meg a jegyekhez tartozo sulyokat: ");
    fgets(sulyokRaw, sizeof(sulyokRaw), stdin);  // read sulyokRaw

    printf( "A megadott sulyok:\n" );
    token = strtok( sulyokRaw, seps );
    while( token != NULL )
    {
        printf( " %s ", token );
        token = strtok( NULL, seps );
    }

}