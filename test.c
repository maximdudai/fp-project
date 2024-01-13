#include <stdio.h>

#define MAX_ESTUDANTE 60
#define MAX_NOME 80

typedef struct {
    int numero;
    char nome[MAX_NOME];
    int nota_final;
}t_estudante;

int menu(void);
char confirmar_saida(void);
int ler_dados_estudante(t_estudante[], int);
void mostrar_dados_estudantes(t_estudante[], int);
int procurar_estudante(t_estudante[], int, int);
void alterar_nota_estudante(t_estudante[], int);
void mostrar_estatisticas(t_estudante[], int);
void gravar_ficheiro(t_estudante[], int);
int ler_ficheiro(t_estudante[]);

int main() {
    int opcao;
    char opcao_saida = 'n';
    t_estudante estudantes[MAX_ESTUDANTE];
    int num_estudantes = 0;
    
    do {
        
        opcao = menu();
        
        switch (opcao) {
            case 1:
                num_estudantes = ler_dados_estudante(estudantes, num_estudantes);
                break;
            case 2:
                mostrar_dados_estudantes(estudantes, num_estudantes);
                break;
            case 3:
                alterar_nota_estudante(estudantes, num_estudantes);
                break;
            case 4:
                break;
            case 5:
                gravar_ficheiro(estudantes, num_estudantes);
                break;
            case 6:
                num_estudantes = ler_ficheiro(estudantes);
                break;
            case 0:
                break;
            default:
                printf("Opcão incorreta");
        }
        opcao_saida = confirmar_saida();
    } while (opcao_saida == 's' || opcao_saida == 'S');
    return 0;
}

int menu(void){
    int opcao;
    printf("\n1 - Inserir dados de um estudante");
    printf("\n2 - Mostrar dados dos estudantes");
    printf("\n3 - Alterar nota final de um estudante");
    printf("\n4 - Estatísticas das avaliações");
    printf("\n5 - Gravar dados em ficheiro");
    printf("\n6 - Ler dados de ficheiro");
    printf("\n0 - Sair");
    printf("\nEscolha a opção: ");

    scanf("%d", &opcao);

    return opcao;
};

char confirmar_saida(void){
    char opcao;

    printf("\nPertende sair? ");
    scanf("%s", &opcao);

    return opcao;
}

int procurar_estudante(t_estudante estudantes[], int num_estudantes, int id_estudante){
    int estudante_idx = -1;
    for (int i = 0; i < num_estudantes; ++i) {
        if(estudantes[i].numero == id_estudante)
            estudante_idx = i;
    }
    return estudante_idx;
}

int ler_dados_estudante(t_estudante estudantes[], int num_estudantes){
    int num_estudante;

    printf("\nInsira o número do estudante: ");
    scanf("%d", &num_estudante);

    if(procurar_estudante(estudantes, num_estudantes, num_estudante) < 0){
        estudantes[num_estudantes].numero = num_estudante;

        fflush(stdin);
        printf("\nInsira o nome do estudante: ");
        fgets(estudantes[num_estudante].nome, sizeof(estudantes->nome), stdin);

        printf("\nInsira a nota do estudante: ");
        scanf("%d", &estudantes[num_estudante].nota_final);

        printf("\nEstudante insirido com sucesso");

        fflush(stdin);
        getchar();

        return num_estudantes = 1;
    }else{
        printf("\nEstudante já existe.");

        fflush(stdin);
        getchar();

        return num_estudantes;
    }
}

void mostrar_dados_estudantes(t_estudante estudante[], int num_estudantes){
    printf("\n################ ESTUDANTES ##############");

    for (int i = 0; i < num_estudantes; ++i) {
        printf("\n### Estudante %d###", i+1);
        printf("\nNúmero: %d", estudante[i].numero);
        printf("\nNome  : %s", estudante[i].nome);
        printf("\nNota final: %d", estudante[i].nota_final);
    }

    fflush(stdin);
    getchar();
}

void gravar_ficheiro(t_estudante estudantes[], int num_estudantes){
    FILE *ficheiro;

    ficheiro = fopen("dados_estudantes.dat", "wb");
    if(ficheiro == NULL){
        printf("\nNão foi possível gravar ficheiro");
    }else{
        fwrite(&num_estudantes, sizeof (int), 1, ficheiro);
        fwrite(estudantes, sizeof (t_estudante), num_estudantes, ficheiro);

        fclose(ficheiro);

        printf("\nFicheiro gravado com sucesso.");
    }

    fflush(stdin);
    getchar();
}

int ler_ficheiro(t_estudante estudantes[]){
    FILE *ficheiro;
    int num_estudantes;

    ficheiro = fopen("dados_estudantes.dat", "rb");
    if(ficheiro == NULL){
        printf("\nNão foi possível gravar ficheiro");
    }else{
        fread(&num_estudantes, sizeof (int), 1, ficheiro);
        int estudantes_lidos = fread(estudantes, sizeof (t_estudante), num_estudantes, ficheiro);

        fclose(ficheiro);
        if(num_estudantes != estudantes_lidos){
            printf("\nFicheiro incorreto ou corrompido.");
            num_estudantes = 0;
        }else{
            printf("Ficheiro lido com sucesso.");
        }
        printf("\nFicheiro gravado com sucesso.");
    }

    fflush(stdin);
    getchar();

    return num_estudantes;
}

void alterar_nota_estudante(t_estudante estudantes[], int num_estudantes){
    int num_estudante;
    printf("Insira o número de estudante para alterar a nota: ");
    scanf("%d", &num_estudante);
    
    int index = procurar_estudante(estudantes, num_estudantes, num_estudante);
    
    if(index<0){
        printf("\nEstudante não existe.");
    }else{
        printf("\nInsira a nota do estudante: ");
        scanf("%d", &estudantes[num_estudante].nota_final);

        printf("\n Nota alterada com sucesso.");
    }

    fflush(stdin);
    getchar();
}