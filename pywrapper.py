from ctypes import cdll
lib = cdll.LoadLibrary('./libfoo.so')

class Session(object):
    def __init__(self):
        self.obj = lib.Session_new()

hello = Session()
