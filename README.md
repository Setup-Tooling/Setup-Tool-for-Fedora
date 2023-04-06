# rpm-fusion-setup (Fedora 38 compatible)

This project helps you installing RPM-Fusion and making dnf.conf changes quickly on Fedora.

_____________________________________________________

pls read the README.md on older versions, if you use those, due to differences in the process
______________________________________________________

Script installs:
- RPM Fusion free (repo)
- RPM Fusion nonfree (repo)
- Group core (to enable downloads through software centers)
- Group multimedia & Group sound-and-video (for more codecs)
- RPM Fusion free tainted (repo)
- libdvdcss (support for copyrighted DVDs)
- RPM Fusion nonfree tainted (repo)
- Flathub (repo) (removed in 38 due to it being enabled by default in Fedora 38)
- system updates (dnf update)

There is a version which reboots your PC/laptop after installing the stuff mentioned above and one which doesn't reboot.
This project has no relation the projects named above.

This needs to be enabled:
![Screenshot from 2023-01-17 00-41-11](https://user-images.githubusercontent.com/95959450/212780926-f5806457-5b99-4c5c-9b70-ef21296ea32e.png)

after enabling the above, right-click the file and press "Run as a Programm"

Now you need to type in your password and press enter.
