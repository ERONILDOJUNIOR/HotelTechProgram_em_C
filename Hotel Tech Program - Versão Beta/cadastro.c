#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include <string.h>
#include <locale.h>
#include <ctype.h>
//#include <conio.h>
#include <time.h>

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


void *abrir(char tipo[3], char* nome_txt, FILE* pont_arquivo){

     if(!(pont_arquivo = fopen(nome_txt, tipo))){
         printf("\n O arquivo nao pode ser aberto!!\n");
         system("PAUSE");
         exit(1);
     }
}

//------QUARTOS----------//





void analize_antes_do_cadastramento_do_hospede(int opcao){


    int tam,i,num,confirmar;
    Quarto Q;

    qut = abrir("ab+", "quartos.txt", qut);
    TelaCadastro("Novo Hóspede");
    printf("\n Digite o Nº do quarto do hóspede: ");
for(;;){

    num = informe_quarto_existente();
    if(num==-1){
        printf("\n\n..Processo de Cadastramento Cancelado..\n\n");
        system("PAUSE");
        return 0;
    }

    if(num==0){
         printf("------------------------------------------------------------");
         printf("\n\n **O Quarto não existe no Hotel :(\n\n\n");
         system("PAUSE");
         return 0;

    }

    rewind(qut);
    while(fread(&Q, sizeof(Quarto),1,qut)){

        if(Q.num_quarto == num){

                if(Q.status == 1 || Q.status == 2) {
                 TelaCadastro("Novo Hóspede");
                 printf("\n");
                        if(Q.status == 1)
                            printf("Quarto Ocupado!\n");
                        else{
                             printf("\n** Quarto Reservado!\n\n");
                             printf(" Deseja realizar o Check-in?\n");
                             printf("\n\n Confirmar?/cancelar? 1/2.: ");
                             scanf("%d", &confirmar);
                             if(confirmar==1){
                                fclose(qut);
                                fazer_check_in_de_reserva(&Q);
                                re_gravar_quarto(Q);
                                return;
                             }
                             else
                                printf("Opção cancelada...\n");

                        }
                        printf("\n Digite Novamente o Nº do quarto do hóspede: ");
                }else{
                        fclose(qut);
                       switch(opcao){
                           case 1:
                            cadastrar_hospede(&Q);
                            re_gravar_quarto(Q);
                            break;
                           case 2:
                            reservar_um_quarto(&Q);
                             re_gravar_quarto(Q);
                             break;
                        }

                 return 0;
               }
            }
     }


}

}











void adicionar_quartos_ao_hotel(Tipo_Quarto* vetor_quarto,int opcao){



         TelaCadastro("Novo Quarto");

         int confirmar;
         Quarto adcionar_quarto;


         strcpy(adcionar_quarto.tipo_quarto.tipo, vetor_quarto[opcao].tipo);
         strcpy(adcionar_quarto.tipo_quarto.num_camas, vetor_quarto[opcao].num_camas);
         strcpy(adcionar_quarto.tipo_quarto.descricao, vetor_quarto[opcao].descricao);
         adcionar_quarto.status = 0;

         printf("\nInforme o Número do Quarto: ");
         adcionar_quarto.num_quarto = informe_quarto_repetido();
         strcpy(adcionar_quarto.estado,"Indefinido");
         TelaCadastro("Novo Quarto");
         printf("\nO seguinte quarto será adcionado ao seu Hotel..: ");
         printf("\n-------------------------------------------------------------");
         printf("\n TIPO DO QUARTO: \t%s - Nº%d\n",adcionar_quarto.tipo_quarto.tipo, adcionar_quarto.num_quarto);
         printf(" Quarto com %s cama(s).", adcionar_quarto.tipo_quarto.num_camas);
         printf("\n DESCRIÇÃO:\n");
         printf(" %s\n",adcionar_quarto.tipo_quarto.descricao);
         printf("---------------------------------------------------\n");

         printf("Confirmar?/cancelar? 1/2.: ");
         scanf("%d", &confirmar);
             if(confirmar==1)
                 gravar_quarto(&adcionar_quarto);
            else
                printf("\nProcesso de adição cancelado...\n\n");




system("PAUSE");

}



