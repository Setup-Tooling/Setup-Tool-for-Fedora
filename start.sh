#!/bin/bash

echo "Welcome to the my setup program!"

PS3='Please enter your choice: '

options=("Modify dnf.conf" "Repo-setup" "Package-Installer" "Codec-setup" "Reboot system" "Quit")
select opt in "${options[@]}"
do
 case $opt in
 "Modify dnf.conf")
            echo "opening dnf modification"
             if [ -f "dnf-mod.sh" ]; then
                chmod +x dnf-mod.sh
            sudo ./dnf-mod.sh
            else
            echo "The dnf-mod.sh script does not exist."
            fi
            ;;
            
 "Repo-setup")
            echo "opening repo setup"
             if [ -f "repo-setup.sh" ]; then
                chmod +x repo-setup.sh
            sudo ./repo-setup.sh
            else
            echo "The repo-setup.sh script does not exist."
            fi
            ;;
            
  "Package-Installer")
            echo "opening package installer"
             if [ -f "package-installer.sh" ]; then
                chmod +x package-installer.sh
            sudo ./package-installer.sh
            else
            echo "The package-installer.sh script does not exist."
            fi
            ;;
            
   "Codec-setup")
           echo "opening codec setup"
             if [ -f "codec-setup.sh" ]; then
                chmod +x codec-setup.sh
            sudo ./codec-setup.sh
            else
            echo "The codec-setup.sh script does not exist."
            fi
            ;;
            
   "Reboot system")
      echo "Rebooting system..."
      sudo reboot
      break
      ;;
      
    "Quit")
        echo "Configuration completed!"
        exit 0
        ;;
        
  *) echo "Invalid option $REPLY";;
  esac
done

echo "Thank you for using the my setup program! Goodbye."
