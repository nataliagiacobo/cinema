#include "game.h"

void gotoxy(int linha, int coluna)
{
    COORD c;
    c.X = coluna;
    c.Y = linha;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void limparConsole()
{
    printf("\e[1;H\e[2J");
}

void textcolor(int cor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cor);
}

void iniciarPrograma(struct poltrona sala[])
{
    FILE *arquivo = fopen("poltronas.txt", "r");

    if(arquivo == NULL){
        iniciarPoltronas(sala);
    } else {
        lerArquivo(sala, arquivo);
    }

    fclose(arquivo);
}

void finalizarPrograma(struct poltrona sala[])
{
    gravarArquivo(sala);
}

void menu()
{
    limparConsole();
    textcolor(9);
    gotoxy(10,21);
    printf("--------------------------------------");
    gotoxy(11,21);
    printf("    C I N E M A    P A R A D I S E    ");
    gotoxy(12,21);
    printf("--------------------------------------");
    gotoxy(13,21);
    printf("   Filme em cartaz: TOP GUN MAVERICK");
    gotoxy(14,21);
    printf("   Horário: 21:00");
    gotoxy(16,21);
    printf("           Reservar ingresso");
    gotoxy(17,21);
    printf("           Comprar ingresso");
    gotoxy(18,21);
    printf("           Cancelar reserva");
    gotoxy(19,21);
    printf("           Sair\n");
    gotoxy(20,21);
    printf("--------------------------------------\n");

}

int escolherOpcao()
{

    int linhaCursor = 16, linhaInicio = 16, linhaFinal = linhaInicio+3;
    int colunaCursor = 26;
    int opcao = 0;

    gotoxy(linhaCursor,colunaCursor);
    printf(" -->");

    while(opcao==0)
    {
        int teclaPressionada = getch();

        switch(teclaPressionada)
        {
        case 80: //para baixo
            printf("\b\b\b\b    ");
            if(linhaCursor==linhaFinal){
                linhaCursor=linhaInicio;
            } else {
                linhaCursor=linhaCursor+1;
            }
            gotoxy(linhaCursor,colunaCursor);
            printf(" -->");

            break;
        case 72: //para cima
            printf("\b\b\b\b    ");
            if(linhaCursor==linhaInicio){
                linhaCursor=linhaFinal;
            } else {
                linhaCursor=linhaCursor-1;
            }
            gotoxy(linhaCursor,colunaCursor);
            printf(" -->");
            break;
        case 13: //enter
            opcao=1;
            return(linhaCursor-linhaInicio+1);
            break;
        default:
            break;
        }
    }
}

void iniciarPoltronas(struct poltrona sala[])
{
    for(int i = 0; i < TAM; i++){
        strcpy(sala[i].nome, "Nome");
        sala[i].cpf = 0;
        sala[i].situacao = 0;
    }

    gravarArquivo(sala);
}

void lerArquivo(struct poltrona sala[], FILE *fileName)
{
    int num, cpf;
    char palavra[50];
    int count = 1;
    int i = 0;

    while( fscanf(fileName, "%[^';']%*c%d;%d%\n", palavra, &cpf, &num) != EOF) {
        strcpy(sala[i].nome, palavra);
        sala[i].cpf = cpf;
        sala[i].situacao = num;
        i++;
    }
}

void gravarArquivo(struct poltrona sala[])
{
    FILE *arquivo = fopen("poltronas.txt", "w");

    for(int i = 0; i < TAM; i++){
        if(i == TAM-1){
            fprintf(arquivo, "%s;%d;%d", sala[i].nome, sala[i].cpf, sala[i].situacao);
        }else{
            fprintf(arquivo, "%s;%d;%d\n", sala[i].nome, sala[i].cpf, sala[i].situacao);
        }
    }

    fclose(arquivo);
}

