from conan import ConanFile
from conan.tools.files import copy
import os

class AkpConan(ConanFile):
    name = "akp"
    version = "1.0.0"
    license = "MIT"
    author = "Akshar Miyani <miyaniakshar1234@gmail.com>"
    url = "https://github.com/miyaniakshar1234/akp"
    description = "Ultra-flashy terminal output and high-performance C/C++ development toolkit by Akshar Miyani."
    topics = ("terminal", "cli", "truecolor", "benchmark", "memory-leak-detector", "c", "cpp")
    no_copy_source = True

    def package(self):
        copy(self, "*.h", src=os.path.join(self.source_folder, "include"), dst=os.path.join(self.package_folder, "include"))

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
