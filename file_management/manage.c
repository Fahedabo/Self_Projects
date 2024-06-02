#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_USERID_LENGTH 100

bool isUserExist(const char* filename, const char* userId) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }
    
    char line[MAX_USERID_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, userId) == 0) {
            fclose(file);
            return true;
        }
    }
    
    fclose(file);
    return false;
}

int countElements(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }
    
    int count = 0;
    char line[MAX_USERID_LENGTH];
    while (fgets(line, sizeof(line), file))
        count++;
    
    fclose(file);
    return count;
}

void addUser(const char* filename, const char* userId) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    if(isUserExist(filename, userId)){
        printf("User already exsists.\n");
        return;
    }
    
    fprintf(file, "%s\n", userId);
    fclose(file);
    printf("User added successfully.\n");
}

void deleteUser(const char* filename, const char* userId) {
    if(!isUserExist(filename, userId)){
         printf("user not in the file.\n");
        return;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }
    
    char line[MAX_USERID_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, userId) != 0)
            fputs(line, temp);
    }
    
    fclose(file);
    fclose(temp);
    
    if (remove(filename) != 0) {
        printf("Error deleting file.\n");
        return;
    }
    
    if (rename("temp.txt", filename) != 0)
        printf("Error renaming file.\n");
    else
        printf("User deleted successfully.\n");
}

int main() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the file name: ");
    scanf("%s", filename);
    
    while (true) {
        printf("\n--- Menu ---\n");
        printf("1. Add User\n");
        printf("2. Delete User\n");
        printf("3. Count Elements\n");
        printf("4. Check User Existence\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the User ID to add: ");
                char userId[MAX_USERID_LENGTH];
                scanf("%s", userId);
                addUser(filename, userId);
                break;
                
            case 2:
                printf("Enter the User ID to delete: ");
                char deleteUserId[MAX_USERID_LENGTH];
                scanf("%s", deleteUserId);
                deleteUser(filename, deleteUserId);
                break;
                
            case 3:
                printf("Number of elements: %d\n", countElements(filename));
                break;
                
            case 4:
                printf("Enter the User ID to check: ");
                char checkUserId[MAX_USERID_LENGTH];
                scanf("%s", checkUserId);
                bool exists = isUserExist(filename, checkUserId);
                if (exists)
                    printf("User exists in the file.\n");
                else
                    printf("User does not exist in the file.\n");
                break;
                
            case 5:
                printf("Exiting the program.\n");
                return 0;
                
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}
