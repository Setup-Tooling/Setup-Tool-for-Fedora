#!/bin/bash

# Check if dnf or flatpak is available
if command -v dnf &> /dev/null
then
    PACKAGE_MANAGER="dnf"
elif command -v flatpak &> /dev/null
then
    PACKAGE_MANAGER="flatpak"
else
    echo "Error: Neither dnf nor flatpak is available on this system."
    exit 1
fi
echo "Welcome to my package install script."
# Prompt the user to enter the packages they want to install
read -p "Enter the names of packages you want to install (separated by spaces): " PACKAGES

# Attempt to install each package using the appropriate package manager
for PACKAGE in $PACKAGES
do
    echo "Trying to install $PACKAGE using $PACKAGE_MANAGER..."
    if [ "$PACKAGE_MANAGER" = "dnf" ]
    then
        if dnf search -C $PACKAGE | grep -q "^$PACKAGE"
        then
            sudo dnf install $PACKAGE -y
        elif command -v flatpak &> /dev/null
        then
            echo "$PACKAGE not found in system repositories, attempting to install using flatpak..."
            flatpak install $PACKAGE -y
        else
            echo "Error: $PACKAGE not found in system repositories, and flatpak is not available on this system."
        fi
    elif [ "$PACKAGE_MANAGER" = "flatpak" ]
    then
        flatpak install $PACKAGE -y
    fi
done

echo "All packages have been installed (if possible)."


