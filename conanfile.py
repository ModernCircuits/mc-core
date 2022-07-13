from conans import ConanFile, CMake


class ModernCircuitsSTL(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package", "markdown"

    requires = [
        "boost/1.79.0",
        "catch2/3.0.1",
        "concurrentqueue/1.0.3",
        "fmt/8.1.1",
        "readerwriterqueue/1.0.6",
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

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()