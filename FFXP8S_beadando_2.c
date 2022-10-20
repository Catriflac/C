#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
Keszitette:
Horvath David Gyorgy
FFXP8S
2022.10.06.

Tesztelve Linux (Debian/Bunsenlabs) és Windows (Win10 64bit) rendszeren

gcc -W -Wall -Wextra -pedantic FFXP8S_beadando_1.c -o cprogram
./cprogram  <-- Linux
.\cprogram  <-- Windows
*/

//Globális tömbök deklarálása
char jegyekRaw[400] = "Jegyek input stringje"; 
char sulyokRaw[400] = "Sulyok input stringje";
//400 - ha valaki minden értéket tizedes pontossággal adna meg...
int feldolgozott [2] [100]; //feldolgozott értékek 2D tömbje

//Globális változók deklarálása
char seps[]   = " ,\t\n";
char *token;
int tokenInt;
float tokenFloat;

int counter1 = 0; int counter2 = 0; int erdemjegy = 1;
bool error;

int jegyCounter[5] = {0,0,0,0,0};   //index+1 jelöli az érdemjegyet, a tartalom pedig az előfordulást
int maxErtek;

//Modulok deklarálása
void intro();
int isNumber(char token[]);
int jegyKezelo();
int sulyKezelo();
int jegySzamlalo(int erdemjegy);
int kalauz();
int atlag();
void clrscr();

//MAIN
int main()
{
    intro();
    do
    {
        printf("Kerem, adja meg a JEGYEKET: ");
        fgets(jegyekRaw, sizeof(jegyekRaw), stdin);  //jegyek beolvasása jegyekRaw-ba
        jegyKezelo();

        printf("Kerem, adja meg a SULYOKAT: ");
        fgets(sulyokRaw, sizeof(sulyokRaw), stdin);  //súlyok beolvasása sulyokRaw-ba
        sulyKezelo();
        
        kalauz();

    } while (error == (true));   //amíg a kalauz() el nem fogadja az inputokat (megegyező bevitt darabszámok esetén)

        jegySzamlalo(erdemjegy);

        atlag();
    
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
            feldolgozott [0] [i] = tokenInt;
            token = strtok( NULL, seps );
            counter1++;
            i++;
        }
        else{
            printf( "Hibas bemenet mellozese! (%s)\n", token );
            token = strtok( NULL, seps );
        }
        
    }

    //Elfogadott értékek kiírása
    printf( "A megadott jegyek: " );    
    for (int j = 0; j < i; j++){
        if(feldolgozott [0] [j] != 0)
        {
            printf("%d ", feldolgozott [0] [j]);   
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
            feldolgozott [1] [i] = tokenInt;
            token = strtok( NULL, seps );
            counter2++;
            i++;
        }
        else{
            printf( "Hibas bemenet mellozese! (%s)\n", token );
            token = strtok( NULL, seps );
            
        }
        
    }

    //Elfogadott értékek kiírása
    printf( "A megadott sulyok:\n" );    
    for (int j = 0; j < i; j++){
        if(feldolgozott [1] [j] != 0)
        {
            printf("%d ", feldolgozott [1] [j]);   
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
            sscanf(token, "%f", &tokenFloat);
            tokenInt = tokenFloat+0.5;    
            printf("Valos bemenet! Kerekites egesz szamra! (%.1f -> %d)\n", tokenFloat, tokenInt);
            return tokenInt;    //törtrészt eldobjuk
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
        clrscr();
        printf("Hiba! A jegyek es megadott sulyok darabszama nem egyezik! Kerem, adjon meg azonos darabszamu jegyet (1-5 kozott) es sulyt (1-9 kozott)!\n");
        error = (true);
        return 1;
    }
    if(counter1 == 0 || counter2 == 0)
    {
        clrscr();
        printf("Hiba! Nem lett megadva jegy es/vagy suly! Kerem, adjon meg legalabb egy-egy erteket!\n");
        error = (true);
        return 1;
    }
    return 0;
}



//Egyes érdemjegyek megszámlálása
int jegySzamlalo(int erdemjegy)
{
    printf("Egyes erdemjegyek darabszama a megadott sorozatban:\n");
    
    //Csak egy érdemjegyet számol, ciklusban kell futtatni (erdemjegy = 1..5)
    for(erdemjegy=1; erdemjegy <= 5; erdemjegy++)
    {
        for(int i = 0; i <= counter1; i++)
        {
            if(feldolgozott [0] [i] == erdemjegy)
                jegyCounter[erdemjegy-1]++;
        }
        printf("%d: %d\n", erdemjegy, jegyCounter[erdemjegy-1]);
    }

    //Leggyakrabban előforduló (legnagyobb jegyCounter[erdemjegy-1] számú) jegy(ek) kiírása
    maxErtek = jegyCounter[0];
    for(int i=0; i<5; i++)
    {
        if(jegyCounter[i] > maxErtek)    
           maxErtek = jegyCounter[i];  
    }
    printf("A leggyakrabban előforduló érdemjegy(ek): ");
    for(int i=0; i<5; i++)
    {
        if(jegyCounter[i] == maxErtek)
        {   
           maxErtek = jegyCounter[i];  
           printf("%d; ", i+1);
        } 
    }
    printf("(%d db elofordulas)\n", maxErtek);
    return 0;
}

//Átlag és súlyozott átlag számítása
int atlag()
{
    float atlag; 
    int oszto = 0;
    float sulyozottAtlag;
    int reszOsszeg = 0;
    float reszOszto = 0;

    for(int i=1; i<=5; i++)
    {
        atlag += jegyCounter[i-1]*i;
        oszto += jegyCounter[i-1];
    }

    //A kalauz() már biztosította, hogy az oszto értéke nem lehet 0
    atlag = atlag/oszto;
    printf("A jegyek atlaga: %.3f\n", atlag);

    for (int i = 0; i < oszto; i++)
        {
        reszOsszeg += feldolgozott [1] [i]*feldolgozott [0] [i];
        reszOszto += feldolgozott [1] [i];
        }
    
    //A kalauz() már biztosította, hogy a reszOszto értéke nem lehet 0
    sulyozottAtlag = reszOsszeg/reszOszto;
    printf("A jegyek sulyozott atlaga: %.3f\n", sulyozottAtlag);

    return 0;
}

//Terminal tisztitasa -platformfuggetlen
void clrscr()
{
    system("@cls||clear");
}

void intro()
{
    clrscr();
    printf("Koszontom a Jegykiertekelo Rendszerben! Kerem, kovesse az utasitasokat!\n");
    sleep(2);
    printf("A bemenetekhez lehetoleg egesz szamokat hasznaljon:\n");
    sleep(1);
    printf("Jegyek eseten 1-5 kozott,\n");
    sleep(1);
    printf("Sulyok eseten 1-9 kozott.\n");
    sleep(2);
    printf("A nem szamokkent megadott ertekeket a program elveti.\n");
    sleep(1);
    printf("A tizedes pontossaggal megadott ertekeket a program kerekitessel olvassa be.\n");
    sleep(1);
    printf("Amennyiben a jegyek es sulyok darabszama nem egyezik, az ertekek megadasa folytatodik.\n\n");
    sleep(1);
}
