#! /bin/bash

# probably "./sus.cpp or something"
infi_wrapApp=$(pwd)/$(find -name "wrapApp.cpp" | head -1)
infi_wrapApph=$(pwd)/$(find -name "wrapApp.h" | head -1)
foreign_app=$(pwd)/$(find -name "externApp.cpp" | head -1)
compat_lib=$(pwd)/$(find -name "compat.cpp" | head -1)

echo "infi_wrapApp" $infi_wrapApp
echo "infi_wrapApph" $infi_wrapApph
echo "foreign_app" $foreign_app
echo "compat_lib" $compat_lib

infi_dir=$(find -name "InfiniTime")

ensure_file () {
	if [[ -L $2 ]] || [[ -e $2 ]]
	then
		echo "$2 exists"
	else
		echo "$2 not exists"
		# ln -s $1 $2
		cp $1 $2
	fi
}

# wrapApp calls externApp which uses compat.cpp

ensure_file $infi_wrapApp "$infi_dir/src/displayapp/screens/wrapApp.cpp"
ensure_file $infi_wrapApph "$infi_dir/src/displayapp/screens/wrapApp.h"
ensure_file $foreign_app "$infi_dir/src/displayapp/apps/externApp.cpp"
ensure_file $compat_lib "$infi_dir/src/compat.cpp"

# sed 's/static constexpr int nScreens = 2;/static constexpr int nScreens = 3;/' $infi_dir/src/displayapp/screens/ApplicationList.h
