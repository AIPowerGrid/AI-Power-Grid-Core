#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

AIPGD=${AIPGD:-$SRCDIR/aipgd}
AIPGCLI=${AIPGCLI:-$SRCDIR/aipg-cli}
AIPGTX=${AIPGTX:-$SRCDIR/aipg-tx}
AIPGQT=${AIPGQT:-$SRCDIR/qt/aipg-qt}

[ ! -x $AIPGD ] && echo "$AIPGD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
aipgVER=($($AIPGCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for aipgd if --version-string is not set,
# but has different outcomes for aipg-qt and aipg-cli.
echo "[COPYRIGHT]" > footer.h2m
$AIPGD --version | sed -n '1!p' >> footer.h2m

for cmd in $AIPGD $AIPGCLI $AIPGTX $AIPGQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${aipgVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${aipgVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
