#!/bin/sh

mkdir -p opk
cp manual.txt opk/manual.txt
cp ./st opk/st.dge
cp ./st.png opk/st.png
cp -r ./terminfo_dir opk/terminfo
cp libst-preload.so opk/libst-preload.so

echo '[Desktop Entry]
Type=Application
Name=SDL Term
Comment=Simple terminal
X-OD-Manual=manual.txt
Exec=st.dge
Icon=st
Terminal=false
Type=Application
Categories=applications;
X-OD-NeedsDownscaling=false' > opk/default.rs90.desktop

mksquashfs ./opk st_rs90.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk
