#! /bin/bash
#! /bin/bash -v

infi_dir="$(pwd)/$(find -name "InfiniTime")"
infi_libs="$(pwd)/$(find -name "infi_libs" | head -1)" # head -1 needed because of unexplained dir copying wierdness.

echo "$infi_dir"
echo "$infi_libs"

cd $infi_dir

git submodule update --init

# rm -rf build
mkdir build
cd build

folderName=$(basename $PWD)
if [[ $folderName != "build" ]]
then
	echo "WARNING: not in build directory; exiting..."
	exit 1
fi

toolchain="$infi_libs/gcc-arm-none-eabi-10.3-2021.10/"
sdk="$infi_libs/nRF5_SDK_15.3.0_59ac345/"
echo "toolchain" "$toolchain"
echo "sdk" "$sdk"

cmake ../ -DARM_NONE_EABI_TOOLCHAIN_PATH=$toolchain -DNRF5_SDK_PATH=$sdk -DBUILD_DFU=1 -DBUILD_RESOURCES=1 -DENABLE_USERAPPS="Apps::wrapApp, Apps::Paint"
echo $(pwd)

# make -j4 pinetime-mcuboot-app
make -j4 pinetime-app

/home/andrei/uniY4/IndivProj/OSes/infiniEmu/infiniemu ./src/pinetime-app*.bin
