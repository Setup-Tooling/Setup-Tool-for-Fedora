#!/bin/bash

# Ask for sudo password
        password=$(whiptail --title "Sudo Password" --passwordbox "Please enter your sudo password:" 10 60 3>&1 1>&2 2>&3)

# Use sudo with the entered password
        echo "$password" | sudo -S echo "This command is executed with sudo"
        

# Use whiptail to display a menu with five options
while true; do
OPTION=$(whiptail --title "Menu" --menu "Choose an option" 15 60 5 \
"1" "Repo Setup" \
"2" "DNF Modification Tool" \
"3" "Codec Setup" \
"4" "Package Management Helper" \
"5" "Premade Scripts" \
"6" "System Info" \
"7" "Update" \
"8" "Reboot" \
"9" "Quit" \
3>&1 1>&2 2>&3)

# Check which option was selected and perform the corresponding action
case $OPTION in
    1)
        # Display a submenu with seven options for Repo Setup
        while true; do
        REPO_OPTION=$(whiptail --title "Repo Setup" --menu "Choose an option" 20 60 8 \
        "1" "Install RPM Fusion Free" \
        "2" "Install RPM Fusion Free Tainted" \
        "3" "Install RPM Fusion Non-Free" \
        "4" "Install RPM Fusion Non-Free Tainted" \
        "5" "Install Flathub" \
        "6" "Install All" \
        "7" "Install and enable snapd" \
        "8" "Install All + snapd" \
        "9" "Back to main menu" \
        3>&1 1>&2 2>&3)

        # Check which option was selected and perform the corresponding action
        case $REPO_OPTION in
            1)
                # Perform action for Option 1 of Repo Setup
                {
                echo 0
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
                echo 50
                sudo dnf groupupdate -y core
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repo" 6 60 0
                ;;
            2)
                # Perform action for Option 2 of Repo Setup
                {
                echo 0
                sudo dnf install -y rpmfusion-free-release-tainted
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repo" 6 60 0
                ;;
            3)
                # Perform action for Option 3 of Repo Setup
                {
                echo 0
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
                echo 50
                sudo dnf groupupdate -y core
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repo" 6 60 0
                ;;
            4)
                # Perform action for Option 4 of Repo Setup
                {
                echo 0
                sudo dnf install -y rpmfusion-nonfree-release-tainted
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repo" 6 60 0
                ;;
            5)
                # Perform action for Option 5 of Repo Setup
                {
                echo 0
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repo" 6 60 0
                ;;
            6)
                # Perform action for Option 6 of Repo Setup
                {
                echo 0
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
                echo 16
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
                echo 33
                sudo dnf groupupdate -y core
                echo 50
                sudo dnf install -y rpmfusion-free-release-tainted
                echo 66
                sudo dnf install -y rpmfusion-nonfree-release-tainted
                echo 83
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repos" 6 60 0
                ;;
            7)
                {
                echo 0
                sudo dnf install -y snapd
                echo 50
                sudo ln -s /var/lib/snapd/snap /snap
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repos" 6 60 0
                ;;
            8)
                {
                echo 0
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
                echo 13
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
                echo 25
                sudo dnf groupupdate -y core
                echo 38
                sudo dnf install -y rpmfusion-free-release-tainted
                echo 50
                sudo dnf install -y rpmfusion-nonfree-release-tainted
                echo 63
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
                echo 75
                sudo dnf install -y snapd
                echo 88
                sudo ln -s /var/lib/snapd/snap /snap
                echo 100
                sleep 1
                } | whiptail --gauge "Installing Repos" 6 60 0
                ;;
            9)
                # Perform action for Option 7 of Repo Setup
                break
                ;;
            *)
                # Display an error message if an invalid option is selected
                whiptail --msgbox "Invalid option selected" 8 40
                ;;
        esac
    done
        ;;
    2)
       # Use whiptail to display a menu with five options
            while true; do
                DNF_OPTION=$(whiptail --title "DNF Modification Tool" --menu "Choose an option" 15 60 5 \
                "1" "Set defaultyes=True" \
                "2" "Set max_parallel_downloads=10" \
                "3" "Set all recommended options" \
                "4" "Add custom option" \
                "5" "Back to main menu" \
                3>&1 1>&2 2>&3)

                # Check which DNF option was selected and perform the corresponding action
                case $DNF_OPTION in
            1)
                # Perform action for Option 1 of DNF modification tool
                sudo dnf config-manager --setopt="defaultyes=True" --save
                ;;
            2)
                # Perform action for Option 2 of DNF modification tool
                sudo dnf config-manager --setopt="max_parallel_downloads=10" --save
                ;;
            3)
                # Perform action for Option 3 of DNF modification tool
                sudo dnf config-manager --setopt="defaultyes=True" --setopt="max_parallel_downloads=10" --save
                ;;
            4)
                # Perform action for Option 4 of DNF modification tool
                soption=$(whiptail --title "Option" --inputbox "Enter an option" 8 40 3>&1 1>&2 2>&3)
                exit_status=$?
                if [ $exit_status = 0 ]; then
                    value=$(whiptail --title "Value" --inputbox "Enter a value for option $option" 8 40 3>&1 1>&2 2>&3)
                    exit_status=$?
                    if [ $exit_status = 0 ]; then
                    sudo dnf config-manager --setopt="$option=$value" --save
                    fi
                fi
                ;;
            5)
                # Perform action for Option 5 of DNF modification tool
                break
                ;;
            *)
                # Display an error message if an invalid option is selected
                whiptail --msgbox "Invalid option selected" 8 40
                ;;
        esac
    done
        ;;
    3)
        # Display a submenu with seven options for Codec Setup
        while true; do
        CODEC_OPTION=$(whiptail --title "Codec Setup" --menu "Choose an option" 20 60 8 \
        "1" "Install general Codecs" \
        "2" "DVD support" \
        "3" "AMD" \
        "4" "Nvidia" \
        "5" "Intel" \
        "6" "Back to main menu" \
        3>&1 1>&2 2>&3)

        # Check which option was selected and perform the corresponding action
        case $CODEC_OPTION in
            1)
            {
            echo 0
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 33
                sudo dnf groupupdate -y multimedia --setop="install_weak_deps=False" --exclude=PackageKit-gstreamer-plugin
            echo 67
                sudo dnf groupupdate -y sound-and-video
            echo 100
            sleep 1
                } | whiptail --gauge "Installing Codecs" 6 60 0
                ;;
            2)
            {
            echo 0
                sudo dnf install -y libdvdcss
            echo 100
            sleep 1
                } | whiptail --gauge "Installing Driver" 6 60 0
                ;;
            3)
            {
            echo 0   
                sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld
            echo 25    
                sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld
            echo 50    
                sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686
            echo 75    
                sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686
            echo 100
            sleep 1
               } | whiptail --gauge "Installing Drivers" 6 60 0
                ;;
            4)
            {
            echo 0
               sudo dnf install -y nvidia-vaapi-driver
            echo 100
            sleep 1
                } | whiptail --gauge "Installing Driver" 6 60 0
                ;;
            5)
            {
            echo 0
               sudo dnf install -y intel-media-driver
            echo 100
            sleep 1
                } | whiptail --gauge "Installing Driver" 6 60 0
                ;;
            6)
                break
                ;;
            *)
                # Display an error message if an invalid option is selected
                whiptail --msgbox "Invalid option selected" 8 40
                ;;
        esac
    done
        ;;
    4)
