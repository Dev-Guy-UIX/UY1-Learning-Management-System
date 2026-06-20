/**
 * @file qcm.h
 * @brief Function declarations for managing QCM questions and answer options
 * @author Team E (Sebastian + ArreyBeatz)
 * @date 29-05-2026
 */

#ifndef QCM_H
#define QCM_H

#include "syllabus.h"
#include "utils.h"

/* ============================================ */
/* HELPER FUNCTIONS (Internal use)              */
/* ============================================ */

char *generate_id(void);
void questions_to_json(Question *question, FILE *file);
void options_to_json(Option *option, FILE *file);

/* ============================================ */
/* PROFESSOR FUNCTIONS - Creating Quizzes       */
/* ============================================ */

int qcm_add_question(Lesson *lesson, char *question_text);
int qcm_add_option(Question *question, const char *option_text, int is_correct);
void qcm_add_keywords(Lesson *lesson, char *keywords);
Question* qcm_get_questions(char course_id[37], char chapter_id[37], char lesson_id[37]);
int qcm_delete_question(Lesson *lesson, int question_id);
int qcm_modify_question(Lesson *lesson, int question_id, const char *new_text);
Option* qcm_get_options(int question_id);
int qcm_delete_option(Question *question, int option_id);
int qcm_modify_option(Question *question, int option_id, const char *new_text, int is_correct);

/* ============================================ */
/* STUDENT FUNCTIONS - Taking Quizzes           */
/* ============================================ */

int qcm_run_quiz(Lesson *lesson);
int qcm_check_answer(Question *question, int answer_number);

/* ============================================ */
/* HELPER FUNCTIONS                             */
/* ============================================ */

int qcm_count_questions(Lesson *lesson);
void qcm_free_questions(Lesson *lesson);

#endif