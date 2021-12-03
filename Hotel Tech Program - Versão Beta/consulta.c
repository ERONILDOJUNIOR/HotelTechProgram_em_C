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
FILE *buff;
FILE* refei;
FILE* reclm;
FILE* temporario;
FILE* acesso;
FILE* funcion;

//------QUARTOS----------//

void quartos_vagos(){
    TelaConsulta("Quartos vagos");
    Quarto Q;
    qut = abrir("rb", "quartos.txt", qut);
    printf("\nQuartos Vagos:\n");
    printf("----------------------------------------------------------------------\n");
    while(fread(&Q, sizeof(Quarto),1,qut)){
        if(Q.status == 0){
            printf("\n TIPO DO QUARTO: \t%s - Nº%d\n", Q.tipo_quarto.tipo, Q.num_quarto);
            printf(" Este Quarto possui %s camas, Senhor.", Q.tipo_quarto.num_camas);
            printf("\n DESCRIÇÃO:\n");
            printf(" %s\n\n", Q.tipo_quarto.descricao);
        }
    }
    system("PAUSE");
    fclose(qut);
}


void mostrar_quartos_cadastrados(){

        TelaConsulta("Quartos já Cadastrados");
        Quarto Q;
        qut = abrir("rb", "quartos.txt", qut);
        while(fread(&Q, sizeof(Quarto),1,qut)){

            printf("\n TIPO DO QUARTO: \t%s - Nº%d\n", Q.tipo_quarto.tipo, Q.num_quarto);
            printf(" Este Quarto possui %s camas, Senhor.", Q.tipo_quarto.num_camas);
            printf("\n Estado: %s", Q.estado);
            printf("\n DESCRIÇÃO:\n");
            printf(" %s\n\n", Q.tipo_quarto.descricao);
        }
        system("PAUSE");
        fclose(qut);
}



int informe_quarto_repetido(char *mensagem){
     Quarto Q;
     qut =abrir("rb", "quartos.txt", qut);
     int logico=0, num_quarto;
do{
     scanf("%d",&num_quarto);
     rewind(qut); logico=0;

     while(fread(&Q, sizeof(Quarto),1,qut)){
        if(Q.num_quarto == num_quarto)
           logico = 1;
     }
     if(logico==1){
        printf("Quarto já existente\n");
        printf("%s",mensagem);
     }

}while(logico==1);

fclose(qut);
return num_quarto;
}


void vizualizar_quarto_para_adicionar(){

        int i, cont=0,opcao;
        Desc = abrir("rb","tipos_quartos.txt", Desc);
        Tipo_Quarto *vetor_quarto = NULL;
        Tipo_Quarto qta;

        while(fread(&qta,sizeof(Tipo_Quarto),1,Desc))
        cont++;
        vetor_quarto = (Tipo_Quarto*)malloc(cont*sizeof(Tipo_Quarto));
        rewind(Desc);

        i=0;
        while(fread(&qta, sizeof(Tipo_Quarto),1,Desc)){
            strcpy(vetor_quarto[i].tipo, qta.tipo);
            strcpy(vetor_quarto[i].descricao, qta.descricao);
            strcpy(vetor_quarto[i].num_camas, qta.num_camas);
            i++;
        }
        fclose(Desc);
            TelaCadastro("Novo Quarto");
        printf("\n");
        for(i=0;i<cont;i++){
        printf("\n %d  Quarto do tipo \"%s\" Com %s cama(s)",i+1, vetor_quarto[i].tipo,vetor_quarto[i].num_camas);

        }
        printf("\n opção..: ");
        setbuf(stdin, NULL);
        scanf("%d", &opcao);
        if(opcao>=0 && opcao<=cont){
            adicionar_quartos_ao_hotel(vetor_quarto,opcao-1);
           }
        free(vetor_quarto);
}


void Mostrar_tipos_quarto(){

    Tipo_Quarto mostrar_quarto;
     Desc =abrir("rb", "tipos_quartos.txt", Desc);
    TelaConsulta("Tipos de Quartos já Cadastrados");

    printf("\n");
    while(fread(&mostrar_quarto, sizeof(Tipo_Quarto),1,Desc)){

        printf(" Tipo: \t%s\n", mostrar_quarto.tipo);
        printf(" Número de camas: %s\n", mostrar_quarto.num_camas);
        printf(" Descrição:\n %s ", mostrar_quarto.descricao);
        printf("--------------------------------------\n\n");

    }
    system("PAUSE");
    fclose(Desc);



}



int informe_quarto_existente(){
    Quarto Q;
    int num_quarto, logico = 0;
    temporario = abrir("rb", "quartos.txt", temporario);
    scanf("%d", &num_quarto);
    if(num_quarto==0)
        return -1;

    while(fread(&Q, sizeof(Quarto),1,temporario)){
            if(Q.num_quarto == num_quarto){
                logico =1;
            }
    }

    if(logico==0){


        return 0;
    }
    fclose(temporario);
    return num_quarto;
}





