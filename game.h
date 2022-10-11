#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#define LINHA 12
#define COLUNA 10
#define TAM 120

struct poltrona{
    char nome[50];
    int cpf;
    int situacao;
};

void menu();

int escolherOpcao();

void iniciarPrograma(struct poltrona sala[]);

void finalizarPrograma(struct poltrona sala[]);

void lerNome(char nome[]);

int lerCPF();

int verificarCPF(int cpfOriginal);

void iniciarPoltronas(struct poltrona sala[]);

void lerArquivo(struct poltrona sala[], FILE *fileName);

void gravarArquivo(struct poltrona sala[]);

void imprimirPoltronas(struct poltrona sala[]);

int escolherPoltrona(struct poltrona sala[]);

void reservarPoltrona(struct poltrona sala[]);

void comprarIngresso(struct poltrona sala[]);

void cancelarReserva(struct poltrona sala[]);

void limparConsole();

void mostrarComprovante(int poltrona, struct poltrona sala[]);

int invalido(int numero);

int traduzirLetraPoltrona(int poltrona);

int traduzirNumeroPoltrona(int poltrona);

#endif // GAME_H_INCLUDED
