#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 150
#define MAX_UC 18
#define MAX_AVALIACOES 5000

// MENU OPTION
#define MENU_CONSULTAR_REGISTAR_ESTUDANTES 1
#define MENU_CONSULTAR_REGISTAR_UC 2
#define MENU_CONSULTAR_REGISTAR_AVALIACOES 3

#define MENU_REGISTAR_ESTUDANTE 1
#define MENU_CONSULTAR_ESTUDANTE 2

#define MENU_REGISTAR_UC 1
#define MENU_CONSULTAR_UC 2

// CONSTANTES
#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 256
#define MAX_UC_NAME_LENGTH 256

// ERROS
#define MAX_ERRO_LENGTH 256
#define MAX_ACCEPTABLE_STRING 512

#define MIN_ACCEPTABLE_NUMBER 0
#define MAX_ACCEPTABLE_NUMBER 9999999
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
void menu_registar_consultar_estudantes(struct estudante_data lista_alunos[], int);
void menu_registar_consultar_uc(struct unidade_curricular lista_uc[], int);

// FUNÇÕES DE REGISTO
void menu_registar_estudante(struct estudante_data lista_alunos[], int);
void menu_registar_uc(struct unidade_curricular lista_uc[], int);
// FUNCÕES DE CONSULTA
void menu_consultar_estudantes(struct estudante_data lista_alunos[], int);
void menu_consultar_uc(struct unidade_curricular lista_uc[], int);

// FUNÇÕES AUXILIARES
int check_total_alunos(int);
int check_numero_aluno(struct estudante_data lista_alunos[], int, int);
int get_aluno_db_id(struct estudante_data lista_alunos[], int);

int check_numero_uc(struct unidade_curricular lista_uc[], int, int);
int get_uc_id(struct unidade_curricular lista_uc[], int);

char *check_email(char[]);
int is_valid_email(char[]);

char *ler_string(char[], char[], int);
int ler_numero(char[], int);

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
    case MENU_CONSULTAR_REGISTAR_ESTUDANTES:
    {
      menu_registar_consultar_estudantes(lista_alunos, alunos_count);
      break;
    }
    case MENU_CONSULTAR_REGISTAR_UC:
    {
      menu_registar_consultar_uc(lista_uc, uc_count);
      break;
    }

    case MENU_CONSULTAR_REGISTAR_AVALIACOES:
    {
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

  switch (option)
  {
  case MENU_REGISTAR_ESTUDANTE:
    menu_registar_estudante(lista_alunos, alunos_count);
    break;
  case MENU_CONSULTAR_ESTUDANTE:
    if (!alunos_count) {
      mostrar_erro("Não existem estudantes registados!\n");
      menu_registar_consultar_estudantes(lista_alunos, alunos_count);
    }

    else
      menu_consultar_estudantes(lista_alunos, alunos_count);
    break;
  }
}

void menu_registar_estudante(struct estudante_data lista_alunos[], int alunos_count)
{
  int db_id = alunos_count + 1, nr_aluno = 0, codigo_curso = 0;
  char nome[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH];

  ler_string("(-) Nome: ", nome, MAX_NAME_LENGTH);
  nr_aluno = ler_numero("(-) Número de aluno: ", MAX_ACCEPTABLE_NUMBER);
  check_email(email);
  codigo_curso = ler_numero("(-) Código do curso: ", MAX_ACCEPTABLE_NUMBER);

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

  int aluno_db_id;

  aluno_db_id = get_aluno_db_id(lista_alunos, alunos_count);

  // caso aluno_db_id seja -1 mandar o usuario para o menu de registar e consultar estudantes

  printf("\nDetalhes sobre aluno: %s (#%d)\n", lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].nr_aluno);

  printf("(-) Nome: %s\n", lista_alunos[aluno_db_id].nome);
  printf("(-) Email: %s\n", lista_alunos[aluno_db_id].email);
  printf("(-) Número de aluno: %d\n", lista_alunos[aluno_db_id].nr_aluno);
  printf("(-) Código do curso: %d\n", lista_alunos[aluno_db_id].codigo_curso);

  menu_registar_consultar_estudantes(lista_alunos, alunos_count);
}

// #2 MENU REGISTAR E CONSULTAR UC
void menu_registar_consultar_uc(struct unidade_curricular lista_uc[], int uc_count)
{
  int option = 0;

  option = ler_numero("Escolhe uma opção: ", 2);

  switch (option)
  {
  case MENU_REGISTAR_UC:
    menu_registar_uc(lista_uc, uc_count);
    break;
  case MENU_CONSULTAR_UC:
    menu_consultar_uc(lista_uc, uc_count);
    break;
  default:
    mostrar_erro("Opção inválida!\n");
    break;
  }
}
// ---------------------------- REGISTAR ----------------------------

