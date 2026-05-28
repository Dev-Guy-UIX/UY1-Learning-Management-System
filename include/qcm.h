/**
 * @file qcm.h
 * @brief Function declarations for managing QCM questions and answer options
 * @author [Tsopdieu]
 * @date 26-05-2026
 * @rule This file shouldonly contain function declarations related to QCM management
 */

#ifndef QCM_H
#define QCM_H

/* Pull in the shared constants */
#include "syllabus.h"

// temp utils
char *generate_id() ;
void questions_to_json(Question *question, FILE *file);
void options_to_json(Option *option, FILE *file) ;

// part 1 [for_author]
int add_question(char *question_text);
Question* get_questions(char course_id[37],char chapter_id[37],char lesson_id[37]) ;
int delete_question(Lesson *lesson, int question_id) ;
int modify_question(Lesson *lesson, int question_id, const char *new_text) ;

//part 2 [for_group_memeber_2]
int add_option(Question *question, const char *option_text, int is_correct) ;
Option* get_options(int question_id) ;
//part 3 [for_group_memeber_3]
int delete_option(Question *question, int option_id) ;
int modify_option(Question *question, int option_id, const char *new_text, int is_correct) ;


// void free_questions(Question *question) ;
// void free_options(Option *option) ;



#endif