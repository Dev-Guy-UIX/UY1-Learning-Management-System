/**
 * @file utils.h
 * @brief Shared constants and utility function declarations used by all modules
 * @author Ulrich
 * @date 25-05-2026
 */

#ifndef UTILS_H
#define UTILS_H

/* Max number of characters in any title */
#define MAX_TITLE 150

/* Max number of characters in lesson content */
#define MAX_CONTENT 2000

/* Max number of characters in QCM question */
#define MAX_QUESTION 300

/* Max characters in one QCM answer option */
#define MAX_OPTION 150

typedef struct Course  Course;


/*lit une chaine de caractere  de facon securise*/
void press_string(char *buffer, int size);

/*lit un entier de facon securise*/
int press_int(int min, int max);

/*convertir une chaine en minuscule*/
void minuscule(char *str);

/*rechercher un mot cle dans une liste*/
void mot_cle(Course *course, const char *mot_cle);

#endif