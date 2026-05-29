/**
 * @file persistence.c
 * @brief Implementation of JSON read/write functions for saving and
 *        loading the full course structure to and from database.json
 * @author [Your Name]
 * @date 26-05-2026
 */
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "persistence.h"
#include "utils.h"
#include "syllabus.h"

void save_course(Course *course, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "{\n\"chapters\":[\n");

    Chapter *ch = course->chapters;

    while (ch) {
        fprintf(f,
            "{\n\"title\":\"%s\",\n\"lessons\":[\n",
            ch->title
        );

        Lesson *ls = ch->lessons;

        while (ls) {
            fprintf(f,
                "{\n\"title\":\"%s\",\n\"questions\":[\n",
                ls->title
            );

            Question *q = ls->questions;

            while (q) {
                fprintf(f,
                    "{\n\"text\":\"%s\",\n\"options\":[",
                    q->text
                );

                for (int i = 0; i < q->option_count; i++) {
                    fprintf(f, "\"%s\"", q->options[i]);
                    if (i < q->option_count - 1)
                        fprintf(f, ",");
                }

                fprintf(f,
                    "],\"answer\":%d\n}",
                    q->answer
                );

                if (q->next) fprintf(f, ",");
                q = q->next;
            }

            fprintf(f, "\n]\n}");

            if (ls->next) fprintf(f, ",");
            ls = ls->next;
        }

        fprintf(f, "\n]\n}");

        if (ch->next) fprintf(f, ",");
        ch = ch->next;
    }

    fprintf(f, "\n]\n}\n");

    fclose(f);
}