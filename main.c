/*===========================*/
/*=== TRABALHO BANCO  ===*/
/*=== Programacao 2 ===*/
/*===========================*/
/*=== Autor: ===*/
/*=== Pedro Augusto ===*/
/*===========================*/
/*==== Turma: ELO13B ===*/
/*===========================*/
/*==== Data: 09/09/2021 ===*/
/*===========================*/



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int contaUtilizada; // variavel global utilizada para encontrar a posicao da conta que o o usuario logou

void menuInicializar(); // menu inicial
int criarConta(int posicao_conta, int contas[5][5], int senhas[5][5]); //fun��o para a cria��o de conta
int entrarNaConta(int contas_inseridas[5], int senhas_inseridas[5], int contas[5][5], int senhas[5][5]); //fun��o para entrar em uma conta
void menuConta(int contas[5][5]); // fun��o que exibe o menu dentro de uma conta
int consultaSaldo(float saldo_conta[5], int contas[5][5]); // fun��o para realizar a cosulta ao saldo
float saque(int contas[5][5], float saldo_conta[5]); //fun��o para realizar o saque
float deposito(int contas[5][5], float saldos[5]); // fun��o para realizar o deposito

int main()
{
    int op_menu_inicializar;//varivel de escolha no primeiro menu
    int op_menu_conta;//variavel para o menu da conta
    int contas[5][5];//variavel para contas, onde possui o numero de contas e seus respectivos numeros
    int senhas[5][5];//vatiavel em formato matriz para o controle de senha dos usuarios
    int cont_contas = 0; //contador de contas criadas
    int contas_inseridas[5];// variavel para conta em que o usuario ir� logar
    int senhas_inseridas[5];// variavel para o usuario digitar a senha para entrar em sua conta
    int flag_menu_conta = 1; //variavel usada para o controle do menu conta

    //VARIAVEIS SALDO
    float saldos[5] = {0,0,0,0,0}; // cada uma das posi��es representa uma determinada conta

    for(int i = 0 ; i < 5 ; i++){
        for(int j = 0 ; j < 5 ; j++){
            contas[i][j] = -1; //-1 � o c�digo escolhido especificamente para determinar um espa�o vazio em formato de n�mero
        }
    }

    do{
        menuInicializar();
        printf("\n\nOPCAO: "); // recolhe a opcao do menu
        scanf("%d", &op_menu_inicializar);


        switch(op_menu_inicializar){
            case 1:
                switch(criarConta(cont_contas, contas, senhas)){
                    case 4: printf("Ja existe uma conta com este n�mero!\n\n");break;
                    case 5: printf("As unidades de sua conta nao sao aceitas!\n\n");break;
                    case 6: printf("As unidades de sua senha nao sao aceitas!\n\n");break;
                    case 3: printf("Desculpe, o sistema ja esta em seu numero maximo de contas!");break;
                    case 0: printf("Conta cadastrada com sucesso!\n\n");cont_contas++;
                }
                system("PAUSE");
                system("CLS");
                break;

            case 2:
                switch(entrarNaConta(contas_inseridas, senhas_inseridas, contas, senhas)){
                    case 9: exit(0);//acabaram as tentativas
                    case 0: //o usuario entro na conta
                        do{
                            menuConta(contas);
                            printf("\n\nOPCAO: "); //recolhe a opcao do menu conta
                            scanf("%d", &op_menu_conta);

                            switch(op_menu_conta){
                                case 1:
                                    consultaSaldo(saldos, contas);
                                    break;
                                case 2:
                                    saldos[contaUtilizada] = saque(contas, saldos);
                                    break;
                                case 3:
                                    saldos[contaUtilizada] = deposito(contas, saldos);
                                    break;
                                case 4:
                                    flag_menu_conta = 0;
                                    system("pause");
                                    system("CLS");
                                    break;
                                case 5:
                                    printf("\n\n=== Obrigado por usar o banco CIMOL!! ===");
                                    exit(0);
                                default:
                                    printf("\nOpcao invalida!\n");
                                    system("pause");
                                    system("CLS");
                            }
                        }while(flag_menu_conta == 1);
                        flag_menu_conta = 1; // atribuicao para entrar corretamente no menu conta da proxima vez
                        break;
                }
                break;
            case 3:
                printf("\n\n=== Obrigado por usar o banco CIMOL! ===");
                exit(0);
                break;
            default:
                printf("\nOpcao invalida!\n");
                system("pause");
                system("CLS");
                fflush(stdin);
                break;
        }
    }while(1);


    return 0;
}

void menuInicializar(){
    printf("********************************\n");
    printf("\t$ BANCO CIMOL $\n");
    printf("********************************\n");
    printf("\tCRIAR CONTA      [1]\n");
    printf("\tENTRAR NA CONTA  [2]\n");
    printf("\tSAIR             [3]\n");
    printf("********************************");
}

int criarConta(int posicao_conta, int contas[5][5], int senhas[5][5]){
    int erro_4 = 0; //erro de cadastro de contas do mesmo numero

    if(posicao_conta < 5)
    {
        system("pause");
        system("cls");
        printf("********************************\n");
        printf("\t$ BANCO CIMOL $\n");
        printf("********************************\n");
        printf("\tCRIACAO DE CONTA\n\n");

        printf("Em seguida informe os 5 digitos que irao corresponder ao numero de sua conta!\n\n");
        Sleep(1000);
        printf("Informe o numero de sua nova conta: ");
        for(int i = 0 ; i < 5 ; i++){
            contas[posicao_conta][i] = getche();
            contas[posicao_conta][i] -= '0'; //logica usando os numeros da tabela ASCII, os caracteres que representam os numeros de 0 a t� 9 possuem valores interiros que subtraindo do valo do 0 na tabela ir�o resultar em seus devidos numeros inteiros
        }
        printf("\n\n");

        //verifica��o se o digito � de 0-9
        for(int j = 0; j < 5 ; j++){
            if(contas[posicao_conta][j] > 9 || contas[posicao_conta][j] < 0)
                return 5;// c�digo de retorno para erro de unidade
        }

        //verifica��o de contas com o mesmo n�mero
        for(int j = 0 ; j < 5 ; j++){
            for(int k = 0 ; k < 5 ; k++){
                if(contas[posicao_conta][k] == contas[j][k] && posicao_conta != j){
                    erro_4++;
                }
                if(k == 4 && erro_4 == 5)
                    return 4;//retorno de ero para conta ja existente
            }
        }
        printf("O numero da conta esta OK!\n\n");
        system("pause");
        system("CLS");
        //cadastro de senha

        printf("********************************\n");
        printf("\t$ BANCO CIMOL $\n");
        printf("********************************\n");
        printf("\tCADASRO DE SENHA\n\n");

        printf("Em seguida informe os 5 digitos que irao corresponder a sua senha! (numeros de 0 a 9)\n\n");
        Sleep(1000);
        printf("Informe os digitos da senha de sua nova conta: ");
        for(int i = 0 ; i < 5 ; i++){
            senhas[posicao_conta][i] = getche();
            senhas[posicao_conta][i] -= '0'; //idem
        }
        printf("\n\n");
        //verifica��o se o digito � de 0-9
        for(int j = 0; j < 5 ; j++){
            if(senhas[posicao_conta][j] > 9 || senhas[posicao_conta][j] < 0)
                return 6;// c�digo de retorno para erro de unidade na senha
        }

        printf("\nA senha esta OK!\n\n");
        system("pause");
        system("CLS");

        return 0;//conta ok
    }
    else{
        system("pause");
        system("CLS");
        return 3;//numero de contas ja esta em seu limite
    }


}

int entrarNaConta(int conta_inseridas[5], int senhas_inseridas[5], int contas[5][5], int senhas[5][5]){
    int conta_correta = 0, senha_correta = 0;//contadores para identifcar se os digitos condizem com contas existentes
    int tentativas_conta = 3;
    int flag_entrar_conta = 0;//controle do processo de repeti��o de entrada da conta
    int position_conta; //posicao da conta

    system("PAUSE");
    system("CLS");
    //verificar a existencia da conta
    while(flag_entrar_conta == 0){
        printf("********************************\n");
        printf("\t$ BANCO CIMOL $\n");
        printf("********************************\n");
        printf("\tEntrar na conta\n\n");
        printf("Em seguida informe os 5 digitos do numero da sua conta \t\t\tTentativas restantes: %d\n\n", tentativas_conta);
        Sleep(1000);

        printf("Informe os digitos de sua conta: ");
        for(int i = 0; i < 5 ; i++){
            conta_inseridas[i] = getche();
            conta_inseridas[i] -= '0';
        }
        printf("\n\n");

        //verifica��o de existencia da conta
        for(int i = 0 ; i< 5 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                if(contas[i][j] == conta_inseridas[j]){
                    conta_correta++;
                }
            }
            if(conta_correta == 5){
                printf("\n\nConta encontrada!\n\n");
                position_conta = i;
                system("PAUSE");
                system("CLS");
                flag_entrar_conta = 1;
                break;
            }
            else{
                conta_correta = 0;
            }
            if(i == 4){
                tentativas_conta--;
                printf("\n\nEsta conta nao existe!\n\n");
                system("pause");
                system("CLS");
                break;
            }

        }
        if(tentativas_conta == 0){
            printf("Acesso negado, procure uma agencia para solucionar o problema!\n\n");
            return 9; //erro de nega��o de conta
        }
    }
    //verifica��o de senha
    tentativas_conta = 3; //reset de tentativas para a senha
    flag_entrar_conta = 0;// reset da flag de controle

    while(flag_entrar_conta == 0){
        printf("********************************\n");
        printf("\t$ BANCO CIMOL $\n");
        printf("********************************\n");
        printf("\tENTRAR NA CONTA\n\n");

        printf("Em seguida informe os 5 digitos da sua senha \t\t\tTentativas restantes: %d\n\n", tentativas_conta);
        Sleep(1000);

        printf("Informe os digitos de sua senha: ");
        for(int i = 0; i < 5; i++){
            senhas_inseridas[i] = getche();
            senhas_inseridas[i] -= '0';
        }
        printf("\n\n");

        //verificando se a senha condiz com a senha da conta especificada anteriormente
        for(int i = 0 ; i< 5 ; i++){
            for(int j = 0 ; j < 5 ; j++){
                if(senhas[i][j] == senhas_inseridas[j]){
                    senha_correta++;
                }
            }
            if(senha_correta == 5){
                printf("\n\Senha Correta!!!\n\n");
                system("PAUSE");
                system("CLS");
                flag_entrar_conta = 1;
                break;
            }
            else{
                senha_correta = 0;
            }
            if(i == 4){
                tentativas_conta--;
                printf("\n\nSenha incorreta!!!\n\n");
                system("pause");
                system("CLS");
                break;
            }
        }
        if(tentativas_conta == 0){
            printf("Acesso negado, procure uma agencia para solucionar o problema!\n\n");
            return 9; //erro de nega��o de conta
        }
    }
    contaUtilizada = position_conta; //controle para se obter o indice exato da conta em que o usuario est� logado no momento
    return 0;
}

