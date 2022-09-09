# SPDX-License-Identifier: BSL-1.0

import re
import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain
from conan.tools.files import copy, load

# TODO remove when `CONAN_RUN_TESTS` will be replaced with a `[conf]` variable
from conans.tools import get_env


class ModernCircuitsSTL(ConanFile):
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
    def _run_tests(self):
        return get_env("CONAN_RUN_TESTS", False)

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
        self.requires("readerwriterqueue/1.0.6")
        self.requires("xsimd/8.1.0")

        if self.settings.os != "Emscripten":
            self.requires("boost/1.79.0")

    def build_requirements(self):
        if self._run_tests:
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
        cmake.configure(build_script_folder=None if self._run_tests else "src")
        cmake.build()
        if self._run_tests:
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

        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.names["cmake_find_package"] = "mc-core"
        self.cpp_info.names["cmake_find_package_multi"] = "mc-core"
        self.cpp_info.names["pkg_config"] = "mc-core"
        self.cpp_info.set_property("cmake_target_name", "mc::core")