void cadastrar_novo_tipo_quarto(){

    TelaCadastro("Novo Tipo De Quarto");
    Tipo_Quarto tipo_quarto;
    int confirmar;
    setbuf(stdin, NULL);
    printf(" Novo Tipo: ");
    scanf("%s", tipo_quarto.tipo);

    setbuf(stdin, NULL);
    printf(" Número de Camas: ");
    scanf("%s",tipo_quarto.num_camas);

    setbuf(stdin, NULL);
    printf(" Descreva-o: ");
    fgets(tipo_quarto.descricao,300, stdin);
    printf("\n-----------------------------------------------------------------------\n");
     printf(" Confirmar?/cancelar? 1/2.: ");
    scanf("%d", &confirmar);
    if(confirmar==1){
    gravar_tipo_quarto(&tipo_quarto);
    }
    else{

        printf("\n\n Cadastramento Cancelado... :(\n\n");
    }
    system("PAUSE");
}



void  reservar_um_quarto(Quarto* Q){


    TelaCadastro("Fazer Reserva");
    setbuf(stdin,NULL);
    int confirmar;
    printf("\n Nome do Hóspede ");
    scanf("%s", Q->hospedagem.pessoa.nome);
    setbuf(stdin,NULL);
    printf(" Cadastro de Pessoa Física(CPF): ");
    scanf("%s", Q->hospedagem.pessoa.cpf);
    printf("\n **Informe a Data Ex.: 15/10/2017\n");
    do{
        printf(" Check-in: Dia: ");
        scanf("%d", &Q->hospedagem.in_dia);
        printf("\t   Mês: ");
        scanf("%d", &Q->hospedagem.in_mes);
        printf("\t   Ano: ");
        scanf("%d", &Q->hospedagem.in_ano);
        printf("\n Data Check-in.: %d/%d/%d",Q->hospedagem.in_dia,Q->hospedagem.in_mes,Q->hospedagem.in_ano);
        printf("\n Confirmar?/cancelar? 1/2.: ");
         scanf("%d", &confirmar);

    }while(confirmar==2);

     do{
        printf(" Check-Out: Dia: ");
        scanf("%d", &Q->hospedagem.out_dia);
        printf("\t   Mês: ");
        scanf("%d", &Q->hospedagem.out_mes);
        printf("\t   Ano: ");
        scanf("%d", &Q->hospedagem.out_ano);
        printf("\n Data Check-Out.: %d/%d/%d",Q->hospedagem.out_dia,Q->hospedagem.out_mes,Q->hospedagem.out_ano);
        printf("\n Confirmar?/cancelar? 1/2.: ");
         scanf("%d", &confirmar);
    }while(confirmar==2);
    Q->num_incricao =  (rand() % 1000);
    printf("\n Número de Inscrição.: %d", Q->num_incricao);
    printf("\n A Reserva foi Efetuada... ;)\n\n");
     printf("\n\n\n**Obs: O número da inscrição é gerado automaticamente...\n");
    system("PAUSE");


    Q->status = 2;

}




//------HOSPEDE----------//

void fazer_check_in_de_reserva(Quarto* Q){

    time_t data;
    time(&data);
    struct tm *tm = localtime(&data);
    TelaCadastro("Novo Hóspede");
    setbuf(stdin,NULL);
    printf("\n Nome do Hóspede.: %s ", Q->hospedagem.pessoa.nome);

    printf("\n Cadastro de Pessoa Física(CPF).: %s",Q->hospedagem.pessoa.cpf);
    Q->hospedagem.in_dia= tm->tm_mday;
    Q->hospedagem.in_mes= tm->tm_mon+1;
    Q->hospedagem.in_ano= tm->tm_year;
    printf("\n Data de Check-In: %d/%d%/%d",  Q->hospedagem.in_dia,Q->hospedagem.in_mes,Q->hospedagem.in_ano+1900);
    printf("\n Sua estadia será até.: %d/%d/%d",Q->hospedagem.out_dia,Q->hospedagem.out_mes,Q->hospedagem.out_ano);
    printf("\n Número de Inscrição.: %d\n\n", Q->num_incricao);
    Q->status = 1;
    printf("\n\n\n O quarto agora está ocupado... ;)\n\n");
    system("PAUSE");
}




void cadastrar_hospede(Quarto* Q){

    time_t data;
    time(&data);
    struct tm *tm = localtime(&data);
    TelaCadastro("Novo Hóspede");
    setbuf(stdin,NULL);
    printf("\n Nome do Hóspede.: ");
    scanf("%s", Q->hospedagem.pessoa.nome);
    setbuf(stdin,NULL);
    printf("Cadastro de Pessoa Física(CPF).: ");
    scanf("%s", Q->hospedagem.pessoa.cpf);
    Q->num_incricao =  (rand() % 1000);
    Q->hospedagem.in_dia= tm->tm_mday;
    Q->hospedagem.in_mes= tm->tm_mon+1;
    Q->hospedagem.in_ano= tm->tm_year;
   printf(" Data de Check-In: %d/%d%/%d",  Q->hospedagem.in_dia,Q->hospedagem.in_mes,Q->hospedagem.in_ano+1900);
    printf("\n Número da Inscrição.: %d", Q->num_incricao);

    printf("\n\n\n**Obs: O número da inscrição é gerado automaticamente...\n\n\n\n\n");
    Q->status = 1;
    system("PAUSE");
}













//------BUFFET----------//


int cod_prato_do_buffet(){

    ItemRefeicao item;
    int cod =0;
    buff = abrir("rb", "buffet.txt", buff);
    while(fread(&item,sizeof(ItemRefeicao),1,buff)){
            cod++;
    }
    fclose(buff);
    return cod+1;

}

void cadastrar_uma_novo_prato(){

    int cod_prato = cod_prato_do_buffet();
   ItemRefeicao IR;
    TelaCadastro("Novo Prato");
    int confirmar;
    printf("\n\nNovo Tipo De Prato - Nome: ");
    setbuf(stdin,NULL);
    scanf("%s", IR.nome);

    printf("Decrição do prato ou modo de preparo: ");
    setbuf(stdin, NULL);
    fgets(IR.descricao,100,stdin);

    printf("Preço: ");
    setbuf(stdin, NULL);

    scanf("%f", &IR.preco);
    IR.num_refeicao = cod_prato;

     printf("\n---------------------------------------------------\n");
        printf(" Confirmar?/cancelar? 1/2.: ");
        scanf("%d", &confirmar);
        if(confirmar == 1){
           gravar_buffet(&IR);
        }
        else{
            printf("\n Processo de Cadastramento Cancelado... :(\n\n");
        }
    system("PAUSE");


}




void pedir_um_prato(char *hospede_atual){

     buff = abrir("rb", "buffet.txt", buff);
     refei = abrir("ab", "refeicao.txt", refei);

    ItemRefeicao *vetor_refeicao=NULL;
    ItemRefeicao item;
    Refeicao *pedido_comida = NULL;
    float preco_total=0;
    int i;
    int opcao, acum,cont = 0,confirmar;


   TelaPedido();
   printf("\nEstá com apetite? O que deseja comer hoje?");
   printf("\nQuando terminar digite zero.\n\n");


    while(fread(&item, sizeof(ItemRefeicao),1,buff)){
        vetor_refeicao = (ItemRefeicao*)realloc(vetor_refeicao,(cont+1)*sizeof(ItemRefeicao));

        strcpy(vetor_refeicao[cont].nome, item.nome);
        strcpy(vetor_refeicao[cont].descricao, item.descricao);
        vetor_refeicao[cont].preco = item.preco;

        printf(" %d - %s: R$ %.2f\n", cont+1,vetor_refeicao[cont].nome, vetor_refeicao[cont].preco);
        printf(" Descrição do Prato: \n %s\n", vetor_refeicao[cont].descricao);
        printf("-------------------------------------------\n");

        cont++;
    }

    printf("Digite o que quer comer: ");
    scanf("%d", &opcao);

    acum=0;
    while(opcao>0&&opcao<=cont){

        pedido_comida = (Refeicao*)realloc(pedido_comida,( acum+1)*sizeof(Refeicao));
        strcpy(pedido_comida[acum].item_comida.nome,vetor_refeicao[opcao-1].nome);
        strcpy(pedido_comida[acum].item_comida.descricao,vetor_refeicao[opcao-1].descricao);
        strcpy(pedido_comida[acum].cpf, hospede_atual);
        pedido_comida[acum].item_comida.preco = vetor_refeicao[opcao-1].preco;
        acum++;
        printf("Digite o que quer comer: ");
        scanf("%d", &opcao);

    }
    TelaPedido();
    printf("\n Seu Pedido foi:\n");
    for(i=0;i<acum;i++){


    printf(" %s - - - -%.2f\n", pedido_comida[i].item_comida.nome,pedido_comida[i].item_comida.preco);
    preco_total = preco_total + pedido_comida[i].item_comida.preco;

    }
    printf(" \n Preço total a pagar: %.2f\n", preco_total);
    printf("-------------------------------------------\n\n");


    printf("\n Deseja salvar seu pedido? ;)");
    printf("\n Confirmar?/cancelar? 1/2.: ");
    scanf("%d", &confirmar);
    if(confirmar==1){
            for(i=0;i<acum;i++){

            if(fwrite(&pedido_comida[i], sizeof(Refeicao),1,refei)!=1){
                printf("\n\nErro na gravação do seu pedido!!\n\n");
                exit(1);
            }
    }
    printf("\n\n\n Pedido realizado com sucesso...");
    printf("\n Bom apetite!!\n\n");



    }
    else
        printf("\n Pedido cancelado... :(\n\n");
        system("PAUSE");
        fclose(refei);
        fclose(buff);
        free(vetor_refeicao);
        free(pedido_comida);


}











