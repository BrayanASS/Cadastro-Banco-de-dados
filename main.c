#include <stdlib.h> //Esta biblioteca contém várias funções e constantes básicas
#include <stdio.h>  //É um cabeçalho da biblioteca padrão do C
#include <locale.h> //Define as configurações de uma determinada localização, definindo acentos e formatos de datas especificas
#include <string.h>  //Esta biblioteca contém uma série de funções para manipular strings
#include <time.h>  //Esta biblioteca contém várias funções e constantes que medem tempo
 
//struct da parte de gestão de contas
typedef struct ficha_conta CONTA;
struct ficha_conta {
  int agencia;
  long int numero;
  float saldo;
  char descricao[10][100];
  int dia[10];
};

//struct da parte de gestão de clientes
typedef struct ficha_cliente CLIENTE;
struct ficha_cliente{
  char nome[30];
  char endereco[30];
  int codigo;
  long int cpf;
  long int telefone;
  CONTA conta[2];
};

//listagem das funções existentes do programa
void menu();
void excluir();
void cadastrarCliente();
void limparBuffer();
void listarClientes();
void buscarClientes();
void atualizar();
void gerenciar_clientes();
void gerenciar_contas();
void listarContas();
void cadastrarContas();
void contasCliente();
int saque();
int deposito();
void transferencia();
void exibirExtrato();

//setado função cabeçalho
void cabecalho() {
  system("clear");
  printf("================== $ Banco $ ===================\n\n");
}

//menu principal
int main() {
    setlocale(LC_ALL, "Portuguese"); //comando da biblioteca <locale.h> para dar a opção de acentuação nos "printf"
    char opcao;
  
    do{
      menu();
      scanf("%c",&opcao);
      if((opcao>='a')&&(opcao<='z')){
        opcao=opcao-32;
      }
        switch(opcao){
        case 'C':               //função do comando "C" no menu principal (gerenciar clientes)
          gerenciar_clientes();
          getchar();
          scanf("%c",&opcao);
          if((opcao>='a')&&(opcao<='z')){
            opcao=opcao-32;
          }
          if(opcao=='C'){
            cadastrarCliente(); //função do comando "C" no menu "gerenciar clientes"
          }
          else if(opcao=='L'){  //função do comando "L" no menu "gerenciar clientes"
            listarClientes();
          }
          else if(opcao=='B'){  //função do comando "B" no menu "gerenciar clientes"
            buscarClientes();
          }
          else if(opcao=='A'){  //função do comando "A" no menu "gerenciar clientes"
            atualizar(); 
          }
          else if(opcao=='E'){  //função do comando "E" no menu "gerenciar clientes"
            excluir();
          }
        break;

        case 'T':
          gerenciar_contas();   //função do comando "C" no menu principal (gerenciar clientes)
          getchar();
          scanf("%c",&opcao);
          if((opcao>='a')&&(opcao<='z')){
            opcao=opcao-32;
          }  
          if(opcao=='R'){       //função do comando "R" no menu "gerenciar contas"
            listarContas();
          }
          else if(opcao=='C'){  //função do comando "C" no menu "gerenciar contas"
            cadastrarContas();
          }
          else if(opcao=='L'){  //função do comando "L" no menu "gerenciar contas"
            contasCliente();
          }
          else if(opcao=='W'){  //função do comando "W" no menu "gerenciar contas"
            cabecalho();
            printf("Realizando saque:\n\n");
            saque(0); 
          }
          else if(opcao=='D'){  //função do comando "D" no menu "gerenciar contas"
            cabecalho();
            printf("Realizando deposito:\n\n");
            deposito(0); 
          }
          else if(opcao=='T'){  //função do comando "T" no menu "gerenciar contas"
            cabecalho();
            printf("Realizando transferência:\n\n");
            transferencia();           
          }
          else if(opcao=='E'){  //função do comando "E" no menu "gerenciar contas"
            exibirExtrato();
          }
        break;

        case 'S':               //caso o comando "S" seja dado, o programa retorna ao menu
        return 0;
        break;
    }
  }
  while(opcao!='S');
}


//=============================== FUNÇÃO LIMPAR BUFFER =================================//


//Função que limpa buffer quando há muitos caracteres para evitar leitura de opções que devem escolhidas pelo usuário

void limparBuffer() {
  char c;
  while((c = getchar()) != '\n' && c != EOF);
}


//======================================== MENU ========================================//


//Função para mostrar o menu principal com o comando "system("clear");" para limpar o menu assim que uma opção for escolhida

void menu() {
  system("clear");
  printf("=============== Bem vindo! =================\n\n");
  printf("Digite um comando para prosseguir:\n");
  printf("C - Gerenciar Clientes\n");
  printf("T - Gerenciar Contas\n");
  printf("S - Sair\n");
}


//======================== FUNÇÃO MENU GERENCIAR CLIENTES =============================//


//Função mostrada ao selecionar a opção "Gerenciar cliente" no menu principal, dando novas opções para manipular os dados dos clientes

void gerenciar_clientes() {
  system("clear");
  printf("============ Gerenciar Clientes ============\n\n");
  printf("Digite um comando para prosseguir:\n");
  printf("C - Cadastrar um cliente\n");
  printf("L - Listar todos os clientes cadastrados\n");
  printf("B - Buscar cliente já cadastrados\n");
  printf("A - Atualizar um cliente cadastrado\n");
  printf("E - Excluir um cliente cadastrado\n");
  printf("S - Sair\n");
}


//=========================== FUNÇÃO MENU GERENCIAR CONTAS ============================//


//Função mostrada ao selecionar a opção "Gerenciar contas" no menu principal, dando novas opções para manipular os dados das contas de cada cliente

void gerenciar_contas() {
  system("clear");
  printf("============ Gerenciar Contas ============\n\n");
  printf("Digite um comando para prosseguir:\n");
  printf("R - Listagem de todas as contas cadastradas.\n");
  printf("C - Cadastrar uma conta para um cliente.\n");
  printf("L - Listar todas as contas de um cliente.\n");
  printf("W - Realizar um saque em uma conta.\n");
  printf("D - Realizar um depósito em uma conta.\n");
  printf("T - Realizar transferência entre contas.\n");
  printf("E - Exibir extrato de uma conta.\n");
  printf("S - Sair.\n");
}


//============================== FUNÇÃO CADASTRAR CLIENTES =============================//


//Ao escrever a opção "C" a função cadastrar clientes é acionada, possibilitando que o usuário possa adicionar novos clientes, necessitando de dados como o Nome, Endereço, Código(apenas numeros), CPF(apenas números) e Telefone(apenas números)
 
void cadastrarCliente() {
  FILE* arquivo;  //Arquivo que contém todos os dados de clientes junto às suas contas
  CLIENTE cliente; //Struct dos clientes
  char nome[30];
  char endereco[30];
  int codigo=-1, i=0,j=0,k=0;
  long int cpf=-1;
  long int telefone=-1;
  CONTA conta[2];

  char o;

  arquivo = fopen("clientes.txt", "ab+");
  fflush(arquivo);
  if(arquivo == NULL) {
    printf("\nProblemas na abertura do arquivo\n\n");
    getchar();
    scanf("%c",&o);
   }
   else{
    //Loop que possibilita o cadastro de vários clientes sem que haja a mesma quantidade de aberturas de arquivos
    do{
      i=0;
      cabecalho();
      printf("Cadastro de cliente:\n\n");
      fflush(stdin);
      printf("Digite o nome: ");
      getchar();
      fgets(nome,30,stdin);
      
      //------------------------- Verificação de Registro -------------------------//


      //Função não declarada a fim de verificar a existência do registro de um determinado cliente
      
      fflush(stdin);
      printf("Digite o endereço: ");
      fgets(endereco,30,stdin);

      printf("Digite o telefone: ");
      scanf("%li",&telefone);
            
      if(telefone>0){
        rewind(arquivo);
        //Loop que verifica se o telefone já foi cadastrado por outro cliente
        while(fread(&cliente, sizeof(CLIENTE), 1, arquivo)==1){
          if(telefone==cliente.telefone){
            printf("Telefone já cadastrado!\n");
            getchar();
            scanf("%c",&o);
            return;
          }
        }
      }
      else{
        //Loop para que se o cliente digitar um valor menor que 0 ou letra haja um erro
        while(telefone<=0){
          printf("\nFormato de telefone incorreto! (0 para sair)\n");
          printf("\nDigite o telefone: ");
          limparBuffer();
          scanf("%li",&telefone);  
          if(telefone==0){
            fclose(arquivo);
            return;
          }
        }
      }

      printf("Digite o código: ");
      scanf("%i",&codigo);
      if(codigo>0){
        rewind(arquivo);
        //Loop que verifica se o codigo já foi cadastrado por outro cliente
        while(fread(&cliente, sizeof(CLIENTE), 1, arquivo)==1){
          if(codigo==cliente.codigo){
            printf("Código já cadastrado!\n");
            getchar();
            scanf("%c",&o);
            return;
          }  
        }
      }
      else{
        //Loop para que se o cliente digitar um valor menor que 0 ou letra haja um erro
        while(codigo<0){
          printf("\nFormato de codigo incorreto! (0 para sair)\n");
          printf("\nDigite o codigo: ");
          limparBuffer();
          scanf("%i",&codigo);
          getchar();   
          if(codigo==0){
            fclose(arquivo);
            return;
          } 
        }
      }

      printf("Digite o CPF/CNPJ: ");
      scanf("%li",&cpf);
      if(cpf>0){
        rewind(arquivo);
        //Loop que verifica se o codigo já foi cadastrado por outro cliente
        while(fread(&cliente, sizeof(CLIENTE), 1, arquivo)==1){
          if(cpf==cliente.cpf){
            printf("CPF/CNPJ já cadastrado!\n");
            getchar();
            scanf("%c",&o);
            return;
          }
        }
      }
      else{
      //Loop que verifica se o codigo já foi cadastrado por outro cliente
        while(cpf<=0){
          printf("\nFormato de CPF/CNPJ incorreto! (0 para sair)\n");
          printf("\nDigite o CPF/CNPJ: ");
          limparBuffer();
          scanf("%li",&cpf);
          getchar();
          if(cpf==0){
            fclose(arquivo);
            return;
          } 
        }
      } 

      for(i=0;i<30;i++){
        cliente.nome[i]=nome[i];
        cliente.endereco[i]=endereco[i];
      }
      cliente.codigo=codigo;
      cliente.cpf=cpf;
      cliente.telefone=telefone;
      //Setar um valor "0" caso a conta ainda não exista (ainda não foi cadastrada)
      for(i=0;i<2;i++){ 
        cliente.conta[i].numero=0;
        cliente.conta[i].saldo=0.00;
        cliente.conta[i].agencia=0;
        cliente.conta[i].dia[i]=0;
        for(k=0;k<10;k++){
          for(j=0;j<100;j++){
            cliente.conta[i].descricao[k][j]='\0';
          }
        }
      }
      fwrite(&cliente, sizeof(CLIENTE), 1, arquivo);

      printf("\nCadastrar outro cliente (s/n)? ");
      getchar();
      scanf("%c",&o);
      if((o>='A')&&(o<='Z')){
        o=o+32;
      }
    }while(o == 's');
    fclose(arquivo);
  }
}


