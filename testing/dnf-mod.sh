#!/bin/bash

# Define a function to install necessary RPMs
function install_rpms {
  dnf install -y rpmfusion-free-release rpmfusion-nonfree-release
  if [ $? -eq 0 ]; then
    echo "Successfully installed RPMs"
  else
    echo "Failed to install RPMs"
    exit 1
  fi
}

# Define a function to update DNF configuration
function update_config {
  config_file="/etc/dnf/dnf.conf"
  echo "defaultyes=$defaultyes" >> "$config_file"
  echo "max_parallel_downloads=$max_parallel_downloads" >> "$config_file"
  echo "fastestmirror=$fastestmirror" >> "$config_file"
  echo "Updated DNF configuration"
}

# Define a function to reboot the system
function reboot_system {
  echo "Rebooting system..."
  shutdown -r now
}

# Parse command line options using getopts
defaultyes=false
max_parallel_downloads=10
fastestmirror=false

while getopts "d:m:f:r" opt; do
  case $opt in
    d)
      defaultyes=true
      ;;
    m)
      max_parallel_downloads=$OPTARG
      ;;
    f)
      fastestmirror=true
      ;;
    r)
      reboot_system
      ;;
    \?)
      echo "Invalid option: -$OPTARG"
      exit 1
      ;;
  esac
done

# Call functions based on command line options
if [ $defaultyes = true ] || [ $max_parallel_downloads != 10 ] || [ $fastestmirror = true ]; then
  update_config
fi

if [ $defaultyes = true ]; then
  install_rpms
fi
