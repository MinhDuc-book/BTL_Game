#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SDL2_sound::SDL2_sound" for configuration "Release"
set_property(TARGET SDL2_sound::SDL2_sound APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SDL2_sound::SDL2_sound PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libSDL2_sound.dll.a"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "SDL2::SDL2"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/SDL2_sound.dll"
  )

list(APPEND _cmake_import_check_targets SDL2_sound::SDL2_sound )
list(APPEND _cmake_import_check_files_for_SDL2_sound::SDL2_sound "${_IMPORT_PREFIX}/lib/libSDL2_sound.dll.a" "${_IMPORT_PREFIX}/bin/SDL2_sound.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
