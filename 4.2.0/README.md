# BurningPho3nix setup script for Fedora (Fedora 38 compatible)

This project helps you installing RPM-Fusion, making dnf.conf changes and installing applications quickly on Fedora.

______________________________________________________

Please read the README.md on older versions, if you use those, due to differences in the process
______________________________________________________

start.sh options:
- open repo-setup.sh
- open package-installer
- open dnf-mod.sh
- reboot system
______________________________________________________

repo-setup.sh gives you the option to install:
- RPM Fusion free (repo)
- RPM Fusion nonfree (repo)
- Group core (to enable downloads through software centers)
- Group multimedia & Group sound-and-video (for more codecs)
- RPM Fusion free tainted (repo)
- libdvdcss (support for copyrighted DVDs)
- RPM Fusion nonfree tainted (repo)
- all of the above
- system updates (dnf update)
- Flathub (repo) (not needed on F38 and later, if third party repos are enabled)

______________________________________________________

package-installer.sh allows you to type in programs you want installed
and it then searches for those packages with dnf and flatpak
and then installs them.
______________________________________________________

dnf-mod.sh options:
- set default answer to Yes/Y
- set maximum simultaneous downloads to 10
- bring in your own dnf.conf changes
______________________________________________________
This project has no relation the projects named above.

This needs to be enabled on start.sh:
![Screenshot from 2023-01-17 00-41-11](https://user-images.githubusercontent.com/95959450/212780926-f5806457-5b99-4c5c-9b70-ef21296ea32e.png)

after enabling the above, right-click in the folder and open it in terminal then type in ./start.sh (if you are on Gnome just right-click the start.sh file and click "run as program")
