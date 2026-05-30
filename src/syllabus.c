/**
 * @file syllabus.c
 * @brief Implementation of course structure management using linked lists.
 *        Handles creation, deletion and recursive display of chapters and lessons
 * @author [Your Name]
 * @date 26-05-2026
 */
#include "../include/syllabus.h"
#include<stdlib.h>
#include<string.h>
#include <stdio.h>

//Helper to safely copy strings and avoid overflow

    static void safe_strcpy(char* dest, const char* src, size_t max_len)
{
   if(!dest || !src) return;
   strncpy(dest, src, max_len-1); 
   dest[max_len -1 ] = '\0';
}
// Creat Course
    Course* syllabus_create_course(const char title[]){
        Course* new_course = malloc(sizeof(Course));
        if(!new_course){
            fprintf( stderr, "Error: failed to allocate Memory for Course\n");
            return NULL;
        }
        safe_strcpy(new_course->title, title, MAX_TITLE);
        new_course -> first_chapter = NULL;
        new_course -> next_course = NULL;
        return new_course;
    }


    Chapter* syllabus_add_chapter(Course* course, const char title[]){
        if(!course || !title) {
            fprintf(stderr, "Error: Empty course or title\n");
            return NULL;
        }
        Chapter* new_chap = malloc(sizeof(Chapter));
        if(!new_chap){
            fprintf(stderr, "Error failed to allocate memory for Chapter\n");
            return NULL;

        }
        safe_strcpy(new_chap->title, title, MAX_TITLE);
        new_chap->first_lesson = NULL;
        new_chap->next_chapter =NULL;
        if(course->first_chapter == NULL){
            course->first_chapter = new_chap;
        } else {
            Chapter* current = course->first_chapter;
            while (current->next_chapter != NULL) {
                current = current->next_chapter;
            }
            current -> next_chapter = new_chap;
        }
        return new_chap;
    }
    Lesson* syllabus_add_lesson(Chapter* chapter, const char title[]){
        if (!chapter || !title){
            fprintf(stderr, "Error: NULL chapter or tilte\n");
            return NULL;
        }
        Lesson* new_lesson = malloc(sizeof(Lesson));
        if(!new_lesson){
            fprintf(stderr, "Error: malloc failed for Lesson\n");
            return NULL;
        }
        new_lesson->id = 1; // TODO : auto-increment later
        safe_strcpy(new_lesson->title , title , MAX_TITLE);
        new_lesson->content[0] = '\0';
        new_lesson->is_completed = 0;
        new_lesson->questions = NULL;
        new_lesson->next_lesson= NULL;

        //Append to the end of the first_lessons list
        if(chapter->first_lesson == NULL) {
            chapter->first_lesson = new_lesson;
        } else {
            Lesson* current = chapter->first_lesson;
            while(current->next_lesson  != NULL) {
                current = current->next_lesson;
            }
            current ->next_lesson = new_lesson;
        }
        return new_lesson;
    }
/*
*/
void syllabus_delete_lesson(Chapter* chapter, Lesson* lesson){
    if(!chapter || !lesson) return;
    // Case 1: Delete first lesson
    if(chapter->first_lesson == lesson){
        chapter->first_lesson = lesson->next_lesson;
        free(lesson);
        return;
    }
    // Case 2: Delete middle/end -find previous node
    Lesson* current = chapter-> first_lesson;
    while(current && current->next_lesson) {
        current = current->next_lesson;
    }
    if(current && current->next_lesson == lesson){
        current->next_lesson = lesson->next_lesson;
        free(lesson);
    }
}
/*
*/
void syllabus_rename_lesson(Lesson* lesson, const char new_title[]){
    if(!lesson || !new_title) return;
    safe_strcpy(lesson -> title, new_title, MAX_TITLE);
}
