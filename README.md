# Setup Tool for Fedora


______________________________________________________

Please read the README.md on older versions, if you use those, due to differences in the process

______________________________________________________

supported Fedora versions
- [ ] 37
- [ ] 38
- [ ] 39

______________________________________________________

supported versions
- [ ] 1.4.101c    (LTS)
- [ ] 1.4.103c    (Stable)
- [ ] 1.5.0c      (Beta)

______________________________________________________

start page options:
- repo setup
- DNF modification
- Codec Setup 
- package management
- premade scripts
- system updates (dnf update & flatpak update & snap refresh)
- system upgrade
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
- snapd
- everything above including snapd

______________________________________________________

DNF modification tool options:
- set default answer to Yes/Y
- set maximum simultaneous downloads to 10
- bring in your own dnf.conf changes
______________________________________________________

Codec Setup options:
- additional general multimedia codecs
- libdvdcss/DVD compatibility
- AMD freeworld drivers
- libva Nvidia driver
- Intel media driver

_______________________________________________________

Package Management Helper:
- install packages
- remove packages
- search for packages

______________________________________________________

Premade scripts:
- Gaming AMD
- Gaming Nvidia
- Gaming Intel
- Streaming AMD
- Streaming Nvidia
- Streaming Intel
- Office

______________________________________________________

If you installed the RPM just type "setup-tool" in the terminal!!!

NOW AVAILABLE ON COPR!!!

sudo dnf copr enable burningpho3nix/Setup-Tool -y

stable:
sudo dnf install setup-tool -y

beta:
sudo dnf install setup-tool-beta -y

LTS:
sudo dnf install setup-tool-lts -y

_______________________________________________________
DISCLAIMER

THIS PROJECT HAS NO RELATION TO THE FEDORA PROJECT NOR THE RPM FUSION PROJECT NOR TO FLATHUB NOR TO SNAPCRAFT.
FURTHERMORE THIS PROJECT HAS NO RELATION TO CANONICAL LTD., RED HAT, RED HAT CZECH, RED HAT INDIA AND IBM.

If you have any problems with software from "The Fedora Project", "RPM-Fusion", "Flathub", Canonical Ltd., "Snapcraft", any "Red Hat" Company or IBM,
please report the issue to them.
If you have issues with this program report those to us through the "Issues" category on Github.