int quarto_ocupado(int num_quarto, Quarto *Q){

    int cont =0, logico=0;

    qut = abrir("rb","quartos.txt",qut);
    while(fread(Q,sizeof(Quarto),1,qut)){


        if(Q->num_quarto == num_quarto){
            if(Q->status==0)

                logico = 1;
                break;
            }

    }

    fclose(qut);
    if(logico == 1)
        return 1; //Quarto Desocupado
    else
        return 0;//Quarto Ocupado




}




void Estado_quarto(){

        TelaConsulta("Estado do Quarto");
        Quarto Q;
        int num, logico = 0;

        qut = abrir("rb", "quartos.txt", qut);
         printf("\n Digite o Número do Quarto a ser Visualizado: ");

		 scanf("%d", &num);
         while(num!=0){




		 rewind(qut);
        while(fread(&Q, sizeof(Quarto),1,qut)){
					if(Q.num_quarto == num){

            printf("\n TIPO DO QUARTO: \t%s - Nº%d\n", Q.tipo_quarto.tipo, Q.num_quarto);
            printf(" Este Quarto possui %s camas, Senhor.", Q.tipo_quarto.num_camas);
            printf("\n DESCRIÇÃO: \n %s", Q.tipo_quarto.descricao);
            printf(" ESTADO: %s\n", Q.estado);
            logico = 1;
        }
        }
        	if(logico!=1){

        		printf("Quarto não encontrado ");
        		logico = 0;
        	}
        		 printf(" Digite o Número do Quarto a ser Visualizado: ");
        		scanf("%d", &num);
        }
        printf("\n\n");
        system("PAUSE");
        fclose(qut);
}

int contador_de_quartos_hotel(){
    int cont = 0;
    Quarto Q;
    qut = abrir("rb", "quartos.txt", qut);
    while(fread(&Q, sizeof(Quarto),1,qut)){
    cont++;
    }
    fclose(qut);
    return cont;
}

//------HOSPEDE----------//


void listar_hospedes(){
    Quarto Q;
    qut = abrir("rb+", "quartos.txt", qut);
    TelaConsulta("Hóspedes");
    while(fread(&Q, sizeof(Quarto),1,qut)){
        if(Q.status == 1){
            printf("\nNome Do Hóspede: \t\t%s", Q.hospedagem.pessoa.nome);
            printf("\nPortador do CPF: \t\t%s\n", Q.hospedagem.pessoa.cpf);
            printf("N° de Inscrição: %d", Q.num_incricao);
            printf("\nSe encontra hospedado no quarto \"%d\" do tipo \"%s\"\n",Q.num_quarto, Q.tipo_quarto.tipo);
            printf("Data de Check-in: %d/%d%/%d",Q.hospedagem.in_dia,Q.hospedagem.in_mes,Q.hospedagem.in_ano+1900);
            printf("\n----------------------------------------------\n\n");
    	}
    	if(Q.status == 2){
    		printf("\nNome Do Hóspede: \t\t%s", Q.hospedagem.pessoa.nome);
            printf("\nPortador do CPF: \t\t%s\n", Q.hospedagem.pessoa.cpf);
            printf("O quarto \"%d\" do tipo \"%s\" se encontra reservado.\n",Q.num_quarto, Q.tipo_quarto.tipo);
            printf(" N° de Inscrição: %d", Q.num_incricao);
            printf("\N Check-in: %d/%d/%d", Q.hospedagem.in_dia,Q.hospedagem.in_mes,Q.hospedagem.out_ano);
            printf("\nCheck-out: %d/%d/%d\n",Q.hospedagem.out_dia,Q.hospedagem.out_mes,Q.hospedagem.out_ano);
            printf("----------------------------------------------\n\n");
		}

    }
    system("PAUSE");
fclose(qut);
}



void mostrar_conta_total_usuario( char* seu_nome,char *hospede_atual){

    TelaConsulta("Conta Total");
    printf("\nConta Buffet:\n");
    visualizar_conta_total_buffet(seu_nome,hospede_atual);
    printf("\nConta Serviços:\n");
    mostrar_conta_servico_usuario(hospede_atual);
    system("PAUSE");
}




