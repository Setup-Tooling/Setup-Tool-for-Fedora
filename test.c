#include <stdio.h>
#include <unistd.h>

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

void displayMenu(const char* programs[], int installedPrograms[], int numPrograms) {
    printf("Installed Programs:\n");
    int option = 1;
    for (int i = 0; i < numPrograms; i++) {
        if (installedPrograms[i]) {
            printf("%d. %s\n", option, programs[i]);
            option++;
        }
    }
}

int main() {
    const char* programs[] = {"setup-tool-cli", "setup-tool-tui", "setup-tool-gui"};
    int numPrograms = sizeof(programs) / sizeof(programs[0]);

    int installedPrograms[numPrograms];
    for (int i = 0; i < numPrograms; i++) {
        installedPrograms[i] = checkProgramExists(programs[i]);
    }

    int hasInstalledPrograms = 0;
    for (int i = 0; i < numPrograms; i++) {
        if (installedPrograms[i]) {
            hasInstalledPrograms = 1;
            break;
        }
    }

    if (!hasInstalledPrograms) {
        printf("No installed programs found.\n");
        return 0;
    }

    displayMenu(programs, installedPrograms, numPrograms);

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

        // The following lines will only be executed if execlp fails
        perror("Failed to execute the program");
        return 1;
    }

    return 0;
}
