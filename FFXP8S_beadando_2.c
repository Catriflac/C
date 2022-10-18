#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//gcc -W -Wall -Wextra -pedantic FFXP8S_beadando_2.c -o cprogram
//.\cprogram

//Globális tömbök deklarálása
char jegyekRaw[300] = "Jegyek input stringje";
char sulyokRaw[300] = "Sulyok input stringje";
int jegyek[100];
int sulyok[100];

//Globális változók deklarálása
char seps[]   = " ,\t\n";
char *token;
int tokenInt;
int counter1 = 0; int counter2 = 0; int erdemjegy = 1;
bool error;

//Modulok deklarálása
int isNumber(char token[]);
int jegyKezelo();
int sulyKezelo();
int jegySzamlalo(int erdemjegy);
int kalauz();

//MAIN
int main()
{
    do
    {
        printf("Adja meg a jegyeket: ");
        fgets(jegyekRaw, sizeof(jegyekRaw), stdin);  //jegyek beolvasása jegyekRaw-ba
        jegyKezelo();

        printf("Adja meg a sulyokat: ");
        fgets(sulyokRaw, sizeof(sulyokRaw), stdin);  //súlyok beolvasása sulyokRaw-ba
        sulyKezelo();
        
        kalauz();

    } while (error == (true));   //amíg a kalauz() el nem fogadja (megegyező bevitt darabszámok esetén)

        printf("Egyes erdemjegyek darabszama a megadott sorozatban:\n");
        for(erdemjegy=1; erdemjegy <= 5; erdemjegy++)
        {
            jegySzamlalo(erdemjegy);
        }
    
}

//A jegyKezelo() és sulyKezelo() modul formailag nagyon hasonlít, de az eltérő feltételek, bemeneti értékek és ellenőrzés miatt indokolt külön kezelni
//Érdemjegyek beolvasása
int jegyKezelo()
{
    //string tördelése tokenekre ciklusban
    token = strtok( jegyekRaw, seps );  //kezdeti tokenérték
    int i = 0;  //összes feldolgozott token száma
    counter1 = 0;   //elfogadott érdemjegyek darabszáma
    while( token != NULL )
    {
        
        sscanf(token, "%d", &tokenInt);
        if( isNumber(token)  && tokenInt < 6 && tokenInt > 0 )
        {
            jegyek[i] = tokenInt;
            token = strtok( NULL, seps );
            counter1++;
        }
        else{
            printf( "Hibas bemenet mellozese! (%s)\n", token );
            token = strtok( NULL, seps );
        }
        i++;
    }

    //Elfogadott értékek kiírása
    printf( "A megadott jegyek: " );    
    for (int j = 0; j < i; j++){
        if(jegyek[j] != 0)
        {
            printf("%d ", jegyek[j]);   
        }  
    }
    printf("\n");
    return counter1; 
}

//Súlyok beolvasása
int sulyKezelo()
{
    //string tördelése tokenekre ciklusban
    token = strtok( sulyokRaw, seps );  //kezdeti tokenérték
    int i = 0;  //összes feldolgozott token száma
    counter2 = 0;   //elfogadott súlyértékek darabszáma
    while( token != NULL )
    {
        
        sscanf(token, "%d", &tokenInt);
        if( isNumber(token)  && tokenInt < 10 && tokenInt > 0 )
        {
            sulyok[i] = tokenInt;
            token = strtok( NULL, seps );
            counter2++;
        }
        else{
            printf( "Hibas bemenet mellozese! (%s)\n", token );
            token = strtok( NULL, seps );
            
        }
        i++;
    }

    //Elfogadott értékek kiírása
    printf( "A megadott sulyok:\n" );    
    for (int j = 0; j < i; j++){
        if(sulyok[j] != 0)
        {
            printf("%d ", sulyok[j]);   
        }  
    }
    printf("\n");
    return counter2;
}

//Bevitt értékek típusos ellenőrzése és hibaelhárítás
int isNumber(char token[])
{
    for (int i = 0; token[i]!= '\0'; i++)
    {
        if(strstr(token, "."))  //ha a token pontot tartalmaz, feltételezzük, hogy valós szám
            {
            printf("Valos bemenet! Tort resz eldobasa!\n");
            return token[i];    //törtrészt eldobjuk
            }
            
        if (isdigit(token[i]) == 0) //ha a token értéke integer...
            return 0;
    }
    return 1;
}

//A "jegykezelő" már fogalt volt. Bevitt jegyek és súlyok darabszámának összehasonlítása
int kalauz()
{
    error = (false);
    if(counter1 != counter2)    //sulyKezelo() és jegyKezelo() return értéke
    {
        printf("Hiba! A jegyek es megadott sulyok darabszama nem egyezik!\n");
        error = (true);
        return 1;
    }
    return 0;
}

//Egyes érdemjegyek megszámlálása
int jegySzamlalo(int erdemjegy)
{
    //Csak egy érdemjegyet számol, ciklusban kell futtatni (erdemjegy = 1..5)
    int jegyCounter = 0;
    size_t N = sizeof(jegyek)/sizeof(jegyek[0]);
    for(int i = 0; (unsigned)i <= N; i++)
    {
        if(jegyek[i] == erdemjegy)
            jegyCounter++;
    }
    printf("%d: %d\n", erdemjegy, jegyCounter);
    return jegyCounter;
}
