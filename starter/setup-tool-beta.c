#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

#define PROGRAMS_PATH "/usr/bin/"

#define CONFIG_FILE "/etc/setup-tool-beta.conf"

int checkProgramExists(const char* programName) {
    char fullPath[100];
    sprintf(fullPath, "%s%s", PROGRAMS_PATH, programName);

    if (access(fullPath, F_OK) != -1) {
        return 1;  // Program exists
    } else {
        return 0;  // Program does not exist
    }
}

int shouldShowNotice() {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (file != NULL) {
        char line[50];
        if (fgets(line, sizeof(line), file) != NULL) {
            fclose(file);
            if (strstr(line, "tp-notice = ") != NULL) {
                char* response = strchr(line, '=') + 2;
                response[strcspn(response, "\n")] = '\0';  // Remove newline character
                if (strcasecmp(response, "True") == 0) {
                    return 1;  // Show the notice
                } else if (strcasecmp(response, "False") == 0) {
                    return 0;  // Don't show the notice
                }
            }
        }
    }
    return 1;  // Show the notice by default
}

void saveUserResponse(char response) {
    const char* configResponse = (response == 'Y' || response == 'y') ? "False" : "True";
    FILE *file = fopen(CONFIG_FILE, "w");
    if (file != NULL) {
        fprintf(file, "tp-notice = %s\n", configResponse);
        fclose(file);
    }
}

int main() {
    const char* programs[] = {"setup-tool-cli-beta", "setup-tool-tui-beta", "setup-tool-gui-beta"};
    int numPrograms = sizeof(programs) / sizeof(programs[0]);

    int installedPrograms[numPrograms];
    int numInstalledPrograms = 0;  // Track the number of installed programs

    for (int i = 0; i < numPrograms; i++) {
        installedPrograms[i] = checkProgramExists(programs[i]);
        if (installedPrograms[i]) {
            numInstalledPrograms++;
        }
    }

    if (numInstalledPrograms == 0) {
        printf("No installed programs found.\n");
        return 0;
    }

    if (shouldShowNotice()) {
        char confirm[2];
        int validInput = 0;

        while (!validInput) {
            printf("This program might pull software from third party repositories,\n");
            printf("if you enable these repositories through this program or through other means.\n");
            printf("Do you accept this? (Y/n): ");
            fgets(confirm, sizeof(confirm), stdin);
            if (confirm[0] == 'Y' || confirm[0] == 'y' || confirm[0] == '\n') {
                validInput = 1;
                saveUserResponse('Y');  // Save user's "Y" response as 'False'
            } else if (confirm[0] == 'N' || confirm[0] == 'n') {
                printf("Exiting the program.\n");
                saveUserResponse('N');  // Save user's "N" response as 'True'
                return 0;
            } else {
                printf("Invalid input. Please enter Y/y or Enter to confirm or N/n to exit.\n");
            }
        }
    }

    if (numInstalledPrograms == 1) {
        int programIndex = 0;
        while (!installedPrograms[programIndex]) {
            programIndex++;
        }

        char fullPath[100];
        sprintf(fullPath, "%s%s", PROGRAMS_PATH, programs[programIndex]);

        execlp(fullPath, programs[programIndex], NULL);

        perror("Failed to execute the program");
        return 1;
    }

    printf("Installed Programs:\n");
    int option = 1;

    for (int i = 0; i < numPrograms; i++) {
        if (installedPrograms[i]) {
            printf("%d. %s\n", option, programs[i]);
            option++;
        }
    }

    int choice;
    printf("Enter the number of the program to launch (or 0 to exit): ");
    scanf("%d", &choice);

    int selectedOption = 1;
    int selectedProgramIndex = -1;

    for (int i = 0; i < numPrograms; i++) {
        if (installedPrograms[i]) {
            if (selectedOption == choice) {
                selectedProgramIndex = i;
                break;
            }
            selectedOption++;
        }
    }

    if (selectedProgramIndex != -1) {
        char fullPath[100];
        sprintf(fullPath, "%s%s", PROGRAMS_PATH, programs[selectedProgramIndex]);

        execlp(fullPath, programs[selectedProgramIndex], NULL);

        perror("Failed to execute the program");
        return 1;
    }

    return 0;
}