//=============================== FUNÇÃO LISTAR CLIENTES ================================//


//Função com o objetivo de mostrar todos os clientes, demonstrando respectivamente seu nome, endereço, código, CPF/CNPJ e telefone, com os nomes de cada cliente em ordem alfabética 

void listarClientes() {
  printf("Ovo da páscoa\n");
  cabecalho();
  FILE* arquivo;
  CLIENTE cliente;
  char nome[100][30];
  char aux[30],o;
  int i=0,j=0, qtd_nomes=0;

  arquivo = fopen("clientes.txt","rb");
  printf("Listagem de todos os clientes:\n\n");

  //---------------------- Ordem alfabética ------------------------//

  rewind(arquivo);
  //Loop para contabilizar a quantidade nomes existentes e resgatar os mesmo
  while(fread(&cliente.nome, sizeof(CLIENTE),1,arquivo)==1){
    for(i=0;i<30;i++){
      nome[j][i]=cliente.nome[i];  //"Resgate" dos nomes
    }
    j++;
    qtd_nomes++;
  }

  //Com a quantidade de nomes esse loop duplo faz uma comparação com o próximo nome, se ele tiver uma diferença (>0), o nome é trocado para o próximo bloco da matriz com a ajuda de uma "aux", e assim por diante
  for (i = 1; i < qtd_nomes; i++) { // Precisa ler apenas a quantidade de nomes existentes
    for (j = 1; j < qtd_nomes; j++) {
      if (strcmp(nome[j - 1], nome[j]) > 0) {
        strcpy(aux, nome[j - 1]);
        strcpy(nome[j - 1], nome[j]);
        strcpy(nome[j], aux);
      }
    }
  }
  
  //----------------------------------------------------------------//

  //Os nomes em ordem alfabética da matriz são comparados com os nomes do arquivo, quando a condicional entra em um valor correto ela imprime os dados, um primeiro loop faz essa leitura do arquivo inteiro para cada nome da matriz
  for(i=0;i<qtd_nomes;i++){
    rewind(arquivo); // Esse rewind é o rolê
    while(fread(&cliente.nome, sizeof(CLIENTE),1,arquivo)==1){
      if(strcmp(nome[i],cliente.nome)==0){
        printf("Nome.....: %s",cliente.nome);
        printf("Endereço.: %s",cliente.endereco);
        printf("Código...: %i\n",cliente.codigo);
        printf("CPF/CNPJ.: %li\n",cliente.cpf);
        printf("Telefone.: %li\n",cliente.telefone);
        printf("\n----------------------------------------------\n\n");
      }
    }
  }
  fclose(arquivo);
  getchar();
  scanf("%c",&o);
}


//============================= FUNÇÃO BUSCAR CLIENTES ================================//


//Função para procurar determinado cliente a partir de duas requisições, por código ou por CPF/CNPJ, sendo uma delas obrigatório, retornando o nome, endereço, código, CPF/CNPJ e o telefone do cliente e dando a opção de refazer a busca (Repetir a ação)

void buscarClientes() {

    FILE* arquivo;
    CLIENTE cliente;
    char nome[30];
    int codigo=-1;
    long int cpf=-1;
    char opcao, o='s';
    int i;


    arquivo = fopen("clientes.txt", "rb");
    if(arquivo == NULL){
      printf("Problemas na abertura do arquivo!\n");
      fflush(stdin);
      scanf("%c",&o);
      getchar();
      return;
    }
    do{ //O loop é usado apenas para a busca de mais de um cliente se desejado pelo usuário
      cabecalho();
      printf("Buscando cliente:\n\n");
      printf("Como deseja buscar pelo cliente:\n");
      printf("C - Por código\n");
      printf("R - Por CPF/CNPJ\n");
      fflush(stdin);
      getchar();
      scanf("%c", &opcao);
      if((opcao>='a')&&(opcao<='z')){
        opcao=opcao-32;
      }
      //As condicionais verificão a opção selecionada pelo usuário
      if (opcao=='C'){ //Opção para o código
        i=0;
        cabecalho(); //Após a escolha o a função cabeçalho é chamada
        printf("Digite o código a pesquisar: ");
        scanf("%i",&codigo);
        while(codigo<=0){
          printf("Valor inválido (0 para sair)!\n");
          limparBuffer();
          printf("Digite o código: ");
          scanf("%i",&codigo);
          if(codigo==0){
            fclose(arquivo);
            return;
          }
        }
        rewind(arquivo);  //O rewind é necessário para que o compilador não leia a partir do final do arquivo
        while(fread(&cliente, sizeof(CLIENTE), 1, arquivo) == 1){
          if(codigo == cliente.codigo){
            i++;
            cabecalho();
            printf("Nome.....: %s",cliente.nome);
            printf("Endereço.: %s",cliente.endereco);
            printf("Código...: %i\n",cliente.codigo);
            printf("CPF/CNPJ.: %li\n",cliente.cpf);
            printf("Telefone.: %li\n",cliente.telefone);
            printf("\n----------------------------------------------\n\n");
            if(fread(&cliente, sizeof(CLIENTE), 1, arquivo) != 1){
              break;
            }
          }
        }
        if(i==0){
          printf("Cliente não encontrado\n");
        }
      }
      else if(opcao=='R'){ //Opção para o cpf/cnpj
        i=0;
        cabecalho(); //Após a escolha o a função cabeçalho é chamada
        printf("Digite o CPF/CNPJ a pesquisar: ");
        scanf("%li",&cpf);
        while(cpf<=0){
          printf("Valor inválido (0 para sair)!\n");
          limparBuffer();
          printf("Digite o CPF/CNPJ: ");
          scanf("%li",&cpf);
          if(cpf==0){
            fclose(arquivo);
            return;
          }
        }
        rewind(arquivo);  //O rewind é necessário para que o compilador não leia a partir do final do arquivo
        while(fread(&cliente, sizeof(CLIENTE), 1, arquivo) == 1){
          if(cpf == cliente.cpf){
            i++;
            cabecalho();
            printf("Nome.....: %s",cliente.nome);
            printf("Endereço.: %s",cliente.endereco);
            printf("Código...: %i\n",cliente.codigo);
            printf("CPF/CNPJ.: %li\n",cliente.cpf);
            printf("Telefone.: %li\n",cliente.telefone);
            printf("\n----------------------------------------------\n\n");
            if(fread(&cliente, sizeof(CLIENTE), 1, arquivo) != 1){
              break;
            }
          }
        }
        if(i==0){
          printf("Cliente não encontrado\n"); 
        } 
      }
      if((opcao!='R')&&(opcao!='C')){
        printf("Opção digitada incorreta!");
        fflush(stdin);
        scanf("%c",&o);
        getchar();
        fclose(arquivo);
        fflush(stdin);
        return;
      }
    printf("Repetir a ação (s/n)?\n");
    getchar();
    scanf("%c",&o);
    if((o>='A')&&(o<='Z')){
      o=o+32;
    }
  }
  while(o=='s');
  fclose(arquivo);
  getchar();
}


//=============================== FUNÇÃO ATUALIZAR ===============================//


//Função com o objetivo de mudar os dados de determinado cliente, tendo como primeiras requisições o código e o CPF/CNPJ de um determinado cliente já cadastrado, os dados do mesmo sera retornado juntamente com a opção de atualizar as informações separadamente (requisitando um novo nome, telefone, endereço, código, CPF/CNPJ do cliente) 

