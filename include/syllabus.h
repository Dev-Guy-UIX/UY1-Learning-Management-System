/**
 * @file syllabus.h
 * @brief Core data structures for the entire platform (Course, Chapter, Lesson)
 * @author Ulrich
 * @date 25-05-2026
 */

#ifndef SYLLABUS_H
#define SYLLABUS_H

/* Pull in the shared constants */
#include "utils.h"

/* =================== QCM STRUCTURES =================== */

/* One answer option for a question */
typedef struct Option
{
    char text[MAX_OPTION];
    int is_correct;
    struct Option *next;
} Option;

/* One QCM question */
typedef struct Question
{
    char text[MAX_QUESTION];
    Option *options;
    struct Question *next;
} Question;

/* =================== LESSON STRUCTURE =================== */

typedef struct Lesson
{
    int id;
    char title[MAX_TITLE];
    char content[MAX_CONTENT];
    int is_completed;
    Question *questions;
    struct Lesson *next_lesson;
} Lesson;

/* =================== CHAPTER STRUCTURE =================== */

typedef struct Chapter
{
    int id;
    char title[MAX_TITLE];
    Lesson *first_lesson;
    struct Chapter *next_chapter;
} Chapter;

/* =================== COURSE STRUCTURE =================== */

typedef struct Course
{
    char title[MAX_TITLE];
    Chapter *first_chapter;
    struct Course* next_course;
} Course;

    Course* syllabus_create_course(const char title[]);
    Chapter* syllabus_add_chapter(Course* course, const char title[]);
    Lesson* syllabus_add_lesson(Chapter* chapter, const char title[] );

#endif