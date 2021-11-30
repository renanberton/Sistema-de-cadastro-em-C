#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

#define true 1
#define false 0
#define ERRO exit(1)

// Comorbidades.
// { "Obesidade", "Hipertensao", "Diabetes", "Tuberculose", "Cardiopatias", "Doencas respiratorias" }
// Obesidade Hipertensao Diabetes Tuberculose Cardiopatias Doencas respiratorias

typedef struct pacienteDados
{
    char nome[800];
    char endereco[800];
    char numResidencia[6];
    char cidade[800];
    char bairro[800];
    char estado[800];
    char cep[10];
    char email[800];
    char cpf[12];
    char telefone[12];
    char data_nasc[12];
    char data_diag[9];
    char comorbidade[1024];
    int *comorb;

} PacienteDados;

typedef struct loginStruct
{
    char login[5];
    char senha[5];

} login[1];

char *concat(char *text, char *text2)
{
    /*
     * Função para concatenar Chars/Strings.
    */

    char *result = malloc(strlen(text) + strlen(text2) + 1); // Reserva memoria para o tamanho dos textos.

    strcpy(result, text);  // Copia o primeiro texto para a variavel { result }.
    strcat(result, text2); // concatena o segundo texto na variavel  { result }.

    return result; // retorna o texto concatenado.
}

