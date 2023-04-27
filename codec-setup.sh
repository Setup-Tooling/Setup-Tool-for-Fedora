#!/bin/bash

echo "Welcome to the my setup program!"

PS3='Please enter your choice: '

options=("Install general Codecs" "DVD support" "AMD" "Nvidia" "Intel" "Quit")
select opt in "${options[@]}"
do
 case $opt in
 "Install general Codecs")
            sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            sudo dnf groupupdate -y multimedia --setop="install_weak_deps=False" --exclude=PackageKit-gstreamer-plugin
            sudo dnf groupupdate -y sound-and-video
            ;;
            
"DVD support")
            sudo dnf install libdvdcss
            ;;
            
      "AMD")
            sudo dnf swap mesa-va-drivers mesa-va-drivers-freeworld
            sudo dnf swap mesa-vdpau-drivers mesa-vdpau-drivers-freeworld
            sudo dnf swap mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686
            sudo dnf swap mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686
            ;;
            
   "Nvidia")
            sudo dnf install nvidia-vaapi-driver
            ;;
      
   "Intel")
            sudo dnf install intel-media-driver
            ;;
      
    "Quit")
            echo "Configuration completed!"
            exit 0
            ;;
        
  *) echo "Invalid option $REPLY";;
  esac
done

echo "Thank you for using the my setup program! Goodbye."
