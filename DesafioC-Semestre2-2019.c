#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados {


char nome[20];
int quantidade;
char validade[20];
int quantidademinima;
};

void inclui();
void lista();
int pesquisa();
void buscarL();
void buscarV();
void listaminimo();
void moviment_estoque();
void altera();
void exclui();

main()
{
 int opc=0;
 struct dados info;
 struct dados *p;
 int tam;
 int x;

 p=&info;
 tam= sizeof(info);

for(;;){
system("cls");

 printf("\t                                                                      |\n");
 printf("\t|               Selecione uma das opcoes                              |\n");
 printf("\t|---------------------------------------------------------------------|\n");
 printf("\t|  [1]Entrada de produto    [2]Lista produtos                         |\n");
 printf("\t|  [3]Buscar pelo o produto                                           |\n");
 printf("\t|  [4]Buscar pela 1 letra do produto                                  |\n");
 printf("\t|  [5]Buscar pela validade  [6]Lista produtos abaixo do estoque minimo|\n");
 printf("\t|  [7]Movimenta a quantidade em estoque [8] altera o produto          |\n");
 printf("\t|  [9]Exclui produto        [10]saida                                 |\n");
 printf("\t----------------------------------------------------------------------|\n");
    scanf("%d",&opc);
    getchar();
    switch(opc)
    {

    case 1:
    inclui(p,tam);
    break;

    case 2:
    lista(p,tam);
    break;

    case 3:
    pesquisa(p,tam);
    break;

    case 4:
    buscarL(p,tam);
    break;

    case 5:
    buscarV(p,tam);
    break;

    case 6:
    listaminimo(p,tam);
    break;
    case 7:
    moviment_estoque(p, tam);
    break;

    case 8:
    altera(p,tam);
    break;

    case 9:
    exclui(p,tam);
    break;


    case 10: exit(0);

    }
}
}

void buscarL (struct dados *ps, int tam)
{
FILE *p;
FILE *p1;
char letra;
int i=0,y, x;
int cont;

    printf(" Pesquise pela primeira letra do produto:\n");
    letra=getchar();
    getchar();


    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r");

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        if( letra == ps->nome[0]){
        printf("Produto achado com sucesso:\n");
        printf("\n Produto: %s ", ps->nome);
        printf("\n Validade: %s \n", ps->validade);
        printf(" Quantidade: %d \n", ps->quantidade);
        printf(" Quantidade minima: %d \n", ps->quantidademinima);
            }
            }


            system("pause");
            fclose(p);




}


void inclui (struct dados *ps, int tam)
{
FILE *p, *p1;
int cont=0;
int i;

p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);



    p = fopen("arquivo.txt", "a");

        if( p == NULL){
        printf("\nERRO");
        exit(1);
        }

    printf(" Escreva o nome do produto:\n");
    scanf("%s", ps->nome);
    do{
    printf(" Escreva a validade do produto (MM/AAAA):\n");
    scanf("%s", ps->validade);
    if(ps -> validade[2]!= '/')
        {
        printf(" Por favor digite com a / \n");

        }
    }while(ps -> validade[2]!= '/');
    printf(" Escreva a quantidade do produto:\n");
    scanf("%d", &ps->quantidade);
    printf(" Escreva a quantidade minima: \n");
    scanf("%d", &ps->quantidademinima);
    fwrite(ps,tam,1,p);
    fclose(p);

    cont++;

    p1 = fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    fclose(p1);
    system("pause");
}

void lista(struct dados *ps, int tam)
{
    FILE *p, *p1;
    int i;
    int cont,comp;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r");

    if( p== NULL)
        {
        puts("\nERRO\n");
        exit(1);
        }

    for(i=0;i<cont; i++){
    comp = i*tam;
    fseek(p,comp,0);
    fread(ps,tam,1,p);



    if(ps -> nome[0] != '*'){

        printf("\n Produto: %s ", ps->nome);
        printf("\n Validade: %s \n", ps->validade);
        printf(" Quantidade: %d \n", ps->quantidade);
        printf(" Quantidade Minima: %d \n",ps->quantidademinima);
        printf("--------------------\n");

        }
    }
        system("pause");
        fclose(p);
}

void buscarV( struct dados*ps, int tam)
{
FILE *p;
FILE *p1;

    char validade1[20];
    int i=0,y, x;
    int cont;

p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);


p = fopen("arquivo.txt", "r");
do{
printf("Digite uma validade para ser buscada (MM/AAAA): \n");
gets(validade1);
if(validade1[2] != '/')
    {
    printf("Por favor digite com a ( / ) \n");
    }
}while(validade1[2] != '/');

