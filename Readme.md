
***Status:***

<s>Expected release date of Alfa version: January 10, 2017.</s>

*Alpha version: complete as of 16 Jan 2017!*

This is an entirely minimal version with a console based interface,
Allows users to login, register, add review and browse reviews.

*Current stage:*
Currently adapting the existing code to be compatible with ctypes,
so it can be easily linked to a Python web framework (flask/django).

Expected web release date: <s>6</s> 16 February, 2017.

*Next stage:*
Store data database (instead of plain text files as it is now).
Draw a nice HTML webpage :)

Expected full release date: 15 March 2017.

***rate ur professor:***

Here is an application/software that allows students to rate and review their
professors. The current version is designed for students of American University of Armenia,
but the software can be used for any other university as well.

I hope that it will help students to choose professors that better meet their
expectations. Constructive feedback will also help professors to improve their
teaching career.

***User Cases:***

Before Login:

1. Login:
  1. Enter email (must include domain of university)
  2. Enter password

2. Registration:
  1. Enter email (must include domain of university)
  3. Choose password

After Login:

1. Logout

2. Rate a professor
  1. Select Professor (returns list of all professors)
  2. Enter number between 1 and 5
  3. Enter feedback/review

3. Browse reviews
  1. Select Professor
