#!/bin/sh
#
# Copyright (C) 2001 Her Majesty the Queen in Right of Canada.
# Permission to use, copy, modify and distribute this software and
# its documentation for any purpose and without fee is hereby granted,
# provided that the above copyright notice appear in all copies, that
# both the copyright notice and this permission notice appear in
# supporting documentation, and that the name of Her Majesty the Queen
# in Right  of Canada not be used in advertising or publicity pertaining
# to distribution of the software without specific, written prior
# permission.  Her Majesty the Queen in Right of Canada makes no
# representations about the suitability of this software for any purpose.
# It is provided "as is" without express or implied warranty.
#

TARGETDIR=ogdi.sourceforge.net:ftp-ogdi/.

if [ $# -lt 1 ] ; then
  echo "Usage: mkogdidist version [-install]"
  echo
  echo "Example: mkogdidist 3.1alpha"
  exit
fi

OGDI_VERSION=$1
DIST_NAME=ogdi-$OGDI_VERSION


rm -rf dist_wrk  
mkdir dist_wrk
cd dist_wrk

export CVSROOT=:pserver:anonymous@cvs.ogdi.sourceforge.net:/cvsroot/ogdi

echo "Please hit enter when prompted for a password."
cvs login

cvs checkout -P devdir

if [ \! -d devdir ] ; then
  echo "cvs checkout reported an error ... abandoning mkogdidist"
  exit
fi

find devdir -name CVS -exec rm -rf {} \;

mv devdir $DIST_NAME

echo "${OGDI_VERSION}: `date`" > $DIST_NAME/VERSION

rm -f ../${DIST_NAME}.tar.gz ../${DIST_NAME}.zip

tar cf ../${DIST_NAME}.tar ${DIST_NAME}
gzip -9 ../${DIST_NAME}.tar
zip -r ../${DIST_NAME}.zip ${DIST_NAME}

cd ..
rm -rf dist_wrk

if test "$2" = "-install" ; then
  scp ${DIST_NAME}.tar.gz $TARGETDIR
  scp ${DIST_NAME}.zip $TARGETDIR
fi
