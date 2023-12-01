
Debian
====================
This directory contains files used to package aipgd/aipg-qt
for Debian-based Linux systems. If you compile aipgd/aipg-qt yourself, there are some useful files here.

## aipg: URI support ##


aipg-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install aipg-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your aipg-qt binary to `/usr/bin`
and the `../../share/pixmaps/aipg128.png` to `/usr/share/pixmaps`

aipg-qt.protocol (KDE)

