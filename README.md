# rpm-fusion-setup (Fedora 38 compatible)

This project helps you installing RPM-Fusion and making dnf.conf changes quickly on Fedora.

_____________________________________________________

pls read the README.md on older versions, if you use those, due to differences in the process
______________________________________________________

Script gives you the option to install:
- RPM Fusion free (repo)
- RPM Fusion nonfree (repo)
- Group core (to enable downloads through software centers)
- Group multimedia & Group sound-and-video (for more codecs)
- RPM Fusion free tainted (repo)
- libdvdcss (support for copyrighted DVDs)
- RPM Fusion nonfree tainted (repo)
- all of the above
- system updates (dnf update)

the script gives you the option reboot

older versions still contained:
- Flathub (repo) (removed in 38 due to it being enabled by default in Fedora 38)

This project has no relation the projects named above.

This needs to be enabled:
![Screenshot from 2023-01-17 00-41-11](https://user-images.githubusercontent.com/95959450/212780926-f5806457-5b99-4c5c-9b70-ef21296ea32e.png)

after enabling the above, right-click in the and open it in terminal then type in ./start.sh
