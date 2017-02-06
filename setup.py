"""
This is a preliminary Python interface (now working console-based)
that needs to be linked to a web-framework (flask or django)
"""

from ctypes import cdll, c_char_p, create_string_buffer
clib = cdll.LoadLibrary('./libfoo.so')

class Session(object):
    def __init__(self):
        self.obj = clib.tunnel_init()

    def talk(self, user_input):
        clib.tunnel_start.restype = c_char_p
        arg = create_string_buffer(user_input.encode('utf-8'))
        result = clib.tunnel_start(self.obj, arg)
        return str(result)

def start_conversation():
    session = Session()
    query = ""
    reply = ""
    while query != "exit":
        reply = session.talk(query)
        print(reply)
        query = input("$ ")
    print('bye')

if __name__ == "__main__":
    start_conversation()