void atualizar() {

  FILE* arquivo;
  FILE* temp;
  CLIENTE cliente;
  char o,a='s';
  char nome[30];
  char endereco[30],descricao[10][100],desc[10][100];
  int codigo=-1,j=0, i,agencia=0,ag,dia[10],D[10];
  float saldo,sa;
  long int cpf=-1,numero,nu;
  long int telefone, salvoT, salvoCPF;
  int salvoC;
 
  arquivo = fopen("clientes.txt","rb");
  temp = fopen("tmp.txt","wb"); //Arquivo temporário

  if((arquivo==NULL)||(temp==NULL)){
    printf("Problemas na abertura do arquivo!\n");
    getchar();
  }
  else{
    cabecalho();
    fflush(stdin);
    printf("Atualizando cliente:\n\n");
    printf("Digite os dados do cliente a ser atualizado:\n\n");
    printf("Digite o código: ");
    scanf("%i",&codigo);
    while(codigo<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o código: ");
      scanf("%i",&codigo);
      if(codigo==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return;
      }
    }
    printf("Digite o CPF/CNPJ: ");
    scanf("%li",&cpf);
    while(cpf<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o CPF/CNPJ: ");
      scanf("%li",&cpf);
      if(cpf==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return;
      }
    }
    
    rewind(arquivo);
    while(fread(&cliente, sizeof(CLIENTE), 1, arquivo) == 1){
      if((codigo=cliente.codigo)&&(cpf==cliente.cpf)){
          printf("\n============== Cliente Cadastrado ==============\n");
          printf("\nNome.....: %s",cliente.nome);
          printf("Endereço.: %s",cliente.endereco);
          printf("Codigo...: %i\n",cliente.codigo);
          printf("CPF/CNPJ.: %li\n",cliente.cpf);
          printf("Telefone.: %li\n",cliente.telefone);
          printf("\n------------------------------------------------\n\n");
          a='n';
          //Resgate dos valores da conta existente do cliente para que o mesmo continue com seus dados salvos
          salvoC=cliente.codigo;
          salvoCPF=cliente.cpf;
          salvoT=cliente.telefone;
          agencia=cliente.conta[0].agencia;
          numero=cliente.conta[0].numero;
          saldo=cliente.conta[0].saldo;
          for(j=0;j<10;j++){
            dia[j]=cliente.conta[0].dia[j];
            for(i=0;i<100;i++){
              descricao[j][i]=cliente.conta[0].descricao[j][i];
            }
          }
          ag=cliente.conta[1].agencia;
          nu=cliente.conta[1].numero;
          sa=cliente.conta[1].saldo;
          for(j=0;j<10;j++){
            D[j]=cliente.conta[1].dia[j];
            for(i=0;i<100;i++){
              desc[j][i]=cliente.conta[1].descricao[j][i];
            }
          }
        }
        else{
          fwrite(&cliente,sizeof(CLIENTE),1,temp); //Todos os outros clientes, com dados diferentes (cpf e codigo) são escritos em um novo arquivo temporário
          if(a!='n'){
            a='s';
          }
        }
      } 
    if(a=='s'){
      printf("Cliente não cadastrado!\n");
      getchar();
      scanf("%c",&o);
      remove("tmp.txt");
      fclose(arquivo);
      fclose(temp);
      return;
    }
  }

  fflush(stdin);

  printf("Atualizando cliente!\nNovos dados:\n\n");
  //Novos dados são requisitados para o usuário
  getchar();
  printf("Digite o nome: ");
  fflush(stdin);
  fgets(nome,30,stdin);

  printf("Digite o endereço: ");
  fflush(stdin);
  fgets(endereco,30,stdin);

  fflush(stdin);
  telefone = -1;
  printf("Digite o telefone: ");
  scanf("%li",&telefone);
  while(telefone<=0){
    printf("Valor inválido (0 para sair)!\n");
    limparBuffer();
    printf("Digite o telefone: ");
    scanf("%li",&telefone);
    if(codigo==0){
      fclose(arquivo);
      fclose(temp);
      remove("tmp.txt");
      return;
    }
  }

  rewind(arquivo);
  while(fread(&cliente.telefone,sizeof(cliente.telefone),1,arquivo)){
  //Verificação para cliente já existente, se sim ele sai da função
    if((telefone==cliente.telefone)&&(salvoT!=cliente.telefone)){
      printf("Cliente já existente!");
      fflush(stdin);
      scanf("%c",&o);
      getchar();
      remove("tmp.txt");
      fclose(arquivo);
      fclose(temp);
      return; //Se algo der errado (cliente cadastrado) o arquivo temporário é deletado e fechado junto ao arquivo dos clientes, nada mudou
    }
  }

  codigo=-1;
  printf("Digite o código: ");
  scanf("%i",&codigo);
  while(codigo<=0){
    printf("Valor inválido (0 para sair)!\n");
    limparBuffer();
    printf("Digite o código: ");
    scanf("%i",&codigo);
    if(codigo==0){
      fclose(arquivo);
      fclose(temp);
      remove("tmp.txt");
      return;
    }
  }

  rewind(arquivo);
  while(fread(&cliente.codigo,sizeof(cliente.codigo),1,arquivo)){
  //Verificação para cliente já existente, se sim ele sai da função
    if((codigo==cliente.codigo)&&(salvoC!=cliente.codigo)){
      printf("Cliente já existente!");
      fflush(stdin);
      scanf("%c",&o);
      getchar();
      remove("tmp.txt");
      fclose(arquivo);
      fclose(temp);
      return;
    }
  }

  cpf = -1;
  printf("Digite o CPF/CNPJ: ");
  scanf("%li",&cpf);
  while(cpf<=0){
    printf("Valor inválido (0 para sair)!\n");
    limparBuffer();
    printf("Digite o CPF/CNPJ: ");
    scanf("%li",&cpf);
    if(cpf==0){
      fclose(arquivo);
      fclose(temp);
      remove("tmp.txt");
      return;
    }
  }

  rewind(arquivo);
  while(fread(&cliente.cpf,sizeof(cliente.cpf),1,arquivo)==1){
    //Verificação para cliente já existente, se sim ele sai da função
    if((cliente.cpf==cpf)&&(salvoCPF!=cliente.cpf)){
        printf("Cliente já cadastrado!\n");
        fflush(stdin);
        scanf("%c",&o);
        getchar();
        remove("tmp.txt");
        fclose(arquivo);
        fclose(temp);
        return;
      }
    }

    for(i=0;i<30;i++){
      cliente.nome[i]=nome[i];
      cliente.endereco[i]=endereco[i];
    }
    cliente.cpf=cpf;
    cliente.telefone=telefone;
    cliente.codigo=codigo;
    //Os valores anteriormente resgatados são jogados aqui para que o cliente continue com sua conta
    cliente.conta[0].agencia=agencia;
    cliente.conta[0].numero=numero;
    cliente.conta[0].saldo=saldo;
    for(j=0;j<10;j++){
      cliente.conta[0].dia[j]=dia[j];
      for(i=0;i<100;i++){
        cliente.conta[0].descricao[j][i]=descricao[j][i];
      }
    }
    cliente.conta[1].agencia=ag;
    cliente.conta[1].numero=nu;
    cliente.conta[1].saldo=sa;
    for(j=0;j<10;j++){
      cliente.conta[1].dia[j]=D[j];
      for(i=0;i<100;i++){
        cliente.conta[1].descricao[j][i]=desc[j][i];
      }
    }
    fwrite(&cliente, sizeof(CLIENTE), 1, temp); //Se todos os dados passarem pelas condicionais teremos a escrita do "novo" cliente no arquivo temporário também, e então o arquivo principal é deletado e o arquivo temporário (tmp.txt) é renomeado para "clientes.txt"
    printf("\nOperação realizada com sucesso!");
    getchar();
    scanf("%c",&o);
    fflush(stdin);
  
    if(remove("clientes.txt")!=0){
      remove("tmp.txt");
    }
    
    rename("tmp.txt","clientes.txt");
  fclose(temp);
  fclose(arquivo);
}

  

//================================= FUNÇÃO EXCLUIR CLIENTE=================================//


//Função que a partir de manipulações de arquivo cria um novo arquivo (tmp.txt) com todos os outros clientes menos o selecionado. Logo depois, exclui o arquivo "clientes.txt" e renomeia o "tmp.txt" como principal("clientes.txt")

void excluir() {

  FILE* arquivo;
  FILE* temp;
  CLIENTE cliente;
  char o,a='s';
  long int cpf=-1;
  int codigo=-1;

  arquivo = fopen("clientes.txt","rb");
  temp = fopen("tmp.txt","wb");

  if(arquivo==NULL||temp==NULL){
    printf("Problemas na abertura do arquivo!\n");
    getchar();
  }else{
    cabecalho();
    printf("Excluindo um cliente:\n\n");
    fflush(stdin);
    //Busca por cliente através do codigo e do cpf
    printf("Digite os dados do cliente a ser excluido:\n");
    printf("Digite o código: ");
    scanf("%i",&codigo);
    while(codigo<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o código: ");
      scanf("%i",&codigo);
      if(codigo==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }
    printf("Digite o cpf: ");
    scanf("%li",&cpf);
    while(cpf<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o cpf: ");
      scanf("%li",&cpf);
      if(cpf==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }

    rewind(arquivo); //Rewind é sempre necessário para que as funções funcionem sem que deixem o ponteiro no final do arquivo e uma outra função não consiga encontrar o cliente
    while(fread(&cliente, sizeof(CLIENTE), 1, arquivo) == 1){
      if((codigo=cliente.codigo)&&(cpf==cliente.cpf)){
          printf("\n============== Cliente Cadastrado ==============\n");
          printf("\nNome.....: %s",cliente.nome);
          printf("Endereço.: %s",cliente.endereco);
          printf("Codigo...: %i\n",cliente.codigo);
          printf("CPF/CNPJ.: %li\n",cliente.cpf);
          printf("Telefone.: %li\n",cliente.telefone);
          printf("\n------------------------------------------------\n\n");
          a='n'; //Esse valor é uma das formas para verificar se o compilador entrou nessa condicional, ou seja, o cliente existe
        }
        else{
          fwrite(&cliente,sizeof(CLIENTE),1,temp);
          if(a!='n'){
            a='s';
          }
        }
      } 
    if(a=='s'){
      printf("\nCliente não cadastrado!\n");
      getchar();
      scanf("%c",&o);
      remove("tmp.txt");
      fclose(arquivo);
      fclose(temp);
      return;
    }
  }
  fclose(arquivo);
  fclose(temp);
  fflush(stdin);

  printf("Deseja excluir (s/n)? "); //Se a opção selecionada for 'n', o compilador remove o arquivo temporário (tmp.txt), ou seja, nada de diferente aconteceu, tudo foi cancelado
  getchar();
  scanf("%c",&o);
  if(o=='s'){
    if(remove("clientes.txt")==0){
      rename("tmp.txt","clientes.txt");
      printf("\nOperacao realizada com sucesso!");
    }
    else{
      remove("tmp.txt");
    }
  }
  else{
    remove("tmp.txt");
    printf("\nExclusão cancelada!");
  }
  scanf("%c",&o);
  getchar();
}


//================================ FUNÇÃO CADASTRAR CONTAS ================================//


//Função com o objetivo de adicionar novas contas. Cria um novo arquivo tmp.txt e cola todos os dados existentes do clientes.txt já adicionando a conta a ser cadastrada, logo depois exclui a antiga clientes.txt e renomeia o tmp.txt como arquivo principal (clientes.txt).

void cadastrarContas(){
  FILE *arquivo;
  FILE *temp;
  
  CLIENTE cliente;
  char nome[30];
  char endereco[30];
  int codigo=-1,i=0,k;
  long int cpf=-1;
  long int telefone;

  CONTA conta[2];
  float saldo;
  int agencia=0,ag=0;
  long int numero=0,nu=0;

  char opcao,o='s',a='n';
  int position;

  cabecalho();
  arquivo = fopen("clientes.txt","rb");
  temp = fopen("tmp.txt","ab");
  printf("Cadastro de conta:\n\n");
  printf("Selecione uma opção para busca de cliente: \n");
  printf("C - para código\n");
  printf("R - para CPF/CNPJ\n");
  fflush(stdin);
  getchar();
  scanf("%c",&opcao);
  if((opcao>='a')&&(opcao<='z')){
    opcao=opcao-32;
  }
  //Verificação da opção digitada, se a mesma for incorreta um aviso é mostrado na tela
  if((opcao!='R')&&(opcao!='C')){
    printf("Opção digitada incorreta!");
    fflush(stdin);
    scanf("%c",&o);
    getchar();
    remove("tmp.txt");
    fclose(arquivo);
    fclose(temp);
    fflush(stdin);
    return;
  }
  //A partir da opção selecionada uma condicional avalia o valor e pede o dado escolhido
  if(opcao=='C'){
    printf("Digite o código do cliente: ");
    scanf("%i",&codigo);
    while(codigo<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o codigo: ");
      scanf("%i",&codigo);
      if(cpf==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }
  }
  else if(opcao=='R'){
    printf("Digite o CPF/CNPJ do cliente: ");
    scanf("%li",&cpf);
    while(cpf<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o CPF/CPNJ: ");
      scanf("%li",&cpf);
      if(cpf==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }
  }

  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){ //A partir de um dos dados o compilador procura o cliente com o mesmo valor, que não pode ser repetido desde o seu cadastro
    if((codigo==cliente.codigo)||(cpf==cliente.cpf)){
      printf("\n============== Cliente Cadastrado ==============\n");
      printf("\nNome.....: %s",cliente.nome);
      printf("Endereço.: %s",cliente.endereco);
      printf("Código...: %i\n",cliente.codigo);
      printf("CPF/CNPJ.: %li\n",cliente.cpf);
      printf("Telefone.: %li\n",cliente.telefone);
      printf("\n------------------------------------------------\n");
      getchar();
      for(i=0;i<30;i++){
        nome[i]=cliente.nome[i];
        endereco[i]=cliente.endereco[i];
      }
      codigo=cliente.codigo;
      cpf=cliente.cpf;
      telefone=cliente.telefone;
      o='n';
      if((cliente.conta[0].agencia==0)&&(cliente.conta[0].numero==0)){
        printf("\nNenhuma conta cadastrada!\n");
      }
      else{
        if((cliente.conta[1].agencia==0)&&(cliente.conta[1].numero==0)){
          a = 's';
          printf("\nUma conta cadastrada!\n");
          ag=cliente.conta[0].agencia;
          nu=cliente.conta[0].numero;
          saldo=cliente.conta[0].saldo;
        }
        else if((cliente.conta[1].agencia!=0)&&(cliente.conta[1].numero!=0)){
          printf("\nMáximo de conta por clientes(2) atingida!");
          fflush(stdin);
          getchar();
          remove("tmp.txt");
          fclose(arquivo);
          fclose(temp);
          return;
        }
      }
      break; //Quando o cliente é encontrado um break é acionado para que, sendo outra forma de verficar se o cliente foi encontrado, se isso não acontecer uma condicional verifica e retorna
    }
  }

  //Todos os outros clientes são escritos no arquivo temporário, com uma condicional para verficar se o cliente lido não é o mesmo do dito pelo usuário
  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
    if((codigo!=cliente.codigo)||(cpf!=cliente.cpf)){
      fwrite(&cliente,sizeof(CLIENTE),1,temp);
    }
  }

  if(o!='n'){
    printf("Cliente não cadastrado!\n");
    scanf("%c",&o);
    getchar();
    remove("tmp.txt");
    fclose(arquivo);
    fclose(temp);
    return;
  }

  if(a!='s'){ //A condicional é para saber qual conta o cliente está cadastrando (1 ou 2), se a conta for a primeira (a!='s'), a outra conta tem que continuar com seus dados = 0
    agencia=-1;
    numero=-1;
    printf("Digite a agência: ");
    scanf("%i",&agencia);
    while(agencia<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite a agência: ");
      scanf("%i",&agencia);
      if(agencia==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }
    printf("Digite o numero: ");
    scanf("%li",&numero);
    while(numero<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o número: ");
      scanf("%li",&numero);
      if(numero==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }
    for(i=0;i<2;i++){
      rewind(arquivo);
      while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
        if((cliente.conta[i].agencia==agencia)&&(cliente.conta[i].numero==numero)){
          printf("Conta existente!");
          fflush(stdin);
          scanf("%c",&o);
          getchar();
          remove("tmp.txt");
          fclose(arquivo);
          fclose(temp);
          return;
        }
      }
    }
    cliente.conta[0].agencia=agencia;
    cliente.conta[0].numero=numero;
    cliente.conta[0].saldo=0.0;
    cliente.conta[1].agencia=0;
    cliente.conta[1].numero=0;
    cliente.conta[1].saldo=0.0;
    for(i=0;i<30;i++){
      cliente.nome[i]=nome[i];
      cliente.endereco[i]=endereco[i];
    }
    for(k=0;k<10;k++){
      for(i=0;i<100;i++){
        cliente.conta[0].descricao[k][i]='\0';
        cliente.conta[1].descricao[k][i]='\0';
      }
    }
    cliente.codigo=codigo;
    cliente.cpf=cpf;
    cliente.telefone=telefone;
    fwrite(&cliente,sizeof(CLIENTE),1,temp); //Após passsar por todas as condicionais e entrar na condicional de ser a primeira conta os dados da segunda conta (=0) são escritos
    remove("cliente.txt");
    rename("tmp.txt","clientes.txt");
  }
  else{ //Se a conta for a segunda (a=='s'), os valores da primeira já resgatados são reescritos e a segunda tem seus dados modificados de 0 para dados escritos pelo usuário
    agencia=-1;
    numero=-1;
    printf("Digite a agência: ");
    scanf("%i",&agencia);
    while(agencia<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite a agência: ");
      scanf("%i",&agencia);
      if(agencia==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }
    printf("Digite o numero: ");
    scanf("%li",&numero);
    while(numero<=0){
      printf("Valor inválido (0 para sair)!\n");
      limparBuffer();
      printf("Digite o número: ");
      scanf("%li",&numero);
      if(numero==0){
        fclose(temp);
        fclose(arquivo);
        remove("tmp.txt");
        return;
      }
    }
    for(i=0;i<2;i++){
      rewind(arquivo);
      while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
        if((cliente.conta[i].agencia==agencia)&&(cliente.conta[i].numero==numero)){
          printf("Conta existente!");
          fflush(stdin);
          scanf("%c",&o);
          getchar();
          remove("tmp.txt");
          fclose(arquivo);
          fclose(temp);
          return;
        }
      }
    }
    cliente.conta[0].saldo=saldo;
    cliente.conta[0].agencia=ag;
    cliente.conta[0].numero=nu;
    cliente.conta[1].agencia=agencia;
    cliente.conta[1].numero=numero;
    cliente.conta[1].saldo=0.0;
    for(i=0;i<30;i++){
      cliente.nome[i]=nome[i];
      cliente.endereco[i]=endereco[i];
    }
    for(k=0;k<10;k++){
      for(i=0;i<100;i++){
        cliente.conta[0].descricao[k][i]='\0';
        cliente.conta[1].descricao[k][i]='\0';
      }
    }
    cliente.codigo=codigo;
    cliente.cpf=cpf;
    cliente.telefone=telefone;
    fwrite(&cliente,sizeof(CLIENTE),1,temp); //Após passsar por todas as condicionais e entrar na condicional de ser a segunda conta, os dados da primeira, resgatados, são reescritos no arquivo temporário e o mesmo tem seu nome renomeado para "clientes.txt"
    remove("cliente.txt");
    rename("tmp.txt","clientes.txt");
  }
  printf("\nCadastro realizado com sucesso!");
  getchar();
  scanf("%c",&o);
  fclose(arquivo);
  fclose(temp);
}

  
//================================== FUNÇÃO LISTAR CONTAS ==================================//


//Função cujo objetivo é mostrar todas a contas de todos os clientes cadastrados, sendo os clientes listados em ordem alfabética e as contas listadas por saldo

void listarContas() {

  printf("Ovo da páscoa\n"); 
  cabecalho();
  FILE* arquivo;
  CLIENTE cliente;
  CONTA conta[2];
  char nome[100][30];
  char aux[30],o;
  int codigo;
  long int cpf;
  int i=0,j=0, qtd_nomes=0;

  printf("Listando todas as contas:\n\n");

  arquivo = fopen("clientes.txt","rb");
  
  //--------------------- Ordem Alfabética -----------------------//
  //Como na listagem de clienstes, a listagem de contas analisa os nomes e deixa os mesmos em ordem alfabética
  rewind(arquivo);
  while(fread(&cliente, sizeof(CLIENTE),1,arquivo)==1){
    for(i=0;i<30;i++){
      nome[j][i]=cliente.nome[i];
    }
    codigo = cliente.codigo;
    cpf = cliente.cpf;
    j++;
    qtd_nomes++;
  }

  for (i = 1; i < qtd_nomes; i++) { // Precisa ler apenas a quantidade de nomes existentes.
    for (j = 1; j < qtd_nomes; j++) {
      if (strcmp(nome[j - 1], nome[j]) > 0) {
        strcpy(aux, nome[j - 1]);
        strcpy(nome[j - 1], nome[j]);
        strcpy(nome[j], aux);
      }
    }
  }
  //---------------------------------------------------------------//
  j=0;
  for(i=0;i<qtd_nomes;i++){
    rewind(arquivo);
    while(fread(&cliente.nome, sizeof(CLIENTE),1,arquivo)==1){
      if(strcmp(nome[i],cliente.nome)==0){
        printf("Nome.....: %s",cliente.nome);
        printf("Código...: %i\n",cliente.codigo);
        printf("CPF/CNPJ.: %li\n",cliente.cpf);
        if((cliente.conta[0].agencia==0)&&(cliente.conta[0].numero==0)){
          printf("\nCONTA: Não cadastrada!\n");
        }
        else{
          printf("\nCONTAS:\n\n"); 
          if((cliente.conta[0].numero!=0)&&(cliente.conta[0].agencia!=0)){
            if((cliente.conta[0].saldo>=cliente.conta[1].saldo)){
            //Ordem decrescente de saldo, se os valores forem iguais a primeira conta cadastrada pelo usuário ao cliente é imprimida, e logo em seguida, se a conta existir, a segunda conta é imprimida também
              printf("Agência..: %i\n",cliente.conta[0].agencia);
              printf("Numero...: %li\n",cliente.conta[0].numero);
              printf("Saldo....: R$%.2f\n",cliente.conta[0].saldo);
            }
            else{
              if((cliente.conta[1].agencia!=0)&&(cliente.conta[1].numero!=0)){
                printf("Agência..: %i\n",cliente.conta[1].agencia);
                printf("Numero...: %li\n",cliente.conta[1].numero);
                printf("Saldo....: R$%.2f\n",cliente.conta[1].saldo);
              }
              printf("\n------------------------------------------------\n\n");
              printf("Agência..: %i\n",cliente.conta[0].agencia);
              printf("Numero...: %li\n",cliente.conta[0].numero);
              printf("Saldo....: R$%.2f\n",cliente.conta[0].saldo);
              j=2; //Valor para verificar se a conta ja foi imprimida
            }
            if((cliente.conta[1].numero!=0)&&(cliente.conta[1].agencia!=0)&&(j!=2)){
              printf("\n------------------------------------------------\n\n"); //Uma condicional verifica se esse é a última conta do cliente, se não ele imprime aslinhas
              printf("Agência..: %i\n",cliente.conta[1].agencia);
              printf("Numero...: %li\n",cliente.conta[1].numero);
              printf("Saldo....: R$%.2f\n",cliente.conta[1].saldo);
            }
          }
          else if((cliente.conta[j].numero==0)&&(cliente.conta[j].agencia==0)){
            break;
          }
        }
        printf("\n================================================\n\n");
      }
    }
  }
  fclose(arquivo);
  fflush(stdin);
  getchar();
  scanf("%c",&o);
}

//=================================== FUNÇÃO CONTAS CLIENTE =================================//


//Função com o objetivo de mostrar todas as contas existentes de um determinado usuário, a partir de uma requisição de um código ou CPF/CNPJ e retorna uma resposta com uma listagem de todas as contas desse cliente

void contasCliente(){
  FILE *arquivo;
  CLIENTE cliente;
  char opcao;
  int codigo,j=0;
  long int cpf;

  arquivo = fopen("clientes.txt","rb");
  cabecalho();
  
  printf("Listando contas de um cliente:\n\n");
  printf("Como deseja buscar pelo cliente:\n");
  printf("C - Por código\nR - Por CPF/CNPJ\n");
  fflush(stdin);
  getchar();
  scanf("%c",&opcao);
  if((opcao>'a')&&(opcao<'z')){
    opcao = opcao - 32;
  }

  if(opcao=='C'){
    printf("Digite o código: ");
    scanf("%i",&codigo);
  }
  else if(opcao=='R'){
    printf("Digite o CPF/CNPJ: ");
    scanf("%li",&cpf);
  }
  else if((opcao!='R')&&(opcao!='C')){ //Verifica se a opção digitada existe
    printf("Opção digitada incorreta!");
    fflush(stdin);
    scanf("%c",&opcao);
    getchar();
    remove("tmp.txt");
    fclose(arquivo);
    fflush(stdin);
    return;
  }

  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
    if((cpf==cliente.cpf)||(codigo==cliente.codigo)){
      printf("\n============== Cliente Cadastrado ==============\n");
      printf("\nNome.....: %s",cliente.nome);
      printf("Código...: %i\n",cliente.codigo);
      printf("CPF/CNPJ.: %li\n",cliente.cpf);
      if((cliente.conta[0].agencia==0)&&(cliente.conta[0].numero==0)){
        printf("\nCONTA: Não cadastrada!\n");
      }
      else{
        //Imprime todas contas existentes, se o valor da conta (agencia e numero) for igual a zero
        printf("\nCONTAS:\n\n");
        if((cliente.conta[0].numero!=0)&&(cliente.conta[0].agencia!=0)){
          if((cliente.conta[0].saldo>=cliente.conta[1].saldo)){
          //Ordem decrescente de saldo, se os valores forem iguais a primeira conta cadastrada pelo usuário ao cliente é imprimida, e logo em seguida, se a conta existir, a segunda conta é imprimida também
            printf("Agência..: %i\n",cliente.conta[0].agencia);
            printf("Numero...: %li\n",cliente.conta[0].numero);
            printf("Saldo....: R$%.2f\n",cliente.conta[0].saldo);
          }
          else{
            if((cliente.conta[1].agencia!=0)&&(cliente.conta[1].numero!=0)){
              printf("Agência..: %i\n",cliente.conta[1].agencia);
              printf("Numero...: %li\n",cliente.conta[1].numero);
              printf("Saldo....: R$%.2f\n",cliente.conta[1].saldo);
            }
            printf("\n------------------------------------------------\n\n");
            printf("Agência..: %i\n",cliente.conta[0].agencia);
            printf("Numero...: %li\n",cliente.conta[0].numero);
            printf("Saldo....: R$%.2f\n",cliente.conta[0].saldo);
            j=2; //Valor para verificar se a conta já foi imprimida
          }
          if((cliente.conta[1].numero!=0)&&(cliente.conta[1].agencia!=0)&&(j!=2)){
            printf("\n------------------------------------------------\n\n"); //Uma condicional verifica se esse é a última conta do cliente, se não ele imprime aslinhas
            printf("Agência..: %i\n",cliente.conta[1].agencia);
            printf("Numero...: %li\n",cliente.conta[1].numero);
            printf("Saldo....: R$%.2f\n",cliente.conta[1].saldo);
          }
        }
      }
      printf("\n================================================\n");
    }
  }
  fflush(stdin);
  getchar();
  scanf("%c",&opcao);
  opcao='\0';
  fclose(arquivo);
}


//==================================== FUNÇÃO TRANSFERENCIA ==================================//


//Função com o objetivo de transferir um determinado saldo de uma conta pra outra, a partir de um saque da primeira conta (a ser debitada) e um deposito na segunda (a ser creditada) 

void transferencia() {
  
  int agenciaD, agenciaC;
  long int numeroD, numeroC;
  int transferencia=0;

  printf("Conta realizante da transferência (ORIGEM):\n\n");
  printf("Digite a agência: ");
  scanf("%i",&agenciaD);
  //conversão de inteiro para string, essa conversão é necessária para podê-lo usar tanto como parâmetro inteiro, quanto para parâmetro em string para colocá-lo como descrição da transferência
  int tamanho = snprintf( NULL, 0, "%d", agenciaD );
  char* agD = malloc( tamanho + 1 );
  snprintf( agD, tamanho + 1, "%d", agenciaD );

  printf("Digite o número: ");
  scanf("%li",&numeroD);
  //conversão de inteiro para string
  tamanho = snprintf( NULL, 0, "%li", numeroD );
  char* nuD = malloc( tamanho + 1 );
  snprintf( nuD, tamanho + 1, "%li", numeroD );

  printf("\nConta recebedora da transferência (DESTINO):\n\n");
  printf("Digite a agência: ");
  scanf("%i",&agenciaC);
  //conversão de inteiro para string
  tamanho = snprintf( NULL, 0, "%d", agenciaC );
  char* agC = malloc( tamanho + 1 );
  snprintf( agC, tamanho + 1, "%d", agenciaC );  

  printf("Digite o número: ");
  scanf("%li",&numeroC);
  //conversão de inteiro para string
  tamanho = snprintf( NULL, 0, "%li", numeroC );
  char* nuC = malloc( tamanho + 1 );
  snprintf( nuC, tamanho + 1, "%li", numeroC );

  if(agenciaD==agenciaC){
    printf("Erro: valor de agência!");
    return;
  }
  if(numeroD==numeroC){
    printf("Erro: valor de numero!");
    return;
  }

  transferencia=-1;
  printf("\nQuanto deseja transferir R$: ");
  scanf("%i",&transferencia);
  while(transferencia<=-1){ //Verifica se o valor é valido ou não para ser transferido
      printf("\nValor incorreto!\n");
      printf("Digite novamente o valor R$ (0 para sair): ");
      limparBuffer();
      scanf("%d",&transferencia);
      if(transferencia==0){
        return;
      }
    }

  if(saque(1,agenciaD,numeroD,agC,nuC,transferencia)==1){ //Se a função saque não conseguir realizar algum procedimento ele imprimirá uma mensagem de erro no console e retornará o valor 1 para que a função de transferência seja cancelada
    return;
  }
  else{ //Se a condicional anterior não acontecer ele passa para o próximo passo que é depositar na conta destino o exato mesmo valor
    printf("\nTransferência para a conta:\n");
    deposito(1,agenciaC,numeroC,agD,nuD,transferencia);
  }
}


//====================================== FUNÇÃO SAQUE =======================================//


//Função com o objetivo de "retirar" um determinado valor do saldo atual de uma determinada conta, caso este valor seja menor que o requisitado, retornará uma mensagem de erro. O saque é retornado em forma de notas de 2, 5, 10, 20, 50, 100 e 200 reais 

int saque(int verifT, int agencia, long int numero, char agenciaC[10], char numeroC[25],int saque){ //O valor de "verifT" é o valor para verificar se a função está fazendo uma tranferência (1) ou um saque (0), esse valor é usado em toda a função para imprimir dados corretos dependendo do seu propósito
  CLIENTE cliente;
  FILE *temp;
  FILE *arquivo;
  int i=0,l=0,codigo=0,j,k=2,ag=0;
  int n200, n100, n50, n20, n10, n5, n2;
  int saldo=0,sa=0,D[10],dias[10];
  long int telefone=0,cpf=0,nu=0;
  char a='s',nome[30],endereco[30],descricao[10][100], o, desc[10][100];

  arquivo = fopen("clientes.txt","rb");
  temp = fopen("tmp.txt","ab");

  if(verifT==0){ //Quando para saque a função pede os dados, mas quando para transferência a função não pede dados, pois os mesmo foram escaneados na função de transferência e dados como parâmetros na função de saque
    agencia=-1;
    numero=-1;
    printf("Digite a agência: ");
    scanf("%i",&agencia);
    while(agencia<=0){
      printf("Valor inválido! (0 para sair)\n");
      limparBuffer();
      printf("Digite a agência: ");
      scanf("%i",&agencia);
      if(agencia==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return 0;
      }
    }
    printf("Digite o numero: ");
    scanf("%li",&numero);  
    while(numero<=0){
      printf("Valor inválido! (0 para sair)\n");
      limparBuffer();
      printf("Digite a número: ");
      scanf("%li",&numero);
      if(numero==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return 0;
      }
    }
  } 

  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
    for(i=0;i<2;i++){
      if((agencia==cliente.conta[i].agencia)&&(numero==cliente.conta[i].numero)){
        if(verifT==0){
          printf("\n============== Cliente Cadastrado ==============\n");
        }
        else if(verifT==1){
          printf("\n================ Cliente Origem ================\n");
        }
        printf("\nNome.....: %s",cliente.nome);
        printf("Endereço.: %s",cliente.endereco);
        //Como nos outros os dados são resgatados, para que não se perca a descrição de outros saques,depósitos ou transferências
        for(j=0;j<30;j++){
          endereco[j]=cliente.endereco[j];
          nome[j]=cliente.nome[j];
        }
        codigo=cliente.codigo;
        cpf=cliente.cpf;
        telefone=cliente.telefone;
        saldo=cliente.conta[i].saldo;
        for(k=1;k<10;k++){ //O valor dos dias e as descrições da conta são resgatados (colocados em uma nova string/matriz) a partir do bloco 1, ou seja, 9 dos 10 das duas strings são ocupados, sendo o único não ocupado o 1
          dias[k]=cliente.conta[i].dia[l];
          for(j=0;j<100;j++){
           descricao[k][j]=cliente.conta[i].descricao[l][j];
          }
          l++;
        }
        if(i==0){
          ag=cliente.conta[1].agencia;
          nu=cliente.conta[1].numero;
          sa=cliente.conta[1].saldo;
          for(k=1;k<10;k++){
            D[k]=cliente.conta[1].dia[l];
            for(j=0;j<100;j++){
              desc[k][j]=cliente.conta[1].descricao[l][j];
            }
          l++;
          }
          k=1; //O valor de k, mesmo que usado no loop anterior, é o valor da outra conta do cliente, sendo ele necessário mais a frente para reescrever os valores da mesma
        }
        else if(i==1){
          ag=cliente.conta[0].agencia;
          nu=cliente.conta[0].numero;
          sa=cliente.conta[0].saldo;
          for(k=1;k<10;k++){
            D[k]=cliente.conta[0].dia[l];
            for(j=0;j<100;j++){
              desc[k][j]=cliente.conta[0].descricao[l][j];
            }
          l++;
          }
          k=0; //O valor de k, mesmo que usado no loop anterior, é o valor da outra conta do cliente, sendo ele necessário mais a frente para reescrever os valores da mesma
        }
        //Alguns dados são resgatados para a posterior verificação de algumas validações, como a de saque (não é possível sacar uma quantidade indisponível de saldo)
        printf("Código...: %i\n",cliente.codigo);
        printf("CPF/CNPJ.: %li\n",cliente.cpf);
        printf("Telefone.: %li\n",cliente.telefone);
        printf("\nCONTA:\n\n");
        printf("Agência..: %i\n",cliente.conta[i].agencia);
        printf("Numero...: %li\n",cliente.conta[i].numero);
        printf("Saldo....: R$%.2f",cliente.conta[i].saldo);
        if(verifT==1){
          printf(" (ANTERIOR)");
        }
        printf("\n\n================================================\n");
        a='n';
        fflush(stdin);
        break;
      }
    }
    if((k==0)||(k==1)){
      break;  
    }
  }

  if(a!='n'){ //Como nas outras há a verificação para o a existência da conta, mas com o "verifT" diferentes impressões são realizadas, mas os mesmos procedimentos são feitos, como o retorno do valor 1 e o fechamento dos arquivos
    if(verifT==0){
      printf("\nConta inexistente!");
    }
    else if(verifT==1){
      printf("\nConta ORIGEM inexistente!");
      printf("\nTranferência cancelada!");
    }
    fflush(stdin);
    getchar();
    scanf("%c",&o);
    remove("tmp.txt");
    fclose(arquivo);
    fclose(temp);
    return 1;
  }

  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
    if((cliente.codigo!=codigo)&&(cliente.cpf!=cpf)){
      fwrite(&cliente,sizeof(CLIENTE),1,temp);
    }
  }
  
  if(verifT==0){ //Parte para o saque quando o mesmo é chamado (verifT==0)
    saque=-1;
    printf("\nDigite quanto deseja sacar R$: ");
    scanf("%d",&saque);
    while(saque<0){
      printf("\nValor incorreto!\n");
      printf("Digite novamente o valor R$ (0 para sair): ");
      limparBuffer();
      scanf("%d",&saque);
      if(saque==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return 0;
      }
    }
    if(saque>saldo){
      printf("Saque maior que saldo, impossível realizá-lo!\n"); //Verifica se o saque é válido (menor do que o valor de saldo disponível na conta)
      fflush(stdin);
      scanf("%c",&o);
      getchar();
      remove("tmp.txt");
      fclose(arquivo);
      fclose(temp);
      return 1;
    }
    limparBuffer();
  }
  else if(verifT==1){ //Para a transferência a impressão é diferente mas o mesmo procedimento é realizado
    if(saque>saldo){
      printf("\nTranferência maior que saldo, impossível realizá-la!\n");
      fflush(stdin);
      scanf("%c",&o);
      getchar();
      remove("tmp.txt");
      fclose(arquivo);
      fclose(temp);
      return 1;
    }
  }

  //usa o valor de data da máquina, se rodado em um copilador com servidor próprio usara o GMT(0) como referência dando alteração de (+3 horas), por conta do valor objetivo que é o BRT(-3)
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);

    //Na parte de transferência é realizado essa transformação de inteiro para string, mas para o valor da agênca e número da conta destino/origem. Nesse caso temos essa transformação para a data, mas com o mesmo intuito de inseri-la em uma descrição do deposito/saque/transferencia

    //--transformando o inteiro em uma string-------------------
    int tamanhoDATA = snprintf( NULL, 0, "%d", tm.tm_mday );
    char* dia = malloc( tamanhoDATA + 1 );
    snprintf( dia, tamanhoDATA + 1, "%d", tm.tm_mday );

    tamanhoDATA = snprintf( NULL, 0, "%d", tm.tm_mon + 1 );
    char* mes = malloc( tamanhoDATA + 1 );
    snprintf( mes, tamanhoDATA + 1, "%d", tm.tm_mon + 1 );

    tamanhoDATA = snprintf( NULL, 0, "%d", tm.tm_year + 1900 );
    char* ano = malloc( tamanhoDATA + 1 );
    snprintf( ano, tamanhoDATA + 1, "%d", tm.tm_year + 1900 );
    //-----------------------------------------------------------

    char data[11];
    int p=0;
    if(tm.tm_mday>=10){
      for(p=0;p<2;p++){
        data[p]=dia[p];
      }
      data[2]='/';
      if(tm.tm_mon<10){
        data[3]='0';
        for(p=4;p<5;p++){
          data[p]=mes[p-4];
        }
        data[5]='/';
        for(p=6;p<10;p++){
          data[p]=ano[p-6];
        }
      }
      else{
        for(p=3;p<4;p++){
          data[p]=mes[p-3];
        }
        data[4]='/';
        for(p=5;p<9;p++){
          data[p]=ano[p-5];
        }
      }
    }
    else{
      data[0]='0';
      data[1]=dia[0];
      data[2]='/';
      if(tm.tm_mon<10){
        data[3]='0';
        for(p=4;p<5;p++){
          data[p]=mes[p-4];
        }
        data[5]='/';
        for(p=6;p<10;p++){
          data[p]=ano[p-6];
        }
      }
      else{
        for(p=3;p<4;p++){
          data[p]=mes[p-3];
        }
        data[4]='/';
        for(p=5;p<9;p++){
          data[p]=ano[p-5];
        }
      }
    }

    
  //___________________________________________________________________________________

  dias[0]=tm.tm_mday; //O dia aqui recebe o valor da data atual do pc, esse valor fica sendo o primeiro da lista, os outros dias da conta do cliente são colocados deposi, o máximo de dias, como a descrição, é de 10, ou seja, sempre que uma transferência/depósito/saque é realizado um dia, sendo ele o último, é excluído
  if(saque<=saldo){
    saldo=saldo-saque;
    for(j=0;j<30;j++){
      cliente.nome[j]=nome[j];
      cliente.endereco[j]=endereco[j];
    }
    cliente.cpf=cpf;
    cliente.telefone=telefone;
    cliente.codigo=codigo;
    cliente.conta[k].agencia=ag;
    cliente.conta[k].numero=nu;
    cliente.conta[k].saldo=sa;
    cliente.conta[i].agencia=agencia;
    cliente.conta[i].numero=numero;
    cliente.conta[i].saldo=saldo;
    for(j=0;j<10;j++){
      cliente.conta[i].dia[j]=dias[j];
      cliente.conta[k].dia[j]=D[j];
    }

    int saveK = k;

    //Abaixo: tranformando o valor da transferência em uma string 
    int tamanhoSAQUE = snprintf( NULL, 0, "%d", saque);
    char* RS = malloc( tamanhoSAQUE + 1 );
    snprintf( RS, tamanhoSAQUE + 1, "%d", saque);
  
    int salvo = l;
    if(verifT==0){ //Tanto no saque quanto na transferência o valor da data é colocado dentro da descrição, mas no saque o usuário tem a possiblidade de digitar algo a mais, que virá antes de toda a descrição prescrita pelo compilador
      printf("Digite uma descrição para o saque:\n");
      fgets(descricao[0],100,stdin);
      int tamanhoDESC = strlen(descricao[0]);
      descricao[0][tamanhoDESC-1]='\0';

      strcat(descricao[0]," [DATA: ");
      for(j=0;j<11;j++){
        descricao[0][tamanhoDESC+7+j]=data[j];
      }
      
      strcat(descricao[0]," SAQUE: (-R$");
      for(j=0;j<tamanhoSAQUE;j++){
        descricao[0][tamanhoDESC+29+j]=RS[j];
      }
      strcat(descricao[0],".00)]");
      descricao[0][tamanhoDESC+29+tamanhoSAQUE+5]='\0';
      for(l=0;l<10;l++){
        for(j=0;j<100;j++){
          cliente.conta[i].descricao[l][j] = descricao[l][j];
          cliente.conta[k].descricao[l][j] = desc[l][j];
        }
      }
      fflush(stdin);
    }
    //descrição da transferência
    else if(verifT==1){
      //No caso da transferência temos uma descrição prescrita pelo compilador
      char resumo[100]={'T','r','a','n','s','f','e','r','e','n','c','i','a',' ','p','a','r','a',' ','c','o','n','t','a',':',' '};
      
      int tamanhoa = strlen(agenciaC);
      int tamanhon = strlen(numeroC);
  
      k=0;
      for(j=26;j<100;j++){
        resumo[j]=agenciaC[k];
        k++;
        if(k==tamanhoa){
          break;
        }
      }

      resumo[tamanhoa+26]='-';
      k=0;
      for(j=tamanhoa+27;j<100;j++){
        resumo[j]=numeroC[k];
        k++;
        if(k==tamanhon){
          break;
        }
      }
      char a[8]={' ','[','D','A','T','A',':',' '};
      for(k=0;k<8;k++){
        resumo[tamanhon+tamanhoa+27+k]=a[k];
      }
      for(k=0;k<11;k++){
        resumo[tamanhon+tamanhoa+27+k+8]=data[k];
      }
      int tamanhoRESUMO = strlen(resumo);
      char valor[6]={' ','(','-','R','$'};
      for(k=0;k<6;k++){
        resumo[tamanhoRESUMO+k]=valor[k];
      }

      for(k=0;k<tamanhoSAQUE;k++){
        resumo[tamanhoRESUMO+5+k]=RS[k];
      }
      
      strcat(resumo,".00)]");
      for(j=0;j<100-tamanhoRESUMO-10-tamanhoSAQUE;j++){
        resumo[tamanhoRESUMO+10+tamanhoSAQUE]='\0';
      }
      
      for(j=0;j<100;j++){
        cliente.conta[i].descricao[0][j]=resumo[j];
      }
      for(l=1;l<10;l++){
        for(j=0;j<100;j++){
          cliente.conta[i].descricao[l][j]=descricao[l][j];
        }
      }
      for(l=0;l<10;l++){
        for(j=0;j<100;j++){
          cliente.conta[saveK].descricao[l][j]=desc[l][j];
        }
      }
    }
    
    fwrite(&cliente,sizeof(CLIENTE),1,temp); //Nos dois casos os valores são escritos dentro do arquivo temporário
    fclose(arquivo);
    fclose(temp);
    remove("clientes.txt");
    rename("tmp.txt","clientes.txt");

    if(verifT==0){
      //No caso do saque o usuário tem uma simulação de quantas notas são sacadas, mas para valores como 1,3,7... não é possível simular notas = 1
      printf("\nSacando...\n");
      n200=saque/200;
      n100=(saque%200)/100;
      n50=((saque%200)%100)/50;
      n20=(((saque%200)%100)%50)/20;
      n10=((((saque%200)%100)%50)%20)/10;
      if ((((((saque%200)%100)%50)%20)%10)==8){
        n5=0;
        n2=4;
      }else if ((((((saque%200)%100)%50)%20)%10)==6){
        n5=0;
        n2=3;
      }else
        n5=(((((saque%200)%100)%50)%20)%10)/5;
        n2=((((((saque%200)%100)%50)%20)%10)%5)/2;
        if(n200>0)
          printf("%d nota(s) de R$ 200,00\n",n200);
        if(n100>0)
          printf("%d nota(s) de R$ 100,00\n",n100);
        if(n50>0)
          printf("%d nota(s) de R$ 50,00\n",n50);
        if(n20>0)
          printf("%d nota(s) de R$ 20,00\n",n20);
        if(n10>0)  
          printf("%d nota(s) de R$ 10,00\n",n10);
        if(n5>0)
          printf("%d nota(s) de R$ 5,00\n",n5);
        if(n2>0)  
          printf("%d nota(s) de R$ 2,00\n",n2);
        scanf("%c",&o);
      }
    }
  return 0;
}


//===================================== FUNÇÃO DEPOSITO =====================================//


//Sendo o contrário da função saque, essa função da a opção do usuário adicionar uma determinada quantia monetária em uma determinada conta de um cliente

int deposito(int verifT, int agencia, long int numero, char agenciaD[10], char numeroD[25],int deposito){ //O depósito tem o mesmo intuito do saque, onde parâmetros como sua verificação "verifT" e a agência e número da conta origem
  CLIENTE cliente;
  FILE *temp;
  FILE *arquivo;
  int i=0,l=0,codigo=0,j=0,k=2,ag,dias[10],D[10];
  int saldo=0,sa;
  long int telefone=0,cpf=0,nu;
  char a='s',nome[30],endereco[30],descricao[10][100],desc[10][100], o;
  
  arquivo = fopen("clientes.txt","rb");
  temp = fopen("tmp.txt","ab");

  if(verifT==0){ //Para valores de verifT, a mesma ideia é usada, verifT = 0 é depósito e verifT = 1 transferência
    agencia = -1;
    numero = -1;
    printf("Digite a agência: ");
    scanf("%i",&agencia);
    while(agencia<=0){
      printf("Valor inválido! (0 para sair)\n");
      limparBuffer();
      printf("Digite a agência: ");
      scanf("%i",&agencia);
      if(agencia==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return 0;
      }
    }
    printf("Digite o numero: ");
    scanf("%li",&numero);  
    while(numero<=0){
      printf("Valor inválido! (0 para sair)\n");
      limparBuffer();
      printf("Digite a número: ");
      scanf("%li",&numero);
      if(numero==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return 0;
      }
    }
  }

  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
    for(i=0;i<2;i++){
      if((agencia==cliente.conta[i].agencia)&&(numero==cliente.conta[i].numero)){
        if(verifT==0){
          printf("\n============== Cliente Cadastrado ==============\n");
        }
        else if(verifT==1){
          printf("\n============== Cliente de destino ==============\n");
        }
        printf("\nNome.....: %s",cliente.nome);
        printf("Endereço.: %s",cliente.endereco);
        //Os dados do cliente e os valores da sua(s) contas são resgatados para serem usado
        for(j=0;j<30;j++){
          endereco[j]=cliente.endereco[j];
          nome[j]=cliente.nome[j];
        }
        codigo=cliente.codigo;
        cpf=cliente.cpf;
        telefone=cliente.telefone;
        saldo=cliente.conta[i].saldo;
        for(k=1;k<10;k++){
          dias[k]=cliente.conta[i].dia[l]; //Os dias e a descrição são resgatados a partir do 1, ou seja 9 dos 10 blocos das 2 strings são ocupados menos o primeiro
          for(j=0;j<100;j++){
            descricao[k][j]=cliente.conta[i].descricao[l][j];
          }
          l++;
        }

        if(i==0){
          ag=cliente.conta[1].agencia;
          nu=cliente.conta[1].numero;
          sa=cliente.conta[1].saldo;
          for(k=0;k<10;k++){
            D[k]=cliente.conta[1].dia[k];
            for(j=0;j<100;j++){
              desc[k][j]=cliente.conta[1].descricao[k][j];
            }
          }
          k=1; //O valor de k, mesmo que usado no loop anterior, é o valor da outra conta do cliente, sendo ele necessário mais a frente para reescrever os valores da mesma
        }
        else if(i==1){
          ag=cliente.conta[0].agencia;
          nu=cliente.conta[0].numero;
          sa=cliente.conta[0].saldo;
          for(k=0;k<10;k++){
            D[k]=cliente.conta[0].dia[k];
            for(j=0;j<100;j++){
              desc[k][j]=cliente.conta[0].descricao[k][j];
            }
            l++;
          }
          k=0; //O valor de k, mesmo que usado no loop anterior, é o valor da outra conta do cliente, sendo ele necessário mais a frente para reescrever os valores da mesma
        }
        printf("Código...: %i\n",cliente.codigo);
        printf("CPF/CNPJ.: %li\n",cliente.cpf);
        printf("Telefone.: %li\n",cliente.telefone);
        printf("\nCONTA:\n\n");
        printf("Agência..: %i\n",cliente.conta[i].agencia);
        printf("Numero...: %li\n",cliente.conta[i].numero);
        printf("Saldo....: R$%.2f",cliente.conta[i].saldo);
        if(verifT==1){
          printf(" (ANTERIOR)");
        }
        printf("\n\n================================================\n");
        a='n';
        fflush(stdin);
        break;
      }
    }
    if((k==0)||(k==1)){
      break;
    }
  }

  if(a!='n'){
    if(verifT==0){
      printf("\nConta inexistente!");
    }
    else if(verifT==1){
      printf("\nConta DESTINO inexistente!");
      printf("\nTranferência cancelada!");
    }
    fflush(stdin);
    getchar();
    scanf("%c",&o);
    remove("tmp.txt");
    fclose(arquivo);
    fclose(temp);
    return 1;
  }

  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){ //Se for possível passar pela verificação de que a conta existe uma escrita completa de todas as outras contas será realizada no arquivo temporário
    if((cliente.codigo!=codigo)&&(cliente.cpf!=cpf)){
      fwrite(&cliente,sizeof(CLIENTE),1,temp);
    }
  }

  //usa o valor de data da máquina, se rodado em um copilador com servidor próprio usara o GMT(0) como referência dando alteração de (+3 horas), por conta do valor objetivo que é o BRT(-3)
  
  time_t mytime;
  mytime = time(NULL);
  struct tm tm = *localtime(&mytime);

  //--transformando o inteiro em uma string-------------------
  int tamanhoDATA = snprintf( NULL, 0, "%d", tm.tm_mday );
  char* dia = malloc( tamanhoDATA + 1 );
  snprintf( dia, tamanhoDATA + 1, "%d", tm.tm_mday );

  tamanhoDATA = snprintf( NULL, 0, "%d", tm.tm_mon + 1 );
  char* mes = malloc( tamanhoDATA + 1 );
  snprintf( mes, tamanhoDATA + 1, "%d", tm.tm_mon + 1 );

  tamanhoDATA = snprintf( NULL, 0, "%d", tm.tm_year + 1900 );
  char* ano = malloc( tamanhoDATA + 1 );
  snprintf( ano, tamanhoDATA + 1, "%d", tm.tm_year + 1900 );
  //-----------------------------------------------------------

  char data[11];
  int p=0;
  if(tm.tm_mday>=10){
    for(p=0;p<2;p++){
      data[p]=dia[p];
    }
    data[2]='/';
    if(tm.tm_mon<10){
      data[3]='0';
      for(p=4;p<5;p++){
        data[p]=mes[p-4];
      }
      data[5]='/';
      for(p=6;p<10;p++){
        data[p]=ano[p-6];
      }
    }
    else{
      for(p=3;p<4;p++){
        data[p]=mes[p-3];
      }
      data[4]='/';
      for(p=5;p<9;p++){
        data[p]=ano[p-5];
      }
    }
  }
  else{
    data[0]='0';
    data[1]=dia[0];
    data[2]='/';
    if(tm.tm_mon<10){
      data[3]='0';
      for(p=4;p<5;p++){
        data[p]=mes[p-4];
      }
      data[5]='/';
      for(p=6;p<10;p++){
        data[p]=ano[p-6];
      }
    }
    else{
      for(p=3;p<4;p++){
        data[p]=mes[p-3];
      }
      data[4]='/';
      for(p=5;p<9;p++){
        data[p]=ano[p-5];
      }
    }
  }

