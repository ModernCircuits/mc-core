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

    requires = [
        "boost/1.79.0",
        "concurrentqueue/1.0.3",
        "fmt/9.0.0",
        "readerwriterqueue/1.0.6",
        "xsimd/8.1.0",
    ]

    default_options = {
        "boost:without_atomic": False,
        "boost:without_chrono": True,
        "boost:without_container": False,
        "boost:without_context": True,
        "boost:without_contract": True,
        "boost:without_coroutine": True,
        "boost:without_date_time": True,
        "boost:without_exception": False,
        "boost:without_fiber": True,
        "boost:without_filesystem": False,
        "boost:without_graph": True,
        "boost:without_graph_parallel": True,
        "boost:without_iostreams": False,
        "boost:without_json": False,
        "boost:without_locale": True,
        "boost:without_log": True,
        "boost:without_math": True,
        "boost:without_mpi": True,
        "boost:without_nowide": True,
        "boost:without_program_options": True,
        "boost:without_python": True,
        "boost:without_random": False,
        "boost:without_regex": False,
        "boost:without_serialization": True,
        "boost:without_stacktrace": True,
        "boost:without_system": False,
        "boost:without_test": True,
        "boost:without_thread": True,
        "boost:without_timer": True,
        "boost:without_type_erasure": True,
        "boost:without_wave": True,
    }

    exports = ["LICENSE.txt"]
    exports_sources = [
        "docs/*",
        "src/*",
        "tests/*",
        "cmake/*",
        "CMakeLists.txt",
    ]
    no_copy_source = True

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
        pass

    def build_requirements(self):
        if self._run_tests:
            self.test_requires("catch2/3.1.0")

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
