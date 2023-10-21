# Note that I, Sparkles am not a Python dev, please help me expand and improve this code.
import ctypes

ATC = ctypes.CDLL("E:\!CODING\ATC\ATC\PythonWrapper\ATC.dll")

ATC.thisReturnsOne.argtypes = []
ATC.thisReturnsOne.restype = ctypes.c_int