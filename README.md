# BurningPho3nix setup script for Fedora (optimized for Fedora 38)

This project helps you installing RPM-Fusion, making dnf.conf changes and installing applications quickly on Fedora.

______________________________________________________

Please read the README.md on older versions, if you use those, due to differences in the process

______________________________________________________

start page options:
- open repo-setup.sh
- open package-installer
- open dnf-mod.sh
- system updates (dnf update & flatpak update)
- reboot system
______________________________________________________

Repo Setup gives you the options to install:
- RPM Fusion free (repo)
- RPM Fusion nonfree (repo)
- Group core (to enable downloads through software centers)
- RPM Fusion free tainted (repo)
- RPM Fusion nonfree tainted (repo)
- Flathub (repo) (not needed on F38 and later, if third party repos are enabled)
- all of the above

______________________________________________________

DNF modification tool options:
- set default answer to Yes/Y
- set maximum simultaneous downloads to 10
- bring in your own dnf.conf changes
______________________________________________________

Codec Setup options:
- additional general multimedia codecs
- libdvdcss/DVD compatibility
- AMD freeworld driver
- Nvidia vaapi driver
- Intel media driver

_______________________________________________________

Package Install Helper:
- allows you to type in programs you want installed
and it then searches for those packages with dnf and flatpak
and then installs them.
______________________________________________________

This needs to be enabled on setup.sh:
![Screenshot from 2023-01-17 00-41-11](https://user-images.githubusercontent.com/95959450/212780926-f5806457-5b99-4c5c-9b70-ef21296ea32e.png)

after that open the containing folder in terminal and type in ./setup.sh or in Gnome just right-click and "run as program"

_______________________________________________________

This version of the script still includes code from the old package-installer.sh script.

_______________________________________________________
DISCLAIMER

THIS PROJECT HAS NO RELATION TO THE FEDORA PROJECT NOR THE RPM FUSION PROJECT NOR TO FLATHUB.
FURTHERMORE THIS PROJECT HAS NO RELATION TO RED HAT, RED HAT CZECH, RED HAT INDIA AND IBM.

If you have any problems with software from "The Fedora Project", "RPM-Fusion", "Flathub", any "Red Hat" Company or IBM,
please report the issue to them.
If you have issues with the script report those to me through the "Issues" category on Github.
