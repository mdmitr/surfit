PREFIX=$HOME/install
APPNAME=surfit
VERSION=3.0

echo "Building Disk Copy image"

LABELNAME="$APPNAME-$VERSION"
SCRATCHIMAGE="$APPNAME-$VERSION.dmg"

echo "Creating scratch image..."
rm -f $SCRATCHIMAGE
hdiutil create $SCRATCHIMAGE -megabytes 250 -layout NONE

# Create a /dev/disk device from the image
drive=`hdid -nomount $SCRATCHIMAGE`
echo $drive

# Create a new filesystem on the disk device
echo newfs_hfs -v "$APPNAME-$VERSION" -b 4096 ${drive}
newfs_hfs -v "$APPNAME-$VERSION" -b 4096 ${drive}

# Remount the dist
echo "Image formatted, ejecting ${drive}..."
hdiutil eject ${drive}

echo "Mounting $SCRATCHIMAGE..."
drive=`hdid $SCRATCHIMAGE`

MOUNTPOINT=`echo $drive | awk '{print $2}'`
drive=`echo $drive | awk '{print $1}'`
echo "Found $drive at $MOUNTPOINT"

echo "Copying application..."
stored_path=`pwd`
cd $MOUNTPOINT

mkdir bin
mkdir lib

cp $PREFIX/bin/surfit bin/
cp $PREFIX/lib/libtcl8.3.dylib lib/
cp $PREFIX/lib/libsstuff.dylib lib/
cp $PREFIX/lib/libsurfit.dylib lib/
cp $PREFIX/lib/libsurfit_io.dylib lib/
cp $PREFIX/lib/libglobe.dylib lib/
cp $PREFIX/lib/libfreeflow.dylib lib/
cp $stored_path/surfit.command surfit.command
cp $stored_path/run_examples.command run_examples.command
cp -r $PREFIX/share/surfit-3.0/ examples/
cp -r $PREFIX/share/doc/surfit-3.0/ doc/

cd $stored_path

echo "Ejecting..."
echo hdiutil eject ${drive}
hdiutil eject ${drive}


# Convert the image to a UDZO compressed image
#echo "Compressing..."
#echo hdiutil convert -format UDZO $SCRATCHIMAGE -o $COMPRESSEDIMAGE
#hdiutil convert -format UDZO $SCRATCHIMAGE -o $COMPRESSEDIMAGE

#echo "Removing scratch image"
#rm -f $SCRATCHIMAGE

#ls -lg $COMPRESSEDIMAGE $COMPRESSEDIMAGE.gz
