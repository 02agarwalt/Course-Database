/*
Homework 4, 600.120 Spring 2015

Tanay Agarwal
tagarwa2@jhu.edu
tagarwa2
03/11/2015
443-691-8192
*/

#include "functions.h"

/*
I have included test functions for the functions that perform specific tasks.
I use these functions in several different places in my program, so as long as
they work, I know the rest of my program should also work. I didn't make tests for
every single function because not all my functions performed specific tasks. I had
a lot of functions that simply got user input, validated it, and then called
one of my focused/specific functions, so that's why I only tested these specific
functions.
 */

void test_find()
{
  //initializing courses and linked list
  Course* testCourse = malloc(sizeof(Course));
  testCourse->depCode = 145;
  testCourse->courseCode = 150;
  Course* testCourse2 = malloc(sizeof(Course));
  testCourse2->depCode = 245;
  testCourse2->courseCode = 250;
  Node* testNode = malloc(sizeof(Node));
  testNode->coursedata = testCourse;
  Node* testNode2 = malloc(sizeof(Node));
  testNode->next = testNode2;
  testNode2->coursedata = testCourse2;
  testNode2->next = NULL;

  //first test: search for first course
  Node* testResult = find(testNode, testCourse);
  assert( (testResult->coursedata->depCode) == 145 );
  assert( (testResult->coursedata->courseCode) == 150 );

  //second test: search for second course
  Node* testResult2 = find(testNode, testCourse2);
  assert( (testResult2->coursedata->depCode) == 245 );
  assert( (testResult2->coursedata->courseCode) == 250 );

  free(testCourse2);
  free(testNode2);
  free(testCourse);
  free(testNode);
}

void test_addCourseLL()
{
  //initialize courses and linked list head
  Course* testCourse10 = malloc(sizeof(Course));
  testCourse10->index = 45050;
  Course* testCourse20 = malloc(sizeof(Course));
  testCourse20->index = 145150;
  Course* testCourse30 = malloc(sizeof(Course));
  testCourse30->index = 245250;
  Node* testNode10 = NULL;

  //add courses to form linked list
  addCourseLL(&testNode10, testCourse20);
  addCourseLL(&testNode10, testCourse10);
  addCourseLL(&testNode10, testCourse30);

  assert(testNode10->coursedata->index == 45050);
  assert(testNode10->next->coursedata->index == 145150);
  assert(testNode10->next->next->coursedata->index == 245250);
  
  free(testCourse30);
  free(testNode10->next->next);
  free(testCourse20);
  free(testNode10->next);
  free(testCourse10);
  free(testNode10);
}

void test_deleteCourseLL()
{
  //initialize everything
  Course* testCourse100 = malloc(sizeof(Course));
  testCourse100->index = 45050;
  Course* testCourse200 = malloc(sizeof(Course));
  testCourse200->index = 145150;
  Course* testCourse300 = malloc(sizeof(Course));
  testCourse300->index = 245250;
  Node* testNode100 = malloc(sizeof(Node));
  testNode100->coursedata = testCourse100;
  Node* testNode200 = malloc(sizeof(Node));
  testNode100->next = testNode200;
  testNode200->coursedata = testCourse200;
  Node* testNode300 = malloc(sizeof(Node));
  testNode200->next = testNode300;
  testNode300->coursedata = testCourse300;

  //delete nodes one by one
  deleteCourseLL(&testNode100, 145150);
  assert(testNode100->next->coursedata->index == 245250);
  deleteCourseLL(&testNode100, 245250);
  assert(testNode100->coursedata->index == 45050);
  deleteCourseLL(&testNode100, 45050);
  assert(testNode100 == NULL);
}

void test_readwrite_database()
{
  //create database of blank records
  FILE* database = fopen("test_database.dat", "w+b");
  Course* empty_course = calloc(1, sizeof(Course));
  strcpy(empty_course->div, "");
  empty_course->depCode = 0;
  empty_course->courseCode = 0;
  empty_course->credCode = 0.0;
  strcpy(empty_course->title, "");
  empty_course->index = 560001;
  fseek(database, 0, SEEK_SET);
  for (int i = 0; i < 3; i++)
    {
      fwrite(empty_course, sizeof(Course), 1, database);
    }
  fclose(database);
  database = fopen("test_database.dat", "r+b");

  //create test course
  Course* newCourse = malloc(sizeof(Course));
  newCourse->depCode = 1;
  newCourse->courseCode = 101;
  newCourse->credCode = 4.5;
  newCourse->index = 1;
  strcpy(newCourse->div, "EN");
  strcpy(newCourse->title, "Test Course");
  //write test course
  writeCourse(newCourse, database, newCourse->index);

  //create test course to read into
  Course* newCourse2 = malloc(sizeof(Course));
  readCourse(newCourse2, database, newCourse->index);

  assert(newCourse2->index == newCourse->index);
  
  free(empty_course);
  free(newCourse);
  free(newCourse2);
  fclose(database);
}

int main(void)
{
  test_find();
  test_addCourseLL();
  test_deleteCourseLL();
  test_readwrite_database();
}
