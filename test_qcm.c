#include <stdio.h>
#include <string.h>
#include "include/syllabus.h"
#include "include/qcm.h"

int main() {
    printf("========================================\n");
    printf("     TESTING QCM MODULE\n");
    printf("========================================\n\n");
    
    // Create a temporary lesson for testing
    Lesson test_lesson;
    strcpy(test_lesson.title, "C Programming Test");
    strcpy(test_lesson.content, "Testing the QCM module");
    test_lesson.is_completed = 0;
    test_lesson.questions = NULL;
    test_lesson.next = NULL;
    
    // Add questions
    printf("1. Adding questions...\n");
    qcm_add_question(&test_lesson, "What does printf() do?");
    qcm_add_question(&test_lesson, "Which symbol is used for pointers?");
    
    // Add options for first question
    printf("\n2. Adding options...\n");
    Question *q1 = test_lesson.questions;
    qcm_add_option(q1, "Reads input from user", 0);
    qcm_add_option(q1, "Prints output to screen", 1);
    qcm_add_option(q1, "Compiles the code", 0);
    qcm_add_option(q1, "Debugs the program", 0);
    
    // Add options for second question
    Question *q2 = test_lesson.questions->next;
    qcm_add_option(q2, "& (ampersand)", 1);
    qcm_add_option(q2, "* (asterisk)", 0);
    qcm_add_option(q2, "# (hash)", 0);
    qcm_add_option(q2, "@ (at)", 0);
    
    // Count questions
    printf("\n3. Counting questions...\n");
    int count = qcm_count_questions(&test_lesson);
    printf("   Number of questions: %d (expected: 2)\n", count);
    
    // Add keywords
    printf("\n4. Adding keywords...\n");
    qcm_add_keywords(&test_lesson, "printf,output,pointers,memory");
    
    // Run the quiz
    printf("\n========================================\n");
    printf("     STARTING QUIZ\n");
    printf("========================================\n");
    printf("Answer Question 1 with option 2\n");
    printf("Answer Question 2 with option 1\n\n");
    
    int score = qcm_run_quiz(&test_lesson);
    
    printf("\n========================================\n");
    printf("     FINAL SCORE: %d%%\n", score);
    printf("========================================\n");
    
    // Free memory
    printf("\n5. Freeing memory...\n");
    qcm_free_questions(&test_lesson);
    
    printf("\n✓ All tests completed!\n");
    return 0;
}