void Visualizar_quartos_informacoes_clientes(){
	  qut =abrir("ab+", "quartos.txt", qut);
		TelaConsulta("Hóspedes");
	  Quarto Q;
	  int num;
	  while(fread(&Q, sizeof(Quarto),1,qut)){

	  	printf("Quarto %d: - %s\n", Q.num_quarto,(Q.status==0)? "Vago":Q.hospedagem.pessoa.nome);

	  }

	  printf("\n-----------------------------------------------------------------\n");

	  printf("opção: ");
      scanf("%d", &num);
	  while(num!=0){

       rewind(qut);
       fseek(qut,(num-1)*(sizeof(Quarto)),SEEK_SET);
	   fread(&Q, sizeof(Quarto),1,qut);
        if(Q.status==1){
    	printf("\n  ... Quarto [%d]....\n", Q.num_quarto);
        printf(" Hospedado por: %s",Q.hospedagem.pessoa.nome);
        printf("\n N° de Inscrição: %d", Q.num_incricao);
    	printf("\n CPF: %s\n", Q.hospedagem.pessoa.cpf);
    	printf("Data de Check-in: %d/%d%/%d",Q.hospedagem.in_dia,Q.hospedagem.in_mes,Q.hospedagem.in_ano+1900);
    	printf("\n-----------------------------------------------------------\n");
        }
        else if(Q.status==2){
        printf("\n  ... Quarto [%d]....\n", Q.num_quarto);
        printf(" Reservado por: %s",Q.hospedagem.pessoa.nome);
    	printf("\n CPF: %s\n", Q.hospedagem.pessoa.cpf);
    	 printf("\n N° de Inscrição: %d", Q.num_incricao);
    	printf("Check-in: %d/%d/%d", Q.hospedagem.in_dia,Q.hospedagem.in_mes,Q.hospedagem.out_ano);
            printf("\nCheck-out: %d/%d/%d",Q.hospedagem.out_dia,Q.hospedagem.out_mes,Q.hospedagem.out_ano);
    	printf("\n-----------------------------------------------------------\n");
       } else{
            printf("\n***Quarto Vago!!! \n\n");
        }


	  printf(":Qpção.: ");
      scanf("%d", &num);
	  }

	  system("PAUSE");

	  fclose(qut);




}


void Nome_visualizar_informacoes_cliente(){
	 qut =abrir("ab+", "quartos.txt", qut);
	TelaConsulta("Hóspedes");
	  Quarto Q;
	  char nome[20];
	  int logico = 0;
	  printf("\n Informe o nome do cliente: ");
		scanf("%s", nome);
		printf("\n\n");
		 while(fread(&Q, sizeof(Quarto),1,qut)){

		 	if(!strcmp(nome, Q.hospedagem.pessoa.nome)){
                if(Q.status==1){
                printf(" Hóspede.: %s",  Q.hospedagem.pessoa.nome);
		 		printf("\n Do Quarto %d",Q.num_quarto);
                printf("\n Número de Inscrição.: %d", Q.num_incricao);
		 		printf("\n CPF.: %s",  Q.hospedagem.pessoa.cpf);
		 		printf("\n------------------------------------------------------------------");


                }
                if(Q.status==2){
                printf(" Reservado Para.: %s",  Q.hospedagem.pessoa.nome);
		 		printf("\n Do Quarto %d",Q.num_quarto);
                printf("\n Número de Inscrição.: %d", Q.num_incricao);
		 		printf("\n CPF.: %s",  Q.hospedagem.pessoa.cpf);
		 		printf("\n------------------------------------------------------------------");
                }

		 		logico = 1;
			 }


	}
		 if(logico!=1)
		 		printf("\nHóspede não encontrado\n");
         printf("\n\n");
         	fclose(qut);
		 system("PAUSE");

}



void Nome_incompleto_visualizar_informacoes_cliente(){
	 qut =abrir("ab+", "quartos.txt", qut);
	TelaConsulta("Hóspedes");
	  Quarto Q;
	  char nome[20];
	  char *p;
	  int logico = 0;
	  printf("\n\n Informe o nome do cliente.: ");
		scanf("%s", nome);

        printf("\n\n");
		 while(fread(&Q, sizeof(Quarto),1,qut)){
		 	p = strstr(Q.hospedagem.pessoa.nome, nome);
		 	if(p){
		 		if(Q.status==1){
                printf(" Hóspede.: %s",  Q.hospedagem.pessoa.nome);
		 		printf("\n No Quarto %d",Q.num_quarto);
                printf("\n Número de Inscrição.: %d", Q.num_incricao);
		 		printf("\n CPF.: %s",  Q.hospedagem.pessoa.cpf);
		 		printf("\n------------------------------------------------------------------");


                }
                if(Q.status==2){
                printf("\n Reservado Para.: %s",  Q.hospedagem.pessoa.nome);
		 		printf("\n Do Quarto %d",Q.num_quarto);
                printf("\n Número de Inscrição.: %d", Q.num_incricao);
		 		printf("\n CPF.: %s",  Q.hospedagem.pessoa.cpf);
		 		printf("\n------------------------------------------------------------------");
                }
			 }
            logico=1;

	}
		 if(logico!=1)
		 		printf("\nHóspede não encontrado\n");

        printf("\n\n");
		 system("PAUSE");
		fclose(qut);
}







