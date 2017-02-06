
***Rate Ur Prof:***

Here is an software that allows students to rate and review their professors.
Because we think that it will help students to choose professors/classes that
are closer to their needs /expectations. Constructive feedback will also help
professors to improve their teaching skills.

This is just a development release with a very "underdeveloped" web-interface
and there are still mane bugs. See *Status* for more details.

***How to run***
On Linux:
  * (If you haven't pip3 on your machine) sudo apt-get install python3-pip
  * pip3 install -r requirements.txt
  * pip3 make all
  * python3 setup.py

Now go to http://127.0.0.1:5000/ on your browser :)

***Status:***

*Preliminary version: complete as of 6 Feb 2017!*

This is an entirely minimal version with still a lot of open questions and bugs.
Allows users to login, register, add review and browse reviews.

*Current stage:*
Currently working on a more or less working user interface (Flask - a Python
web framework) that can easily run on the top of the C++ main code.

*Next stage:*
Store data database (instead of plain text files as it is now).
Draw a nice HTML webpage :)

Expected full beta date: 15 March 2017.
