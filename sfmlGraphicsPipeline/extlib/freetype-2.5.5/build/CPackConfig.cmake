# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "C:/Users/gabri/Documents/dev/infographique2/sfmlGraphicsPipeline/extlib/freetype-2.5.5;C:/Users/gabri/Documents/dev/infographique2/sfmlGraphicsPipeline/extlib/freetype-2.5.5/build")
set(CPACK_CMAKE_GENERATOR "MinGW Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.31/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "freetype built using CMake")
set(CPACK_GENERATOR "TGZ")
set(CPACK_INNOSETUP_ARCHITECTURE "x86")
set(CPACK_INSTALL_CMAKE_PROJECTS "C:/Users/gabri/Documents/dev/infographique2/sfmlGraphicsPipeline/extlib/freetype-2.5.5/build;freetype;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/freetype")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "freetype 2.5.5}")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "freetype 2.5.5}")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "C:/MinGW/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "C:/MinGW/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "C:/Users/gabri/Documents/dev/infographique2/sfmlGraphicsPipeline/extlib/freetype-2.5.5/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/Program Files/CMake/share/cmake-3.31/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "freetype")
set(CPACK_PACKAGE_FILE_NAME "freetype-2.5.5}-win32")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "freetype 2.5.5}")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "freetype 2.5.5}")
set(CPACK_PACKAGE_NAME "freetype")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "2.5.5}")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "5")
set(CPACK_PACKAGE_VERSION_PATCH "5}")
set(CPACK_READELF_EXECUTABLE "C:/MinGW/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "C:/Program Files/CMake/share/cmake-3.31/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "C:/Program Files/CMake/share/cmake-3.31/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/Program Files/CMake/share/cmake-3.31/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/.svn/;.swp$;.#;/#;/build/;/serial/;/ser/;/parallel/;/par/;~;/preconfig.out;/autom4te.cache/;/.config")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/gabri/Documents/dev/infographique2/sfmlGraphicsPipeline/extlib/freetype-2.5.5/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "freetype-2.5.5-r")
set(CPACK_SYSTEM_NAME "win32")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win32")
set(CPACK_WIX_SIZEOF_VOID_P "4")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/gabri/Documents/dev/infographique2/sfmlGraphicsPipeline/extlib/freetype-2.5.5/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
