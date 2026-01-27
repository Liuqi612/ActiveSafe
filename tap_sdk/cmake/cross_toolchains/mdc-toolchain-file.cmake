set(BUILDTOOLS_TARGET_PLATFORM "mdc")
find_package(ADBuildTools REQUIRED)

#######################
#    Project Config
#######################
set(CMAKE_INSTALL_PREFIX "/opt/senseauto/tmp/senseauto-pilot-prediction")
set(CMAKE_INSTALL_RPATH ".${CMAKE_INSTALL_PREFIX}/lib")

set(AD_CROSS_COMPILE ON)
set(LOW_END_VERSION ON)

set(NV_JETSON_FEATURE OFF)
set(CUDA_DISABLED ON)
set(OPENCV_DISABLED OFF)
set(PCL_DISABLED ON)
set(AD_PYTHON_SUPPORT OFF)

set(CXXSTD_FSLIB "stdc++fs")

#set(CROSS_SYSLIB_DIRS "${BT_SYSROOT}/usr/lib/aarch64-linux-gnu")

message("-- Building orin aarch64 deb...")