command_exists() {
    type "$1" &>/dev/null
}

# Function to display the main menu using Whiptail
show_main_menu() {
    whiptail --title "Package Management Helper" --menu "Choose an option:" 15 50 4 \
        1 "Install a package" \
        2 "Remove a package" \
        3 "Search for a package" \
        4 "Exit" \
        3>&1 1>&2 2>&3
}

packageOptionLoop=true

while "$packageOptionLoop"; do
    choice=$(show_main_menu)

    case $choice in
        1)
            packageName=$(whiptail --inputbox "Enter the name of the package to install:" 8 50 --title "Install a Package" 3>&1 1>&2 2>&3)
            if [[ -n $packageName ]]; then
                if command_exists "flatpak"; then
                    command="flatpak install -y $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                elif command_exists "dnf"; then
                    command="sudo dnf install -y $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                elif command_exists "snap"; then
                    command="sudo snap install $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                else
                    whiptail --msgbox "No package manager found. Please install either Flatpak, DNF, or Snap." 10 50
                fi
            else
                whiptail --msgbox "Package name cannot be empty." 10 50
            fi
            ;;
        2)
            packageName=$(whiptail --inputbox "Enter the name of the package to remove:" 8 50 --title "Remove a Package" 3>&1 1>&2 2>&3)
            if [[ -n $packageName ]]; then
                if command_exists "flatpak"; then
                    command="flatpak uninstall -y $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                elif command_exists "dnf"; then
                    command="sudo dnf remove -y $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                elif command_exists "snap"; then
                    command="sudo snap remove $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                else
                    whiptail --msgbox "No package manager found. Please install either Flatpak, DNF, or Snap." 10 50
                fi
            else
                whiptail --msgbox "Package name cannot be empty." 10 50
            fi
            ;;
        3)
            packageName=$(whiptail --inputbox "Enter the name of the package to search:" 8 50 --title "Search for a Package" 3>&1 1>&2 2>&3)
            if [[ -n $packageName ]]; then
                if command_exists "flatpak"; then
                    command="flatpak search $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                elif command_exists "dnf"; then
                    command="sudo dnf search $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                elif command_exists "snap"; then
                    command="sudo snap search $packageName"
                    whiptail --msgbox "Executing command: $command" 10 50
                    $command
                else
                    whiptail --msgbox "No package manager found. Please install either Flatpak, DNF, or Snap." 10 50
                fi
            else
                whiptail --msgbox "Package name cannot be empty." 10 50
            fi
            ;;
        4)
            # Exit the script
            packageOptionLoop=false
            ;;
        *)
            # Invalid option, do nothing
            ;;
            esac
    done
        ;;
    5)
      while true; do
        PRE_OPTION=$(whiptail --title "Premade Scripts" --menu "Choose an option" 20 60 8 \
        "1" "Gaming-AMD" \
        "2" "Gaming-Nvidia" \
        "3" "Gaming-Intel" \
        "4" "Streaming-AMD" \
        "5" "Streaming-Nvidia" \
        "6" "Streaming-Intel" \
        "7" "Office" \
        "8" "Back to main menu" \
        3>&1 1>&2 2>&3)

        # Check which option was selected and perform the corresponding action
        case $PRE_OPTION in
         1)
            {
            echo 0
                sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save
            echo 5
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            echo 11
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            echo 16
                sudo dnf groupupdate -y core
            echo 21
                sudo dnf install -y rpmfusion-free-release-tainted
            echo 26
                sudo dnf install -y rpmfusion-nonfree-release-tainted
            echo 32
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
            echo 37
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 42
                sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin
            echo 47
                sudo dnf groupupdate -y sound-and-video
            echo 53
                sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld
            echo 58
                sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld
            echo 63
                sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686
            echo 68
                sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686
            echo 74
                flatpak install com.discordapp.Discord -y
            echo 79
                flatpak com.usebottles.bottles -y
            echo 84
                flatpak install net.davidotek.pupgui2 -y
            echo 89
                flatpak install net.lutris.Lutris -y
            echo 95
                sudo dnf install -y steam
            echo 100
            sleep 1
                } | whiptail --gauge "Running Script" 6 60 0
                ;;
            2)
            {
            echo 0
                sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save
            echo 6
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            echo 13
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            echo 19
                sudo dnf groupupdate -y core
            echo 25
                sudo dnf install -y rpmfusion-free-release-tainted
            echo 31
                sudo dnf install -y rpmfusion-nonfree-release-tainted
            echo 38
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
            echo 44
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 50
                sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin
            echo 56
                sudo dnf groupupdate -y sound-and-video
            echo 63
                flatpak install com.discordapp.Discord -y
            echo 69
                flatpak com.usebottles.bottles -y
            echo 75
                flatpak install net.davidotek.pupgui2 -y
            echo 81
                flatpak install net.lutris.Lutris -y
            echo 88
                sudo dnf install -y steam
            echo 94
                sudo dnf install -y nidia-vaapi-driver
            echo 100
            sleep 1
                } | whiptail --gauge "Running Script" 6 60 0
                ;;
            3)
            {
            echo 0
                sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save
            echo 6
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            echo 13
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            echo 19
                sudo dnf groupupdate -y core
            echo 25
                sudo dnf install -y rpmfusion-free-release-tainted
            echo 31
                sudo dnf install -y rpmfusion-nonfree-release-tainted
            echo 38
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
            echo 44
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 50
                sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin
            echo 56
                sudo dnf groupupdate -y sound-and-video
            echo 63
                flatpak install com.discordapp.Discord -y
            echo 69
                flatpak com.usebottles.bottles -y
            echo 75
                flatpak install net.davidotek.pupgui2 -y
            echo 81
                flatpak install net.lutris.Lutris -y
            echo 88
                sudo dnf install -y steam
            echo 94
                sudo dnf install -y intel-media-driver
            echo 100
            sleep 1
                } | whiptail --gauge "Running Script" 6 60 0
                ;;
            4)
            {
            echo 0
                sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save
            echo 5
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            echo 9
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            echo 14
                sudo dnf groupupdate -y core
            echo 18
                sudo dnf install -y rpmfusion-free-release-tainted
            echo 23
                sudo dnf install -y rpmfusion-nonfree-release-tainted
            echo 27
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
            echo 32
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 36
                sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin
            echo 41
                sudo dnf groupupdate -y sound-and-video
            echo 45
                sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld
            echo 50
                sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld
            echo 55
                sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686
            echo 59
                sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686
            echo 64
                flatpak install com.discordapp.Discord -y
            echo 68
                flatpak com.usebottles.bottles -y
            echo 73
                flatpak install net.davidotek.pupgui2 -y
            echo 77
                flatpak install net.lutris.Lutris -y
            echo 82
                sudo dnf install -y steam
            echo 86
                flatpak install com.obsproject.Studio -y
            echo 91
                sudo dnf install -y kdenlive krita
            echo 95
                flatpak install org.gimp.GIMP -y
            echo 100
            sleep 1
                } | whiptail --gauge "Running Script" 6 60 0
                ;;
            5)
            {
            echo 0
                sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save
            echo 5
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            echo 11
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            echo 16
                sudo dnf groupupdate -y core
            echo 21
                sudo dnf install -y rpmfusion-free-release-tainted
            echo 26
                sudo dnf install -y rpmfusion-nonfree-release-tainted
            echo 32
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
            echo 37
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 42
                sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin
            echo 47
                sudo dnf groupupdate -y sound-and-video
            echo 53
                sudo dnf install -y nvidia-vaapi-driver
            echo 58
                sudo dnf install -y kdenlive krita
            echo 63
                flatpak install com.obsproject.Studio -y
            echo 68
                flatpak install org.gimp.GIMP -y
            echo 74
                flatpak install com.discordapp.Discord -y
            echo 79
                flatpak com.usebottles.bottles -y
            echo 84
                flatpak install net.davidotek.pupgui2 -y
            echo 89
                flatpak install net.lutris.Lutris -y
            echo 95
                sudo dnf install -y steam
            echo 100
            sleep 1
                } | whiptail --gauge "Running Script" 6 60 0
                ;;
            6)
            {
            echo 0
                sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save
            echo 5
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            echo 11
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            echo 16
                sudo dnf groupupdate -y core
            echo 21
                sudo dnf install -y rpmfusion-free-release-tainted
            echo 26
                sudo dnf install -y rpmfusion-nonfree-release-tainted
            echo 32
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
            echo 37
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 42
                sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin
            echo 47
                sudo dnf groupupdate -y sound-and-video
            echo 53
                sudo dnf install -y intel-media-driver
            echo 58
                sudo dnf install -y kdenlive krita
            echo 63
                flatpak install com.obsproject.Studio -y
            echo 68
                flatpak install org.gimp.GIMP -y
            echo 74
                flatpak install com.discordapp.Discord -y
            echo 79
                flatpak com.usebottles.bottles -y
            echo 84
                flatpak install net.davidotek.pupgui2 -y
            echo 89
                flatpak install net.lutris.Lutris -y
            echo 95
                sudo dnf install -y steam
            echo 100
            sleep 1
                } | whiptail --gauge "Running Script" 6 60 0
                ;;
            7)
            {
            echo 0
                sudo dnf config-manager --setopt=\"defaultyes=True\" --setopt=\"max_parallel_downloads=10\" --save
            echo 9
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            echo 18
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            echo 27
                sudo dnf groupupdate -y core
            echo 36
                sudo dnf install -y rpmfusion-free-release-tainted
            echo 45
                sudo dnf install -y rpmfusion-nonfree-release-tainted
            echo 55
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
            echo 64
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            echo 73
                sudo dnf groupupdate -y multimedia --setop=\"install_weak_deps=False\" --exclude=PackageKit-gstreamer-plugin
            echo 82
                sudo dnf groupupdate -y sound-and-video
            echo 91
                flatpak install flathub org.libreoffice-LibreOffice -y
            echo 100
            sleep 1
                } | whiptail --gauge "Running Script" 6 60 0
                ;;
            8)
                break
                ;;
            *)
                # Display an error message if an invalid option is selected
                whiptail --msgbox "Invalid option selected" 8 40
                ;;
        esac
    done
        ;;
    7)
      {
        echo 0
        sudo dnf update -y
        echo 33
        flatpak update -y
        echo 67
        snap refresh
        echo 100
        sleep 1
       } | whiptail --gauge "Updating System" 6 60 0
        ;;
    8)
        echo Rebooting system...
        reboot
        ;;
    9)
        whiptail --msgbox "Exiting script..." 8 40
        exit 0
        ;;
    *)
        whiptail --msgbox "Invalid option selected" 8 40
        ;;
    esac
done