void imprimirPoltronas(struct poltrona sala[])
{
    int linha = 0;
    int coluna = 0;

    textcolor(7);
    printf("    + --- + --- + --- + --- + --- + --- + --- + --- + --- + --- +\n    |");

    for(int poltrona = 0; poltrona < TAM; poltrona++){
        if(poltrona%COLUNA == 0 && poltrona>0){
            printf("\n    + --- + --- + --- + --- + --- + --- + --- + --- + --- + --- +\n    |");
            linha++;
            coluna = 0;
        }
        textcolor(definirCor(sala[poltrona].situacao));
        printf(" %c%02d", 65+linha, coluna+1);
        textcolor(7);
        printf(" |");
        coluna++;
    }

    printf("\n    + --- + --- + --- + --- + --- + --- + --- + --- + --- + --- +\n\n");
    printf("                          * * * T E L A * * *                    ");

    gotoxy(9,68);
    printf("LEGENDA:");

    textcolor(2);
    gotoxy(10,68);
    printf("Livre");

    textcolor(5);
    gotoxy(11,68);
    printf("Reservado");

    textcolor(4);
    gotoxy(12,68);
    printf("Vendido\n\n");

    textcolor(7);
}

int definirCor(int numero)
{
    switch(numero){
    case 0:         //livre
        return 2;
    case 1:         //reservado
        return 5;
    case 2:         //vendido
        return 4;
    default:
        return 1;
    }
}

int escolherPoltrona(struct poltrona sala[])
{
    int linhaCursor = 4, linhaInicio = 4, linhaFinal = 26;
    int colunaCursor = 7, colunaInicio = 7, colunaFinal = 63;
    int opcao = 0;
    int poltrona = 0;

    gotoxy(linhaCursor,colunaCursor);

    while(opcao==0)
    {
        int teclaPressionada = getch();

        switch(teclaPressionada)
        {
        case 80: //para baixo
            if(linhaCursor+2 <= linhaFinal){
                linhaCursor = linhaCursor + 2;
                poltrona+=COLUNA;
                gotoxy(linhaCursor,colunaCursor);
            }
            break;
        case 72: //para cima
            if(linhaCursor-2>=(linhaInicio)){
                linhaCursor=linhaCursor-2;
                poltrona-=COLUNA;
                gotoxy(linhaCursor,colunaCursor);
            }
            break;
        case 77:  //para direita
            if(colunaCursor+6<colunaFinal){
                colunaCursor=colunaCursor+6;
                poltrona++;
                gotoxy(linhaCursor,colunaCursor);
            }
            break;
        case 75: //para esquerda
            if(colunaCursor-6 >= colunaInicio){
                colunaCursor=colunaCursor-6;
                gotoxy(linhaCursor,colunaCursor);
                poltrona--;
            }
            break;
        case 13: //enter
            opcao=1;
            break;
        default:
            break;
        }
    }

    return poltrona;
}

void reservarPoltrona(struct poltrona sala[])
{
    char nome[50];

    limparConsole();
    printf("\n       RESERVA - Selecione a poltrona e aperte enter:\n\n");
    imprimirPoltronas(sala);
    int poltrona = escolherPoltrona(sala);

    if(sala[poltrona].situacao == 0){
        sala[poltrona].situacao = 1;
        lerNome(nome);
        strcpy(sala[poltrona].nome, nome);
        sala[poltrona].cpf = lerCPF();
        mostrarComprovante(poltrona, sala);
    } else {
        if(invalido(2)==0){
            reservarPoltrona(sala);
        }
    }

}

void comprarIngresso(struct poltrona sala[])
{
    limparConsole();
    printf("\n       COMPRA - Selecione a poltrona e aperte enter:\n\n");
    imprimirPoltronas(sala);
    int res = 0;
    int poltrona = escolherPoltrona(sala);

    if(sala[poltrona].situacao == 0){
        char nome[50];
        lerNome(nome);
        strcpy(sala[poltrona].nome, nome);
        sala[poltrona].cpf = lerCPF();
        sala[poltrona].situacao = 2;
        mostrarComprovante(poltrona, sala);
    } else if (sala[poltrona].situacao == 1){
        while(res==0){
            if(verificarCPF(sala[poltrona].cpf)==1){
                sala[poltrona].situacao = 2;
                mostrarComprovante(poltrona, sala);
                res=1;
            }else{
                res = invalido(1);
            }
        }
    } else {
        if(invalido(2)==0){
            comprarIngresso(sala);
        }
    }


}

