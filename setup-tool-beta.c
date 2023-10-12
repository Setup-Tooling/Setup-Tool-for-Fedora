#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

#define PROGRAMS_PATH "/usr/bin/"

int checkProgramExists(const char* programName) {
    char fullPath[100];
    sprintf(fullPath, "%s%s", PROGRAMS_PATH, programName);

    if (access(fullPath, F_OK) != -1) {
        return 1;  // Program exists
    } else {
        return 0;  // Program does not exist
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