int isChar(char *c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isDigit(char *c)
{
    if ((c >= '0' && c <= '9'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int calcIdade(char dataNasc[8], int anoAtual)
{
    int idade;
    int dataInt;
    int dataNascLen = sizeof(dataNasc);
    char anoBuf[5];

    anoBuf[0] = dataNasc[4];
    anoBuf[1] = dataNasc[5];
    anoBuf[2] = dataNasc[6];
    anoBuf[3] = dataNasc[7];

    dataInt = atoi(anoBuf);
    idade = anoAtual - dataInt;
    return idade;
}

int isValidEmail(char *email)
{
    if (!isChar(email[0]))
    {
        return 0;
    }
    int At = -1, Dot = -1;

    for (int i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            At = i;
        }
        else if (email[i] == '.')
        {
            Dot = i;
        }
    }

    if (At == -1 || Dot == -1)
    {
        return 0;
    }

    if (At > Dot)
    {
        return 0;
    }

    return !(Dot >= (strlen(email) - 1));
}

int checkRisco(char *filename)
{
    FILE *fp;
    filename = concat("./Grupo_de_risco/", filename);
    filename = concat(filename, ".txt");

    fp = fopen(filename, "r");
    if (fp)
    {
        fclose(fp);
        return 1;
    }
    else
    {
        fclose(fp);
        return 0;
    }
}

void grupoDeRisco(char *cep, char ano_nasc[8], int comorbidade)
{
    char *dadosrisco, bufIdade[5];
    int idade;
    int anoAtual = 2021;

    idade = calcIdade(ano_nasc, anoAtual);

    itoa(idade, bufIdade, 10);
    // Junta os dados do usuário em uma string.
    fflush(stdin);
    dadosrisco = concat("CEP: ", concat(cep, "\n"));
    dadosrisco = concat(concat(dadosrisco, concat("Idade: ", bufIdade)), "\n\n");

    if (idade >= 65 || comorbidade == 1) // Verfica se o paciente tem +65 ou se comorbidade e 1.
    {
        if (checkRisco(cep))
        {
            FILE *arquivo;
            arquivo = fopen(concat("./Grupo_de_risco/", concat(cep, ".txt")), "a");
            fwrite(dadosrisco, 6, sizeof(dadosrisco), arquivo);
            fputs("\n", arquivo);
            fputs("\n", arquivo);
            fclose(arquivo);
        }

        else
        {
            createFile(cep, dadosrisco, ".txt", "Grupo_de_risco");
        }
    }
    else
    {
    }
}

void menu()
{
    /* Tela de menu */

    int opcao;
    char *op;

    while (1)
    {
        fflush(stdin); // Salva itens que não foram salvo em uma memoria temporaria.
        printf(" ====== Sistema de Cadastro - COVID-19 ====== \n\n");
        printf("(1) - Cadastro de Pacientes\n");
        printf("(2) - Procurar Pacientes\n");
        printf("(3) - Alterar Pacientes\n");
        printf("(4) - Excluir Pacientes\n");
        printf("(5) - Sair do Sistema\n\n");
        printf("Escolha a opcao desejada: \n");
        printf("[?]: ");
        scanf("%d", &opcao);
        printf("\n");

        if (opcao == 1)
        {
            system("cls");
            cadastro();
        }
        else if (opcao == 2)
        {
            system("cls");
            consulta();
        }
        else if (opcao == 3)
        {

            alterar();
        }
        else if (opcao == 4)
        {
            excluir();
        }
        else if (opcao == 5)
        {
            exit(0); // Sair do programa.
        }

        system("cls");
    }
}

void loguin()
{
    char usuario[15];  // Variável para guarda o nome do usuário.
    char password[12]; // Variável para guarda a senha do usuário.

    printf("---------------------------\n");
    printf("     L  O  G  -  I   N      \n");
    printf("---------------------------\n\n\n");
    system("pause");
    system("cls");

    printf("Digite o usuario: \n");
    scanf("%[^\n]%*c", &usuario);
    printf("\n");

    printf("Enter your password: \n");
    scanf("%[^\n]%*c", &password);
    printf("\n");

    if (strcmp(usuario, "admin") == 0) // Verifica se o usuario é igual "admin".
    {
        if (strcmp(password, "123") == 0) // Verifica se a senha é igual "123".
        {
            system("cls");
            printf("Log-in efetuado com sucesso.\n");
            printf("Seja bem-vindo. \n\n\n");
            system("pause");
            system("cls");
            menu();
        }
        else
        {
            system("cls");
            printf("Senha incorreta. \n");
            printf("Verifique os dados e tente novamente. \n\n");
            system("pause");
            system("cls");
            loguin();
        }
    }
    else
    {
        system("cls");
        printf("Usuario e/ou senha incorretos.\n");
        printf("Verifique os dados e tente novamente. \n\n");
        system("pause");
        system("cls");
        loguin();
    }
}

void cadastro()
{
    int op; //Armazena a escolha do usuário.
    int comorbidade;
    char dados[30]; //Quarda os dados do usuário.
    char risco[5];  //Guarda os dados do grupo de risco.

    PacienteDados paciente;

    while (1)
    {
        /* Pega os dados do paciente. */
        while (1)
        {
            printf("Digite o nome do paciente: ");
            scanf(" %[^\n]s", paciente.nome);
            printf("\n");

            if (checkFileExist(paciente.nome, "Pacientes"))
            {
                fprintf(stderr, "ERRO: O paciente ja foi cadastrado.\n\n");
            }
            else
            {
                break;
            }
        }

        printf("Digite o rua do paciente: ");
        scanf(" %[^\n]s", paciente.endereco);
        printf("\n");

        while (1)
        {
            printf("Digite o numero da residencia do paciente: ");
            scanf(" %[^\n]s", paciente.numResidencia);
            printf("\n");

            if (!atoi(paciente.numResidencia))
            {
                fprintf(stderr, "ERRO: Coloque apenas numeros.\n\n");
            }
            else if (paciente.numResidencia[0] == "-")
            {
                fprintf(stderr, "ERRO: Coloque numero positivos.\n\n");
            }
            else if (strlen(paciente.numResidencia) > 5)
            {
                fprintf(stderr, "ERRO: Numero longo, coloque ate 4 digitos.\n\n");
            }
            else
            {
                break;
            }
        }

        printf("Digite a cidade do paciente: ");
        scanf(" %[^\n]s", paciente.cidade);
        printf("\n");

        printf("Digite o bairro do paciente: ");
        scanf(" %[^\n]s", paciente.bairro);
        printf("\n");

        printf("Digite o estado do paciente: ");
        scanf(" %[^\n]s", paciente.estado);
        printf("\n");

        while (1)
        {
            printf("Digite o CEP do paciente: \n");
            printf("Somente numeros, sem // ou .. \n");
            scanf(" %[^\n]s", paciente.cep);
            printf("\n");

            if (!atoi(paciente.cep))
            {
                fprintf(stderr, "ERRO: Coloque apenas numeros.\n\n");
            }
            else if (atoi(paciente.cep) == 0 || atoi(paciente.cep) < 0)
            {
                fprintf(stderr, "ERRO: Coloque numero positivos.\n\n");
            }
            else if (strlen(paciente.cep) > 8 || strlen(paciente.cep) < 8)
            {
                fprintf(stderr, "ERRO: CEP invalido, coloque 8 digitos.\n\n");
            }
            else
            {
                break;
            }
        }

        while (1)
        {
            printf("Digite o email do paciente: ");
            scanf(" %[^\n]s", paciente.email);
            printf("\n");

            if (!isValidEmail(paciente.email))
            {
                fprintf(stderr, "ERRO: O email nao e valido.\n\n");
            }
            else
            {
                break;
            }
        }

        while (1)
        {
            printf("Digite o CPF do paciente: \n");
            printf("Somente numeros, sem // ou .. \n");
            scanf(" %[^\n]s", paciente.cpf);
            printf("\n");

            if (!atoi(paciente.cpf))
            {
                fprintf(stderr, "ERRO: Coloque apenas numeros.\n\n");
            }
            else if (strlen(paciente.cpf) > 11 || strlen(paciente.cpf) < 11)
            {
                fprintf(stderr, "ERRO: CPF nao e valido, coloque 11 digitos.\n\n");
            }
            else if (checkFileExist(paciente.cpf, "Pacientes"))
            {

                printf("Usuario ja cadastrado.\n");
                printf("Verifique o dado e tente novamente.\n\n\n");
            }

            else
            {
                break;
            }
        }

        while (1)
        {
            printf("Digite o Telefone ou numero de celular do paciente: ");
            printf("Somente numeros, sem espaços ou - \n");
            scanf(" %[^\n]s", paciente.telefone);
            printf("\n");

            if (!atoi(paciente.telefone))
            {
                fprintf(stderr, "ERRO: Coloque apenas numeros.\n\n");
            }
            else if (strlen(paciente.telefone) < 8 || strlen(paciente.telefone) > 11)
            {
                fprintf(stderr, "ERRO: Digite um numero de telefone ou celular valido.\n\n");
            }
            else
            {
                break;
            }
        }

        fflush(stdin);
        while (1)
        {
            printf("Digite a data nascimento do paciente: DDMMAAAA\n\n");
            printf("Somente numeros, sem // ou .. \n");
            scanf(" %[^\n]s", paciente.data_nasc);
            printf("\n");

            if (!atoi(paciente.data_nasc))
            {
                fprintf(stderr, "ERRO: Coloque apenas numeros.\n\n");
            }
            else if (strlen(paciente.data_nasc) > 8 || strlen(paciente.data_nasc) < 8)
            {
                fprintf(stderr, "ERRO: Data invalida, coloque 8 digitos.\n\n");
            }
            else
            {
                break;
            }
        }

        fflush(stdin);
        while (1)
        {
            printf("Digite a data do diagnostico do paciente: DDMMAAAA\n\n");
            printf("Somente numeros, sem // ou .. \n");
            scanf(" %[^\n]s", paciente.data_diag);
            printf("\n");

            if (!atoi(paciente.data_diag))
            {
                fprintf(stderr, "ERRO: Coloque apenas numeros.\n");
            }
            else if (strlen(paciente.data_diag) > 8 || strlen(paciente.data_diag) < 8)
            {
                fprintf(stderr, "ERRO: Data invalida, coloque 8 digitos.\n\n");
            }
            else
            {
                break;
            }
        }

        while (1)
        {
            printf("O paciente possui alguma comorbidade como:\n( Obesidade, Hipertensao, Diabetes, Tuberculose, Cardiopatias, Doencas respiratorias, entre outros? )\n\n");
            printf("[1] Sim\n");
            printf("[2] Nao\n");
            printf("[?] \n");

            fflush(stdin); // Limpa residuos do stdin
            scanf(" %d", &paciente.comorb);
            printf("\n");

            if (paciente.comorb == 1)
            {
                printf("Qual a comorbidade? : \n");
                scanf("  %[^\n]s", paciente.comorbidade);
            }
            system("cls");
            break;
        }

        // Guarda todas as informações do usuário dentro da variável { dados }.
        sprintf(dados, "Nome: %s\nEndereco: %s\nCidade: %s\nEstado: %s\nCep: %s\nE-mail: %s\nCPF: %s\nTelefone: %s\nData de nascimento: %s\nData de diagnostico: %s\nTipo de comorbidade: %s\n",
                paciente.nome, paciente.endereco, paciente.cidade, paciente.estado,
                paciente.cep, paciente.email, paciente.cpf, paciente.telefone,
                paciente.data_nasc, paciente.data_diag, paciente.comorbidade);

        fflush(stdin);
        createFile(paciente.cpf, dados, "", "Pacientes");

        fflush(stdin);
        grupoDeRisco(paciente.cep, paciente.data_nasc, paciente.comorb);

        printf("DADOS GRAVADOS COM SUCESSO!!!\n\n");
        printf("Deseja cadastrar outro paciente? [1]Sim ou [2]Nao\n");
        printf("[?]: ");
        scanf("%d", &op); // Recebe a escolha do usuário.

        if (op == 1) // Checa qual a opção que o usuário escolheu.
        {
            system("cls"); // Limpa a tela.
            cadastro();    // Chama a tela de cadastro.
        }
        else
        {
            system("cls"); // Limpa a tela.
            menu();        // Chama a tela de menu.
        }
    }
}

void excluir()
{
    int ret;
    FILE *fp;
    char *filename = "";
    char *cpf;
    int op;

    system("cls");
    printf("Digite o CPF que deseja deletar: \n");
    scanf("%s", cpf);

    system("cls");
    if (checkFileExist(cpf, "Pacientes") == true)
    {
        printf("Usuario %s encontrado. \n", cpf);
        printf("Tem certeza que deseja excluir? \n");
        printf("SIM [1]\n");
        printf("NAO [2]\n");
        scanf("%d", &op);

        if (op == 1)
        {
            filename = "./Pacientes/";
            filename = concat(filename, cpf); // ./Pacientes/22222222222;
            fp = fopen(filename, "r");

            fprintf(fp, "%s", "");
            fclose(fp);

            ret = remove(filename);

            if (ret == 0)
            {
                system("cls");
                printf("Cadastro deletado com sucesso.\n");
            }
        }
    }
    else
    {
        printf("Usuario nao cadastrado.\n\n");
        printf("Verifique o CPF informado e tente novamente. \n\n");
    }
    system("pause");
    system("cls");
    menu();
}

void alterar()
{
    int op;
    char *cpf;
    char *filename = "";
    FILE *fp;
    int ret;

    system("cls");
    printf("Digite o CPF do paciente que deseja alterar: \n");
    scanf(" %s", cpf);
    printf("%c", cpf);

    if (checkFileExist(cpf, "Pacientes"))
    {
        printf("Usuario %s encontrado \n", cpf);
        printf("Tem certeza que deseja alterar o usuario? \n");
        printf("SIM [1]\n");
        printf("NAO [2]\n");
        scanf("%d", &op);
        system("cls");

        if (op == 1)
        {
            filename = "./Pacientes/";
            filename = concat(filename, cpf); // ./Pacientes/22222222222;
            fp = fopen(filename, "r");

            fprintf(fp, "%s", "");
            fclose(fp);

            ret = remove(filename);
            cadastro();
        }
        else
        {
            menu();
        }
    }
    else
    {
        system("cls");
        printf("Usuario nao cadastrado. \n");
        printf("Verifique o CPF informado e tente novamente mais tarde.\n\n");
        system("pause");
        system("cls");
        menu();
    }
}

void consulta()
{
    /*
     * Função que verifica a existencia de um arquivo.
    */
    FILE *fp;
    int contador;
    char *filename, *folder;

    system("cls");
    printf("Digite o CPF do paciente que deseja consultar: \n\n");
    scanf(" %s", &filename);
    filename = concat(&filename, ""); // filename = "filename.txt";

    if (folder != "")
    {
        folder = concat(concat("./", "Pacientes"), "/"); // folder = "./folder/";
    }
    else
    {
        printf("Usuario nao encontrado.");
    }

    filename = concat("./Pacientes/", filename); // filename = "./folder/filename";

    system("cls");
    fp = fopen(filename, "r");
    if (fp) // Verifica se o programa abriu;
    {
        while ((contador = getc(fp)) != EOF)
        {
            putchar(contador);
        }
    }
    else
    {
        printf("Usuario nao cadastrado. \n");
        printf("Verifique o CPF informado e tente novamente.\n\n");
    }
    fclose(fp);
    system("pause");
}

int checkFileExist(char *filename, char *folder)
{
    /*
     * Função que verifica a existencia de um arquivo.
    */

    FILE *fp;

    if (folder != "")
    {
        folder = concat(concat("./", folder), "/"); // folder = "./folder/";
    }
    else
    {
        return false;
    }

    filename = concat(folder, filename); // filename = "./folder/filename.txt";

    fp = fopen(filename, "r");
    if (fp) // Verifica se o programa abriu;
    {
        fclose(fp);
        return true;
    }
    else
    {
        fclose(fp);
        return false;
    }
}

int checkFolderExist(char *dirname)
{
    /*
    * Função que verificar a existencia de um diretorio.
    */

    DIR *dir;

    dirname = concat(concat("./", dirname), "/"); // folder = "./folder/";

    dir = opendir(dirname);
    if (!dir)
    { // Verifica se o arquivo existe.
        return true;
    }
    else
    {
        return false;
    }
}

void createFile(char *filename, char *content, char *type, char *folder)
{
    /*
     * Cria arquivos dentro da pasta desejada.
     * Caso a pasta não exista ele cria.
     */

    FILE *fp; // Variavel para entrada de arquivo.

    filename = concat(filename, type);

    if (checkFileExist(filename, "Pacientes"))
    {
        fprintf(stderr, "ERRO: O arquivo %s ja existe.\n", filename);
        printf("Favor verificar os dados e tentar novamente. \n");
        system("pause");
        system("cls");
        menu();
    }

    if (folder != "")
    {
        folder = concat(concat("./", folder), "/"); // folder = "./folder/";
        filename = concat(folder, filename);        // filename = "./folder/filename.txt";

        if (checkFolderExist(folder)) // Checa se a pasta não existe.
        {
            mkdir(folder); // Cria uma pasta caso ela não exista.
        }
    }

    fp = fopen(filename, "w");  // Cria o arquivo.
    fprintf(fp, "%s", content); // Colocar o texto dentro do arquivo.
    fclose(fp);                 // Fechar o arquivo.
}

void *incTextInFile(char *filename, char *text, char *folder)
{
    /**
     *  Acrecenta texto no arquivo especificado.
    */

    FILE *fp; // Variavel para entrada de arquivo.
    DIR *dir; // Variavel para entrada de diretorios/pasta.

    if (folder != "")
    {
        folder = concat(concat("./", folder), "/"); // folder = "./folder/";
        filename = concat(folder, filename);        // filename = "./folder/filename";

        dir = opendir(folder); // Abri o diretorio.

        if (dir)
        { // Se conseguiu abrir o diretorio/pasta.
            if (fp = fopen(filename, "a"))
            {
                fputs(concat(text, "\n"), fp);
                fclose(fp);
            }
            else
            { // Se n�o conseguiu abrir o arquivo.
            }
        }
        else
        { // Se n�o conseguiu abrir o diretorio/pasta.
        }
    }
}

char *readFile(char *file, char *folder)
{
    /**
     * Faz leitura de um arquivo o retorna como texto.
    */

    FILE *fp;          // Ler a entrada de arquivo.
    DIR *dir;          // Ler a entrada do diretorio.
    char buffer[1024]; // Buffer para os caracteres.
    char *filename;

    folder = concat(concat("./", folder), "/"); // folder = "./folder/";
    filename = concat(file, ".txt");            // filename = "filename.txt";
    dir = opendir(folder);                      // Abri o diretorio/pasta.

    if (folder != "")
    {
        filename = concat(folder, filename); // filename = "./folder/filename.txt";

        if (dir)
        { // Se conseguiu abrir o diretorio/pasta.
            if (fp = fopen(filename, "r"))
            { // Se conseguiu abrir o arquivo.
                while (fscanf(fp, "%[^\n] ", buffer) != EOF)
                {                           // Loop que s� para quando chegar no fim do arquivo
                    printf("%s\n", buffer); // Imprime o texto do arquivo.
                }
                fclose(fp); // Fechar o arquivo.
            }
            else
            { // Se nao conseguir abrir o arquivo.
                return "FILE NOT FOUND.";
            }
        }
        else
        { // Se não conseguir abrir a o diretorio/pasta.
            return "FOLDER NOT FOUND.";
        }
    }
    else
    { // Se o parametro { folder } não for uma string vazia.
        if (fp = fopen(filename, "r"))
        { // Se conseguiu abrir o arquivo.
            while (fscanf(fp, "%[^\n]", buffer) != EOF)
            {                           // Loop que s� para no fim do arquivo.
                printf("%s\n", buffer); // imprime na tela o texto do arquivo.
            }
            fclose(fp); // fecha o arquivo.
        }
        else
        { // Se n�o conseguir abrir o diretorio/pasta.
            return "FILE NOT FOUND.";
        }
    }
}
