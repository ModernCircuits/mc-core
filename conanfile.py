# SPDX-License-Identifier: BSL-1.0

import re
import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import copy, load
from conan.tools.build import check_min_cppstd


required_conan_version = ">=2.0.0"


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

    generators = "CMakeDeps"

    def set_version(self):
        path = os.path.join(self.recipe_folder, "src/CMakeLists.txt")
        content = load(self, path)
        regex = r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)"
        ver = re.search(regex, content).group(1)
        self.version = ver.strip()

    def validate(self):
        check_min_cppstd(self, "20")

    def requirements(self):
        self.requires("concurrentqueue/1.0.3")
        self.requires("fmt/9.1.0")
        self.requires("gcem/1.16.0")
        self.requires("range-v3/0.12.0")
        self.requires("tl-expected/20190710")
        self.requires("tl-optional/1.0.0")
        self.requires("xsimd/10.0.0")

        if self.settings.os != "Emscripten":
            self.requires("boost/1.81.0")

        self.test_requires("catch2/3.3.1")

    def config_options(self):
        self.options["boost"].header_only = True

    def layout(self):
        skip_tests = self.conf.get("tools.build:skip_test", default=False)
        cmake_layout(self, src_folder="src" if skip_tests else ".")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
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

    def imports(self):
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)
