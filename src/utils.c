/**
 * @file utils.c
 * @brief Implementation of utility functions: string manipulation,
 *        keyword search and user input validation
 * @author Ange
 * @date 26-05-2026
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #include "../include/utils.h"
 #include "../include/syllabus.h"


void press_string(char *buffer, int size){
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

/*lit un entier de facon securise*/
int press_int(int min, int max){
    int value;
    char buffer[64];

    while (1)
    {
          fgets(buffer, sizeof(buffer),stdin);
          if (sscanf(buffer, "%d", &value)==1){
            if(value>= min && value <= max){
                return value;
            }
          }
          printf("Entree invalide. Entrez un nombre entre %d et d%", min, max);
    }
    
}

/*convertir une chaine en minuscule*/
void minuscule(char *str){
    for (int i = 0; str[i] != '\0'; i++){
        str[i] = tolower((unsigned char)str[i]); 
    }
}

/*rechercher un mot cle dans une liste*/

void mot_cle(Course *course, const char *mot_cle) {
    char kw_lower[MAX_TITLE] ;
    char title_lower[MAX_TITLE] ;
    int found = 0 ;

    strncpy(kw_lower, mot_cle, MAX_TITLE - 1) ;
    kw_lower[MAX_TITLE - 1] = '\0' ;
    minuscule(kw_lower) ;

    printf(" \n=== Résultats pour %s  ===\n ", mot_cle) ;

    /* Parcourt les chapitres avec un pointeur */
    Chapter *chap = course->chapters ;
  while (chap != NULL) {

        /* Parcourt les leçons avec un pointeur */
        Lesson *lesson = chap->lessons ;
        while (lesson != NULL) {

            strncpy(title_lower, lesson->title, MAX_TITLE - 1) ;
            title_lower[MAX_TITLE - 1] = '\0' ;
            minuscule(title_lower) ;

            if (strstr(title_lower, kw_lower) != NULL) {
                printf( " Chapitre : %s — Leçon : %s\n ",chap->title, lesson->title) ;
                found++ ;
            }

            lesson = lesson->next ; /* leçon suivante */
        }

        chap = chap->next ; /* chapitre suivant */
    }

    if (found == 0){
        printf("   Aucun résultat.\n ") ;
    }
    else {
        printf("%d résultat(s) trouvé(s).\n ", found);
         
    }     
}

