#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_DEFINITION_LENGTH 200
#define MAX_SYNONYMS 10
#define HASHMAP_SIZE 100

typedef struct Node {
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];
    char synonyms[MAX_SYNONYMS][MAX_WORD_LENGTH];
    struct Node *next;
} Node;

typedef struct HashMap {
    Node *table[HASHMAP_SIZE];
} HashMap;

unsigned int hash(const char *word) {
    unsigned int hash = 0;
    while (*word) {
        hash = (hash << 5) + *word++;
    }
    return hash % HASHMAP_SIZE;
}

HashMap* createHashMap() {
    HashMap *map = malloc(sizeof(HashMap));
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

void addWord(HashMap *map, const char *word, const char *definition, const char synonyms[MAX_SYNONYMS][MAX_WORD_LENGTH], int synonymCount) {
    unsigned int index = hash(word);
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->word, word);
    strcpy(newNode->definition, definition);
    for (int i = 0; i < synonymCount; i++) {
        strcpy(newNode->synonyms[i], synonyms[i]);
    }
    newNode->next = map->table[index];
    map->table[index] = newNode;
}

void removeWord(HashMap *map, const char *word) {
    unsigned int index = hash(word);
    Node *current = map->table[index];
    Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            if (prev == NULL) {
                map->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Word removed successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Word not found in dictionary.\n");
}

char* searchWord(HashMap *map, const char *word) {
    unsigned int index = hash(word);
    Node *current = map->table[index];

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return current->definition;
        }
        current = current->next;
    }
    return NULL;
}

void searchSynonyms(HashMap *map, const char *word) {
    unsigned int index = hash(word);
    Node *current = map->table[index];

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            printf("Synonyms: ");
            int found = 0;
            for (int i = 0; i < MAX_SYNONYMS && strlen(current->synonyms[i]) > 0; i++) {
                printf("%s ", current->synonyms[i]);
                found = 1;
            }
            if (!found) {
                printf("No synonyms found.");
            }
            printf("\n");
            return;
        }
        current = current->next;
    }
    printf("No synonyms found for the word.\n");
}

void saveToFile(HashMap *map, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < HASHMAP_SIZE; i++) {
        Node *current = map->table[i];
        while (current != NULL) {
            fprintf(fp, "%s:%s:", current->word, current->definition);
            for (int j = 0; j < MAX_SYNONYMS && strlen(current->synonyms[j]) > 0; j++) {
                fprintf(fp, "%s,", current->synonyms[j]);
            }
            fprintf(fp, "\n");
            current = current->next;
        }
    }
    fclose(fp);
}

void loadFromFile(HashMap *map, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No dictionary file found. Starting with an empty dictionary.\n");
        return;
    }

    char line[MAX_WORD_LENGTH + MAX_DEFINITION_LENGTH + 2 + (MAX_SYNONYMS * MAX_WORD_LENGTH)];
    while (fgets(line, sizeof(line), fp)) {
        char *word = strtok(line, ":");
        char *definition = strtok(NULL, ":");
        char *synonymStr = strtok(NULL, "\n");
        char synonyms[MAX_SYNONYMS][MAX_WORD_LENGTH] = {""};
        int synonymCount = 0;

        if (synonymStr) {
            char *synonym = strtok(synonymStr, ",");
            while (synonym && synonymCount < MAX_SYNONYMS) {
                strcpy(synonyms[synonymCount++], synonym);
                synonym = strtok(NULL, ",");
            }
        }

        if (word && definition) {
            addWord(map, word, definition, synonyms, synonymCount);
        }
    }
    fclose(fp);
}

void freeHashMap(HashMap *map) {
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        Node *current = map->table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(map);
}

int main() {
    HashMap *dictionary = createHashMap();
    loadFromFile(dictionary, "dictionary.txt");
    while (1) {
        printf("\nWhat would you like to do?\n");
        printf("1. Add word\n");
        printf("2. Remove word\n");
        printf("3. Search word\n");
        printf("4. Search synonyms\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        getchar(); // Consume newline

        if (choice == 1) {
            char word[MAX_WORD_LENGTH];
            char definition[MAX_DEFINITION_LENGTH];
            char synonyms[MAX_SYNONYMS][MAX_WORD_LENGTH];
            int synonymCount = 0;

            printf("Enter the word: ");
            fgets(word, sizeof(word), stdin);
            strtok(word, "\n"); // Remove newline
            printf("Enter the definition: ");
            fgets(definition, sizeof(definition), stdin);
            strtok(definition, "\n"); // Remove newline

            printf("Enter number of synonyms: ");
            scanf("%d", &synonymCount);
            getchar(); // Consume newline

            for (int i = 0; i < synonymCount; i++) {
                printf("Enter synonym %d: ", i + 1);
                fgets(synonyms[i], sizeof(synonyms[i]), stdin);
                strtok(synonyms[i], "\n"); // Remove newline
            }

            addWord(dictionary, word, definition, synonyms, synonymCount);
            saveToFile(dictionary, "dictionary.txt");
            printf("Word added successfully.\n");
        } else if (choice == 2) {
            char word[MAX_WORD_LENGTH];
            printf("Enter the word to remove: ");
            fgets(word, sizeof(word), stdin);
            strtok(word, "\n"); // Remove newline
            removeWord(dictionary, word);
            saveToFile(dictionary, "dictionary.txt");
            printf("Word removed successfully.\n");
        } else if (choice == 3) {
            char word[MAX_WORD_LENGTH];
            printf("Enter the word to search: ");
            fgets(word, sizeof(word), stdin);
            strtok(word, "\n"); // Remove newline
            char *definition = searchWord(dictionary, word);
            if (definition) {
                printf("Definition: %s\n", definition);
            } else {
                printf("Word not found.\n");
            }
        } else if (choice == 4) {
            char word[MAX_WORD_LENGTH];
            printf("Enter the word to search synonyms: ");
            fgets(word, sizeof(word), stdin);
            strtok(word, "\n"); // Remove newline
            searchSynonyms(dictionary, word);
        } else if (choice == 5) {
            saveToFile(dictionary, "dictionary.txt");
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }




    freeHashMap(dictionary);  
    return 0;
}
