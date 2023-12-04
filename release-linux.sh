VERSION=1.0.2.0
rm -rf ./release-linux
mkdir release-linux

cp ./src/aipgd ./release-linux/
cp ./src/aipg-cli ./release-linux/
cp ./src/qt/aipg-qt ./release-linux/
cp ./AIPGCOIN_small.png ./release-linux/

cd ./release-linux/
strip aipgd
strip aipg-cli
strip aipg-qt

#==========================================================
# prepare for packaging deb file.

mkdir aipgcoin-$VERSION
cd aipgcoin-$VERSION
mkdir -p DEBIAN
echo 'Package: aipgcoin
Version: '$VERSION'
Section: base 
Priority: optional 
Architecture: all 
Depends:
Maintainer: Aipg
Description: Aipg coin wallet and service.
' > ./DEBIAN/control
mkdir -p ./usr/local/bin/
cp ../aipgd ./usr/local/bin/
cp ../aipg-cli ./usr/local/bin/
cp ../aipg-qt ./usr/local/bin/

# prepare for desktop shortcut
mkdir -p ./usr/share/icons/
cp ../AIPGCOIN_small.png ./usr/share/icons/
mkdir -p ./usr/share/applications/
echo '
#!/usr/bin/env xdg-open

[Desktop Entry]
Version=1.0
Type=Application
Terminal=false
Exec=/usr/local/bin/aipg-qt
Name=aipgcoin
Comment= aipg coin wallet
Icon=/usr/share/icons/AIPGCOIN_small.png
' > ./usr/share/applications/aipgcoin.desktop

cd ../
# build deb file.
dpkg-deb --build aipgcoin-$VERSION

#==========================================================
# build rpm package
rm -rf ~/rpmbuild/
mkdir -p ~/rpmbuild/{RPMS,SRPMS,BUILD,SOURCES,SPECS,tmp}

cat <<EOF >~/.rpmmacros
%_topdir   %(echo $HOME)/rpmbuild
%_tmppath  %{_topdir}/tmp
EOF

#prepare for build rpm package.
rm -rf aipgcoin-$VERSION
mkdir aipgcoin-$VERSION
cd aipgcoin-$VERSION

mkdir -p ./usr/bin/
cp ../aipgd ./usr/bin/
cp ../aipg-cli ./usr/bin/
cp ../aipg-qt ./usr/bin/

# prepare for desktop shortcut
mkdir -p ./usr/share/icons/
cp ../AIPGCOIN_small.png ./usr/share/icons/
mkdir -p ./usr/share/applications/
echo '
[Desktop Entry]
Version=1.0
Type=Application
Terminal=false
Exec=/usr/bin/aipg-qt
Name=aipgcoin
Comment= aipg coin wallet
Icon=/usr/share/icons/AIPGCOIN_small.png
' > ./usr/share/applications/aipgcoin.desktop
cd ../

# make tar ball to source folder.
tar -zcvf aipgcoin-$VERSION.tar.gz ./aipgcoin-$VERSION
cp aipgcoin-$VERSION.tar.gz ~/rpmbuild/SOURCES/

# build rpm package.
cd ~/rpmbuild

cat <<EOF > SPECS/aipgcoin.spec
# Don't try fancy stuff like debuginfo, which is useless on binary-only
# packages. Don't strip binary too
# Be sure buildpolicy set to do nothing

Summary: Aipg wallet rpm package
Name: aipgcoin
Version: $VERSION
Release: 1
License: MIT
SOURCE0 : %{name}-%{version}.tar.gz
URL: https://www.aipgcoin.net/

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root

%description
%{summary}

%prep
%setup -q

%build
# Empty section.

%install
rm -rf %{buildroot}
mkdir -p  %{buildroot}

# in builddir
cp -a * %{buildroot}


%clean
rm -rf %{buildroot}


%files
/usr/share/applications/aipgcoin.desktop
/usr/share/icons/AIPGCOIN_small.png
%defattr(-,root,root,-)
%{_bindir}/*

%changelog
* Tue Aug 24 2021  Aipg Project Team.
- First Build

EOF

rpmbuild -ba SPECS/aipgcoin.spec