//_______________________________________________________________________________________

  dias[0]=tm.tm_mday; //O dia aqui recebe o valor da data atual do pc, esse valor fica sendo o primeiro da lista, os outros dias da conta do cliente são colocados deposi, o máximo de dias, como a descrição, é de 10, ou seja, sempre que uma transferência/depósito/saque é realizado um dia, sendo ele o último, é excluído
  if(verifT==0){
    deposito=-1;
    printf("\nDigite quanto deseja depositar R$: ");
    scanf("%i",&deposito);
    while(deposito<=-1){ //Se o valor do depósito for negativo, uma mensagem de erro é imprimida na tela e o usuário entra em um loop até que digite o valor correto (>0) ou que digite 0 para sair do loop
      printf("\nValor incorreto!\n");
      printf("\nDigite novamente o valor R$ (0 para sair): ");
      limparBuffer();
      scanf("%i",&deposito);
      if(deposito==0){
        fclose(arquivo);
        fclose(temp);
        remove("tmp.txt");
        return 0;
      }
    }
    limparBuffer();
    saldo=saldo+deposito;
  }
  else if(verifT==1){ //Se for uma transferência o valor é simplesmente depositado na conta
    saldo=saldo+deposito;
  }
  for(j=0;j<30;j++){
    cliente.nome[j]=nome[j];
    cliente.endereco[j]=endereco[j];
  }
  cliente.cpf=cpf;
  cliente.telefone=telefone;
  cliente.codigo=codigo;
  cliente.conta[k].agencia=ag;
  cliente.conta[k].numero=nu;
  cliente.conta[k].saldo=sa;
  cliente.conta[i].agencia=agencia;
  cliente.conta[i].numero=numero;
  cliente.conta[i].saldo=saldo;
  for(j=0;j<10;j++){ //Os dias são reescritos
    cliente.conta[i].dia[j]=dias[j];
    cliente.conta[k].dia[j]=D[j];
  }
  int saveK=k; //O valor de k é salvo, porque o mesmo será usado como loop, mas o seu valor ainda é necessário para a conta do cliente, poderia ser substituído por uma outra variável, mas nos dois casos teríamos que criar uma variável nova
  
  //Abaixo: transformando a transferência em uma string
  int tamanhoDEPOSITO = snprintf( NULL, 0, "%d", deposito);
  char* RS = malloc( tamanhoDEPOSITO + 1 );
  snprintf( RS, tamanhoDEPOSITO + 1, "%d", deposito);

  int salvo = l;
  if(verifT==0){ //Como no saque uma descrição personalizada pode ser digitada pelo usuário e a mesma aparecerá antes da descrição prescrita pelo compilador
    printf("Digite uma descrição para o depósito:\n");
    fgets(descricao[0],100,stdin);
    int tamanhoDESC = strlen(descricao[0]);
    descricao[0][tamanhoDESC-1]='\0';
    strcat(descricao[0]," [DATA: ");
    for(j=0;j<11;j++){
      descricao[0][tamanhoDESC+7+j]=data[j];
    }
    strcat(descricao[0]," DEPOSITO: (+R$");
    for(j=0;j<tamanhoDEPOSITO;j++){
      descricao[0][tamanhoDESC+21+j+11]=RS[j];
    }
    strcat(descricao[0],".00)]");
    descricao[0][tamanhoDESC+21+tamanhoDEPOSITO+11+5]='\0';
    for(l=0;l<10;l++){
      for(j=0;j<100;j++){     
        cliente.conta[i].descricao[l][j] = descricao[l][j];
        cliente.conta[k].descricao[l][j] = desc[l][j];
      }
    }
  }
  //descrição da transferência
  else if(verifT==1){
    k=0; //O valor de k (número da outra conta) está salvo em "saveK"
    char resumo[100]={'T','r','a','n','s','f','e','r','e','n','c','i','a',' ','d','e',' ','c','o','n','t','a',':',' '};
    //Uma mensagem prescrita é colocado na string "resumo", que será colocada como descrição do cliente

    int tamanhoa = strlen(agenciaD);
    int tamanhon = strlen(numeroD);
  
    for(j=24;j<100;j++){
      resumo[j]=agenciaD[k];
      k++;
      if(k==tamanhoa){
        break;
      }
    }
    char a = '-';
    resumo[tamanhoa+24]= a;
    k=0;
    for(j=tamanhoa+25;j<100;j++){
      resumo[j]=numeroD[k];
      k++;
      if(k==tamanhon){
        break;
      }
    }
    char DA[8]={' ','[','D','a','t','a',':',' '};
    for(k=0;k<8;k++){
      resumo[tamanhon+tamanhoa+25+k]=DA[k];
    }
    for(k=0;k<11;k++){
      resumo[tamanhon+tamanhoa+25+k+8]=data[k];
    }

    int tamanhoRESUMO = strlen(resumo);

    char valor[6]={' ','(','+','R','$'};
    for(k=0;k<6;k++){
      resumo[tamanhoRESUMO+k]=valor[k];
    }

    for(k=0;k<tamanhoDEPOSITO;k++){
      resumo[tamanhoRESUMO+5+k]=RS[k];
    }

    strcat(resumo,".00");
    strcat(resumo,")]");
    resumo[tamanhoRESUMO+5+tamanhoDEPOSITO+5]='\0';

    for(j=0;j<100;j++){ //A descrição do cliente recebe o resumo (prescrito) na primeira posição
      cliente.conta[i].descricao[0][j]=resumo[j];
    }
    for(j=0;j<100;j++){ //A descrição da conta aqui recebe as outras descrições de transferências/depósitos/saques, para que fique em sequência de realização todas as outras descrições são jogadas 1 bloco da string para a direita (l=1), a descrição é uma matriz com limite de 10 descrições a cada 10 a última descrição feita é perdida no processo
      for(l=1;l<10;l++){
        cliente.conta[i].descricao[l][j]=descricao[l][j];
      }
    }
    for(l=0;l<10;l++){ //Aqui a OUTRA conta do cliente recebe as suas respectivas descrições
      for(j=0;j<100;j++){
        cliente.conta[saveK].descricao[l][j]=desc[l][j];
      }
    }
  }

  fflush(stdin);
      
  fwrite(&cliente,sizeof(CLIENTE),1,temp); //Quando tudo estiver passado pelas condicionais e a descrição estiver escrita corretamente
  fclose(arquivo);
  fclose(temp);
  remove("clientes.txt");
  rename("tmp.txt","clientes.txt");

  if(verifT==0){
    printf("\nDeposito realizado com sucesso!");
    fflush(stdin);
    getchar();
  }
  else if(verifT==1){
    printf("\nTransferência realizada com sucesso!");
    fflush(stdin);
    getchar();
    scanf("%c",&o);
  }
  return 0;
}


