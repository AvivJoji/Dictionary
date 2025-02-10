#include <stdio.h>
#include <string.h>

#define MAX_WORDS 1000

// Structure to represent a word and its definition
struct WordDefinition {
    char word[50];
    char definition[100];
};

// Structure to represent the online dictionary
struct OnlineDictionary {
    struct WordDefinition words[MAX_WORDS];
    int wordCount;
};

// Function to add a word to the dictionary
void addWord(struct OnlineDictionary* dict, const char* word, const char* definition) {
    if (dict->wordCount < MAX_WORDS) {
        strcpy(dict->words[dict->wordCount].word, word);
        strcpy(dict->words[dict->wordCount].definition, definition);
        dict->wordCount++;

        // Sort the dictionary after adding a new word
        for (int i = 0; i < dict->wordCount - 1; i++) {
            for (int j = i + 1; j < dict->wordCount; j++) {
                if (strcmp(dict->words[i].word, dict->words[j].word) > 0) {
                    // Swap words
                    struct WordDefinition temp = dict->words[i];
                    dict->words[i] = dict->words[j];
                    dict->words[j] = temp;
                }
            }
        }

        printf("Word added to the dictionary and dictionary sorted.\n");
    } else {
        printf("Dictionary is full. Cannot add more words.\n");
    }
}

// Function to search for a word in the dictionary using binary search
const char* searchWord(const struct OnlineDictionary* dict, const char* word) {
    int low = 0;
    int high = dict->wordCount - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int comparison = strcmp(dict->words[mid].word, word);

        if (comparison == 0) {
            return dict->words[mid].definition; // Word found
        } else if (comparison < 0) {
            low = mid + 1; // Search in the right half
        } else {
            high = mid - 1; // Search in the left half
        }
    }

    return "Word not found in the dictionary.";
}

int main() {
    // Creating an online dictionary
    struct OnlineDictionary onlineDict;
    onlineDict.wordCount = 0;

    int option;
    char word[50];
    char definition[100];

    do {
        // Display menu options
        printf("\nOnline Dictionary Menu:\n");
        printf("1. Add Word\n");
        printf("2. Search Word\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                // Add Word
                printf("Enter word: ");
                scanf("%s", word);
                printf("Enter definition: ");
                getchar(); // Consume the newline character left in the input buffer
                fgets(definition, sizeof(definition), stdin);
                definition[strcspn(definition, "\n")] = '\0'; // Remove the trailing newline
                addWord(&onlineDict, word, definition);
                break;

            case 2:
                // Search Word
                printf("Enter word to search: ");
                scanf("%s", word);
                const char* result = searchWord(&onlineDict, word);
                printf("Definition of '%s': %s\n", word, result);
                break;

            case 3:
                // Exit
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid option. Please enter a valid option.\n");
        }

    } while (option != 3);

    return 0;
}
