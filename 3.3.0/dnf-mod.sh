#!/bin/bash

PS3="Please select an option: "

echo "Welcome to my DNF configuration script!"
select choice in "Set defaultyes=True" "Set max_parallel_downloads=10" "Set fastestmirror=True" "Set all options" "Add custom option" "Quit"; do
  case $choice in
    "Set defaultyes=True")
      sudo dnf config-manager --setopt="defaultyes=True" --save
      echo "defaultyes=True has been set."
      
      ;;
    "Set max_parallel_downloads=10")
      sudo dnf config-manager --setopt="max_parallel_downloads=10" --save
      echo "max_parallel_downloads=10 has been set."
      
      ;;
    "Set fastestmirror=True")
      sudo dnf config-manager --setopt="fastestmirror=True" --save
      echo "fastestmirror=True has been set."
      
      ;;
    "Set all options")
      sudo dnf config-manager --setopt="defaultyes=True" --setopt="max_parallel_downloads=10" --setopt="fastestmirror=True" --save
      echo "All options have been set."
      
      ;;
    "Add custom option")
      echo "Enter the name of the option you want to add (without any spaces): "
      read option_name
      echo "Enter the value of the option: "
      read option_value
      sudo dnf config-manager --setopt="$option_name=$option_value" --save
      echo "$option_name=$option_value has been added."
      
      ;;
    "Quit")
      if [ -f "start.sh" ]; then
        chmod +x start.sh
        ./start.sh
      else
        echo "The start.sh script does not exist."
      fi
      break
      ;;
    *)
      echo "Invalid choice. Please try again."
      ;;
  esac
done

echo "Configuration completed!"