//------FUNCIONARIO----------//


void Preencher_Funcionario(){

	int confirmar;
	Funcionario funcionario;

	    TelaCadastro("Funcionário");


	printf("\n\n Nome de Funcionário:  ");
    setbuf(stdin,NULL);
	scanf("%[^\n]", funcionario.pessoa.nome);

	 if(funcionario.pessoa.nome[0]==48){
	     printf("\n---------------------------------------------------------------");
         printf("\nCadastramento Cancelado!...\n\n");
         system("PAUSE");
         return;
	 }

	setbuf(stdin,NULL);

	printf(" Digite o CPF : ");
	scanf("%[^\n]", funcionario.pessoa.cpf);
	setbuf(stdin,NULL);
	printf(" Informe Telefone: ");
	scanf("%[^\n]", funcionario.pessoa.telefone);
	setbuf(stdin,NULL);

	printf(" Cargo do Funcionário: ");
	scanf("%[^\n]", funcionario.cargo);
	setbuf(stdin,NULL);

	printf(" Seu Salário R$: ");
	scanf("%f", &funcionario.salarios);
	setbuf(stdin,NULL);
	printf("---------------------------------------------------------------");
	printf("\n Confirmar?/cancelar? 1/2.: ");
        scanf("%d", &confirmar);

            if(confirmar==1)
              Gravar_Funcionario(&funcionario);
            else
                printf("\nCadastramento Cancelada...\n\n");

system("PAUSE");

}











//------SERVICO----------//



void cadastrar_novo_servico(){


    TelaCadastro("Novo Serviço");
    Servico tipo_servico;

    int confirmar;
    setbuf(stdin, NULL);
    printf("\n\n  Novo Tipo de Serviço.: ");
    scanf("%s", tipo_servico.tipoServico);

    setbuf(stdin, NULL);
    printf(" Preço do Serviço R$: ");
    scanf("%f",&tipo_servico.precoServico);

    setbuf(stdin, NULL);
    printf(" Descrição: ");
    fgets(tipo_servico.descricao,300, stdin);
    printf("\n---------------------------------------------------\n");
        printf(" Confirmar?/cancelar? 1/2.: ");
        scanf("%d", &confirmar);
     if(confirmar==1)
	gravar_tipo_servico(&tipo_servico);
	else
        printf("\n\n Cadastramento cancelado...:( \n\n");

    system("PAUSE");
}