//------BUFFET----------//


void visualizar_buffet(){

    ItemRefeicao item;
    buff = abrir("rb", "buffet.txt", buff);
    int i=0;

    TelaConsulta("Buffet");
    printf("\n");
    while(fread(&item, sizeof(ItemRefeicao),1,buff)){
         printf(" %d - %s:  R$ %.2f\n", i+1, item.nome, item.preco);
         printf(" Descrição do Prato: \n %s", item.descricao);
         printf("-------------------------------------------------------------\n");

    }
    printf("\n\n");
    fclose(buff);
    system("PAUSE");

}



void visualizar_conta_total_buffet(char *seu_nome,char* hospede_atual){

     refei = abrir("rb", "refeicao.txt", refei);
   // TelaConsulta();
    float preco_total=0;
    printf("\nEstá comendo muito %s!\n", seu_nome);
    Refeicao refeicao;

    while(fread( &refeicao, sizeof(Refeicao),1,refei)){

        if(!strcmp( refeicao.cpf, hospede_atual)){
            printf(" %s - - - -%.2f\n",refeicao.item_comida.nome, refeicao.item_comida.preco);
            preco_total +=refeicao.item_comida.preco;

       }

    }


    printf(" \nPreço total a pagar Buffet: %.2f\n", preco_total);
    printf("-------------------------------------------\n");
    fclose(refei);

}










//------FUNCIONARIO----------//





void Funcionario_Leitura (){

	TelaConsulta("Funionário(s)");
	Funcionario funcionario;

	funcion = abrir("rb", "funcionario.txt", funcion);
    printf("\n\n Nosso(s) Funcionários é(são)\n\n");
	while(fread(&funcionario, sizeof(Funcionario), 1, funcion )){

        printf("\n Nome.: %s", funcionario.pessoa.nome);
		printf("\n CPF.: %s", funcionario.pessoa.cpf);
		printf("\n Telefone.:%s", funcionario.pessoa.telefone);
		 printf("\n Cargo.: %s", funcionario.cargo);
		printf("\n Salário R$.: %.2f", funcionario.salarios);


	printf("\n-----------------------------------------------------------------");
	}
	printf("\n\n");
	fclose(funcion);
	system("PAUSE");
}










//------SERVICO----------//





void visualizar_tipos_servico(){


    Servico tipo_servico;
    serv = abrir("rb", "tipos_servico.txt", serv);
    TelaConsulta("Serviços");

    printf("\n");
    while(fread(&tipo_servico, sizeof(Servico),1,serv)){

        printf(" Tipo de Serviço: \t%s\n", tipo_servico.tipoServico);
        printf(" Preço R$: \t\t%.2f\n", tipo_servico.precoServico);
        printf(" Descrição:\n %s ", tipo_servico.descricao);
        printf("--------------------------------------\n\n");

    }
    system("PAUSE");
    fclose(serv);




}


void mostrar_conta_servico_usuario(char *cpf){

    float conta_total=0;
    consumoServico consumo;
    conumoServ = abrir("rb", "consumo_servico.txt", conumoServ);
   // TelaConsulta();
    while(fread(&consumo, sizeof(consumoServico),1,conumoServ)){
        if(!strcmp(consumo.cpf,cpf)){
            printf("\n %s R$:\t\t%.2f", consumo.pedido_servico, consumo.precoServicoUsuario);
            conta_total+=consumo.precoServicoUsuario;
        }
    }
    printf("\n-----------------------------------------------\n");
    printf("\n Contal Total a Pagar Serviços: %.2f\n\n", conta_total);
    fclose(conumoServ);

}











//------RECLAMACAO----------//


void vizualizar_reclamacoes_respondidas(char* hospede_atual){
     reclm = abrir("rb", "reclamacoes.txt", reclm);
    TelaReclamacao();
    printf("\n Mensagens respondidas: \n\n");
     Reclamacoes reclama;
     while(fread(&reclama,sizeof(Reclamacoes),1,reclm)){
        if(!strcmp(reclama.cpf, hospede_atual)){
                if(reclama.status == 2){
            printf("%s\n", reclama.resposta);
            printf("---------------------------------------------------------------\n");
            }
        }
     }
    system("PAUSE");
     fclose(reclm);
}


int cont_reclamacoes(){
     reclm = abrir("rb", "reclamacoes.txt", reclm);
     Reclamacoes reclama;
     int cont=0;
     while(fread(&reclama,sizeof(Reclamacoes),1,reclm)){
        cont++;
     }
     fclose(reclm);
     return cont;
}






