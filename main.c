#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define FILENAME_SIZE 128

typedef struct {
    char filename[FILENAME_SIZE];
    int file_size;
} FileEntry;

FileEntry file_table[MAX_FILES]; // Array to store file data
int storage_space = 1000000;     // variablr to store partition storage default is set to this

// Function to calculate and display disk utilization
void showDiskUtilization() {
    int used_space = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        used_space += file_table[i].file_size;
    }
    printf("\nDisk Utilization: %d KB used. Remaining size is %d KB\n", used_space, storage_space);
}

// Function to display all existing files and their sizes
void showAllFiles() {
    printf("\nExisting Files:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table[i].file_size > 0) {
            printf("File: %s, Size: %d KB\n", file_table[i].filename, file_table[i].file_size);
        }
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

    for (int i = 0; i < MAX_FILES; i++) {
        if (file_table[i].file_size == 0) {
            strcpy(file_table[i].filename, filename);
            file_table[i].file_size = file_size;
            storage_space -= file_size;
            printf("\nFile '%s' created with size %d KB.\n", filename, file_size);
            return;
        }
    }

    printf("\nFile limit reached. Cannot create more files.\n");
}

// Function to delete a file
void deleteFile() {
    char filename[FILENAME_SIZE];
    printf("Enter the filename to delete: ");
    scanf("%s", filename);

    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(file_table[i].filename, filename) == 0) {
            storage_space += file_table[i].file_size;
            file_table[i].file_size = 0;
            strcpy(file_table[i].filename, "");
            printf("\nFile '%s' deleted.\n", filename);
            return;
        }
    }
    printf("\nFile '%s' not found. Deletion failed.\n", filename);
}

// Function to rename a file
void renameFile() {
    char old_filename[FILENAME_SIZE];
    char new_filename[FILENAME_SIZE];

    printf("\nEnter the current filename: ");
    scanf("%s", old_filename);

    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(file_table[i].filename, old_filename) == 0) {
            printf("\nEnter the new filename: ");
            scanf("%s", new_filename);
            if (strlen(new_filename) > FILENAME_SIZE) {
                printf("\nNew filename is too long. Maximum length is %d characters.\n", FILENAME_SIZE);
                return;
            }
            strcpy(file_table[i].filename, new_filename);
            printf("\nFile '%s' renamed to '%s'.\n", old_filename, new_filename);
            return;
        }
    }
    printf("\nFile '%s' not found. Renaming failed.\n", old_filename);
}

int main() {
    int choice;

    printf("\nWelcome to the File System..\n");

    printf("\nEnter the storage size to allocate for this partition in KBs: ");
    scanf("%d", &storage_space);

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
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }
}