void pedir_um_servico(char* hospede_atual){

	Servico viz_servico;
	Servico *vetor_servico=NULL;
	consumoServico *pedir_servico=NULL;



	serv = abrir("rb", "tipos_servico.txt", serv);
	int cont=0;
	int i=0,k, opcao;
	float soma_pedido;



	while(fread(&viz_servico, sizeof(Servico),1,serv)){
	vetor_servico = (Servico*)realloc(vetor_servico,(cont+1)*sizeof(Servico));
	strcpy(vetor_servico[cont].tipoServico, viz_servico.tipoServico);
	vetor_servico[cont].precoServico = viz_servico.precoServico;
	strcpy(vetor_servico[cont].descricao, viz_servico.descricao);


	cont++;
	}



	TelaPedido();
	printf("\n");
	for(i=0;i<cont;i++){

		printf(" %d - %s R$:  %.2f\n", i+1,vetor_servico[i].tipoServico, vetor_servico[i].precoServico);
		printf(" Descrição: %s\n", vetor_servico[i].descricao);


	}

	printf("Digite o Servico ");
    scanf("%d", &opcao);
    i=0;


    while(opcao>0&&opcao<=cont){

        pedir_servico = (consumoServico*)realloc(pedir_servico,( i+1)*sizeof(consumoServico));
        strcpy(pedir_servico[i].pedido_servico, vetor_servico[opcao-1].tipoServico);
        pedir_servico[i].precoServicoUsuario = vetor_servico[opcao-1].precoServico;
        strcpy(pedir_servico[i].cpf, hospede_atual);
        i++;
        printf("Digite o Serviço: ");
        scanf("%d", &opcao);


    }


	soma_pedido = 0;
	TelaPedido();
	printf("\n\nSeu pedido foi:\n ");
	for(k=0;k<i;k++){
		printf(" \nTipo de Serviço: %s ", pedir_servico[k].pedido_servico );
		printf(" \nPreço: %.2f", pedir_servico[k].precoServicoUsuario);
		printf("\n-------------------------------------------------------\n");
		soma_pedido +=  pedir_servico[k].precoServicoUsuario;
	}

	printf("\n\nPreço total a pagar: %.2f\n\n", soma_pedido);
	system("PAUSE");
	fclose(serv);
    gravar_consumo_servico_usuario(pedir_servico);

}
void  gravar_resposta(FILE* reclm, Reclamacoes reclama){
    temporario = abrir("wb", "temporario.txt", temporario);
    rewind(reclm);
    Reclamacoes reclama_aux;

    while(fread(&reclama_aux, sizeof(Reclamacoes),1,reclm)){

            if(reclama_aux.num_reclamacao == reclama.num_reclamacao){
                reclama_aux.status = 2;
                strcpy(reclama_aux.resposta, reclama.resposta);
                fwrite(&reclama_aux, sizeof(Reclamacoes),1,temporario);
            }
            else{
                fwrite(&reclama_aux, sizeof(Reclamacoes),1,temporario);
            }

    }
     fclose(reclm);
        remove("reclamacoes.txt");
    fclose(temporario);
     rename("temporario.txt","reclamacoes.txt");




}










//------RECLAMACAO----------//


void responder_reclamacao(){
    TelaReclamacao();
     reclm = abrir("rb", "reclamacoes.txt", reclm);
     int cont=0;
     Reclamacoes reclama;
     int *indice_reclamacoes=NULL;
     int i=0,j=0;
    int opcao;
    printf("\n Mensagens Aguardando respostas..:\n\n\n");
     while(fread(&reclama,sizeof(Reclamacoes),1,reclm)){

        if(reclama.status == 1){
          indice_reclamacoes = (int*)realloc(indice_reclamacoes,( cont+1)*sizeof(int));


        printf("%d -Mensagem do Quarto %d\n",cont+1, reclama.num_quarto);
        printf("|%s|\n",reclama.reclamacao);
        printf("------------------------------------------------------------\n");
        indice_reclamacoes[cont] = reclama.num_reclamacao;

        cont++;

    }

     }
    if(cont>0){
     printf("\nDigite a número da Mensagem que deseja responder: ");

    scanf("%d", &opcao);
    rewind(reclm);
    fseek(reclm,indice_reclamacoes[opcao-1]*(sizeof(Reclamacoes)),SEEK_SET);
    fread(&reclama,sizeof(Reclamacoes),1,reclm);
    printf("\nIncorfomidade - |%s|", reclama.reclamacao);
    printf("\nPara responder escreva-a abaixo:\n");
    printf(": ");
    setbuf(stdin,NULL);
    scanf("%[^\n]s",reclama.resposta);
    gravar_resposta(reclm, reclama);
    }else{
        printf("\n\n Nenhuma mensagem para responder...;)\n\n");
        fclose(reclm);
    }
    system("PAUSE");


}



void reclamacao(char* hospede_atual, int num_quarto){


    TelaReclamacao();
    Reclamacoes reclama;
    int num_reclamcao;
    int confirmar;
    num_reclamcao = cont_reclamacoes();


    setbuf(stdin, NULL);
    printf("\n Qual é o seu problema ou o motivo do seu descontentamento? ");
    printf("\nResponderemos o mais breve possível! ;)\n ");
    printf("\n Informe o seu problema.: ");
    scanf("%[^\n]s", reclama.reclamacao);
     printf("---------------------------------------------------\n");
        printf("Confirmar?/cancelar? 1/2.: ");
        scanf("%d", &confirmar);

            if(confirmar==1){
            	strcpy(reclama.resposta, " ");
    			strcpy(reclama.cpf,hospede_atual);
    			reclama.num_quarto = num_quarto;
  			    reclama.num_reclamacao = num_reclamcao;
  			    reclama.status =1;

				gravar_reclamacao(reclama);






			}

            else
                printf("\n Reclamação Cancelada...\n\n");

            system("PAUSE");






}



