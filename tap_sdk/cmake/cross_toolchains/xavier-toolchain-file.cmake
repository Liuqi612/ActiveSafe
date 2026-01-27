set(BUILDTOOLS_TARGET_PLATFORM "xavier")
find_package(ADBuildTools REQUIRED)
#######################
#    Project Config
#######################

#######################
#    Install Config
#######################
set(CMAKE_INSTALL_PREFIX "/opt/senseauto/tmp/senseauto-pilot-prediction")
set(CPACK_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "senseauto-msgs, senseauto-framework-sdk")

message("-- Building xavier aarch64 deb...")