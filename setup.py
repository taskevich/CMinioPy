import os
import sys
import subprocess
import shutil

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from pathlib import Path


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        super().__init__(name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            subprocess.check_output(["cmake", "--version"])
        except OSError:
            raise RuntimeError("CMake must be installed")
        super().run()

    def build_extension(self, ext):
        ext_fullpath = Path(self.get_ext_fullpath(ext.name))
        extdir = ext_fullpath.parent.resolve()

        cfg = "Release"

        build_temp = Path(self.build_temp) / ext.name.replace(".", "_")
        build_temp.mkdir(parents=True, exist_ok=True)

        cmake_args = [
            f"-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake",
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{cfg.upper()}={extdir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            f"-DCMAKE_BUILD_TYPE={cfg}",
        ]

        subprocess.check_call(["cmake", ext.sourcedir] + cmake_args, cwd=build_temp)
        subprocess.check_call(["cmake", "--build", ".", "--config", cfg], cwd=build_temp)

        if self.inplace:
            dest = Path(ext.sourcedir) / ext_fullpath.name
            shutil.copy2(extdir / ext_fullpath.name, dest)


setup(
    name="CMinioPy",
    version="0.0.1",
    author="Vadim Task : @t4skevich",
    description="Python wrapper for minio-cpp client",
    ext_modules=[CMakeExtension("cminiopy", sourcedir=".")],
    cmdclass={"build_ext": CMakeBuild},
    install_requires=["pybind11"],
    python_requires=">=3.6",
    zip_safe=False,
)
