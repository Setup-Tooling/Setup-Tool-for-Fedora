#!/bin/bash

echo "Welcome to the my codec setup program!"

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
            sudo dnf install -y libdvdcss
            ;;
            
      "AMD")
            sudo dnf swap -y mesa-va-drivers mesa-va-drivers-freeworld
            sudo dnf swap -y mesa-vdpau-drivers mesa-vdpau-drivers-freeworld
            sudo dnf swap -y mesa-va-drivers.i686 mesa-va-drivers-freeworld.i686
            sudo dnf swap -y mesa-vdpau-drivers.i686 mesa-vdpau-drivers-freeworld.i686
            ;;
            
   "Nvidia")
            sudo dnf install -y nvidia-vaapi-driver
            ;;
      
   "Intel")
            sudo dnf install -y intel-media-driver
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
        
  *) echo "Invalid option $REPLY";;
  esac
done

echo "Thank you for using the my codec setup program! Goodbye."
