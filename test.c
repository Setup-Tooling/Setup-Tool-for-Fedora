#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void runCommand(char* command) {
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("Error executing command.\n");
        exit(1);
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }

    pclose(pipe);
}

int main() {
    char password[64];
    printf("Please enter your sudo password: ");
    fgets(password, sizeof(password), stdin);

    char sudoCommand[128];
    sprintf(sudoCommand, "echo '%s' | sudo -S echo 'This command is executed with sudo'", password);
    runCommand(sudoCommand);

    while (1) {
        printf("\n");
        printf("Choose an option:\n");
        printf("1. Repo Setup\n");
        printf("2. DNF Modification Tool\n");
        printf("3. Codec Setup\n");
        printf("4. Package Management Helper\n");
        printf("5. Update\n");
        printf("6. Reboot\n");
        printf("7. Quit\n");

        int option;
        printf("Option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                while (1) {
                    printf("\n");
                    printf("Choose an option for Repo Setup:\n");
                    printf("1. Install RPM Fusion Free\n");
                    printf("2. Install RPM Fusion Free Tainted\n");
                    printf("3. Install RPM Fusion Non-Free\n");
                    printf("4. Install RPM Fusion Non-Free Tainted\n");
                    printf("5. Install Flathub\n");
                    printf("6. Install All\n");
                    printf("7. Back to main menu\n");

                    int repoOption;
                    printf("Option: ");
                    scanf("%d", &repoOption);

                    switch (repoOption) {
                        case 1:
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            break;
                        case 2:
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            break;
                        case 3:
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            break;
                        case 4:
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            break;
                        case 5:
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            break;
                        case 6:
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            break;
                        case 7:
                            // Return to main menu
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (repoOption == 7) {
                        break;
                    }
                }
                break;
            }
            case 2: {
            while (1) {
                    printf("\n");
                    printf("Choose an option for DNF modification tool:\n");
                    printf("1. Set defaultyes=True\n");
                    printf("2. Set max_parallel_downloads=10\n");
                    printf("3. Set all recommended options\n");
                    printf("4. Add custom option\n");
                    printf("5. Back to main menu\n");

                    int confOption;
                    printf("Option: ");
                    scanf("%d", &confOption);

                    switch (confOption) {
                        case 1:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --save");
                            break;
                        case 2:
                            runCommand("sudo dnf config-manager --setopt=\"max_parallel_downloads=10\" --save");
                            break;
                        case 3:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            break;
                        case 4:
                            printf("this feature will come later on");
                            //runCommand("...");
                            break;
                        case 5:
                            // Return to main menu
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (confOption == 5) {
                        break;
                    }
                }
                break;
            }
            case 3: {
                // Codec Setup
                // Add your code here
                break;
            }
            case 4: {
                // Package Install Helper
                while (1) {
                    printf("\n");
                    printf("Choose an option for Package Management Helper:\n");
                    printf("1. Install a package\n");
                    printf("2. Remove a package\n");
                    printf("3. Search for a package\n");
                    printf("4. Back to main menu\n");

                    int packageOption;
                    printf("Option: ");
                    scanf("%d", &packageOption);

                    char packageName[64];

                    switch (packageOption) {
                        case 1:
                            printf("Enter the name of the package to install: ");
                            scanf("%s", packageName);
                            sprintf(sudoCommand, "sudo dnf install -y %s", packageName);
                            runCommand(sudoCommand);
                            break;
                        case 2:
                            printf("Enter the name of the package to remove: ");
                            scanf("%s", packageName);
                            sprintf(sudoCommand, "sudo dnf remove -y %s", packageName);
                            runCommand(sudoCommand);
                            break;
                        case 3:
                            printf("Enter the name of the package to search: ");
                            scanf("%s", packageName);
                            sprintf(sudoCommand, "sudo dnf search %s", packageName);
                            runCommand(sudoCommand);
                            break;
                        case 4:
                            // Return to the main menu
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (packageOption == 4) {
                        break;
                    }
                }

                break;
            }
            case 5: {
                runCommand("sudo dnf update -y & flatpak update -y");
                break;
            }
            case 6: {
                runCommand("sudo reboot");
                break;
            }
            case 7: {
                printf("Exiting program.\n");
                return 0;
            }
            default: {
                printf("Invalid option. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}

