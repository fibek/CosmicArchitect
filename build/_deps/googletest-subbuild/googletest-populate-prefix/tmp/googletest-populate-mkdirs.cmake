# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-src")
  file(MAKE_DIRECTORY "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-src")
endif()
file(MAKE_DIRECTORY
  "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-build"
  "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/fibek/prog/put/sem3/prog_obiektowe/CosmicArchitect/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()