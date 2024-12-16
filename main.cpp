#include <cstdio>
#include <cstdlib>
#include <cstring>


typedef struct File {
    char name[50];
    char *content;
    struct File *next;
} File;

File *head = nullptr;


void create_file() {
    char name[50];
    char content[1024];

    printf("Digite o nome do arquivo: ");
    scanf("%s", name);


    File *temp = head;
    while (temp != nullptr) {
        if (strcmp(temp->name, name) == 0) {
            printf("Erro: O arquivo '%s' já existe.\n", name);
            return;
        }
        temp = temp->next;
    }

    printf("Digite o conteúdo do arquivo: ");
    scanf(" %[^\n]", content);


    File *new_file = static_cast<File *>(malloc(sizeof(File)));
    strcpy(new_file->name, name);
    new_file->content = static_cast<char *>(malloc(strlen(content) + 1));
    strcpy(new_file->content, content);
    new_file->next = head;

    head = new_file;
    printf("Arquivo '%s' criado com sucesso!\n", name);
}


void list_files() {
    if (head == nullptr) {
        printf("Nenhum arquivo encontrado.\n");
        return;
    }

    File *temp = head;
    printf("Arquivos disponíveis:\n");
    while (temp != nullptr) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
}


void read_file() {
    char name[50];
    printf("Digite o nome do arquivo para leitura: ");
    scanf("%s", name);

    File *temp = head;
    while (temp != nullptr) {
        if (strcmp(temp->name, name) == 0) {
            printf("Conteúdo do arquivo '%s':\n%s\n", name, temp->content);
            return;
        }
        temp = temp->next;
    }

    printf("Erro: O arquivo '%s' não foi encontrado.\n", name);
}


void write_file() {
    char name[50];

    printf("Digite o nome do arquivo para escrita: ");
    scanf("%s", name);

    File *temp = head;
    while (temp != nullptr) {
        if (strcmp(temp->name, name) == 0) {
            char new_content[1024];
            printf("Digite o novo conteúdo do arquivo: ");
            scanf(" %[^\n]", new_content);

            free(temp->content);
            temp->content = static_cast<char *>(malloc(strlen(new_content) + 1));
            strcpy(temp->content, new_content);

            printf("Conteúdo do arquivo '%s' atualizado com sucesso!\n", name);
            return;
        }
        temp = temp->next;
    }

    printf("Erro: O arquivo '%s' não foi encontrado.\n", name);
}


void delete_file() {
    char name[50];
    printf("Digite o nome do arquivo para exclusão: ");
    scanf("%s", name);

    File *temp = head, *prev = nullptr;

    while (temp != nullptr) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            free(temp->content);
            free(temp);

            printf("Arquivo '%s' excluído com sucesso!\n", name);
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Erro: O arquivo '%s' não foi encontrado.\n", name);
}


void display_menu() {
    printf("\n=== Simulador de Sistema de Arquivos ===\n");
    printf("1. Criar arquivo\n");
    printf("2. Listar arquivos\n");
    printf("3. Ler arquivo\n");
    printf("4. Escrever em arquivo\n");
    printf("5. Excluir arquivo\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int choice;

    while (true) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                list_files();
                break;
            case 3:
                read_file();
                break;
            case 4:
                write_file();
                break;
            case 5:
                delete_file();
                break;
            case 6:
                printf("Encerrando o simulador.\n");
                return 0;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}
