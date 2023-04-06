#!/bin/bash

echo "Welcome to the my repository installer!"

PS3='Please enter your choice: '
options=("Modify dnf.conf" "Install RPM Fusion Free" "Install RPM Fusion Free Tainted" "Install RPM Fusion Non-Free" "Install RPM Fusion Non-Free Tainted" "Install All" "Update" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "Modify dnf.conf")
            echo "Enter the name and value of the option you want to add or modify (e.g. install_weak_deps=yes)"
            read -p "Option: " option
            # Prompt the user to confirm the modification
            read -p "Are you sure you want to add/modify the following option to dnf.conf: $option? (y/n): " confirm
            if [ "$confirm" == "y" ]; then
                # Remove existing instances of the option, if any
                sudo sed -i "/^#*\s*$option/d" /etc/dnf/dnf.conf
                # Add the option to the end of the file
                echo "$option" | sudo tee -a /etc/dnf/dnf.conf > /dev/null
                echo "dnf.conf updated successfully."
            else
                echo "Modification cancelled."
            fi
            ;;
        "Install RPM Fusion Free")
            sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            sudo dnf groupupdate -y core
            ;;
        "Install RPM Fusion Free Tainted")
            sudo dnf groupupdate -y multimedia --setop="install_weak_deps=False" --exclude=PackageKit-gstreamer-plugin
            sudo dnf groupupdate -y sound-and-video
            sudo dnf install -y rpmfusion-free-release-tainted
            ;;
        "Install RPM Fusion Non-Free")
            sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            sudo dnf groupupdate -y core
            ;;
        "Install RPM Fusion Non-Free Tainted")
            sudo dnf install -y rpmfusion-nonfree-release-tainted
            ;;
        "Enable compatibility for DVDs"
            sudo dnf install -y libdvdcss
            ;;
        "Install All")
            sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm
            sudo dnf groupupdate -y core
            sudo dnf groupupdate -y multimedia --setop="install_weak_deps=False" --exclude=PackageKit-gstreamer-plugin
            sudo dnf groupupdate -y sound-and-video
            sudo dnf install -y rpmfusion-free-release-tainted
            sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            sudo dnf install -y rpmfusion-nonfree-release-tainted
            sudo dnf install -y libdvdcss
            ;;
        "Update")
            sudo dnf update -y && flatpak update -y
            ;;
        "Quit")
            break
            ;;
        *) echo "Invalid option $REPLY";;
    esac
done

echo "Thank you for using the my repository installer! Goodbye."
