#!/bin/bash

DPI=150
PDF_DESTINATION=""

help() {
echo "optimize_pdf help"
echo "-h : show this help"
echo "-d : (optional) output pdf document resolution, by default : 300"
echo "-s : pdf source file, this file must exist"
echo "-o : pdf output file"
}

full_path() {
if [ -z $1 ]; then
exit;
else
if [ `expr substr ${1:-a} 1 2` != "/" ]; then
FULL_FILE=`pwd`"/"$1
fi
fi
echo $FULL_FILE
}

isNumeric(){ echo "$@" | grep -q -v "[^0-9]" ;}

while getopts "s:o:d:h" flag
do
case $flag in
#Source : source file
"s")
PDF_FILE=`full_path $OPTARG`
if [ ! -e $PDF_FILE ]; then
echo "Please provide a valid source file"
exit=1
fi
;;
#Output : output file
"o")
PDF_DESTINATION=$OPTARG
;;
#Dpi : desired resolution
"d")
if [ -z `isNumeric $OPTARG` ]; then
DPI=$OPTARG
else
echo "Please provide a numeric value for your DPI"
exit=1
fi
;;
"h")
exit=1
;;
esac
done

#Is there a target file?
if [ -z $PDF_DESTINATION ]; then
echo "Please provide a file name for output"
exit=1
fi

#At least one error, we're not going any further
if [ $exit ]; then
help
exit
fi

pdftops \
-paper match \
-nocrop \
-noshrink \
-nocenter \
-level3 \
-q \
"$PDF_FILE" - \
| ps2pdf14 \
-dEmbedAllFonts=true \
-dUseFlateCompression=true \
-dOptimize=true \
-dProcessColorModel=/DeviceRGB \
-dUseCIEColor=true \
-r72 \
-dDownsampleGrayImages=true \
-dGrayImageResolution=$DPI \
-dAutoFilterGrayImages=false \
-dGrayImageDownsampleType=/Bicubic \
-dDownsampleMonoImages=true \
-dMonoImageResolution=$DPI \
-dMonoImageDownsampleType=/Bicubic \
-dDownsampleColorImages=true \
-dColorImageResolution=$DPI \
-dAutoFilterColorImages=false \
-dColorImageDownsampleType=/Bicubic \
-dPDFSETTINGS=/prepress \
- "$PDF_DESTINATION"

