#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct endereco
{  
	char  logradouro[80];  
	char  bairro[20];  
	char  CEP[10];  
	char  cidade[20];  
	char  estado[20];  
	char  fone[15];  
	char  cel[15];
	char  email[30]; 
}endereco;

typedef struct info_casa
{
	int num_casa;
	char status_casa;
}info_casa;

typedef struct prop
{
	int reg_prop;
	char nome[80];
	long int CPF[15];
	struct endereco end_prop;
	int qtd_casa;
	struct info_casa casa[5];
}prop;

void aloca(prop **p, int tam);
int verifica();
void cadastro(prop *p,int qreg);
void gravaCad(prop *p);
void gravaEnd(prop *p);
void mostraCad(prop *p,int qreg);
void cadastro_end(prop *p, int qreg);
void menu(int qreg, prop *p);
void cadastroImo(prop *p,int qreg);
int	 busca_prop(prop *p,int num_reg);

int main()
{
	prop *pd=NULL;
	char op;
	int qreg;
	aloca(&pd,1);
	do{
	qreg=verifica();
	menu(qreg,pd);
	
	printf("Deseja continuar?: s/n");
	scanf("%c", &op);
	}while(op != 'n' || 'N');
	
	return 0;
}//main

void aloca(prop **p, int tam)
{
	if((*p=(prop*)realloc(*p,tam*sizeof(prop))) == NULL)
		exit(1);
}//aloca

int verifica()
{
	long int cont=0;
	FILE *fptr=NULL;
	if((fptr=fopen("Cadastro.bin","rb"))==NULL)
		return cont;
	else
	{
		fseek(fptr,0,2); //Posicionamento do fim do arquivo
		cont=ftell(fptr)/sizeof(prop); // quantidade de cadastros
		fclose(fptr);
		return cont;
	}
}//verifica

void cadastro_end(prop *p, int qreg)
{
	printf("-- Cadastro de endereco --");
	printf("\nLogradouro: ");
	gets(p->end_prop.logradouro);
	fflush(stdin);
	printf("\nBairro: ");
	gets(p->end_prop.bairro);
	fflush(stdin);
	printf("\nCEP: ");
	gets(p->end_prop.CEP);
	fflush(stdin);
	printf("\nCidade: ");
	gets(p->end_prop.cidade);
	fflush(stdin);
	printf("\nEstado: ");
	gets(p->end_prop.estado);
	fflush(stdin);
	printf("\nFone residencial: ");
	gets(p->end_prop.fone);
	fflush(stdin);
	printf("\nCelular: ");
	gets(p->end_prop.cel);
	fflush(stdin);
	printf("\nEmail: ");
	gets(p->end_prop.email);
	fflush(stdin);
}//endereco do proprietario

void cadastro(prop *p,int qreg)
{
	p->reg_prop = qreg; //numero de registro
	printf("\nRegistro: %i",p->reg_prop);
	fflush(stdin);
	printf("\nNome: ");
	gets(p->nome);
	fflush(stdin);
	printf("\nCPF: ");
	scanf("%i",&(p->CPF));
	fflush(stdin);
	cadastro_end(p,qreg);
	cadastroImo(p,qreg);
	gravaEnd(p);
	gravaCad(p);
}//cadastro proprietario

void gravaEnd(prop *p)
{
	FILE *fptr=NULL;
	if((fptr=fopen("Cadastro.bin","ab"))==NULL)
		printf("\nErro ao abrir o arquivo!"); //caso nao consiga abrir o arquivo
	else
		fwrite(p,sizeof(endereco),1,fptr);
	fclose(fptr);
}//grava o endereco do proprietario

void gravaCad(prop *p)
{
	FILE *fptr=NULL;
	if((fptr=fopen("Cadastro.bin","ab"))==NULL)
		printf("\nErro ao abrir o arquivo!"); //caso nao consiga abrir o arquivo
	else
		fwrite(p,sizeof(prop),1,fptr);
	fclose(fptr);
}//grava o cadastro do proprietario

void mostraCad(prop *p,int qreg)
{
	int i;
	FILE *fptr = NULL;
	system("cls");
	if((fptr=fopen("Cadastro.bin","rb"))==NULL)
		printf("\nErro ao abrir o arquivo");
	else
	{
		for(i=0;i<qreg;i++)
		{
			fseek(fptr,i*sizeof(prop),0);
			fread(p,sizeof(prop),1,fptr);
			printf("-----PROPRIETARIOS CADASTRADOS------\n");
			printf("\nRegistro: %i",p->reg_prop);
			printf("\nNome: %s",p->nome);
			printf("\nCPF: %i",p->CPF);
			printf("\nLogradouro: %s",p->end_prop.logradouro);
			printf("\nBairro: %s",p->end_prop.bairro);
			printf("\nCEP: %s",p->end_prop.CEP);
			printf("\nCidade: %s",p->end_prop.cidade);
			printf("\nEstado: %s",p->end_prop.estado);
			printf("\nFone: %s",p->end_prop.fone);
			printf("\nCel: %s",p->end_prop.cel);
			printf("\nEmail: %s",p->end_prop.email);
			printf("\n");	
		}
		fclose(fptr);
		system("pause");
	}	
}//funcao mostra cadastro

void menu(int qreg, prop *p)
{
	int cont;
	int registro;
	printf("\n-- Projeto Imobiliaria --\n");
	do
	{
		system("cls");
		printf("(1) Cadastro de proprietario\n(2)Cadastro de Imovel\n(3)Mostrar Proprietarios\n(4)Sair\n");
		scanf("%i",&cont);
		switch (cont)
		{
			case 1:
				qreg = verifica();
				cadastro(p,qreg+1);
				qreg++;
				fflush(stdin);
				break;
			case 2:
				cadastroImo(p,qreg);
				break;
			case 3:
				mostraCad(p,qreg);
				break;
			case 4:
				printf("Obrigado por se cadastrar, ate mais!");
				return;
		}
	}while(cont != '4');
}//menu principal

void cadastroImo(prop *p,int qreg)
{
	int i,quantimo;
	printf("-- Cadastro de Imovel --\n");
	printf("Quantidade de Imoveis: ");
	do
	{
		scanf("%i",&quantimo);
		if(quantimo < 1 && quantimo > 5)
			printf("Numero de casas acima do permitido!\n");
	}while(quantimo < 1 && quantimo > 5);
	for(i=0;i<quantimo;i++)
	{
		(p->casa)->num_casa = i; 
		printf("\nNumero casa: %i",(p->casa->num_casa)+1);
		fflush(stdin);
		printf("\nCasa Alugada (A) / Casa Livre (L): ");
		scanf("%c",&(p->casa->status_casa));
		fflush(stdin);
	}
}//cadastra o imovel do proprietario

int	busca_prop(prop *p,int num_reg)
{
int i,achou=-1,qreg;
FILE *fptr=NULL;

qreg=verifica();
system("cls");
if((fptr=fopen("Cadastro.bin","rb"))==NULL)
  printf("\nErro\n\n");
else
  {
  for(i=0;i<qreg;i++)
    {
	fseek(fptr,i*sizeof(prop),0);
	fread(p,sizeof(prop),1,fptr);	
	if(p->reg_prop==num_reg)
	  {
	  achou=i;   //posicao no arquivo
	  i=qreg;
      }//if
    }//for
  fclose(fptr);  //DENTRO do else - abriu com rb
  }//else
return achou;
}//busca
