#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <stdarg.h>

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

void runCommand(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char command[256];
    vsnprintf(command, sizeof(command), format, args);

    va_end(args);

    FILE* pipe = popen(command, "r");
    if (!pipe) {
        printf("Error executing command.\n");
        exit(1);
    }

    char buffer[512];
    FILE* logFile = fopen("/tmp/setup-tool.log", "a"); // Open the log file in append mode
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
        fprintf(logFile, "%s", buffer); // Write the output to the log file
    }

    fclose(logFile);
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

int getMenuOption(int maxOption) {
    int option;
    scanf("%d", &option);
    while (option < 1 || option > maxOption) {
        printf("Invalid option. Please try again.\n");
        scanf("%d", &option);
    }
    return option;
}

int main() {
    bool flatpakInstalled = commandExists("flatpak --version");
    bool snapInstalled = commandExists("snap --version");
    bool dnfInstalled = commandExists("dnf --version");

    if (!flatpakInstalled && !snapInstalled && !dnfInstalled) {
    printf("Flatpak, Snap, and DNF package managers are not installed on this system.\n");
    printf("Please install at least one of them to use the Package Management Helper.\n");
              }
    int option;

    char* password = getSecurePassword();

    char command[256];
    char customOption[256];
    char packageName[256];
    char sudoCommand[256];

    sprintf(sudoCommand, "echo '%s' | sudo -S echo 'This program is executed with sudo'", password);
    runCommand(sudoCommand);


        while (1) {
        printf("\n");
        printf("Choose an option:\n");
        printf("1. Repo Setup\n");
        printf("2. DNF Modification Tool\n");
        printf("3. Codec Setup\n");
        printf("4. Package Management Helper\n");
        printf("5. Premade Scripts\n");
        printf("6. System Info\n");
        printf("7. Update\n");
        printf("8. Reboot\n");
        printf("9. Quit\n");
        printf("Option: ");
        option = getMenuOption(9);

        switch (option) {
            case 1: {
                int repoOption;
                while (1) {
                    printf("\n");
                    printf("Choose an option for Repo Setup:\n");
                    printf("1. Install RPM Fusion Free\n");
                    printf("2. Install RPM Fusion Free Tainted\n");
                    printf("3. Install RPM Fusion Non-Free\n");
                    printf("4. Install RPM Fusion Non-Free Tainted\n");
                    printf("5. Install Flathub\n");
                    printf("6. Install All\n");
                    printf("7. Install and enable snapd\n");
                    printf("8. Install All + snapd\n");
                    printf("9. Back to main menu\n");
                    printf("Option: ");
                    repoOption = getMenuOption(9);

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
                            runCommand("sudo dnf install -y snapd");
                            runCommand("sudo ln -s /var/lib/snapd/snap /snap");
                            break;
                        case 8:
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf install -y snapd");
                            runCommand("sudo ln -s /var/lib/snapd/snap /snap");
                            break;
                        case 9:
                            printf("Returning to main menu.\n");
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (repoOption == 9) {
                        break;
                    }
                }
                break;
            }
            case 2: {
                int dnfOption;
                while (1) {
                    printf("\n");
                    printf("Choose an option for DNF modification tool:\n");
                    printf("1. Set defaultyes=True\n");
                    printf("2. Set max_parallel_downloads=10\n");
                    printf("3. Set all recommended options\n");
                    printf("4. Add custom option\n");
                    printf("5. Back to main menu\n");
                    printf("Option: ");
                    dnfOption = getMenuOption(5);

                    switch (dnfOption) {
                        case 1:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --save");
                            break;
                        case 2:
                            runCommand("sudo dnf config-manager --setopt=\"max_parallel_downloads=10\" --save");
                            break;
                        case 3:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            break;
                        case 4: {
                            char customOption[256];
                            printf("Enter the custom option: ");
                            scanf("%s", customOption);

                            char command[256];
                            snprintf(command, sizeof(command), "sudo dnf config-manager --setopt=\"%s\" --save", customOption);
                            runCommand(command);
                            break;
                        }
                        case 5:
                            printf("Returning to main menu.\n");
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (dnfOption == 5) {
                        break;
                    }
                }
                break;
            }
            case 3: {
                int codecOption;
                while (1) {
                    printf("\n");
                    printf("Choose an option for Codec Support:\n");
                    printf("1. Install general Codecs\n");
                    printf("2. DVD support\n");
                    printf("3. AMD\n");
                    printf("4. Nvidia\n");
                    printf("5. Intel\n");
                    printf("6. Back to main menu\n");
                    printf("Option: ");
                    codecOption = getMenuOption(6);

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
                            break;
                        case 6:
                            printf("Returning to main menu.\n");
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

                int packageOption;
                int packageOptionLoop = 1;
                while (packageOptionLoop) {
                    printf("\n");
                    printf("Choose an option for Package Management Helper:\n");
                    printf("1. Install a package\n");
                    printf("2. Remove a package\n");
                    printf("3. Search for a package\n");
                    printf("4. Back to main menu\n");
                    printf("Option: ");
                    packageOption = getMenuOption(4);

                    switch (packageOption) {
                        case 1: {
                            printf("Enter the name of the package to install: ");
                          scanf(" %[^\n]", packageName);

                          printf("Package Name: %s\n", packageName);

                           if (flatpakInstalled) {
                            sprintf(command, "flatpak install -y %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } else if (dnfInstalled) {
                            sprintf(command, "sudo dnf install -y %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } else if (snapInstalled) {
                            sprintf(command, "sudo snap install %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } else {
                            printf("No package manager found. Please install either Flatpak, DNF, or Snap.\n");
                        }
                        break;
                        }
                        case 2: {
                            printf("Enter the name of the package to remove: ");
                        scanf(" %[^\n]", packageName);

                        printf("Package Name: %s\n", packageName);

                        if (flatpakInstalled) {
                            sprintf(command, "flatpak uninstall -y %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } else if (dnfInstalled) {
                            sprintf(command, "sudo dnf remove -y %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } else if (snapInstalled) {
                            sprintf(command, "sudo snap remove %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } else {
                            printf("No package manager found. Please install either Flatpak, DNF, or Snap.\n");
                        }
                        break;
                        }
                        case 3: {
                            printf("Enter the name of the package to search: ");
                        scanf(" %[^\n]", packageName);

                        printf("Package Name: %s\n", packageName);

                        if (flatpakInstalled) {
                            sprintf(command, "flatpak search %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } if (dnfInstalled) {
                            sprintf(command, "sudo dnf search %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } if (snapInstalled) {
                            sprintf(command, "sudo snap search %s", packageName);
                            printf("Executing command: %s\n", command);
                            system(command);
                        } else {
                            printf("No package manager found. Please install either Flatpak, DNF, or Snap.\n");
                        }
                        break;
                        }
                        case 4: {
                        // Return to the main menu
                        packageOptionLoop = false;
                        break;
                        }
                        default: {
                            printf("Invalid option. Please try again.\n");
                            break;
                        }
                    if (packageOption == 4) {
                        packageOptionLoop = false;
                        break;
                     }
                }
            }
            break;
        }
            case 5: {
                int scriptOption;
                while (1) {
                    printf("\n");
                    printf("Choose an option for premade script:\n");
                    printf("1. Gaming-AMD\n");
                    printf("2. Gaming-Nvidia\n");
                    printf("3. Gaming-Intel\n");
                    printf("4. Streaming-AMD\n");
                    printf("5. Streaming-Nvidia\n");
                    printf("6. Streaming-Intel\n");
                    printf("7. Office\n");
                    printf("8. Back to main menu\n");
                    printf("Option: ");
                    scriptOption = getMenuOption(8);

                    switch (scriptOption) {
                        case 1:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            runCommand("sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld");
                            runCommand("sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld");
                            runCommand("sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686");
                            runCommand("sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686");
                            runCommand("flatpak install com.discordapp.Discord -y");
                            runCommand("flatpak com.usebottles.bottles -y");
                            runCommand("flatpak install net.davidotek.pupgui2 -y");
                            runCommand("flatpak install net.lutris.Lutris -y");
                            runCommand("sudo dnf install -y steam");
                            break;
                        case 2:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            runCommand("flatpak install com.discordapp.Discord -y");
                            runCommand("flatpak com.usebottles.bottles -y");
                            runCommand("flatpak install net.davidotek.pupgui2 -y");
                            runCommand("flatpak install net.lutris.Lutris -y");
                            runCommand("sudo dnf install -y steam");
                            runCommand("sudo dnf install -y nvidia-vaapi-driver");
                            break;
                        case 3:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            runCommand("flatpak install com.discordapp.Discord -y");
                            runCommand("flatpak com.usebottles.bottles -y");
                            runCommand("flatpak install net.davidotek.pupgui2 -y");
                            runCommand("flatpak install net.lutris.Lutris -y");
                            runCommand("sudo dnf install -y steam");
                            runCommand("sudo dnf install -y intel-media-driver");
                            break;
                        case 4:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            runCommand("sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld");
                            runCommand("sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld");
                            runCommand("sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686");
                            runCommand("sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686");
                            runCommand("flatpak install com.discordapp.Discord -y");
                            runCommand("flatpak com.usebottles.bottles -y");
                            runCommand("flatpak install net.davidotek.pupgui2 -y");
                            runCommand("flatpak install net.lutris.Lutris -y");
                            runCommand("sudo dnf install -y steam");
                            runCommand("flatpak install com.obsproject.Studio -y");
                            runCommand("sudo dnf install -y kdenlive krita");
                            runCommand("flatpak install org.gimp.GIMP -y");
                            break;
                        case 5:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            runCommand("flatpak install com.discordapp.Discord -y");
                            runCommand("flatpak com.usebottles.bottles -y");
                            runCommand("flatpak install net.davidotek.pupgui2 -y");
                            runCommand("flatpak install net.lutris.Lutris -y");
                            runCommand("sudo dnf install -y steam");
                            runCommand("sudo dnf install -y nvidia-vaapi-driver");
                            runCommand("flatpak install com.obsproject.Studio -y");
                            runCommand("sudo dnf install -y kdenlive krita");
                            runCommand("flatpak install org.gimp.GIMP -y");
                            break;
                        case 6:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            runCommand("flatpak install com.discordapp.Discord -y");
                            runCommand("flatpak com.usebottles.bottles -y");
                            runCommand("flatpak install net.davidotek.pupgui2 -y");
                            runCommand("flatpak install net.lutris.Lutris -y");
                            runCommand("sudo dnf install -y steam");
                            runCommand("sudo dnf install -y intel-media-driver");
                            runCommand("flatpak install com.obsproject.Studio -y");
                            runCommand("sudo dnf install -y kdenlive krita");
                            runCommand("flatpak install org.gimp.GIMP -y");
                            break;
                        case 7:
                            runCommand("sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm");
                            runCommand("sudo dnf groupupdate -y core");
                            runCommand("sudo dnf install -y rpmfusion-free-release-tainted");
                            runCommand("sudo dnf install -y rpmfusion-nonfree-release-tainted");
                            runCommand("flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo");
                            runCommand("sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing");
                            runCommand("sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin");
                            runCommand("sudo dnf groupupdate -y sound-and-video");
                            runCommand("flatpak install flathub org.libreoffice.LibreOffice -y");
                            break;
                        case 8:
                            printf("Returning to main menu.\n");
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (scriptOption == 8) {
                        break;
                    }
                }
                break;
            }
            case 6:{
                int sysOption;
                while (1) {
                    printf("\n");
                    printf("Choose an option for system info:\n");
                    printf("1. Short, Quick Overview\n");
                    printf("2. PCI/PCIE Devices\n");
                    printf("3. USB Devices\n");
                    printf("4. Storage Devices\n");
                    printf("5. Back to main menu\n");
                    printf("Option: ");
                    sysOption = getMenuOption(5);

                    switch (sysOption) {
                        case 1:
                            runCommand("neofetch");
                            break;
                        case 2:
                            runCommand("lspci");
                            break;
                        case 3:
                            runCommand("lsusb");
                            break;
                        case 4:
                            runCommand("df -H");
                            break;
                        case 5:
                            printf("Returning to main menu.\n");
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (sysOption == 5) {
                        break;
                    }
                }
                break;
            }
            case 7:{
                if (dnfInstalled || flatpakInstalled || snapInstalled) {
                    char updateCommand[512] = "sudo ";
                    if (dnfInstalled)
                        strcat(updateCommand, "dnf update --refresh -y ");
                    if (flatpakInstalled)
                        strcat(updateCommand, "&& flatpak update -y ");
                    if (snapInstalled)
                        strcat(updateCommand, "&& snap refresh");

                    runCommand(updateCommand);
                } else {
                    printf("DNF, Flatpak, and Snap are not installed.\n");
                }
                break;
            }
            case 8:
                runCommand("sudo reboot");
                break;
            case 9:
                printf("Quitting the program.\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
                break;
            }
        }
    if (option == 9)
    return 0;
}
