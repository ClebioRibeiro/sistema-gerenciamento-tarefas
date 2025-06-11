#include <stdio.h>
#include <string.h>
/*
---------------------------------------------------------------------------
------------------------ DECLARAÇAO DE FUNCOES ----------------------------
-------------- DEFINICOES DE FUNCOES ABAIXO DO INT MAIN -------------------
---------------------------------------------------------------------------
*/
void add(char a[2][3][25]);
void listar();


/*
---------------------------------------------------------------------------
----------------------------- INT MAIN ------------------------------------
---------------------------------------------------------------------------
*/
int main()
{
    char m[2][3][25];
    int swt, c;
    //printf("");
    printf("Sistema de Gerenciamento de Tarefas\n");
    printf("1 - Adicionar\n2 - Listar\n5 - Sair\n");
    scanf("%d", &swt);
    while ((c = getchar()) != '\n' && c != EOF);

    while(swt != 5)
    {
        switch(swt)
        {
            case 1:
            add(m);
            break;

            case 2:
            listar();
            break;

            default:
            printf("Escolha Invalida\n");

        }

        printf("\nContinuar?\n");
        printf("1 - Adicionar\n2 - Listar\n5 - Sair\n");
        scanf("%d", &swt);
        while ((c = getchar()) != '\n' && c != EOF);
    }
    

    return 0;
}


/* 
---------------------------------------------------------------------------
---------------------------------------------------------------------------
-------------------------------- FIM INT MAIN -----------------------------
---------------------------------- FUNCOES---------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------

*/

/*
---------------------------------- ADD ------------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------
*/

void add(char a[2][3][25])
{
    int i,j;
    FILE *pt;

    pt = fopen("aedtext.txt", "w");

    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++){

            printf("linha %d coluna %d: ", i,j);
            fgets(a[i][j], 25, stdin);
            
            
            // tirar quebra de linha ('\n') da string
            
            if(strlen(a[i][j]) > 0 && a[i][j][strlen(a[i][j]) - 1] ==   '\n')
            {
                a[i][j][strlen(a[i][j]) - 1] = '\0';
            }
            // fim tirar quebra de linha ('\n') da string

            if(j<2)
            {
                fprintf(pt, strcat(a[i][j]," "));
            }
            else
            {
                fprintf(pt, strcat(a[i][j],"\n"));
            }
            
            
        } // for menor
        
    }

    fclose(pt);
} // fim add


/*
-------------------------------- LISTAR -----------------------------------
---------------------------------------------------------------------------
---------------------------------------------------------------------------
*/

void listar()
{
    char strg[25];
    FILE *pt;
    int ct=1;

    pt = fopen("aedtext.txt", "r");

    while(fgets(strg, 25, pt))
    {
        if(ct == 3)
        {
            printf("%s\n", strg);
            ct=1;
        }
        else
        {
            printf("%s ", strg);
            ct++;
        }
        
    }
} // fim listar