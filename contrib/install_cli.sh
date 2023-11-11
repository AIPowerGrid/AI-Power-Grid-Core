 #!/usr/bin/env bash

 # Execute this file to install the aipg cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%AIPG-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/AIPG-Qt.app/Contents/MacOS/aipgd /usr/local/bin/aipgd
 sudo ln -s ${LOCATION}/AIPG-Qt.app/Contents/MacOS/aipg-cli /usr/local/bin/aipg-cli
