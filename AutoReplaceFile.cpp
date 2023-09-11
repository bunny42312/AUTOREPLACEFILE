#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <conio.h>

void deleteAllFilesInDirectory(const char *directoryPath) {
    DIR *dir = opendir(directoryPath);

    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    char filePath[255];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            snprintf(filePath, sizeof(filePath), "%s\\%s", directoryPath, entry->d_name);

            if (remove(filePath) == 0) {
            } else {
                perror("Error deleting file");
            }
        }
    }

    closedir(dir);
}

int main() {
    DIR *package;
    struct dirent *entry;
    const char *appData = getenv("localappdata");

    // Welcome
    printf("\t - Welcome To Push File! -\n");
    printf("\t - Credit Discord Mxniny#3112 - \n\n\n");

    // Clear Console
    system("cls");
    char packagePath[255];
    snprintf(packagePath, sizeof(packagePath), "%s\\Packages", appData);

    package = opendir(packagePath);

    printf("\t - Welcome To Push File! -\n");
    printf("\t - Credit Discord Mxniny#3112 - \n\n\n");

    // Check if the Packages directory can be opened
    if (package == NULL) {
        printf("Can't Open Folder!\n");
        return 1;
    }

    // Open the ./autoexec directory
    DIR *autoexecDir = opendir("./autoexec");

    if (autoexecDir == NULL) {
        printf("Can't Open ./autoexec Folder!\n");
        closedir(package);
        return 1;
    }

    struct stat st;
    char autoexecPath[255];
    char destinationPath[255];
 char t[255];
    // Iterate over files in ./autoexec
    struct dirent *autoexecFile;
    while ((autoexecFile = readdir(autoexecDir)) != NULL) {
        snprintf(autoexecPath, sizeof(autoexecPath), "./autoexec/%s", autoexecFile->d_name);

        // Check if the entry is a regular file
        if (stat(autoexecPath, &st) == 0 && S_ISREG(st.st_mode)) {
            // Iterate over entries in the Packages directory
            rewinddir(package);
            while ((entry = readdir(package)) != NULL) {
                if (strstr(entry->d_name, "ROBLOXCORPORATION.ROBLOX") != NULL) {
                    // Create the destination path
                    snprintf(destinationPath, sizeof(destinationPath), "%s\\Packages\\%s\\AC\\autoexec\\%s",
                             appData, entry->d_name, autoexecFile->d_name);

                    // Delete existing file in destination
                    snprintf(t, sizeof(destinationPath), "%s\\Packages\\%s\\AC\\autoexec",
                             appData, entry->d_name);
                             
                    deleteAllFilesInDirectory(t);
                    
                    // Copy the file
                    int sourceFile = open(autoexecPath, O_RDONLY);
                    int destinationFile = open(destinationPath, O_WRONLY | O_CREAT, 0644);

                    char buffer[1024];
                    ssize_t bytesRead;

                    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer))) > 0) {
                        write(destinationFile, buffer, bytesRead);
                    }

                    close(sourceFile);
                    close(destinationFile);
                }
            }
        }
    }

    printf("Already Replaced All Files!");
    printf("\n\n\n\n-- Thanks for using --");

    // Close directories
    closedir(autoexecDir);
    closedir(package);

    getch();
    return 0;
}

