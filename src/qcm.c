/**
 * @file qcm.c
 * @brief Implementation of QCM logic: adding questions, recording
 *        student answers and computing quiz results
 * @author [Your Name]
 * @date 26-05-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
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