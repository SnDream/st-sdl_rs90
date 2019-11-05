#!/bin/sh

mkdir -p opk
cp ./st opk/st.dge
cp ./st.png opk/st.png

echo '[Desktop Entry]
Type=Application
Name=st
Comment=Simple terminal
Exec=st.dge
Icon=st
Terminal=false
Type=Application
Categories=applications;
X-OD-NeedsDownscaling=false' > opk/default.rs90.desktop

mksquashfs ./opk st_rs90.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk
