
sudo dnf swap -y ffmpeg-free ffmpeg --allowerasing
            sudo dnf groupupdate -y multimedia --setop="install_weak_deps=False" --exclude=PackageKit-gstreamer-plugin
            sudo dnf groupupdate -y sound-and-video
