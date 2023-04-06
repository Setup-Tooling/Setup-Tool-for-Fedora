#!/bin/bash

PS3="Please select an option: "

echo "Welcome to my DNF configuration script!"
select choice in "Set defaultyes=True" "Set max_parallel_downloads=10" "Set fastestmirror=True" "Set all options" "Add custom option" "Quit"; do
  case $choice in
    "Set defaultyes=True")
      sed -i 's/#\? *defaultyes *=.*/defaultyes=True/g' /etc/dnf/dnf.conf
      echo "defaultyes=True has been set."
      break
      ;;
    "Set max_parallel_downloads=10")
      sed -i 's/#\? *max_parallel_downloads *=.*/max_parallel_downloads=10/g' /etc/dnf/dnf.conf
      echo "max_parallel_downloads=10 has been set."
      break
      ;;
    "Set fastestmirror=True")
      sed -i 's/#\? *fastestmirror *=.*/fastestmirror=True/g' /etc/dnf/dnf.conf
      echo "fastestmirror=True has been set."
      break
      ;;
    "Set all options")
      sed -i 's/#\? *defaultyes *=.*/defaultyes=True/g' /etc/dnf/dnf.conf
      sed -i 's/#\? *max_parallel_downloads *=.*/max_parallel_downloads=10/g' /etc/dnf/dnf.conf
      sed -i 's/#\? *fastestmirror *=.*/fastestmirror=True/g' /etc/dnf/dnf.conf
      echo "All options have been set."
      break
      ;;
    "Add custom option")
      echo "Enter the name of the option you want to add (without any spaces): "
      read option_name
      echo "Enter the value of the option: "
      read option_value
      sed -i "s/#\? *$option_name *=.*/$option_name=$option_value/g" /etc/dnf/dnf.conf
      echo "$option_name=$option_value has been added."
      break
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

