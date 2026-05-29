/**
 * @file qcm.c
 * @brief Implementation of QCM logic: adding questions, recording
 *        student answers and computing quiz results
 * @author [Your Name]
 * @date 26-05-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <uuid/uuid.h>  // Commented out by ArreyBeatz (29-05-2026) - UUID library not available on Windows
#include "../include/qcm.h"

// command to install uuid library for ubuntu: sudo apt update && sudo apt install -y uuid-dev
// command to compile: gcc -o qcm_utils qcm.utils.c -luuid

// command to instsll uuid library for windows: pacman -S mingw-w64-x86_64-libuuid
// command to compile: gcc -I. main.c qcm.utils.c -o qcm.utils.exe -luuid

//if any problem found generating the id on window , use basic [int] type for the id
//this function will only be used for testing our module in the main.c file ou any other dedicated file

#define T1 "\t"
#define T2 "\t\t"
#define T3 "\t\t\t"
#define T4 "\t\t\t\t"
#define T5 "\t\t\t\t\t"
#define T6 "\t\t\t\t\t\t"
#define T7 "\t\t\t\t\t\t\t"
#define T8 "\t\t\t\t\t\t\t\t"



// Sebastian's original UUID version (commented out by ArreyBeatz on 29-05-2026 because UUID library not available on Windows Git Bash)

/*
char *generate_id() {
    uuid_t id;
    uuid_generate(id);

    char *buffer = malloc(37 * sizeof(char));
    if (buffer == NULL) {
        printf(" Memory allocation failed (generate_id).\n");
        return NULL;
    }

    uuid_unparse(id, buffer);
    return buffer;
}
*/


// New version added by ArreyBeatz (29-05-2026) - uses simple counter, no external library needed (works without UUID library)
static int id_counter = 1;

char *generate_id(void) {
    char *buffer = malloc(37 * sizeof(char));
    if (buffer == NULL) {
        printf("Memory allocation failed (generate_id).\n");
        return NULL;
    }
    
    // Create a simple ID like "Q001", "Q002", etc.
    snprintf(buffer, 37, "Q%03d", id_counter++);
    return buffer;
}



void questions_to_json(Question *question, FILE *file) {
    Question *head = question;
    while(head!=NULL){
    Option *option_head = head->options;
    fprintf(file, "%s{\n", T5);
    fprintf(file, "%s\"id\":\"%s\",\n", T6, head->id);
    fprintf(file, "%s\"text\":\"%s\",\n", T6, head->text);
    fprintf(file, "%s\"options\":[\n",T6);
    options_to_json(option_head, file);
    fprintf(file, "%s]\n", T6);
    fprintf(file, "%s}", T5);
    if(head->next!=NULL){
        fprintf(file, ",");
    };
    fprintf(file, "\n");
    head = head->next;
    }
}
void options_to_json(Option *option, FILE *file){
    Option *head=option;
        while(head!=NULL){
            fprintf(file, "%s{\n", T7);
            fprintf(file,"%s\"text\":\"%s\",\n", T8, head->text);
            fprintf(file, "%s\"is_correct\":%d\n", T8, head->is_correct);
            fprintf(file, "%s}", T7);
            if(head->next!=NULL){
                fprintf(file, ",");
            };
            fprintf(file, "\n");
            head=head->next;
        };
}





/* ============================================ */
/* PROFESSOR FUNCTIONS - Creating Quizzes       */
/* ============================================ */

