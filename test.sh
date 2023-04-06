#!/bin/bash

echo "Welcome to the Fedora repository installer!"

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
            ;;
        "Install RPM Fusion Free Tainted")
            sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-tainted-$(rpm -E %fedora).noarch.rpm
            ;;
        "Install RPM Fusion Non-Free")
            sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
            ;;
        "Install RPM Fusion Non-Free Tainted")
            sudo dnf install -y https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-tainted-$(rpm -E %fedora).noarch.rpm
            ;;
        "Install All")
            sudo dnf install -y https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://mirrors.rpmfusion.org/free/fedora/rpmfusion-free-release-tainted-$(rpm -E %fedora).noarch.rpm https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm https://mirrors.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-tainted-$(rpm -E %fedora).noarch.rpm
            ;;
        "Update")
            sudo dnf update -y
            flatpak update -y
            ;;
        "Quit")
            break
            ;;
        *) echo "Invalid option $REPLY";;
    esac
done


