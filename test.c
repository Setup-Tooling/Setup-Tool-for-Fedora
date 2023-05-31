#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>

char *getSecurePassword() {
    struct termios oldTerm, newTerm;
    char *password = NULL;

    if (tcgetattr(STDIN_FILENO, &oldTerm) == -1) {
        printf("Error turning off terminal echoing.\n");
        exit(1);
    }

    newTerm = oldTerm;
    newTerm.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &newTerm) == -1) {
        printf("Error turning off terminal echoing.\n");
        exit(1);
    }

    password = getpass("Please enter your sudo password: ");

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldTerm) == -1) {
        printf("Error restoring terminal settings.\n");
        exit(1);
    }

    return password;
}

void runCommand(const char* command) {
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

bool commandExists(const char* command) {
    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        return false;
    }
    pclose(fp);
    return true;
}

int main() {
    char* password = getSecurePassword();

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
                while (1) {
                    printf("\n");
                    printf("Choose an option for Codec Support:\n");
                    printf("1. Install general Codecs\n");
                    printf("2. DVD support\n");
                    printf("3. AMD\n");
                    printf("4. Nvidia\n");
                    printf("5. Intel\n");
                    printf("6. Back to main menu\n");

                    int codecOption;
                    printf("Option: ");
                    scanf("%d", &codecOption);

                    switch (codecOption) {
                        case 1:
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            break;
                        case 2:
                            runCommand("sudo dnf install -y libdvdcss");
                            break;
                        case 3:
                            runCommand("sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld");
                            runCommand("sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld");
                            runCommand("sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686");
                            runCommand("sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686");
                            break;
                        case 4:
                            runCommand("sudo dnf install -y nvidia-vaapi-driver");
                            break;
                        case 5:
                            runCommand("sudo dnf install -y intel-media-driver");
                        case 6:
                            // Return to main menu
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (codecOption == 6) {
                        break;
                    }
                }
                break;
            }
            case 4: {
              // Package Install Helper
              // Check if Flatpak, Snap, and DNF are installed
              bool flatpakInstalled = commandExists("flatpak --version");
              bool snapInstalled = commandExists("snap --version");
              bool dnfInstalled = commandExists("dnf --version");

              if (!flatpakInstalled && !snapInstalled && !dnfInstalled) {
                  printf("Flatpak, Snap, and DNF package managers are not installed on this system.\n");
                  printf("Please install at least one of them to use the Package Management Helper.\n");
                  break;
              }

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

                          if (flatpakInstalled) {
                              sprintf(sudoCommand, "flatpak install -y %s", packageName);
                          } else if (snapInstalled) {
                              sprintf(sudoCommand, "sudo snap install %s", packageName);
                          } else {
                              sprintf(sudoCommand, "sudo dnf install -y %s", packageName);
                          }

                          runCommand(sudoCommand);
                          break;
                    case 2:
                        printf("Enter the name of the package to remove: ");
                        scanf("%s", packageName);

                        if (flatpakInstalled) {
                            sprintf(sudoCommand, "flatpak uninstall -y %s", packageName);
                        } else if (snapInstalled) {
                            sprintf(sudoCommand, "sudo snap remove %s", packageName);
                        } else {
                            sprintf(sudoCommand, "sudo dnf remove -y %s", packageName);
                        }

                        runCommand(sudoCommand);
                        break;
                    case 3:
                        printf("Enter the name of the package to search: ");
                        scanf("%s", packageName);

                        if (flatpakInstalled) {
                            sprintf(sudoCommand, "flatpak search %s", packageName);
                        } else if (snapInstalled) {
                            sprintf(sudoCommand, "sudo snap search %s", packageName);
                        } else {
                            sprintf(sudoCommand, "sudo dnf search %s", packageName);
                        }

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
                runCommand("sudo dnf update -y && flatpak update -y && sudo snap refresh");
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

