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
#define MENU_CONSULTAR_ESTATISTICAS 4
#define MENU_GUARDAR_LER_FICHEIROS 5

//entrega 2 (main)
#define MENU_CALCULAR_ALUNOS_AVALIADOS 6
#define MENU_CALCULAR_ALUNOS_NAO_AVALIADOS 7

#define MENU_REGISTAR_ESTUDANTE 1
#define MENU_CONSULTAR_ESTUDANTE 2

#define MENU_REGISTAR_UC 1
#define MENU_CONSULTAR_UC 2

#define MENU_REGISTAR_AVALIACAO 1
#define MENU_CONSULTAR_AVALIACAO 2

// CONSTANTES
#define MAX_NAME_LENGTH 100
#define MAX_EMAIL_LENGTH 256
#define MAX_UC_NAME_LENGTH 256
#define MAX_DATA_CHARS 12

//entrega 2
#define MAX_CONCELHO_LENGTH 144

#define MIN_NUMBER_STUDENT 2000000
#define MAX_NUMBER_STUDENT 2999999

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
  char concelho[MAX_CONCELHO_LENGTH];
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
  //entrega 2
  int avaliado;

  char data[MAX_DATA_CHARS];
  int nota;
};

// MENU
int show_menu_principal(void);
char confirmar_saida(void);

int menu_registar_consultar_estudantes(struct estudante_data lista_alunos[], int);
int menu_registar_consultar_uc(struct unidade_curricular lista_uc[], int);
int menu_registar_consultar_avaliacoes(struct avaliacao_data lista_avaliacoes[], int, struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int);
void menu_consultar_estatisticas(struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int, struct avaliacao_data lista_avaliacoes[], int);
int menu_ler_guardar_ficheiros(struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int, struct avaliacao_data lista_avaliacoes[], int);

// FUNÇÕES DE REGISTO
int menu_registar_estudante(struct estudante_data lista_alunos[], int);
int menu_registar_uc(struct unidade_curricular lista_uc[], int);
int menu_registar_avaliacao(struct avaliacao_data lista_avaliacoes[], int, struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int);

// FUNCÕES DE CONSULTA
void menu_consultar_estudantes(struct estudante_data lista_alunos[], int);
void menu_consultar_uc(struct unidade_curricular lista_uc[], int);
void menu_consultar_avaliacoes(struct avaliacao_data lista_avaliacoes[], int, struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[]);
void menu_consultar_ects(struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int, struct avaliacao_data lista_avaliacoes[], int);
void menu_consultar_media_ects(struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int, struct avaliacao_data lista_avaliacoes[], int);
void menu_consultar_percentagem_ects_aprovados(struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int, struct avaliacao_data lista_avaliacoes[], int);

//entrega 2
void menu_calcular_avaliados(struct avaliacao_data lista_avaliacoes[], struct unidade_curricular lista_uc[], int, int);
void menu_calcular_nao_avaliados(struct avaliacao_data lista_avaliacoes[], struct unidade_curricular lista_uc[], int, int);

// FUNÇÕES DE FICHEIROS
void menu_guardar_ficheiro(struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int, struct avaliacao_data lista_avaliacoes[], int);
void menu_ler_ficheiro(struct estudante_data lista_alunos[], int, struct unidade_curricular lista_uc[], int, struct avaliacao_data lista_avaliacoes[], int);
// FUNÇÕES AUXILIARES
int check_total_alunos(int);
int check_numero_aluno(struct estudante_data lista_alunos[], int, int);
int get_aluno_db_id(struct estudante_data lista_alunos[], int);
void get_avaliacao_type(int, char[]);

//entrega 2
int calcular_avaliados(struct avaliacao_data lista_avaliacoes[], int, int);
int calcular_nao_avaliados(struct avaliacao_data lista_avaliacoes[], int, int);

//entrega 2
void is_aluno_avaliado(int, char[]);

int check_numero_uc(struct unidade_curricular lista_uc[], int, int);
int get_uc_id(struct unidade_curricular lista_uc[], int);

char *check_email(char[]);
int is_valid_email(char[]);

//entrega 2
char *check_concelho(char []);
int is_valid_concelho(char []);

char *ler_string(char[], char[], int);
int ler_numero(char[], int, int);

// FUNÇÕES DE ERRO
void mostrar_erro(char erro[]);

