/**
 * @file main.c
 * @brief Entry point of the C-LMS platform. Handles main menu and navigation
 * @author [Your Name]
 * @date 26-05-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/syllabus.h"
#include "../include/qcm.h"
#include "../include/persistence.h"
#include "../include/contenu.h"

int main() {
    char *id = generate_id();
    Question *question = malloc(sizeof(Question));
    Option *option1 = malloc(sizeof(Option));
    Option *option2 = malloc(sizeof(Option));
    Option *option3 = malloc(sizeof(Option));  
    Option *option4 = malloc(sizeof(Option));
    if (question == NULL || option1 == NULL || option2 == NULL || option3 == NULL || option4 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    strcpy(question->id, id);
    strcpy(question->text, "What is the capital of France?");
    question->options = option1;
    option1->next = option2;
    option2->next = option3;
    option3->next = option4;
    option4->next = NULL;

    option1->is_correct = 1;
    strcpy(option1->text, "Option 1");
    option2->is_correct = 0;
    strcpy(option2->text, "Option 2");
    option3->is_correct = 0;
    strcpy(option3->text, "Option 3");
    option4->is_correct = 0;
    strcpy(option4->text, "Option 4");

    FILE *file = fopen("question.json", "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }
    questions_to_json(question, file);

    return 0;
}