void cancelarReserva(struct poltrona sala[])
{
    limparConsole();
    printf("\n       CANCELAR RESERVA - Selecione a poltrona e aperte enter:\n\n");
    imprimirPoltronas(sala);
    int poltrona = escolherPoltrona(sala);
    int res = 0;

    if(sala[poltrona].situacao == 1){
        while(res==0){
            if(verificarCPF(sala[poltrona].cpf)==1){
                sala[poltrona].situacao = 0;
                mostrarComprovante(poltrona, sala);
                res=1;
            }else{
                res = invalido(1);
            }
        }
    } else {
        if(invalido(2)==0){
            cancelarReserva(sala);
        }
    }
}

void mostrarComprovante(int poltrona, struct poltrona sala[])
{
    limparConsole();
    char status[50];
    char numeroPoltrona[10];


    switch(sala[poltrona].situacao)
    {
        case 0:
            strcpy(status, "        ***RESERVA CANCELADA***");
            break;
        case 1:
            strcpy(status, "        ***RESERVA REALIZADA***");
            break;
        case 2:
            strcpy(status, "        ***INGRESSO COMPRADO***");
            break;
        default:
            break;
    }

    textcolor(9);
    gotoxy(10,21);
    printf("--------------------------------------");
    gotoxy(11,21);
    printf("         C O M P R O V A N T E    ");
    gotoxy(12,21);
    printf("--------------------------------------");
    gotoxy(14,21);
    textcolor(definirCor(sala[poltrona].situacao));
    printf("%s", status);
    textcolor(9);
    gotoxy(16,21);
    printf("   CINE PARADISE");
    gotoxy(17,21);
    printf("   Filme: TOP GUN MAVERICK");
    gotoxy(18,21);
    printf("   Horário: 21:00");

    gotoxy(20,21);
    printf("   Nome: %s", sala[poltrona].nome);
    textcolor(9);
    gotoxy(21,21);
    printf("   CPF: %d", sala[poltrona].cpf);
    gotoxy(22,21);
    printf("   Poltrona: %c%02d", traduzirLetraPoltrona(poltrona), traduzirNumeroPoltrona(poltrona));
    gotoxy(23,21);
    textcolor(9);
    printf("--------------------------------------");
    gotoxy(30,21);
    textcolor(7);
    printf("Tecle ENTER para voltar ao menu principal\n\n\n\n\n\n\n");

    while( getchar() != '\n' );
    limparConsole();
}

int invalido(int numero)
{
    limparConsole();

    if(numero==1){
    gotoxy(10,21);
    printf("             CPF INVÁLIDO!");
    } else if(numero==2){
    gotoxy(10,21);
    printf("         POLTRONA INDISPONÍVEL!");
    }

    gotoxy(12,21);
    printf("     Tecle ENTER e tente novamente!!");
    gotoxy(13,21);
    printf("Tecle ESC para voltar ao menu principal!!");

    int teclaPressionada;

    do{
        teclaPressionada = getch();
    } while (teclaPressionada != 13 && teclaPressionada != 27);

    if(teclaPressionada == 13){
        return 0;
    } else {
        return 1;
    }

}

void lerNome(char nome[])
{
    limparConsole();
    gotoxy(10,21);
    printf("       INSIRA SEU NOME: ");
    gotoxy(12,21);
    gets(nome);
}

int lerCPF()
{
    limparConsole();
    int cpf;
    gotoxy(10,21);
    printf("       INSIRA SEU CPF: ");
    gotoxy(12,21);
    scanf("%d", &cpf);
    fflush(stdin);

    return cpf;
}

int verificarCPF(int cpfOriginal)
{
    int resposta, cpfVerificacao;
    limparConsole();
    gotoxy(10,21);
    printf("     CONFIRME SEU CPF: ");
    gotoxy(12,21);
    scanf("%d", &cpfVerificacao);
    fflush(stdin);

    if(cpfOriginal == cpfVerificacao){
        return 1;
    } else {
        return -1;
    }

}

int traduzirLetraPoltrona(int poltrona)
{
    int letra = (poltrona/COLUNA)+65;
    return letra;
}

int traduzirNumeroPoltrona(int poltrona)
{
    int numero = (poltrona%COLUNA)+1;
    return numero;
}

