#include <stdio.h>
#include <string.h> // Para strlen, strcpy, strcmp

// --- DECLARACAO DE FUNCOES (adicione a nova funcao aqui) ---
void adicionarTarefa(char a[10][3][50], char b[3][50]);
void listar(char a[10][3][50]);
void editarTarefa(char a[10][3][50]);
void excluirTarefa(char a[10][3][50]); // <-- Nova função

// --- INT MAIN (continua o mesmo, mas precisará adicionar a opção) ---
int main()
{
    char m[10][3][50], v[3][50], str[] = " - ";
    int swt, c, l, q;

    // Inicializa a matriz 'm' com " - "
    for(l=0; l<10; l++)
    {
        for(c=0; c<3; c++)
        {
            strcpy(m[l][c], str);
        }
    }

    printf("Sistema de Gerenciamento de Tarefas\n");

    // Loop principal do menu
    do
    {
        printf("\nOpcoes:\n");
        printf("1 - Adicionar Tarefa\n");
        printf("2 - Listar Tarefas\n");
        printf("3 - Editar Tarefa\n");
        printf("4 - Excluir Tarefa\n"); // <-- Nova opção
        printf("6 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &swt);
        while ((q = getchar()) != '\n' && q != EOF); // Limpa o buffer de entrada

        switch(swt)
        {
            case 1:
                adicionarTarefa(m, v);
                break;
            case 2:
                listar(m);
                break;
            case 3:
                editarTarefa(m);
                break;
            case 4: // Novo case para excluir
                excluirTarefa(m);
                break;
            case 6:
                printf("Saindo do sistema. Ate mais!\n");
                break;
            default:
                printf("Escolha Invalida. Por favor, tente novamente.\n");
                break;
        }
    } while(swt != 6);

    return 0;
}

// --- FUNCOES (adicionarTarefas e listar continuam as mesmas da resposta anterior) ---

void adicionarTarefa(char a[10][3][50], char b[3][50])
{
    int i, j;
    int tarefaAdicionada = 0;

    for(i=0; i<3; i++)
    {
        switch(i)
        {
            case 0: printf("Tarefa: "); break;
            case 1: printf("Prioridade: "); break;
            case 2: printf("Status: "); break;
        }
        fgets(b[i], 50, stdin);
        if (strlen(b[i]) > 0 && b[i][strlen(b[i]) - 1] == '\n') {
            b[i][strlen(b[i]) - 1] = '\0';
        }
    }

    for(i=0; i<10; i++)
    {
        if (strcmp(a[i][0], " - ") == 0)
        {
            for(j=0; j<3; j++)
            {
                strcpy(a[i][j], b[j]);
            }
            tarefaAdicionada = 1;
            break;
        }
    }

    if (tarefaAdicionada) {
        printf("Tarefa Adicionada com sucesso!\n");
    } else {
        printf("A lista de tarefas esta cheia! Nao foi possivel adicionar.\n");
    }
}

void listar(char a[10][3][50])
{
    int i;
    int contador_tarefas = 0;

    printf("\n--- LISTA DE TAREFAS ---\n");
    printf("No. | Tarefa (Titulo)           | Prioridade      | Status        \n");
    printf("----|---------------------------|-----------------|---------------\n");

    for(i=0; i<10; i++)
    {
        if (strcmp(a[i][0], " - ") != 0)
        {
            printf("%-3d | %-25s | %-15s | %-13s \n", i + 1, a[i][0], a[i][1], a[i][2]);
            contador_tarefas++;
        }
    }
    if (contador_tarefas == 0) {
        printf("Nenhuma tarefa cadastrada ainda.\n");
    }
    printf("------------------------------------------------------------------\n");
}

void editarTarefa(char a[10][3][50])
{
    int numeroTarefa;
    int opcaoCampo;
    char novoValor[50];

    listar(a);

    printf("\n--- EDITAR TAREFA ---\n");
    printf("Digite o numero da tarefa que deseja editar (0 para cancelar): ");
    scanf("%d", &numeroTarefa);
    while (getchar() != '\n' && getchar() != EOF);

    if (numeroTarefa == 0) {
        printf("Edicao cancelada.\n");
        return;
    }

    int indiceTarefa = numeroTarefa - 1;

    if (indiceTarefa < 0 || indiceTarefa >= 10 || strcmp(a[indiceTarefa][0], " - ") == 0)
    {
        printf("Numero de tarefa invalido ou tarefa nao existente.\n");
        return;
    }

    printf("\nTarefa selecionada para edicao (No. %d):\n", numeroTarefa);
    printf("Titulo: %s\n", a[indiceTarefa][0]);
    printf("Prioridade: %s\n", a[indiceTarefa][1]);
    printf("Status: %s\n", a[indiceTarefa][2]);

    printf("\nQual campo deseja editar?\n");
    printf("1 - Titulo\n");
    printf("2 - Prioridade\n");
    printf("3 - Status\n");
    printf("0 - Cancelar edicao do campo\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcaoCampo);
    while (getchar() != '\n' && getchar() != EOF);

    if (opcaoCampo == 0) {
        printf("Edicao de campo cancelada.\n");
        return;
    }

    if (opcaoCampo < 1 || opcaoCampo > 3) {
        printf("Opcao de campo invalida.\n");
        return;
    }

    printf("Digite o novo valor para ");
    switch(opcaoCampo) {
        case 1: printf("Titulo: "); break;
        case 2: printf("Prioridade: "); break;
        case 3: printf("Status: "); break;
    }
    fgets(novoValor, 50, stdin);
    if (strlen(novoValor) > 0 && novoValor[strlen(novoValor) - 1] == '\n') {
        novoValor[strlen(novoValor) - 1] = '\0';
    }

    strcpy(a[indiceTarefa][opcaoCampo - 1], novoValor);

    printf("Tarefa editada com sucesso!\n");
}

// --- NOVA FUNÇÃO: EXCLUIR TAREFA ---
void excluirTarefa(char a[10][3][50])
{
    int numeroTarefa;
    int i, j;
    char str_vazio[] = " - "; // String para marcar como vazio

    listar(a); // Primeiro, lista as tarefas para o usuário saber qual excluir

    printf("\n--- EXCLUIR TAREFA ---\n");
    printf("Digite o numero da tarefa que deseja excluir (0 para cancelar): ");
    scanf("%d", &numeroTarefa);
    while (getchar() != '\n' && getchar() != EOF); // Limpa o buffer

    if (numeroTarefa == 0) {
        printf("Exclusao cancelada.\n");
        return; // Sai da função
    }

    // Ajusta o número da tarefa para o índice do array (ex: 1 -> 0, 2 -> 1)
    int indiceExcluir = numeroTarefa - 1;

    // Valida o índice da tarefa
    if (indiceExcluir < 0 || indiceExcluir >= 10 || strcmp(a[indiceExcluir][0], " - ") == 0)
    {
        printf("Numero de tarefa invalido ou tarefa nao existente.\n");
        return;
    }

    // Confirmacao (boa prática antes de excluir dados)
    printf("Tem certeza que deseja excluir a tarefa '%s'? (S/N): ", a[indiceExcluir][0]);
    char confirmacao;
    scanf(" %c", &confirmacao); // O espaço antes de %c ignora whitespaces, incluindo o \n anterior
    while (getchar() != '\n' && getchar() != EOF); // Limpa o buffer

    if (confirmacao == 'S' || confirmacao == 's') {
        // Mover as tarefas seguintes uma posição para cima
        // Isso preenche o "buraco" deixado pela tarefa excluída
        for (i = indiceExcluir; i < 9; i++) // Vai até o penúltimo elemento (índice 8)
        {
            for (j = 0; j < 3; j++)
            {
                // Copia a tarefa da linha 'i+1' para a linha 'i'
                strcpy(a[i][j], a[i+1][j]);
            }
        }

        // A última linha (índice 9) agora pode conter uma cópia duplicada
        // ou o valor original se a penúltima linha foi a excluída.
        // Precisamos marcá-la como vazia.
        for (j = 0; j < 3; j++)
        {
            strcpy(a[9][j], str_vazio); // Marca a última linha como vazia
        }

        printf("Tarefa excluida com sucesso!\n");
    } else {
        printf("Exclusao cancelada.\n");
    }
}
