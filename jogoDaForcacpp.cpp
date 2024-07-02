#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <iostream>
using namespace std;

#define TAMANHO_PALAVRA 20

char chutes[26];
int chutesDados = 0;
char palavrasecreta[TAMANHO_PALAVRA];

void abertura();
void chuta();
int  jachutou(char letra);
void desenhaforca();
int  enforcou();
int  acertou();
void escolhePalavra();
void adicionaPalavra();
int chutesErrados();

int main() {
    setlocale(LC_ALL, "Portuguese");
    
    adicionaPalavra();
    escolhePalavra();
    
    abertura();

    do {
        desenhaforca();
        chuta();
        cout  << !acertou();
        
        
        
    } while (!acertou() && !enforcou());
    
    if(acertou()){
        printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }else{
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
   system("pause");
    return 0;
}

void abertura() {
  printf("*****************************\n");
  printf("*       Jogo de Forca       *\n");
  printf("*****************************\n\n");
}

void chuta(){
    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

//int jachutou(char letra){
//    int achou = 0;
//    int j;
//    for(int j = 0; j < chutesDados; j++) {
//        if(chutes[j] == letra) {
//            achou = 1;
//            break;
//        }
//    }
//    return achou;
//}

int jachutou(char letra) {
    int achou = 0, j;
    for(j = 0; j < chutesDados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca() {

    int erros =  chutesErrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", 
        (erros>=1?'(':' '), 
        (erros>=1?'_':' '), 
        (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", 
        (erros>=3?'\\':' '), 
        (erros>=2?'|':' '), 
        (erros>=3?'/': ' '));
    printf(" |       %c     \n", 
        (erros>=2?'|':' '));
    printf(" |      %c %c   \n", 
        (erros>=4?'/':' '), 
        (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

printf("\n\n");

    printf("Você já deu %d chutes\n", chutesDados);

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

int chutesErrados(){
    int erros = 0;

    for(int i = 0; i < chutesDados; i++){
        int existe = 0;
        for(int j = 0; j < strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou(){
    return chutesErrados() >= 5;
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

void escolhePalavra(){
    FILE *f;
    int randomico, qtdDePalvras;
    srand(time(0));
    
    f = fopen("palavras.txt", "r");
    
    if(f == 0){
        cout << "DESCULPE, BANCO DE DADOS NÃO DISPONÍVEL";
        exit(1);
    }
    
    fscanf(f, "%d", &qtdDePalvras);
    
    
    randomico = rand() % qtdDePalvras;
    
    for(int i = 0; i <= randomico; i++){
         fscanf(f, "%s", palavrasecreta);
    }
    
    fclose(f);
}

void adicionaPalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