void menu_registar_uc(struct unidade_curricular lista_uc[], int uc_count)
{
  int db_id = uc_count + 1, uc_codigo = 0, ano = 0, semestre = 0, ects = 0;
  char nome[MAX_UC_NAME_LENGTH];

  ler_string("(-) Nome: ", nome, MAX_UC_NAME_LENGTH);

  uc_codigo = ler_numero("(-) Código da UC: ", 9);
  ano = ler_numero("(-) Ano: ", 2);
  semestre = ler_numero("(-) Semestre: ", 2);
  ects = ler_numero("(-) ECTS: ", 6);

  strcpy(lista_uc[db_id - 1].nome, nome);
  lista_uc[db_id - 1].db_id = db_id;
  lista_uc[db_id - 1].uc_codigo = uc_codigo;
  lista_uc[db_id - 1].ano = ano;
  lista_uc[db_id - 1].semestre = semestre;
  lista_uc[db_id - 1].ects = ects;

  printf("\n(+) Unidade curricular registada com sucesso!\n");

  menu_registar_consultar_uc(lista_uc, db_id);
}
void menu_consultar_uc(struct unidade_curricular lista_uc[], int uc_count)
{
  int uc_db_id = -1;

  uc_db_id = get_uc_id(lista_uc, uc_count);

  // caso uc_db_id seja -1 mandar o usuario para o menu de registar e consultar uc

  printf("\nDetalhes sobre unidade curricular: %s (#%d)\n", lista_uc[uc_db_id].nome, lista_uc[uc_db_id].uc_codigo);

  printf("(-) Nome: %s\n", lista_uc[uc_db_id].nome);
  printf("(-) Código da UC: %d\n", lista_uc[uc_db_id].uc_codigo);
  printf("(-) Ano: %d\n", lista_uc[uc_db_id].ano);
  printf("(-) Semestre: %d\n", lista_uc[uc_db_id].semestre);
  printf("(-) ECTS: %d\n", lista_uc[uc_db_id].ects);

  menu_registar_consultar_uc(lista_uc, uc_count);
}

// -------------------------------------------------------- FUNÇÕES AUXILIARES --------------------------------------------------------

int get_uc_id(struct unidade_curricular lista_uc[], int uc_count)
{
  int uc_id = 0, uc_db_id = -1;
  do
  {
    printf("\nIndique o código da unidade curricular (total unidades curriculares %d): ", uc_count);
    scanf("%d", &uc_id);
    uc_db_id = check_numero_uc(lista_uc, uc_count, uc_id);
    if (uc_db_id <= -1)
      mostrar_erro("A unidade curricular não existe!\n");
  } while (uc_db_id <= -1);
  return uc_id;
}

int get_aluno_db_id(struct estudante_data lista_alunos[], int alunos_count)
{
  int aluno_id = 0, aluno_db_id = -1;
  do
  {
    printf("\nIndique o número de aluno (total alunos %d): ", alunos_count);
    scanf("%d", &aluno_id);
    aluno_db_id = check_numero_aluno(lista_alunos, alunos_count, aluno_id);
    if (aluno_db_id <= -1)
      mostrar_erro("O aluno não existe!\n");
  } while (aluno_db_id <= -1);
  return aluno_db_id;
}

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

int check_numero_uc(struct unidade_curricular lista_uc[], int uc_count, int uc_id)
{
  // percorrer ao ficheiro (data.txt) e verificar se o aluno existe
  int uc_index = -1;
  for (int i = 0; i < uc_count; i++)
  {
    if (lista_uc[i].uc_codigo == uc_id || lista_uc[i].db_id == uc_id)
    {
      uc_index = i;
      break;
    }
  }
  return uc_index;
}

char *ler_string(char *prompt, char *string, int max_length)
{
  do
  {
    printf("%s", prompt);
    fgets(string, max_length, stdin);
    string[strcspn(string, "\n")] = '\0';
  } while (!strlen(string) || strlen(string) > max_length);

  return string;
}

int ler_numero(char *prompt, int max_length)
{
  int number = 0;

  do
  {
    printf("%s", prompt);
    scanf("%d", &number);
    fflush(stdin);

    if (!number || number > max_length)
      mostrar_erro("Número inválido!\n");

  } while (!number || number > max_length);

  return number;
}

char *check_email(char *emailAddress)
{

  do
  {
    ler_string("(-) Email: ", emailAddress, MAX_EMAIL_LENGTH);

  } while (!is_valid_email(emailAddress));

  return emailAddress;
}

int is_valid_email(char emailAddress[])
{
  int isValid = 0;

  for (int i = 0; i < MAX_EMAIL_LENGTH; i++)
  {
    if (emailAddress[i] == '@')
    {
      isValid = 1;
      break;
    }
  }

  if (!isValid)
    printf("Email inválido!\n");

  return isValid;
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
