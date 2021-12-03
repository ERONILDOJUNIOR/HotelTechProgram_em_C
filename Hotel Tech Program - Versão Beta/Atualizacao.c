#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include <string.h>
#include <locale.h>
#include <ctype.h>
//#include <conio.h>

FILE* Desc;
FILE* qut;
FILE* serv;
FILE* conumoServ;
FILE* buff;
FILE* refei;
FILE* reclm;
FILE* temporario;
FILE* acesso;
FILE* funcion;

//------QUARTOS----------//

int informe_quarto_vago(int num_quarto){

    Quarto Q;
    int logico=0;
    qut = abrir("rb", "quartos.txt", qut);
    while(fread(&Q, sizeof(Quarto),1,qut)){
            if(Q.num_quarto==num_quarto)
                if(Q.status==1)
                logico = 1;
 }
 fclose(qut);
 return logico;
}



void menu_atualizar_quarto(Quarto Q,Quarto aux){


      TelaQualquer("   ...Modificação Quarto....");
      char opcao;
	  int confirmar;

      printf("\n 1  Número do Quarto: %d  ", aux.num_quarto);
      printf("\n 2  Quantidade de Cama(s): %s", aux.tipo_quarto.num_camas);
      printf("\n 3   Descrição: %s", aux.tipo_quarto.descricao);
      printf(" 4  Finalizar\n\n");

      do{

	do{
	fflush(stdin);
	printf("\nEscolha: ");
	scanf("%c", &opcao);
    }while (isdigit(opcao) != 1);


        switch(opcao){
        setbuf(stdin,NULL);
        case '1':printf(" N° Quarto: ");Q.num_quarto=informe_quarto_repetido("N° Quarto: ");

        break;

        case '2':printf(" N° de Camas: "); scanf("%s", Q.tipo_quarto.num_camas);
        break;

        case '3': printf(" Descrição: ");setbuf(stdin,NULL); fgets(aux.tipo_quarto.descricao,300, stdin);
        break;
        case '4': printf("\n Correção Finalizada...\n");
        break;
        default: printf("\n Comando Desconhecido");
         }
       }while(opcao!='4');

		printf("\nConfirmar?/cancelar?/ 1/2.: ");
		scanf("%d", &confirmar);

    if(confirmar==1){
    re_gravar_quartos(Q.num_quarto);
    gravar_quarto(&aux);
    }
    else{
        printf("\n\n Cadastramento Cancelado... :(\n\n");
    }








}
void atualizar_quarto(){

        TelaAtualizacao(" Informações de Quarto");
        Quarto Q, Quarto_aux;
        int num_quarto,confirmar,logico=0, num_anterior;
        qut = abrir("rb", "quartos.txt", qut);
        printf("\n\n Informe o número do Quarto desejado.: ");
        scanf("%d", &num_quarto);
        while(fread(&Q, sizeof(Quarto),1,qut)){

        if(Q.num_quarto==num_quarto){
            printf("\n TIPO DO QUARTO: \t%s - Nº%d\n", Q.tipo_quarto.tipo, Q.num_quarto);
            printf(" Este Quarto possui %s camas, Senhor.", Q.tipo_quarto.num_camas);
            printf("\n Estado: %s", Q.estado);
            printf("\n DESCRIÇÃO:\n");
            printf(" %s\n", Q.tipo_quarto.descricao);
            logico=1;
            break;
        }
        }
        fclose(qut);
        if(logico==1){
            printf("----------------------------------------------------------\n");
            printf(" Confirmar?/cancelar? 1/2.: ");
            scanf("%d", &confirmar);

            if(confirmar==1){
                    if((informe_quarto_vago(Q.num_quarto))==0){
                         menu_atualizar_quarto(Q,Q);

                    }
                    else
                        printf(" ATENÇÃO: O quarto não pode ser atualizado, pois se encontra hospedado!!!\n\n");


            }
            else
                printf("\n Remoção Cancelada...\n\n");
            }
        else{
                printf("\n Quarto não encontrado...\n\n");
            }
        system("PAUSE");




}









//------HOSPEDE----------//



void atualizacao_menu_hospede(Quarto* Q){



      TelaQualquer("   ...Modificação Hóspede....");
      char opcao;

      printf("\n 1 Nome: %s  ", Q->hospedagem.pessoa.nome);
      printf("\n 2 CPF: %s", Q->hospedagem.pessoa.cpf);
      printf("\n 3 Finalizar\n\n");

      do{

	do{
	fflush(stdin);
	printf("\nEscolha: ");
	scanf("%c", &opcao);
    }while (isdigit(opcao) != 1);


        switch(opcao){
        setbuf(stdin,NULL);
        case '1':printf(" Nome: "); scanf("%s", Q->hospedagem.pessoa.nome);
        break;

        case '2':printf(" CPF: "); scanf("%s", Q->hospedagem.pessoa.cpf);
        break;

        case '3': printf("\n Correção Finalizada...\n");
            break;
        default: printf("\n Comando Desconhecido");
         }
       }while(opcao!='3');

}



void atualizar_hospede(){

    Quarto Q;
    int num_quarto, opcao,confirmar;

    TelaAtualizacao("Hóspede");
    printf("\n\n Informe o Nº do Quarto.: ");
    num_quarto = informe_quarto_existente();

    if(num_quarto){
      if((quarto_ocupado(num_quarto,&Q))==0){


             atualizacao_menu_hospede(&Q);
             printf("\n---------------------------------------------------\n");
             printf(" Confirmar?/cancelar? 1/2.: ");
             scanf("%d", &confirmar);

            if(confirmar==1)
           re_gravar_quarto(Q);
            else
            printf("\n Correção Cancelada...\n\n");

    }else
        printf("\n\n O quarto está vago...\n\n");
    }
    else
        printf("\n\n O Quarto informado não existe ;(");

    system("PAUSE");


}










