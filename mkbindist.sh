#!/bin/sh

if [ $# -lt 1 ] ; then
  echo "Usage: mkbindist.sh version [-install]"
  echo
  echo "Example: mkbindist.sh 1.1.5"
  exit
fi

VERSION=$1
PLATFORM=$TARGET

#
#	Prepare tree.
#

DIST_DIR=ogdi-${PLATFORM}-bin.${VERSION}

rm -rf $DIST_DIR
mkdir $DIST_DIR

mkdir $DIST_DIR/bin
mkdir $DIST_DIR/lib
mkdir $DIST_DIR/include
mkdir $DIST_DIR/sample

cp bin/$TARGET/*.* $DIST_DIR/bin
cp lib/$TARGET/ogdi* $DIST_DIR/lib
cp ogdi/include/*.h $DIST_DIR/include

rm -f ${DIST_DIR}.tar.gz
tar cf ${DIST_DIR}.tar ${DIST_DIR}
gzip -9 ${DIST_DIR}.tar
echo "Created: ${DIST_DIR}.tar.gz"

zip -r ${DIST_DIR}.zip $DIST_DIR
echo "Created: ${DIST_DIR}.zip"
