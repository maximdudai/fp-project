#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 150
#define MAX_UC 18
#define MAX_AVALIACOES 5000

#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 256
#define MAX_UC_NAME_LENGTH 256

#define MAX_ERRO_LENGTH 256
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

// MENU
int show_menu_principal(void);
void menu_registar_consultar_estudantes(struct estudante_data lista_alunos[], int alunos_count);

// FUNÇÕES DE REGISTO
void menu_registar_estudante(struct estudante_data lista_alunos[], int alunos_count);
// FUNCÕES DE CONSULTA
void menu_consultar_estudantes(struct estudante_data lista_alunos[], int alunos_count);

// FUNÇÕES AUXILIARES
int check_total_alunos(int total_alunos);
int check_numero_aluno(struct estudante_data lista_alunos[], int alunos_count, int aluno_id);

// FUNÇÕES DE ERRO
void mostrar_erro(char erro[]);

int main(void)
{

  int menu_option = 0;

  struct estudante_data lista_alunos[MAX_ALUNOS];
  int alunos_count = 0;

  struct unidade_curricular lista_uc[MAX_UC];
  int uc_count = 0;

  struct avaliacao_data lista_avaliacoes[MAX_AVALIACOES];
  int avaliacoes_count = 0;

  do
  {
    menu_option = show_menu_principal();

    switch (menu_option)
    {
    case 1:
    {
      menu_registar_consultar_estudantes(lista_alunos, alunos_count);
      break;
    }

    default:
      break;
    }

  } while (menu_option != 0);

  return 0;
}

int show_menu_principal(void)
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
    printf("▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃ M E N U ▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃\n");

    printf("\n(-) Escolhe uma opção: ");
    scanf("%d", &option);

    if (option < 0 || option > 5)
      printf("Opção inválida!\n");

  } while (option < 0 || option > 5);

  return option;
}

// MENU REGISTAR E CONSULTAR ESTUDANTES
// ---------------------------- REGISTAR ----------------------------
void menu_registar_consultar_estudantes(struct estudante_data lista_alunos[], int alunos_count)
{
  int option = 0;

  do
  {
    printf("▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃ M E N U ▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃\n");

    printf("\n① Registar os dados dos estudantes");
    printf("\n② Consultar os dados dos estudantes\n");
    printf("\n");
    printf("Ⓞ - Sair\n");
    printf("\n(-) Escolhe uma opção: ");
    scanf("%d", &option);

    if (option < 0 || option > 2)
      mostrar_erro("Opção inválida!\n");

  } while (option < 0 || option > 2);

  printf("\n\n opcao: %d\n\n", option);
  switch (option)
  {
  case 1:
    menu_registar_estudante(lista_alunos, alunos_count);
    break;
  case 2:
    if (!alunos_count)
      mostrar_erro("Não existem estudantes registados!\n");
    else
      menu_consultar_estudantes(lista_alunos, alunos_count);
    break;
  default:
    mostrar_erro("Opção inválida!\n");
    break;
  }
}

void menu_registar_estudante(struct estudante_data lista_alunos[], int alunos_count)
{
  int db_id = alunos_count + 1;

  int nr_aluno = 0;
  char nome[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH];
  int codigo_curso = 0;
  printf("\n(-) Número de aluno: ");
  scanf("%d", &nr_aluno);

  // Limpar o buffer de entrada para evitar problemas com fgets
  while ((getchar()) != '\n');

  printf("(-) Nome: ");
  fgets(nome, MAX_NAME_LENGTH, stdin);
  nome[strcspn(nome, "\n")] = '\0';

  printf("(-) Email: ");
  fgets(email, MAX_EMAIL_LENGTH, stdin);
  email[strcspn(email, "\n")] = '\0';

  printf("(-) Código do curso: ");
  scanf("%d", &codigo_curso);

  // Copiar os dados para a struct no índice apropriado
  strcpy(lista_alunos[db_id - 1].nome, nome);
  strcpy(lista_alunos[db_id - 1].email, email);
  lista_alunos[db_id - 1].nr_aluno = nr_aluno;
  lista_alunos[db_id - 1].db_id = db_id;
  lista_alunos[db_id - 1].codigo_curso = codigo_curso;

  printf("\n(+) Estudante registado com sucesso!\n");

  menu_registar_consultar_estudantes(lista_alunos, db_id);
}

// ---------------------------- CONSULTAR ----------------------------
void menu_consultar_estudantes(struct estudante_data lista_alunos[], int alunos_count)
{

  int estudante_id = 0, aluno_db_id = -1;
  do
  {
    printf("\nIndique o numero de estudante (total estudantes %d): ", alunos_count);
    scanf("%d", &estudante_id);

    aluno_db_id = check_numero_aluno(lista_alunos, alunos_count, estudante_id);

    if (aluno_db_id <= -1)
      mostrar_erro("O estudante não existe!\n");

  } while (aluno_db_id <= -1);

  printf("\nDetalhes sobre aluno: %s (#%d)\n", lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].nr_aluno);

  printf("(-) Nome: %s\n", lista_alunos[aluno_db_id].nome);
  printf("(-) Email: %s\n", lista_alunos[aluno_db_id].email);
  printf("(-) Número de aluno: %d\n", lista_alunos[aluno_db_id].nr_aluno);
  printf("(-) Código do curso: %d\n", lista_alunos[aluno_db_id].codigo_curso);

  menu_registar_consultar_estudantes(lista_alunos, alunos_count);
}

// -------------------------------------------------------- FUNÇÕES AUXILIARES --------------------------------------------------------
// Verificar se o numero total de alunos já foi atingido
int check_total_alunos(int total_alunos)
{
  if (total_alunos >= MAX_ALUNOS)
    mostrar_erro("O numero maximo de alunos foi atingido!\n");
  return 1;

  return 0;
}

// verificar se o aluno existe
int check_numero_aluno(struct estudante_data lista_alunos[], int alunos_count, int aluno_id)
{
  // percorrer ao ficheiro (data.txt) e verificar se o aluno existe
  int aluno_index = -1;
  for (int i = 0; i < alunos_count; i++)
  {
    if (lista_alunos[i].nr_aluno == aluno_id || lista_alunos[i].db_id == aluno_id)
    {
      aluno_index = i;
      break;
    }
  }
  return aluno_index;
}

void mostrar_erro(char erro[])
{
  char mensagem_erro[MAX_ERRO_LENGTH];
  int i;
  for (i = 0; i < MAX_ERRO_LENGTH && erro[i] != '\0'; i++)
  {
    mensagem_erro[i] = erro[i];
  }

  mensagem_erro[i] = '\0';

  printf("(*) ERRO: %s\n", mensagem_erro);
}