//------BUFFET----------//



void menu_atualizar_buffet(ItemRefeicao* item){



      TelaQualquer("   ...Modificação Buffet....");
      char opcao;

      printf("\n 1 Nome do Prato: %s  ", item->nome);
      printf("\n 2 Descrição: %s\n", item->descricao);
      printf(" 3 Preço ", item->preco);
      printf("\n 4 Finalizar\n\n");
        do{
	do{
	fflush(stdin);
	printf("\nEscolha: ");
	scanf("%c", &opcao);
    }while (isdigit(opcao) != 1);

        switch(opcao){
        setbuf(stdin,NULL);
        case '1':printf(" Nome: ");  setbuf(stdin,NULL);scanf("%s",item->nome);
        break;

        case '2':printf(" Descrição: "); setbuf(stdin,NULL); fgets(item->descricao,300,stdin);
        break;

        case '3': printf(" Preço: ");  setbuf(stdin,NULL);scanf("%s", &item->preco);
        break;
        case '4': printf("\n Correção Finalizada...\n");
        break;
        default: printf("\n Comando Desconhecido");
         }
       }while(opcao!='4');

}


void atualizar_buffet(){

    buff = abrir("rb", "buffet.txt", buff);
    ItemRefeicao item;
    char nome_prato[20];
    int logico = 0,confirmar;
    TelaAtualizacao("Buffet");
    printf("\n Informe o nome do Prato.: ");
    scanf("%s", nome_prato);
    while(fread(&item,sizeof(ItemRefeicao),1,buff)){

        if(!strcmp(item.nome, nome_prato)){
            printf("\n Nome: %s",item.nome);
            printf("\n Descrição: %s",item.descricao);
            printf(" Preço: %.2f", item.preco);
            printf("\n---------------------------------------------------------------------\n");
            logico = 1;
            break;


    }

    }
    fclose(buff);
    if(logico==1){
        printf(" Confirmar?/cancelar? 1/2.: ");
        scanf("%d", &confirmar);
        if(confirmar == 1){
            menu_atualizar_buffet(&item);
            re_gravar_buffet_atualizado(item);
        }
        else
            printf("\n\n Processo de Atualização cancelado\n\n");
    }
    else{
        printf("\n Prato não encontrado... :(\n\n");
    }
    system("PAUSE");


}













//------FUNCIONARIO----------//

void  menu_atualizar_funcionario(Funcionario *funcionario){



      TelaQualquer("   ...Modificação Funcioário....");
      char opcao;

      printf("\n 1 Nome do Funcionário: %s  ",funcionario->pessoa.nome);
      printf("\n 2 CPF: %s", funcionario->pessoa.cpf);
      printf("\n 3 Telefone: %s",funcionario->pessoa.telefone);
      printf("\n 4 Cargo/Função: %s", funcionario->cargo);
      printf(" 5 Salário: %.2f",funcionario->salarios) ;
      printf("\n 6 Finalizar\n\n");

      do{

	do{
	fflush(stdin);
	printf("\nEscolha: ");
	scanf("%c", &opcao);
    }while (isdigit(opcao) != 1);

        switch(opcao){
        setbuf(stdin,NULL);
        case '1':printf(" Nome do Funcionário: "); scanf("%s",funcionario->pessoa.nome);
        break;

        case '2':printf("CPF: "); scanf("%s",funcionario->pessoa.cpf);
        break;

        case '3': printf(" Telefone: "); scanf("%s",funcionario->pessoa.telefone);
        break;
        case '4': printf(" Cargo/Função: ");scanf("%s",funcionario->cargo);
        break;

        case '5': printf(" Salário: "); scanf("%f",&funcionario->salarios);
        break;
        case '6': printf("\n Correção Finalizada...\n");
        break;
        default: printf("\n Comando Desconhecido");
         }
       }while(opcao!= '6');




}


void atualizar_funcionario(){


	 TelaRemocao("Atualizar: Funcionário");
	 funcion = abrir("rb", "funcionario.txt", funcion);
	 Funcionario funcionario;
	 char *p;
	 char logico=0;
	 char nome[20], cpf[9];


	 printf("\n\nInforme o nome do funcionário.: ");
	 setbuf(stdin,NULL);
	 scanf("%s", nome);

	 while(fread(&funcionario,sizeof(Funcionario),1,funcion)){
	 	p = strstr(funcionario.pessoa.nome,nome);
	 	if(p){

	 	printf("\nNome: %s",funcionario.pessoa.nome);
	 	printf("\nPortador do CPF: %s", funcionario.pessoa.cpf);
	 	printf("\n-------------------------------------------------------------------------------\n");
	 	logico = 1;
	 }
	 }
	  fclose(funcion);

	 if(logico!=1)
	 	printf("\n**Funcionário não encontrado\n\n");
	else{
		printf("\nInforme o número do cpf do funcionário que deseja removê-lo");
	    printf("\nCPF: ");
   	    scanf("%s", cpf);
   	    menu_atualizar_funcionario(&funcionario);
   	    re_gravar_funcionario_atualizado(funcionario);
    }
 	system("PAUSE");



}










//------SERVICO----------//















//------RECLAMACAO----------//







