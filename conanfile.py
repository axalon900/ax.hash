import os

from conans import ConanFile, tools

class AxhashConan(ConanFile):
    name = "ax.hash"
    version = "0.1.0"
    license = "BSD-3-Clause"
    author = "Martin Miralles-Cordal <m.mirallescordal@rutgers.edu>"
    url = "https://github.com/axalon900/ax.hash"
    description = "Simple hashing tools for using your types with hash maps and sets"
    topics = ("c++", "stl", "hash", "container")
    no_copy_source = True
    exports_sources = "include/*"
    generators = "cmake_find_package"
    build_requires = "Catch2/[~=2.9]@catchorg/stable"

    def package(self):
        self.copy("include/*.h")
        self.copy("include/*.hpp")

    def package_id(self):
        self.info.header_only()
