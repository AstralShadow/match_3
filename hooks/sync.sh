#!/bin/bash
# Assures that an assets subdir changes are preserved
# Takes one argument - the expression that captures the
#  files. An example: sync.sh map/*.map


echo
echo Syncing changes in $1

if [ ! -d $ASSETS_DIR/$(dirname $1) ]; then
    echo "Can't find $ASSETS_DIR/$(dirname $1)"
    exit
fi

if [ ! -d $BDIR/$ASSETS_DIR/$(dirname $1) ]; then
    echo "Can't find $BDIR/$ASSETS_DIR/$(dirname $1)"
    exit
fi


for file in $BDIR/$ASSETS_DIR/$1; do
    origin=$ASSETS_DIR/$(dirname $1)/$(basename $file)
    if ! cmp -s "$file" "$origin"; then
        echo "Updating $origin"
        cp $file $origin
    fi
done