int main(void)
{

  int menu_option = 0;
  char opcao_saida = 'n';

  struct estudante_data lista_alunos[MAX_ALUNOS];
  int alunos_count = 0;

  struct unidade_curricular lista_uc[MAX_UC];
  int uc_count = 0;

  struct avaliacao_data lista_avaliacoes[MAX_AVALIACOES];
  int avaliacoes_count = 0;

  int file_option = 0;

  do
  {
    menu_option = show_menu_principal();

    switch (menu_option)
    {
    case MENU_CONSULTAR_REGISTAR_ESTUDANTES:
    {
      alunos_count = menu_registar_consultar_estudantes(lista_alunos, alunos_count);
      break;
    }
    case MENU_CONSULTAR_REGISTAR_UC:
    {
      uc_count = menu_registar_consultar_uc(lista_uc, uc_count);
      break;
    }

    case MENU_CONSULTAR_REGISTAR_AVALIACOES:
    {
      if (!alunos_count)
      {
        mostrar_erro("Não existem estudantes registados!\n");
      }
      else
        avaliacoes_count = menu_registar_consultar_avaliacoes(lista_avaliacoes, avaliacoes_count, lista_alunos, alunos_count, lista_uc, uc_count);
      break;
    }
    case MENU_CONSULTAR_ESTATISTICAS:
    {
      if (!alunos_count || !uc_count || !avaliacoes_count)
      {
        mostrar_erro("Não existem dados suficientes para obter estatisticas!\n");
      }
      else
        menu_consultar_estatisticas(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
      break;
    }
    case MENU_GUARDAR_LER_FICHEIROS:
    {
      file_option = menu_ler_guardar_ficheiros(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);

      switch (file_option)
      {
        case 1:
        {
          menu_guardar_ficheiro(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
          break;
        }
        case 2:
        {
          menu_ler_ficheiro(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
          break;
        }
        default:
          break;
        }

      break;
    }
    //entrega 2
    case MENU_CALCULAR_ALUNOS_AVALIADOS: {
        if(!avaliacoes_count || !uc_count) {
            mostrar_erro("Nao dados suficientes!");
        }
        else {
            menu_calcular_avaliados(lista_avaliacoes, lista_uc, avaliacoes_count, uc_count);
        }
        break;
    }
    case MENU_CALCULAR_ALUNOS_NAO_AVALIADOS: {
        if(!avaliacoes_count || !uc_count) {
            mostrar_erro("Nao existem dados suficientes!");
        }
        else {
            menu_calcular_nao_avaliados(lista_avaliacoes, lista_uc, avaliacoes_count, uc_count);
        }
        break;
    }
    case 0:
      break;

    default:
      printf("Opcão incorreta");
    }

    opcao_saida = confirmar_saida();
  } while (opcao_saida == 'n' || opcao_saida == 'N');

  return 0;
}

char confirmar_saida(void)
{
  char opcao;

  printf("\nPertende sair? ");
  scanf(" %c", &opcao);

  return opcao;
}

int show_menu_principal(void)
{
  int option = 0;

  printf("\n------------------------------------------- M E N U -------------------------------------------\n");
  printf("1 - Registar e consultar os dados dos estudantes\n");
  printf("2 - Registar e consultar os dados das unidades curriculares\n");
  printf("3 - Registar e consultar os dados das avaliações\n");
  printf("4 - Estatisticas\n");
  printf("5 - Guardar e ler de ficheiros binários os dados da aplicação\n");
  //entrega 2
  printf("6 - Calcular aluno avaliados\n");
  printf("7 - Calcular alunos nao avaliados\n");
  printf("\n");
  printf("0 - Sair\n");
  printf("------------------------------------------- M E N U -------------------------------------------\n");

  printf("\n(-) Escolhe uma opção: ");
  scanf("%d", &option);

  return option;
}
// MENU REGISTAR E CONSULTAR ESTUDANTES
// ---------------------------- REGISTAR ----------------------------
int menu_registar_consultar_estudantes(struct estudante_data lista_alunos[], int alunos_count)
{
  int option = 0;

  do
  {
    printf("\n① Registar os dados dos estudantes");
    printf("\n② Consultar os dados dos estudantes\n");
    printf("\n");
    printf("Ⓞ - Sair\n");

    option = ler_numero("Escolhe uma opção: ", 0, 2);

  } while (option < 0 || option > 2);

  switch (option)
  {
  case MENU_REGISTAR_ESTUDANTE:
    alunos_count = menu_registar_estudante(lista_alunos, alunos_count);
    break;
  case MENU_CONSULTAR_ESTUDANTE:
    if (!alunos_count)
    {
      mostrar_erro("Não existem estudantes registados!\n");
      menu_registar_consultar_estudantes(lista_alunos, alunos_count);
    }
    else
      menu_consultar_estudantes(lista_alunos, alunos_count);
    break;
  }
  return alunos_count;
}

int menu_registar_estudante(struct estudante_data lista_alunos[], int alunos_count)
{
  int db_id = alunos_count + 1, nr_aluno = 0, codigo_curso = 0;
  char nome[MAX_NAME_LENGTH], email[MAX_EMAIL_LENGTH];
  //entrega 2
  char concelho[MAX_CONCELHO_LENGTH];

  fflush(stdin);
  ler_string("(-) Nome: ", nome, MAX_NAME_LENGTH);
  do
  {
    nr_aluno = ler_numero("(-) Número de aluno (2000000 - 2999999): ", MIN_NUMBER_STUDENT, MAX_NUMBER_STUDENT);

    if (check_numero_aluno(lista_alunos, alunos_count, nr_aluno) != -1)
      mostrar_erro("O aluno já existe!\n");
  } while (check_numero_aluno(lista_alunos, alunos_count, nr_aluno) != -1);

  check_email(email);

  //Entrega 2
  check_concelho(concelho);

  codigo_curso = ler_numero("(-) Código do curso: ", 1000, MAX_ACCEPTABLE_NUMBER);
  strcpy(lista_alunos[db_id - 1].nome, nome);
  strcpy(lista_alunos[db_id - 1].email, email);
  //Entrega 2
  strcpy(lista_alunos[db_id - 1].concelho, concelho);

  lista_alunos[db_id - 1].nr_aluno = nr_aluno;
  lista_alunos[db_id - 1].db_id = db_id;
  lista_alunos[db_id - 1].codigo_curso = codigo_curso;
  printf("\n(+) Estudante registado com sucesso!\n");
  menu_registar_consultar_estudantes(lista_alunos, db_id);
  return db_id;
}

// ---------------------------- CONSULTAR ----------------------------
void menu_consultar_estudantes(struct estudante_data lista_alunos[], int alunos_count)
{
  int aluno_db_id;
  aluno_db_id = get_aluno_db_id(lista_alunos, alunos_count);
  // caso aluno_db_id seja -1 mandar o usuario para o menu de registar e consultar estudantes
  printf("\nDetalhes sobre aluno: %s (#%d)\n", lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].nr_aluno);
  //entrega 2 (+concelho)
  printf("ID\tNome\t\tEmail\t\tNúmero de aluno\t\tCódigo do curso\t\tConcelho\n");
  printf("--------------------------------------------------------------------------\n");
  printf("%d\t\t%s\t\t%s\t\t%d\t\t%d\t%s\n", aluno_db_id, lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].email, lista_alunos[aluno_db_id].nr_aluno, lista_alunos[aluno_db_id].codigo_curso, lista_alunos[aluno_db_id].concelho);

  menu_registar_consultar_estudantes(lista_alunos, alunos_count);
}

// #2 MENU REGISTAR E CONSULTAR UC
// ---------------------------- REGISTAR ----------------------------
int menu_registar_consultar_uc(struct unidade_curricular lista_uc[], int uc_count)
{
  int option = 0;
  do
  {
    printf("\n① Registar os dados das unidades curriculares");
    printf("\n② Consultar os dados das unidades curriculares\n");
    printf("\n");
    printf("Ⓞ - Sair\n");

    option = ler_numero("Escolhe uma opção: ", 0, 2);

  } while (option < 0 || option > 2);

  switch (option)
  {
  case MENU_REGISTAR_UC:
    uc_count = menu_registar_uc(lista_uc, uc_count);
    break;
  case MENU_CONSULTAR_UC:
    if (!uc_count)
    {
      mostrar_erro("Não existem unidades curriculares registadas!\n");
      menu_registar_consultar_uc(lista_uc, uc_count);
    }
    else
      menu_consultar_uc(lista_uc, uc_count);
    break;
  }

  return uc_count;
}
// ---------------------------- REGISTAR ----------------------------

int menu_registar_uc(struct unidade_curricular lista_uc[], int uc_count)
{
  int db_id = uc_count + 1, uc_codigo = 0, ano = 0, semestre = 0, ects = 0;
  char nome[MAX_UC_NAME_LENGTH];
  ler_string("(-) Nome: ", nome, MAX_UC_NAME_LENGTH);
  do
  {
    uc_codigo = ler_numero("(-) Código da UC: ", 1, MAX_ACCEPTABLE_NUMBER);

    if (check_numero_uc(lista_uc, uc_count, uc_codigo) != -1)
      mostrar_erro("A unidade curricular já existe!\n");

  } while (check_numero_uc(lista_uc, uc_count, uc_codigo) != -1);

  ano = ler_numero("(-) Ano: ", 1, 2);
  semestre = ler_numero("(-) Semestre: ", 1, 2);
  ects = ler_numero("(-) ECTS: ", 1, 7);

  strcpy(lista_uc[db_id - 1].nome, nome);
  lista_uc[db_id - 1].db_id = db_id;
  lista_uc[db_id - 1].uc_codigo = uc_codigo;
  lista_uc[db_id - 1].ano = ano;
  lista_uc[db_id - 1].semestre = semestre;
  lista_uc[db_id - 1].ects = ects;

  printf("\n(+) Unidade curricular registada com sucesso!\n");

  menu_registar_consultar_uc(lista_uc, db_id);

  return db_id;
}
void menu_consultar_uc(struct unidade_curricular lista_uc[], int uc_count)
{
  int uc_db_id;

  uc_db_id = get_uc_id(lista_uc, uc_count);

  // caso uc_db_id s eja -1 mandar o usuario para o menu de registar e consultar uc

  printf("\nDetalhes sobre unidade curricular: %s (#%d)\n", lista_uc[uc_db_id].nome, lista_uc[uc_db_id].uc_codigo);

  printf("ID\t\tNome\t\tCódigo da UC\t\tAno\t\tSemestre\t\tECTS\n");
  printf("-----------------------------------------------------------------------------------\n");
  printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n", uc_db_id, lista_uc[uc_db_id].nome, lista_uc[uc_db_id].uc_codigo, lista_uc[uc_db_id].ano, lista_uc[uc_db_id].semestre, lista_uc[uc_db_id].ects);

  menu_registar_consultar_uc(lista_uc, uc_count);
}

// #3 MENU REGISTAR E CONSULTAR AVALIACOES
// ---------------------------- REGISTAR ----------------------------
int menu_registar_consultar_avaliacoes(struct avaliacao_data lista_avaliacoes[], int avaliacoes_count, struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count)
{
  int option = 0;
  do
  {
    printf("\n① Registar os dados das avaliações");
    printf("\n② Consultar os dados das avaliações\n");
    printf("\n");
    printf("Ⓞ - Sair\n");

    option = ler_numero("Escolhe uma opção: ", 0, 2);

  } while (option < 0 || option > 2);

  switch (option)
  {
  case MENU_REGISTAR_AVALIACAO:
    avaliacoes_count = menu_registar_avaliacao(lista_avaliacoes, avaliacoes_count, lista_alunos, alunos_count, lista_uc, uc_count);
    break;

  case MENU_CONSULTAR_AVALIACAO:
    if (!avaliacoes_count)
    {
      mostrar_erro("Não existem avaliações registadas!\n");
      menu_registar_consultar_avaliacoes(lista_avaliacoes, avaliacoes_count, lista_alunos, alunos_count, lista_uc, uc_count);
    }
    else
      menu_consultar_avaliacoes(lista_avaliacoes, avaliacoes_count, lista_alunos, alunos_count, lista_uc);
    break;
  }

  return avaliacoes_count;
}

int menu_registar_avaliacao(struct avaliacao_data lista_avaliacoes[], int avaliacoes_count, struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count)
{
  int db_id = avaliacoes_count + 1, aluno_id = 0, uc_id = 0, ano_letivo = 0, tipo = 0, nota = 0;
  //entrega 2
  int avaliado = 0;

  char data[MAX_DATA_CHARS];
  aluno_id = get_aluno_db_id(lista_alunos, alunos_count);
  uc_id = get_uc_id(lista_uc, uc_count);
  ler_string("(-) Data: ", data, MAX_DATA_CHARS);
  ano_letivo = ler_numero("(-) Ano letivo: ", 2023, 2024);
  tipo = ler_numero("(-) Tipo (1 - Avaliacao Final Semetre | 2 - Recurso | 3 - Especial): ", 1, 3);

  //entrega 2
  avaliado = ler_numero("(-) Avaliado (1 = Avaliado | 2 = Faltou | 3 = Desistiu): ", 1, 3);
  if(avaliado == 1)
    nota = ler_numero("(-) Nota: ", 0, 20);

  lista_avaliacoes[db_id - 1].db_id = db_id;
  lista_avaliacoes[db_id - 1].aluno_id = aluno_id;
  lista_avaliacoes[db_id - 1].uc_id = uc_id;
  lista_avaliacoes[db_id - 1].ano_letivo = ano_letivo;
  lista_avaliacoes[db_id - 1].tipo = tipo;
  strcpy(lista_avaliacoes[db_id - 1].data, data);
  lista_avaliacoes[db_id - 1].nota = nota;
  //entrega 2
  lista_avaliacoes[db_id - 1].avaliado = avaliado;

  printf("\n(+) Avaliação registada com sucesso!\n");
  menu_registar_consultar_avaliacoes(lista_avaliacoes, db_id, lista_alunos, alunos_count, lista_uc, uc_count);
  return db_id;
}

// ---------------------------- CONSULTAR ----------------------------
void menu_consultar_avaliacoes(struct avaliacao_data lista_avaliacoes[], int avaliacoes_count, struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[])
{
  char tipo_result[MAX_ACCEPTABLE_STRING];

  //entrega 2
  char aluno_avaliado[MAX_ACCEPTABLE_STRING];

  int aluno_db_id = get_aluno_db_id(lista_alunos, alunos_count);

  printf("\nAvaliações do aluno: %s (#%d)\n", lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].nr_aluno);

  printf("ID\tID Estudante\tID UC\tAno letivo\tTipo\tData\tNota\tAvaliado\n");
  printf("-----------------------------------------------------------------------------------\n");

  for (int i = 0; i < avaliacoes_count; i++)
  {
    if (lista_avaliacoes[i].aluno_id == aluno_db_id)
    {
      get_avaliacao_type(lista_avaliacoes[i].tipo, tipo_result);

      //entrega 2
      is_aluno_avaliado(lista_avaliacoes[i].avaliado, aluno_avaliado);

      printf("%d\t%d\t%d\t%d\t%s\t%s\t%d\t%s\n", i, lista_avaliacoes[i].aluno_id, lista_avaliacoes[i].uc_id, lista_avaliacoes[i].ano_letivo, tipo_result, lista_avaliacoes[i].data, lista_avaliacoes[i].nota, aluno_avaliado);
    }
  }

  menu_registar_consultar_avaliacoes(lista_avaliacoes, avaliacoes_count, lista_alunos, alunos_count, lista_uc, avaliacoes_count);
}