for(y=0;y<cont;y++)
    {
    fread(ps,tam,1,p);
     for(x = 0; validade1[x] != '\0';x++){

    if(validade1[x] != ps -> validade[x]){
                break;
            }
     }
      if(validade1[x] == '\0' && ps -> validade[x] == '\0')
    {
        printf("Produto achado com sucesso:\n");
        printf("\n Produto: %s ", ps->nome);
        printf("\n Validade: %s \n", ps->validade);
        printf(" Quantidade: %d \n", ps->quantidade);
        system("pause");
        return y;
    }
    }
     printf("registro nao existe\n");
     system("pause");
     return -1;
}
int pesquisa(struct dados *ps, int tam)
{
    FILE *p;
    FILE *p1;

    char nome1[20];
    int i=0,y, x;
    int cont;


    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r");

    printf("Informe um nome para pesquisa: ");
    gets(nome1);

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] != ps -> nome[x]){
                break;
            }
        }

    if(nome1[x] == '\0' && ps -> nome[x] == '\0')
    {
        printf("Produto achado com sucesso:\n");
        printf("\n Produto: %s ", ps->nome);
        printf("\n Validade: %s \n", ps->validade);
        printf(" Quantidade: %d \n", ps->quantidade);
        printf(" Quantidade minima: %d \n", ps->quantidademinima);
        system("pause");
        return y;
    }
    }

    printf("registro nao existe\n");
    system("pause");
    return -1;
}

void moviment_estoque(struct dados *ps, int tam)
{
FILE *p;
FILE *p1;

int reg;
int nbytes;
char opc;
int quantidad;


p=fopen("arquivo.txt", "r+");
reg = pesquisa(ps,tam);
nbytes=tam*reg;
printf("(+)ou(-):\n");
scanf("%c", &opc);

if(opc == '+')
    {
    printf(" Escreva a quantidade que voce vai adicionar no estoque:\n ");
    scanf("%d",&quantidad);
    ps -> quantidade = ps->quantidade + quantidad;
    fseek(p,nbytes,0);
    fwrite(ps,tam,1,p);

    }

else if (opc == '-'){
        do{
    printf(" Escreva a quantidade que voce vai retirar no estoque: \n");
    scanf("%d", &quantidad);

     if(ps->quantidade == 0)
    {
        printf(" Nao existe nenhuma quantidade no seu estoque de %s\n", ps->nome);
        goto vai;
    }

    ps -> quantidade = ps->quantidade - quantidad;

   if( ps->quantidade <0){
       printf("!Voce retirou mais do que havia no estoque, tente retirar menos!\n");
   }

   }while( ps->quantidade <0);
   vai:
    fseek(p,nbytes,0);
    fwrite(ps,tam,1,p);

    }

fclose(p);
system("pause");
}

void listaminimo(struct dados *ps, int tam)
{
FILE *p, *p1;
int x=0,y=0,i=0;
int cont;
int lista [80];
int conte=0;

p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);

p = fopen("arquivo.txt", "r");

if( p== NULL)
        {
        puts("\nERRO\n");
        exit(1);
        }
printf(" Aqui estao os produtos abaixos do estoque minimo:\n");
for(y=0;y<cont;y++)
    {
    fread(ps,tam,1,p);
     if(ps->quantidade < ps -> quantidademinima){
        printf("\n Produto: %s ", ps->nome);
        printf("\n Validade: %s \n", ps->validade);
        printf(" Quantidade: %d \n", ps->quantidade);
        printf(" Quantidade minima: %d \n", ps->quantidademinima);
        printf("\n------------------------------");
        conte++;
            }

}
if(conte==0)
    {
    printf("!NAO TEM NENHUM PRODUTO ABAIXO DO ESTOQUE MINIMO!\n\n");
    }
system("pause");

}

void altera(struct dados *ps, int tam)
{
    FILE *p, *p1;
    int nreg;
    int nbytes;
    char validade[20];
    int quantid;
    int minimo;
    int opc;

    nreg =  pesquisa(ps, tam);
    nbytes = tam * nreg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,nbytes,0);
    fread(ps, tam, 1, p );

    printf("Digite qual parte do arquivo voce quer alterar\n(1)Produto \n(2)Validade \n(3)Quantidade \n(4)Quantidademinima \n ");
    scanf("%d", &opc);
    switch(opc)
    {
case 1:
   printf("Digite o novo nome do produto: \n");
   scanf("%s",ps->nome);

   fseek(p,nbytes,0);
   fwrite(ps, tam,1,p);
   break;
case 2:
   printf("Digite a nova data de validade (MM/AAAA): \n ");
   scanf("%s",ps->validade);
   fseek(p,nbytes,0);
   fwrite(ps, tam,1,p);
   break;
case 3:
   printf("Digite uma nova Quantidade: \n");
   scanf("%d", &ps->quantidade);
   fseek(p,nbytes,0);
   fwrite(ps, tam,1,p);
   break;
case 4:
   printf(" Digite uma nova quantidade minima:\n ");
   scanf("%d", &ps->quantidademinima);
   fseek(p,nbytes,0);
   fwrite(ps, tam,1,p);
   break;
    }
    printf(" Digite (2) depois para conferir as alteracoes\n");
    fclose(p);
}

void exclui(struct dados *ps, int tam)
{
    FILE *p;
    p = fopen("arquivo.txt", "r+");
    int nreg;
    int nbytes;

    nreg = pesquisa(ps, tam);
    nbytes = tam * nreg;

    fseek(p,nbytes,0);
    fread(ps, tam, 1, p );
    printf("\n\nnome apagagado %s\n",ps -> nome);
    ps->nome[0]= '*' ;
    printf("O nome do produto ficou %s\n\n",ps -> nome);

    fseek(p,nbytes,0);
    fwrite(ps,tam,1,p);
    system("pause");
    fclose(p);

}

