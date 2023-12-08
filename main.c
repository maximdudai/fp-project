#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 150
#define MAX_UC 18
#define MAX_AVALIACOES 5000

#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 256

#define MAX_UC_NAME_LENGTH 256
struct estudante_data
{
  int db_id;
  int nr_aluno;
  char nome[MAX_NAME_LENGTH];
  int codigo_curso;
  char email[MAX_EMAIL_LENGTH];
};

struct unidade_curricular
{
  int db_id;
  int uc_codigo;
  char nome[MAX_UC_NAME_LENGTH];
  int ano;
  int semestre;
  int ects;
};

struct avaliacao_data
{
  int db_id;
  int aluno_id;
  int uc_id;
  int ano_letivo;
  int tipo;
  int data;
  int nota;
};

int show_menu(void);
int registar_estudante(int total_alunos);

// 
int check_total_alunos(int total_alunos);
char mostrar_erro(char erro);

int main(void)
{

  int menu_option = 0;
  int lista_alunos[MAX_ALUNOS],  alunos_count = 0;

  do
  {
    menu_option = show_menu();

  } while (menu_option != 0);

  return 0;
}

int registar_estudante(int alunos_count)
{
  if(check_total_alunos(alunos_count))
    return mostrar_erro("O numero maximo de alunos foi atingido!\n");

  struct estudante_data lista_alunos;

  int nr_aluno = alunos_count + 1;
  char nome[MAX_NAME_LENGTH];
  char email[MAX_EMAIL_LENGTH];
  int codigo_curso = 0;

  printf("\n(-) Número de aluno: ");
  scanf("%d", &nr_aluno);

  printf("(-) Nome: ");
  scanf("%s", nome);

  printf("(-) Email: ");
  scanf("%s", email);

  printf("(-) Código do curso: ");
  scanf("%d", &codigo_curso);

  lista_alunos.nr_aluno = nr_aluno;
  strcpy(lista_alunos.nome, nome);
  strcpy(lista_alunos.email, email);

  printf("\n(+) Estudante registado com sucesso!\n");

  return 0;
}

int show_menu(void)
{

  int option = 0;

  do
  {
    printf("\n▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃ M E N U ▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃\n");
  
    printf("① - Registar e consultar os dados dos estudantes\n");
    printf("② - Registar e consultar os dados das unidades curriculares\n");
    printf("③ - Registar e consultar os dados das avaliações\n");
    printf("④ - Consultar o total de ECTS aprovados por um estudante\n");
    printf("⑤ - Consultar a média aritmética de ECTS por semestre letivo por um aluno\n");
    printf("\n");
    printf("Ⓞ - Sair\n");
    printf("▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃ M E N U ▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃\n");

    printf("\n(-) Escolhe uma opção: ");
    scanf("%d", &option);

    if(option < 0 || option > 5)
      printf("Opção inválida!\n");

  } while(option < 0 || option > 5);

  return option;
}

// Verificar se o numero total de alunos já foi atingido
int check_total_alunos(int total_alunos)
{
  if(total_alunos == MAX_ALUNOS)
    mostrar_erro("O numero maximo de alunos foi atingido!\n");
    return 1;

  return 0;
}
// Verificar se o numero de aluno já existe

char mostrar_erro(char erro) {
  printf("(*) ERRO: %s", erro);
  return 0;
}