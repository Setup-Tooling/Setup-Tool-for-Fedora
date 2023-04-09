#!/bin/bash

PS3="Please select an option: "

dnf_conf="/etc/dnf/dnf.conf"

echo "Welcome to my DNF configuration script!"
select choice in "Set defaultyes=True" "Set max_parallel_downloads=10" "Set fastestmirror=True" "Set all options" "Add custom option" "Quit"; do
  case $choice in
    "Set defaultyes=True")
      echo "defaultyes=True" > /tmp/dnf_conf
      ;;
    "Set max_parallel_downloads=10")
      echo "max_parallel_downloads=10" > /tmp/dnf_conf
      ;;
    "Set fastestmirror=True")
      echo "fastestmirror=True" > /tmp/dnf_conf
      ;;
    "Set all options")
      echo "defaultyes=True" > /tmp/dnf_conf
      echo "max_parallel_downloads=10" >> /tmp/dnf_conf
      echo "fastestmirror=True" >> /tmp/dnf_conf
      ;;
    "Add custom option")
      echo "Enter the name of the option you want to add (without any spaces): "
      read option_name
      echo "Enter the value of the option: "
      read option_value
      echo "$option_name=$option_value" > /tmp/dnf_conf
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

  # If a configuration option was selected, update the dnf.conf file
  if [ -n "$choice" ]; then
    # Make a backup of the original dnf.conf file
    cp "$dnf_conf" "$dnf_conf.bak"
    # Overwrite the original dnf.conf file with the new configuration
    cat /tmp/dnf_conf >> "$dnf_conf"
    echo "$choice has been set."
    # Remove the temporary file
    rm /tmp/dnf_conf
    break
  fi
done

echo "Configuration completed!"
