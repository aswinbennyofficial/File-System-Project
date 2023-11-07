#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_SIZE 128

typedef struct FileEntry {
    char* filename;
    int file_size;
    struct FileEntry* next;
} FileEntry;

FileEntry* file_table = NULL;
int storage_space;     // variable to store partition storage default is set to this
int partition_size; // used to store the size of partition

// Function to calculate and display disk utilization
void showDiskUtilization() {
    int used_space = 0;
    FileEntry* current = file_table;

    while (current != NULL) {
        used_space += current->file_size;
        current = current->next;
    }

    printf("\nDisk Utilization: %d KB used out of %d KB. Remaining size is %d KB\n", used_space, partition_size, storage_space);
}

// Function to display all existing files and their sizes
void showAllFiles() {
    printf("\nExisting Files:\n");
    FileEntry* current = file_table;

    while (current != NULL) {
        printf("File: %s, Size: %d KB\n", current->filename, current->file_size);
        current = current->next;
    }
}

// Function to create a new file
void createFile() {
    char filename[FILENAME_SIZE];
    int file_size;

    printf("\nEnter the filename: ");
    scanf("%s", filename);

    if (strlen(filename) > FILENAME_SIZE) {
        printf("\nFilename is too long. Maximum length is %d characters.\n", FILENAME_SIZE);
        return;
    }

    printf("\nEnter the file size (KB): ");
    scanf("%d", &file_size);

    if (file_size <= 0) {
        printf("\nInvalid file size. Please enter a positive value.\n");
        return;
    }

    if (storage_space - file_size < 0) {
        printf("\nNot enough space to create the file.\n");
        return;
    }

    FileEntry* new_entry = (FileEntry*)malloc(sizeof(FileEntry));
    new_entry->filename = strdup(filename); //makes a new dynamically allocated string taht is copy of filename
    new_entry->file_size = file_size;
    new_entry->next = NULL;

    if (file_table == NULL) {
        file_table = new_entry;
    } else {
        FileEntry* current = file_table;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_entry;
    }

    storage_space -= file_size;
    printf("\nFile '%s' created with size %d KB.\n", filename, file_size);
}

// Function to delete a file
void deleteFile() {
    char filename[FILENAME_SIZE];
    printf("Enter the filename to delete: ");
    scanf("%s", filename);

    FileEntry* current = file_table;
    FileEntry* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->filename, filename) == 0) {
            storage_space += current->file_size;

            if (prev == NULL) {
                // If the first entry is to be deleted
                file_table = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->filename);
            free(current);
            printf("\nFile '%s' deleted.\n", filename);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("\nFile '%s' not found. Deletion failed.\n", filename);
}

// Function to rename a file
void renameFile() {
    char old_filename[FILENAME_SIZE];
    char new_filename[FILENAME_SIZE];

    printf("\nEnter the current filename: ");
    scanf("%s", old_filename);

    FileEntry* current = file_table;

    while (current != NULL) {
        if (strcmp(current->filename, old_filename) == 0) {
            printf("\nEnter the new filename: ");
            scanf("%s", new_filename);

            if (strlen(new_filename) > FILENAME_SIZE) {
                printf("\nNew filename is too long. Maximum length is %d characters.\n", FILENAME_SIZE);
                return;
            }

            free(current->filename);
            current->filename = strdup(new_filename); //strdup dynamically allocates memmory of string with copy of file name
            printf("\nFile '%s' renamed to '%s'.\n", old_filename, new_filename);
            return;
        }

        current = current->next;
    }

    printf("\nFile '%s' not found. Renaming failed.\n", old_filename);
}

int main() {
    int choice;

    printf("\nWelcome to the File System..\n");

    printf("\nEnter the storage size to allocate for this partition in KBs: ");
    scanf("%d", &partition_size);
    storage_space = partition_size;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Show Disk Utilization\n");
        printf("4. Show All Files\n");
        printf("5. Rename File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                deleteFile();
                break;
            case 3:
                showDiskUtilization();
                break;
            case 4:
                showAllFiles();
                break;
            case 5:
                renameFile();
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice..\n");
        }
    }


    return 0;
}
