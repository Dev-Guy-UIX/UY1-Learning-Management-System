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
#include "../../include/qcm.h"

// command to install uuid library for ubuntu: sudo apt update && sudo apt install -y uuid-dev
// command to compile: gcc -o qcm_utils qcm.utils.c -luuid

// command to instsll uuid library for windows: pacman -S mingw-w64-x86_64-libuuid
// command to compile: gcc -I. main.c qcm.utils.c -o qcm.utils.exe -luuid

//if any problem found generating the id on window , use basic [int] type for the id
//this function will only be used for testing our module in the main.c file ou any other dedicated file
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

