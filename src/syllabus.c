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
        new_course -> chapters = NULL;
        new_course -> next = NULL;
        return new_course;
    }