//================================= FUNÇÃO EXIBIR EXTRATO =================================//


//Nessa função, é requisitado uma agência e um número de conta que deve ter sido cadastrada previamente, logo após é pedido a quantidade de dias a serem analisados para posteriormente ser retornando todas as movimentações feitas nessa conta até aquela data determinada além de também voltar todos os dados e atual saldo da conta

void exibirExtrato(){
  FILE *arquivo;

  CLIENTE cliente;
  char endereco[30],nome[30];
  char descricao[10][100],a='s';
  int agencia,i=0,j=0,k=0;
  long int numero,telefone,cpf;
  int limite=0,codigo,dias[10];
  float saldo,sa;

  arquivo = fopen("clientes.txt","rb");

  cabecalho();
  printf("Extrato...\n\n");

  printf("Digite a agência: ");
  scanf("%i",&agencia);
  printf("Digite o número: ");
  scanf("%li",&numero);
  printf("Digite a quantidade de dias: ");
  scanf("%i",&limite);

  rewind(arquivo);
  while(fread(&cliente,sizeof(CLIENTE),1,arquivo)==1){
    for(i=0;i<2;i++){
      if((agencia==cliente.conta[i].agencia)&&(numero==cliente.conta[i].numero)){
        printf("\n============== Cliente Cadastrado ==============\n");
        printf("\nNome.....: %s",cliente.nome);
        printf("Endereço.: %s",cliente.endereco);
        for(k=0;k<10;k++){
          for(j=0;j<100;j++){
            descricao[k][j]=cliente.conta[i].descricao[k][j];
          }
          dias[k]=cliente.conta[i].dia[k];
        }
        printf("Código...: %i\n",cliente.codigo);
        printf("CPF/CNPJ.: %li\n",cliente.cpf);
        printf("Telefone.: %li\n",cliente.telefone);
        printf("\nCONTA:\n\n");
        printf("Agência..: %i\n",cliente.conta[i].agencia);
        printf("Numero...: %li\n",cliente.conta[i].numero);
        printf("Saldo....: R$%.2f",cliente.conta[i].saldo);
        printf("\n\n================================================\n");
        a='n';
        fflush(stdin);
        break;
      }
    }
  }
  if(a!='n'){
    printf("\nConta inexistente!");
    fclose(arquivo);
    fflush(stdin);
    getchar();
    scanf("%c",&a);
    return;
  }
  printf("\nEXTRATO:\n");
  rewind(arquivo);
  
  for(k=0;k<10;k++){
    if(descricao[k][0]=='\0'){
      break;
    }
    if(dias[k]<=limite+dias[k]){ //Os dias são escritos exatamente da mesma forma que a descrição, ou seja, conforme um saque/depósito/transferência é realizado, o dia e a descrição são escritos ao mesmo tempo e da mesma forma, logo a descrição acompanha o dia que é um valor não imprimido, mas guardado dentro da struct de contas
      printf("\n%s\n",descricao[k]);
    }
  }
  fflush(stdin);
  getchar();
  scanf("%c",&a);
}