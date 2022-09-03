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
        self.requires("fmt/9.0.0")
        self.requires("readerwriterqueue/1.0.6")
        self.requires("xsimd/8.1.0")

        if self.settings.os != "Emscripten":
            self.requires("boost/1.79.0")

    def build_requirements(self):
        if self._run_tests:
            self.test_requires("catch2/3.1.0")

    def config_options(self):
        self.options["boost"].without_atomic = False
        self.options["boost"].without_chrono = True
        self.options["boost"].without_container = False
        self.options["boost"].without_context = True
        self.options["boost"].without_contract = True
        self.options["boost"].without_coroutine = True
        self.options["boost"].without_date_time = True
        self.options["boost"].without_exception = False
        self.options["boost"].without_fiber = True
        self.options["boost"].without_filesystem = False
        self.options["boost"].without_graph = True
        self.options["boost"].without_graph_parallel = True
        self.options["boost"].without_iostreams = False
        self.options["boost"].without_json = False
        self.options["boost"].without_locale = True
        self.options["boost"].without_log = True
        self.options["boost"].without_math = True
        self.options["boost"].without_mpi = True
        self.options["boost"].without_nowide = True
        self.options["boost"].without_program_options = True
        self.options["boost"].without_python = True
        self.options["boost"].without_random = False
        self.options["boost"].without_regex = False
        self.options["boost"].without_serialization = True
        self.options["boost"].without_stacktrace = True
        self.options["boost"].without_system = False
        self.options["boost"].without_test = True
        self.options["boost"].without_thread = True
        self.options["boost"].without_timer = True
        self.options["boost"].without_type_erasure = True
        self.options["boost"].without_wave = True

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