// #4 MENU CONSULTAR ESTATISTICAS
void menu_consultar_estatisticas(struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count, struct avaliacao_data lista_avaliacoes[], int avaliacoes_count)
{
  int option = 0;
  do
  {
    printf("\n① Consultar o total de ECTS aprovados por um estudante");
    printf("\n② Consultar a média aritmética de ECTS por semestre letivo por um aluno");
    printf("\n③ Percentagem de ECTS em cada semestre letivo por um aluno");
    printf("\n\n");
    printf("Ⓞ - Sair\n");
    option = ler_numero("Escolhe uma opção: ", 0, 3);
  } while (option < 0 || option > 3);

  switch (option)
  {
  case 1:
  {
    if (!alunos_count || !uc_count || !avaliacoes_count)
      mostrar_erro("Não existem dados suficientes para esta consulta!\n");
    else
      menu_consultar_ects(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
    break;
  }
  case 2:
  {
    if (!alunos_count)
    {
      mostrar_erro("Não existem estudantes registados!\n");
    }
    else
      menu_consultar_media_ects(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
    break;
  }
  case 3:
  {
    if (!alunos_count)
    {
      mostrar_erro("Não existem estudantes registados!\n");
    }
    else
      menu_consultar_percentagem_ects_aprovados(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
    break;
  }
  }
}

// ---------------------------- CONSULTAR ----------------------------
void menu_consultar_percentagem_ects_aprovados(struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count, struct avaliacao_data lista_avaliacoes[], int avaliacoes_count)
{
  int aluno_db_id = get_aluno_db_id(lista_alunos, alunos_count);
  int total_ects = 0, total_semestre = 0, total_semestre_ects = 0, total_semestre_ects_count = 0;
  char tipo_result[MAX_ACCEPTABLE_STRING];

  //entrega 2
  char aluno_avaliado[MAX_ACCEPTABLE_STRING];

  printf("\nPercentagem de ECTS em cada semestre letivo por %s (#%d)\n", lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].nr_aluno);
  printf("ID\tID UC\tAno letivo\tTipo\tData\tNota\tAvaliado\n");
  printf("-----------------------------------------------------------------------------------\n");
  for (int i = 0; i < avaliacoes_count; i++)
  {
    if (lista_avaliacoes[i].aluno_id == aluno_db_id && lista_avaliacoes[i].nota >= 10)
    {
      get_avaliacao_type(lista_avaliacoes[i].tipo, tipo_result);

      //entrega 2
      is_aluno_avaliado(lista_avaliacoes[i].avaliado, aluno_avaliado);

      printf("%d\t%d\t%d\t%s\t%s\t%d\t%s\n", i, lista_avaliacoes[i].uc_id, lista_avaliacoes[i].ano_letivo, tipo_result, lista_avaliacoes[i].data, lista_avaliacoes[i].nota, aluno_avaliado);
      total_ects += lista_uc[lista_avaliacoes[i].uc_id].ects;
      total_semestre_ects += lista_uc[lista_avaliacoes[i].uc_id].ects;
      total_semestre_ects_count++;
      total_semestre++;
    }
    else if (lista_avaliacoes[i].aluno_id == aluno_db_id && lista_avaliacoes[i].nota < 10)
      total_semestre++;
    if (total_semestre_ects_count == 6)
    {
      printf("\nPercentagem de ECTS do semestre %d: %d\n", total_semestre, (total_semestre_ects / total_semestre_ects_count) * 100 / 30);
      total_semestre_ects = 0;
      total_semestre_ects_count = 0;
    }
  }
  printf("\nPercentagem de ECTS por semestre letivo: %d\n", (total_ects * 100) / 180);
  menu_consultar_estatisticas(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
}

void menu_consultar_ects(struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count, struct avaliacao_data lista_avaliacoes[], int avaliacoes_count)
{
  int aluno_db_id = get_aluno_db_id(lista_alunos, alunos_count);
  int total_ects = 0;
  char tipo_result[MAX_ACCEPTABLE_STRING];

  //entrega 2
  char aluno_avaliado[MAX_ACCEPTABLE_STRING];

  printf("\nTotal de ECTS aprovados por %s (#%d)\n", lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].nr_aluno);
  printf("ID\tID UC\tAno letivo\tTipo\tData\tNota\tAvaliado\n");
  printf("-----------------------------------------------------------------------------------\n");
  for (int i = 0; i < avaliacoes_count; i++)
  {
    if (lista_avaliacoes[i].aluno_id == aluno_db_id && lista_avaliacoes[i].nota >= 10)
    {
      get_avaliacao_type(lista_avaliacoes[i].tipo, tipo_result);

      //entrega 2
      is_aluno_avaliado(lista_avaliacoes[i].avaliado, aluno_avaliado);

      printf("%d\t%d\t%d\t%s\t%s\t%d\t%s\n", i, lista_avaliacoes[i].uc_id, lista_avaliacoes[i].ano_letivo, tipo_result, lista_avaliacoes[i].data, lista_avaliacoes[i].nota, aluno_avaliado);
      total_ects += lista_uc[lista_avaliacoes[i].uc_id].ects;
    }
  }
  printf("\nTotal de ECTS aprovados: %d\n", total_ects);
  menu_consultar_estatisticas(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
}

void menu_consultar_media_ects(struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count, struct avaliacao_data lista_avaliacoes[], int avaliacoes_count)
{
  int aluno_db_id = get_aluno_db_id(lista_alunos, alunos_count);
  int total_ects = 0, total_semestre = 0, total_semestre_ects = 0, total_semestre_ects_count = 0;
  char tipo_result[MAX_ACCEPTABLE_STRING];

  //entrega 2
  char aluno_avaliado[MAX_ACCEPTABLE_STRING];

  printf("\nMédia aritmética de ECTS por semestre letivo por %s (#%d)\n", lista_alunos[aluno_db_id].nome, lista_alunos[aluno_db_id].nr_aluno);
  printf("ID\tID UC\tAno letivo\tTipo\tData\tNota\tAvaliado\n");
  printf("-----------------------------------------------------------------------------------\n");
  for (int i = 0; i < avaliacoes_count; i++)
  {
    if (lista_avaliacoes[i].aluno_id == aluno_db_id && lista_avaliacoes[i].nota >= 10)
    {
      get_avaliacao_type(lista_avaliacoes[i].tipo, tipo_result);

      //entrega 2
      is_aluno_avaliado(lista_avaliacoes[i].avaliado, aluno_avaliado);

      printf("%d\t%d\t%d\t%s\t%s\t%d\t%s\n", i, lista_avaliacoes[i].uc_id, lista_avaliacoes[i].ano_letivo, tipo_result, lista_avaliacoes[i].data, lista_avaliacoes[i].nota, aluno_avaliado);
      total_ects += lista_uc[lista_avaliacoes[i].uc_id].ects;
      total_semestre_ects += lista_uc[lista_avaliacoes[i].uc_id].ects;
      total_semestre_ects_count++;
      total_semestre++;
    }
    else if (lista_avaliacoes[i].aluno_id == aluno_db_id && lista_avaliacoes[i].nota < 10)
      total_semestre++;
    if (total_semestre_ects_count == 6)
    {
      printf("\nMédia aritmética de ECTS do semestre %d: %d\n", total_semestre, total_semestre_ects / total_semestre_ects_count);
      total_semestre_ects = 0;
      total_semestre_ects_count = 0;
    }
  }
  printf("\nMédia aritmética de ECTS por semestre letivo: %d\n", total_ects);
  menu_consultar_estatisticas(lista_alunos, alunos_count, lista_uc, uc_count, lista_avaliacoes, avaliacoes_count);
}

// #5 MENU GUARDAR E LER DE FICHEIROS BINÁRIOS OS DADOS DA APLICAÇÃO
int menu_ler_guardar_ficheiros(struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count, struct avaliacao_data lista_avaliacoes[], int avaliacoes_count)
{
  int option = 0;
  do
  {
    printf("\n① Guardar os dados da aplicação num ficheiro binário");
    printf("\n② Ler os dados da aplicação de um ficheiro binário\n");
    printf("\n");
    printf("Ⓞ - Sair\n");
    option = ler_numero("Escolhe uma opção: ", 0, 2);

  } while (option < 0 || option > 2);

  return option;
}

void menu_ler_ficheiro(struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count, struct avaliacao_data lista_avaliacoes[], int avaliacoes_count)
{
  FILE *ficheiro;
  ficheiro = fopen("app_data.bin", "rb");
  if (ficheiro == NULL)
  {
    mostrar_erro("Não foi possível abrir o ficheiro!\n");
  }
  else
  {
    fread(&alunos_count, sizeof(int), 1, ficheiro);
    fread(&uc_count, sizeof(int), 1, ficheiro);
    fread(&avaliacoes_count, sizeof(int), 1, ficheiro);
    fread(lista_alunos, sizeof(struct estudante_data), alunos_count, ficheiro);
    fread(lista_uc, sizeof(struct unidade_curricular), uc_count, ficheiro);
    fread(lista_avaliacoes, sizeof(struct avaliacao_data), avaliacoes_count, ficheiro);
    fclose(ficheiro);

    printf("\nDados lidos com sucesso!\n");
  }
}

void menu_guardar_ficheiro(struct estudante_data lista_alunos[], int alunos_count, struct unidade_curricular lista_uc[], int uc_count, struct avaliacao_data lista_avaliacoes[], int avaliacoes_count)
{
  FILE *ficheiro;
  ficheiro = fopen("app_data.bin", "wb");
  if (ficheiro == NULL)
  {
    mostrar_erro("Não foi possível abrir o ficheiro!\n");
    return;
  }
  fwrite(&alunos_count, sizeof(int), 1, ficheiro);
  fwrite(&uc_count, sizeof(int), 1, ficheiro);
  fwrite(&avaliacoes_count, sizeof(int), 1, ficheiro);
  fwrite(lista_alunos, sizeof(struct estudante_data), alunos_count, ficheiro);
  fwrite(lista_uc, sizeof(struct unidade_curricular), uc_count, ficheiro);
  fwrite(lista_avaliacoes, sizeof(struct avaliacao_data), avaliacoes_count, ficheiro);
  fclose(ficheiro);

  printf("\nDados guardados com sucesso!\n");
}

//entrega 2

void menu_calcular_avaliados(struct avaliacao_data lista_avaliacoes[], struct unidade_curricular lista_uc[], int avaliacoes_count, int uc_count) {

  int uc_codigo = 0, total_avaliados = 0;

  do
  {
    uc_codigo = ler_numero("(-) Código da UC: ", 1, MAX_ACCEPTABLE_NUMBER);

  } while (check_numero_uc(lista_uc, uc_count, uc_codigo) == -1);

  total_avaliados = calcular_avaliados(lista_avaliacoes, uc_codigo, avaliacoes_count);
  printf("Numero total de alunos avaliados: %d.", total_avaliados);

}



void menu_calcular_nao_avaliados(struct avaliacao_data lista_avaliacoes[], struct unidade_curricular lista_uc[], int avaliacoes_count, int uc_count) {

  int uc_codigo = 0, total_nao_avaliados = 0;

  do
  {
    uc_codigo = ler_numero("(-) Código da UC: ", 1, MAX_ACCEPTABLE_NUMBER);

  } while (check_numero_uc(lista_uc, uc_count, uc_codigo) == -1);

  total_nao_avaliados = calcular_nao_avaliados(lista_avaliacoes, uc_codigo, avaliacoes_count);
  printf("Numero total de alunos nao avaliados: %d.", total_nao_avaliados);

}
// -------------------------------------------------- FUNÇÕES AUXILIARES --------------------------------------------------

//entrega 2
int calcular_avaliados(struct avaliacao_data lista_avaliacoes[], int uc, int avaliacoes_count) {

    int total_avaliados = 0;

    for(int i = 0; i < avaliacoes_count; i++) {
        if(lista_avaliacoes[i].avaliado == 1) {
            total_avaliados ++;
        }
    }

    return total_avaliados;

}

int calcular_nao_avaliados(struct avaliacao_data lista_avaliacoes[], int uc, int avaliacoes_count) {

    int total_avaliados = 0;
    for(int i = 0; i < avaliacoes_count; i++) {
        if(lista_avaliacoes[i].avaliado != 1 && lista_avaliacoes[i].uc_id == uc) {
            total_avaliados ++;
        }
    }

    return total_avaliados;

}

int get_uc_id(struct unidade_curricular lista_uc[], int uc_count)
{
  int uc_id = 0, uc_db_id = -1;
  do
  {
    uc_id = ler_numero("Indique o código da unidade curricular (0 = sair): ", -1, MAX_ACCEPTABLE_NUMBER);

    if (uc_id == 0)
    {
      menu_registar_consultar_uc(lista_uc, uc_count);
    }
    else
      uc_db_id = check_numero_uc(lista_uc, uc_count, uc_id);

    if (uc_db_id <= -1)
      mostrar_erro("A unidade curricular não existe!\n");

  } while (uc_db_id <= -1);

  return uc_db_id;
}

int get_aluno_db_id(struct estudante_data lista_alunos[], int alunos_count)
{
  int aluno_id = 0, aluno_db_id = -1;
  do
  {
    printf("Indique o número de aluno (total alunos %d): ", alunos_count);
    scanf("%d", &aluno_id);

    aluno_db_id = check_numero_aluno(lista_alunos, alunos_count, aluno_id);
    if (aluno_db_id <= -1)
      mostrar_erro("O aluno não existe!\n");
  } while (aluno_db_id <= -1);
  return aluno_db_id;
}

void get_avaliacao_type(int tipo, char result[])
{
  const char *avaliacao_type[3] = {
      "Avaliação Final Semestre",
      "Recurso",
      "Especial"};
  strcpy(result, avaliacao_type[tipo - 1]);
  result[MAX_ACCEPTABLE_STRING - 1] = '\0';
}

//entrega 2
void is_aluno_avaliado(int tipo, char result[])
{
  const char *avaliacao_type[3] = {
      "Avaliado",
      "Faltou",
      "Desitiu"};
  strcpy(result, avaliacao_type[tipo - 1]);
  result[MAX_ACCEPTABLE_STRING - 1] = '\0';
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
    if (lista_alunos[i].nr_aluno == aluno_id)
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
    if (lista_uc[i].uc_codigo == uc_id)
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
    fflush(stdin);
    fgets(string, max_length, stdin);
    string[strcspn(string, "\n")] = '\0';
  } while (!strlen(string) || strlen(string) > max_length);

  return string;
}

int ler_numero(char *prompt, int min_number, int max_number)
{
  int number = 0;

  do
  {
    fflush(stdin);
    printf("%s", prompt);
    scanf("%d", &number);

    if (number < min_number || number > max_number)
      mostrar_erro("Número inválido!\n");

  } while (number < min_number || number > max_number);

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

//entrega 2
char *check_concelho(char *concelho)
{
  do
  {
    ler_string("(-) Concelho: ", concelho, MAX_CONCELHO_LENGTH);

  } while (!is_valid_concelho(concelho));

  return concelho;
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

//entrega 2
int is_valid_concelho(char concelho[])
{
  int validConcelho = 0;
  if(strlen(concelho) || strlen(concelho) < MAX_CONCELHO_LENGTH) {
    validConcelho = 1;
  }
  else
    mostrar_erro("Concelho introduzido errado.");

  return validConcelho;
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
