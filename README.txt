Homework 4, 600.120 Spring 2015

Tanay Agarwal
tagarwa2@jhu.edu
tagarwa2
03/11/2015
443-691-8192

To compile the program, type "make" in the command line.
To run tests, type "make test".
To run the program, type ./hw4 databasename.dat < directives.txt
where databasename.dat is the database file that either already
exists or you want created, and directives.txt is a plain text file
which contains a list of input for the program to process.

Please do not mess with any of the files included in the zip. The
test function will create a new database file, don't let it scare you.

Here is what the menu of options looks like:

0. Quit
1. Create new courses from a plain text file (enter file name)
2. Add a single course to the database (enter course data)
3. Display details of particular course (enter department and course number: ddd.nnn)
4. Display all actual courses in database
5. Change the name of a course (enter ddd.nnn and new course name
6. Delete a course from the database (enter department and course number: ddd.nnn)
7. Add a course to a semester listing (enter semester, department, course number, letter grade in upper case)
8. Remove a course from a semester listing (enter semester, department, course number, letter grade)
9. Display a semester listing (enter semester number)

When you enter an option, you must include the relevant data
associated with that operation on the same line. Each line of input
should have all the necessary information for the operation
to take place.