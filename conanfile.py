# SPDX-License-Identifier: BSL-1.0

import re
import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain
from conan.tools.files import copy, load

required_conan_version = ">=1.50.0"


class ModernCircuitsCore(ConanFile):
    name = "mc-core"
    url = "https://github.com/ModernCircuits/mc-core"
    description = "Wrapper around the STL, Boost & other useful libraries."
    license = "BSL-1.0"

    settings = "os", "compiler", "build_type", "arch"

    no_copy_source = True
    exports = ["LICENSE.txt"]
    exports_sources = [
        "docs/*",
        "src/*",
        "cmake/*",
        "CMakeLists.txt",
    ]

    @property
    def _build_all(self):
        return bool(self.conf["user.build:all"])

    def set_version(self):
        path = os.path.join(self.recipe_folder, "src/CMakeLists.txt")
        content = load(self, path)
        regex = r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)"
        ver = re.search(regex, content).group(1)
        self.version = ver.strip()

    def requirements(self):
        self.requires("concurrentqueue/1.0.3")
        self.requires("fmt/9.1.0")
        self.requires("gcem/1.14.1")
        self.requires("range-v3/0.12.0")
        self.requires("readerwriterqueue/1.0.6")
        self.requires("tl-expected/1.0.0")
        self.requires("tl-optional/1.0.0")
        self.requires("xsimd/8.1.0")

        if self.settings.os != "Emscripten":
            self.requires("boost/1.80.0")

    def build_requirements(self):
        if self._build_all:
            self.test_requires("catch2/3.1.0")

    def config_options(self):
        self.options["boost"].header_only = True

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=None if self._build_all else "src")
        cmake.build()
        if self._build_all:
            cmake.test()

    def package(self):
        copy(
            conanfile=self,
            pattern="LICENSE.txt",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "licenses"),
        )

        copy(
            conanfile=self,
            pattern="*.hpp",
            src=os.path.join(self.source_folder, "src"),
            dst=os.path.join(self.package_folder, "include"),
        )

        copy(
            conanfile=self,
            pattern="*.ipp",
            src=os.path.join(self.source_folder, "src"),
            dst=os.path.join(self.package_folder, "include"),
        )

        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.names["cmake_find_package"] = "mc-core"
        self.cpp_info.names["cmake_find_package_multi"] = "mc-core"
        self.cpp_info.names["pkg_config"] = "mc-core"
        self.cpp_info.set_property("cmake_target_name", "mc::core")
