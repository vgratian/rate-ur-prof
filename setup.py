
"""
This is a preliminary Python interface (now working console-based)
that needs to be linked to a web-framework (flask or django)
"""

from flask import Flask, session, redirect, url_for, escape, request, render_template
from ctypes import cdll, c_char_p, create_string_buffer
clib = cdll.LoadLibrary('./libfoo.so')

class Session(object):

    query = ''

    def __init__(self):
        self.obj = clib.tunnel_init()

    def talk(self):
        user_input = self.query
        clib.tunnel_start.restype = c_char_p
        arg = create_string_buffer(user_input.encode('utf-8'))
        result = clib.tunnel_start(self.obj, arg)
        return str(result)

hello = Session()
app = Flask(__name__)
hotword = ''

@app.route("/", methods=['GET', 'POST'])
def home():
    if  request.method == 'POST':
        hello.query = request.form['query']
        return redirect(url_for('home'))
    else:
        text = hello.talk()
        return text + render_template('index.html') + "\nQUERY: " + hello.query

app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'

if __name__ == "__main__":
    app.run(host='127.0.0.1',port=8888)
