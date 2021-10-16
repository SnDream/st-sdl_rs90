#!/bin/sh

mkdir -p opk
cp manual.txt opk/manual.txt
cp ./st opk/st.dge
cp ./st.png opk/st.png
cp -r ./terminfo_dir opk/terminfo
cp -r rs90ExtraUtils opk/rs90ExtraUtils
cp libst-preload.so opk/libst-preload.so

echo '[Desktop Entry]
Type=Application
Name=STerminal+
Comment=Simple terminal
X-OD-Manual=manual.txt
Exec=st.dge
Icon=st
Terminal=false
Type=Application
Categories=applications;
X-OD-NeedsDownscaling=false' > opk/default.rs90.desktop

echo '[Desktop Entry]
Type=Application
Name=rs90ExtraUtils
Comment=Misc Scripts for rs90
X-OD-Manual=rs90ExtraUtils/manual.txt
Exec=st.dge -e /opk/rs90ExtraUtils/rs90eu
Icon=st
Terminal=false
Type=Application
Categories=settings;
X-OD-NeedsDownscaling=false' > opk/rs90eu.rs90.desktop

echo '[Desktop Entry]
Type=Application
Name=Software Clock
Comment=Set Time & Date
Exec=st.dge -e /opk/rs90ExtraUtils/swclock
Icon=st
Terminal=false
Type=Application
Categories=settings;
X-OD-NeedsDownscaling=false' > opk/swclock.hide.desktop

mksquashfs ./opk st_rs90eu.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk
