import ctypes
import os

if os.name == "nt":
    ATC = ctypes.CDLL("../../ATC/build/ATC.dll")
else:
    ATC = ctypes.CDLL("../../ATC/build/ATC.so")

ATC.thisReturnsOne.argtypes = []
ATC.thisReturnsOne.restype = ctypes.c_int