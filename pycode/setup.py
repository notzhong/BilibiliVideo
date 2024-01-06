from distutils.core import setup
from Cython.Build import cythonize

setup(name='audio', version='1.0.1', ext_modules=cythonize("meger.py"))
