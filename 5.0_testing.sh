#!/bin/bash

# Use whiptail to display a menu with five options
while true; do
OPTION=$(whiptail --title "Menu" --menu "Choose an option" 15 60 5 \
"1" "Repo Setup" \
"2" "DNF modification tool" \
"3" "Codec Setup" \
"4" "Package Install Helper (not working right now)" \
"5" "Quit" \
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
        "7" "Back to main menu" \
        3>&1 1>&2 2>&3)

        # Check which option was selected and perform the corresponding action
        case $REPO_OPTION in
            1)
                # Perform action for Option 1 of Repo Setup
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
                sudo dnf groupupdate -y core
                ;;
            2)
                # Perform action for Option 2 of Repo Setup
                sudo dnf install -y rpmfusion-free-release-tainted
                ;;
            3)
                # Perform action for Option 3 of Repo Setup
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
                sudo dnf groupupdate -y core
                ;;
            4)
                # Perform action for Option 4 of Repo Setup
                sudo dnf install -y rpmfusion-nonfree-release-tainted
                ;;
            5)
                # Perform action for Option 5 of Repo Setup
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
                ;;
            6)
                # Perform action for Option 6 of Repo Setup
                sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
                sudo dnf groupupdate -y core
                sudo dnf install -y rpmfusion-free-release-tainted
                sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
                sudo dnf install -y rpmfusion-nonfree-release-tainted
                flatpak remote-add --if-not-exists flathub https://flathub.org/repo/flathub.flatpakrepo
                ;;
            7)
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
        CODEC_OPTION=$(whiptail --title "Repo Setup" --menu "Choose an option" 20 60 8 \
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
                sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
                sudo dnf groupupdate -y multimedia --setop="install_weak_deps=False" --exclude=PackageKit-gstreamer-plugin
                sudo dnf groupupdate -y sound-and-video
                ;;
            2)
                sudo dnf install -y libdvdcss
                ;;
            3)
                sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld
                sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld
                sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686
                sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686
                ;;
            4)
               sudo dnf install -y nvidia-vaapi-driver
                ;;
            5)
               sudo dnf install -y intel-media-driver
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
        ## PLACEHOLDER
        if [ -f "package-installer.sh" ]; then
         chmod +x package-installer.sh
         sudo ./package-installer.sh
        else
         echo "The package-installer.sh script does not exist."
        fi
       
        ;;
    5)
        whiptail --msgbox "Exiting script..." 8 40
        exit 0
        ;;
    *)
        whiptail --msgbox "Invalid option selected" 8 40
        ;;
    esac
done