int qcm_add_question(Lesson *lesson, char *question_text) {
    if (lesson == NULL) {
        printf("Error: Lesson does not exist!\n");
        return -1;
    }
    
    Question *new_q = (Question*)malloc(sizeof(Question));
    if (new_q == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    
    char *id = generate_id();
    strncpy(new_q->id, id, 36);
    new_q->id[36] = '\0';
    free(id);
    
    strncpy(new_q->text, question_text, MAX_QUESTION - 1);
    new_q->text[MAX_QUESTION - 1] = '\0';
    new_q->options = NULL;
    new_q->next = NULL;
    
    if (lesson->questions == NULL) {
        lesson->questions = new_q;
    } else {
        Question *current = lesson->questions;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_q;
    }
    
    printf("✓ Question added: %s (ID: %s)\n", question_text, new_q->id);
    return 0;
}

int qcm_add_option(Question *question, const char *option_text, int is_correct) {
    if (question == NULL) {
        printf("Error: Question does not exist!\n");
        return -1;
    }
    
    Option *new_opt = (Option*)malloc(sizeof(Option));
    if (new_opt == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    
    strncpy(new_opt->text, option_text, MAX_OPTION - 1);
    new_opt->text[MAX_OPTION - 1] = '\0';
    new_opt->is_correct = is_correct;
    new_opt->next = NULL;
    
    if (question->options == NULL) {
        question->options = new_opt;
    } else {
        Option *current = question->options;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_opt;
    }
    
    printf("  ✓ Option added: %s %s\n", option_text, is_correct ? "(CORRECT)" : "");
    return 0;
}

void qcm_add_keywords(Lesson *lesson, char *keywords) {
    if (lesson == NULL) return;
    strncat(lesson->content, "\n[KEYWORDS: ", MAX_CONTENT - strlen(lesson->content) - 1);
    strncat(lesson->content, keywords, MAX_CONTENT - strlen(lesson->content) - 1);
    //strncat(lesson->content, "]", 1);
    
    // Instead of strncat(lesson->content, "]", 1);
int len = strlen(lesson->content);
if (len < MAX_CONTENT - 1) {
    lesson->content[len] = ']';
    lesson->content[len + 1] = '\0';
}
    printf("✓ Keywords added: %s\n", keywords);
}

/* Stub functions for delete/modify (can be completed later) */
Question* qcm_get_questions(char course_id[37], char chapter_id[37], char lesson_id[37]) {
    (void)course_id; (void)chapter_id; (void)lesson_id;
    printf("Warning: qcm_get_questions not fully implemented yet\n");
    return NULL;
}

int qcm_delete_question(Lesson *lesson, int question_id) {
    (void)lesson; (void)question_id;
    printf("Warning: qcm_delete_question not fully implemented yet\n");
    return -1;
}

int qcm_modify_question(Lesson *lesson, int question_id, const char *new_text) {
    (void)lesson; (void)question_id; (void)new_text;
    printf("Warning: qcm_modify_question not fully implemented yet\n");
    return -1;
}

Option* qcm_get_options(int question_id) {
    (void)question_id;
    printf("Warning: qcm_get_options not fully implemented yet\n");
    return NULL;
}

int qcm_delete_option(Question *question, int option_id) {
    (void)question; (void)option_id;
    printf("Warning: qcm_delete_option not fully implemented yet\n");
    return -1;
}

int qcm_modify_option(Question *question, int option_id, const char *new_text, int is_correct) {
    (void)question; (void)option_id; (void)new_text; (void)is_correct;
    printf("Warning: qcm_modify_option not fully implemented yet\n");
    return -1;
}

/* ============================================ */
/* STUDENT FUNCTIONS - Taking Quizzes           */
/* ============================================ */

int qcm_run_quiz(Lesson *lesson) {
    if (lesson == NULL || lesson->questions == NULL) {
        printf("No questions available for this lesson.\n");
        return 0;
    }
    
    int total = 0, correct = 0;
    Question *current_q = lesson->questions;
    
    printf("\n╔════════════════════════════════════╗\n");
    printf("║         QUIZ: %-20s ║\n", lesson->title);
    printf("╚════════════════════════════════════╝\n\n");
    
    while (current_q != NULL) {
        total++;
        printf("Question %d: %s\n", total, current_q->text);
        printf("----------------------------------------\n");
        
        Option *current_opt = current_q->options;
        int opt_num = 1, correct_option_num = 0;
        
        while (current_opt != NULL) {
            printf("  %d. %s\n", opt_num, current_opt->text);
            if (current_opt->is_correct) correct_option_num = opt_num;
            current_opt = current_opt->next;
            opt_num++;
        }
        
        int answer;
        printf("\nYour answer (1-%d): ", opt_num - 1);
        scanf("%d", &answer);
        
        if (answer == correct_option_num) {
            printf("✓ CORRECT!\n\n");
            correct++;
        } else {
            printf("✗ WRONG! Correct answer was %d\n\n", correct_option_num);
        }
        
        current_q = current_q->next;
    }
    
    int score = (correct * 100) / total;
    printf("╔════════════════════════════════════╗\n");
    printf("║ Score: %d/%d (%d%%)                ║\n", correct, total, score);
    printf("╚════════════════════════════════════╝\n");
    
    if (score >= 70 && !lesson->is_completed) {
        lesson->is_completed = 1;
        printf("\n🎉 Lesson marked as completed!\n");
    }
    
    return score;
}

int qcm_check_answer(Question *question, int answer_number) {
    if (question == NULL || question->options == NULL) return 0;
    Option *current = question->options;
    int opt_num = 1;
    while (current != NULL) {
        if (opt_num == answer_number) return current->is_correct;
        current = current->next;
        opt_num++;
    }
    return 0;
}

/* ============================================ */
/* HELPER FUNCTIONS                             */
/* ============================================ */

int qcm_count_questions(Lesson *lesson) {
    if (lesson == NULL || lesson->questions == NULL) return 0;
    int count = 0;
    Question *current = lesson->questions;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void qcm_free_questions(Lesson *lesson) {
    if (lesson == NULL || lesson->questions == NULL) return;
    
    Question *current_q = lesson->questions;
    while (current_q != NULL) {
        Option *current_opt = current_q->options;
        while (current_opt != NULL) {
            Option *temp_opt = current_opt;
            current_opt = current_opt->next;
            free(temp_opt);
        }
        Question *temp_q = current_q;
        current_q = current_q->next;
        free(temp_q);
    }
    lesson->questions = NULL;
    printf("✓ Questions and options freed from memory.\n");
}