void menuConta(int contas[5][5]){
    printf("********************************\t\t\t\tCONTA: ");

    for(int i = 0; i < 5 ; i++)
        printf("%d", contas[contaUtilizada][i]);

    printf("\n\t$ BANCO CIMOL $\n");
    printf("********************************\n");
    printf("\tCONSULTA SALDO      [1]\n");
    printf("\tSAQUE               [2]\n");
    printf("\tDEPOSITO            [3]\n");
    printf("\tSAIR DA CONTA       [4]\n");
    printf("\tSAIR                [5]\n");
    printf("********************************");
}

//exibi��o do saldo
int consultaSaldo(float saldo_conta[5], int contas[5][5]){
    printf("\n");
    system("pause");
    system("CLS");

    printf("********************************\t\t\t\tCONTA: ");

    for(int i = 0; i < 5 ; i++)
        printf("%d", contas[contaUtilizada][i]);

    printf("\n\t$ BANCO CIMOL $\n");
    printf("********************************\n");
    printf("\tCONSULTA SALDO      \n");


    printf("\n\n=== Saldo === >> R$ %.2f\n\n", saldo_conta[contaUtilizada]);
    system("pause");
    system("CLS");
}

float saque(int contas[5][5], float saldo_conta[5]){
    float valor_saque;
    int flag_saque = 0; //controle da repeti��o at� atingir valores de saque aceitaveis

    printf("\n");

    do{
        system("pause");
        system("CLS");

        printf("********************************\t\t\t\tCONTA: ");

        for(int i = 0; i < 5 ; i++)
            printf("%d", contas[contaUtilizada][i]);

        printf("\n\t$ BANCO CIMOL $\n");
        printf("********************************\n");
        printf("\tSAQUE      \n");

        printf("\n\nInforme o valor desejado de saque: R$ ");
        scanf("%f", &valor_saque);

        if(valor_saque <= 0.0)
        {
            printf("\n\n== Voce deve informar um valor positivo valido!\n\n");
            flag_saque = 1;
        }
        else
            flag_saque = 0;
    }while(flag_saque == 1);

    if(saldo_conta[contaUtilizada] - valor_saque < 0) //verifica��o de saldo neagtivo e alerta ao usuario
        printf("\n\n\a === Voce esta utilizando o seu limite ===");

    Sleep(1000);
    printf("\n\nO valor foi sacado!\n\n");
    system("pause");
    system("CLS");

    return saldo_conta[contaUtilizada] - valor_saque; // retorno do novo valor de saldo
}

float deposito(int contas[5][5], float saldos[5]){
    float valor_deposito;
    int flag_deposito; // controle do looping para a identifica��o de valores aceitos no deposito
    printf("\n");

    do{
        system("pause");
        system("CLS");

        printf("********************************\t\t\t\tCONTA: ");

        for(int i = 0; i < 5 ; i++)
            printf("%d", contas[contaUtilizada][i]);

        printf("\n\t$ BANCO CIMOL $\n");
        printf("********************************\n");
        printf("\tDEPOSITO      \n");

        printf("\n\nInforme o valor desejado de deposito: R$ ");
        scanf("%f", &valor_deposito);

        if(valor_deposito <= 0.0)
        {
            printf("\n\n== Voce deve informar um valor positivo valido!\n\n");
            flag_deposito = 1;
        }
        else
            flag_deposito = 0;
    }while(flag_deposito == 1);

    Sleep(1000);
    printf("\n\nO valor foi depositado com sucesso!\n\n");
    system("pause");
    system("CLS");

    return saldos[contaUtilizada] + valor_deposito; // retorno do novo valor de saldo
}

