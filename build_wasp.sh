#! /bin/bash
#! /bin/bash -v

echo "CD-ing to $(dirname $0)"
cd $(dirname $0)

wasp_dir="$(pwd)/$(find -name "wasp-os" | head -1)"
wasp_libs="$(pwd)/$(find -name "wasp_libs" | head -1)" # head -1 needed because of unexplained dir copying wierdness.

echo "$wasp_dir"
echo "$wasp_libs"

cd $wasp_dir

if [[ -e "./bin-.*"  ]]
then
	echo "bins exist"
	# rm -rf ./bin-*
fi

PATH="$PATH:$wasp_libs/gcc-arm-none-eabi-10-2020-q4-major/bin/"

make submodules
make softdevice

make -j `nproc` BOARD=pinetime all

exit 0

rm -rf build
mkdir build
cd build

folderName=$(basename $PWD)
if [[ $folderName != "build" ]]
then
	echo "WARNING: not in build directory; exiting..."
	exit 1
fi

toolchain="$wasp_libs/gcc-arm-none-eabi-10.3-2021.10/"
sdk="$wasp_libs/nRF5_SDK_15.3.0_59ac345/"
echo "toolchain" "$toolchain"
echo "sdk" "$sdk"

cmake ../ -DARM_NONE_EABI_TOOLCHAIN_PATH=$toolchain -DNRF5_SDK_PATH=$sdk -DBUILD_DFU=1 -DBUILD_RESOURCES=1 -DENABLE_USERAPPS="Apps::wrapApp"
echo $(pwd)

make -j4 pinetime-mcuboot-app
