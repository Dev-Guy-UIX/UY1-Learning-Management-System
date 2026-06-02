#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contenu.h"

/* affiche la liste des lecons d'un chapitre avec leur statut */
void contenu_list_lessons(Chapter *chapter) {
    if (chapter == NULL) {
        printf("Erreur : chapitre introuvable.\n");
        return;
    }

    printf("\nLecons du chapitre : %s\n", chapter->title);

    Lesson *lecon = chapter->lessons;

    if (lecon == NULL) {
        printf("Aucune lecon dans ce chapitre.\n");
        return;
    }

    while (lecon != NULL) {
        if (lecon->is_completed == 1) {
            printf("  %d. [TERMINE] %s\n", lecon->id, lecon->title);
        } else {
            printf("  %d. [EN COURS] %s\n", lecon->id, lecon->title);
        }
        lecon = lecon->next;
    }
}

/* affiche le contenu d'une lecon */
void contenu_display_lesson(Lesson *lesson) {
    if (lesson == NULL) {
        printf("Erreur : leçon introuvable.\n");
        return;
    }
    printf("\n :LECON : %s\n", lesson->title);
    printf("%s\n", lesson->content);
    printf("\n");
}

/* marque une lecon comme terminee */
void contenu_mark_completed(Lesson *lesson) {
    if (lesson != NULL) {
        lesson->is_completed = 1;
        printf("Lecon \"%s\" marquee comme terminee !\n", lesson->title);
    }
}

/* Compte et affiche combien de lecons sont terminees */
void contenu_show_progress(Course *course) {
    if (course == NULL) {
        printf("Erreur : cours introuvable.\n");
        return;
    }

    int total = 0;
    int terminees = 0;

    Chapter *chapitre = course->chapters;
    while (chapitre != NULL) {
        Lesson *lecon = chapitre->lessons;
        while (lecon != NULL) {
            total++;
            if (lecon->is_completed == 1) {
                terminees++;
            }
            lecon = lecon->next;
        }
        chapitre = chapitre->next;
    }

    printf("\n Progression : %s \n", course->title);
    printf("Lecons terminees : %d / %d\n", terminees, total);

    if (total > 0) {
        int largeur = 20;
        int rempli = (terminees * largeur) / total;
        printf("[");
        for (int i = 0; i < largeur; i++) {
            if (i < rempli) {
                printf("#");
            } else {
                printf("-");
            }
        }
        printf("]\n");
    }
}

/* permet a l'etudiant de naviguer dans un chapitre */
void contenu_browse_chapter(Chapter *chapter) {
    if (chapter == NULL) {
        printf("Erreur : chapitre introuvable.\n");
        return;
    }

    int choix;
    while (1) {
        contenu_list_lessons(chapter);
        printf("\n0. Retour au menu principal\n");
        printf("Votre choix (numero de la lecon) : ");
        
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choix == 0) {
            break;
        }

        Lesson *lecon = chapter->lessons;
        int trouve = 0;
        while (lecon != NULL) {
            if (lecon->id == choix) {
                trouve = 1;
                contenu_display_lesson(lecon);

                if (lecon->is_completed == 0) {
                    printf("Marquer comme terminee ? (1=Oui / 0=Non) : ");
                    int rep;
                    if (scanf("%d", &rep) == 1 && rep == 1) {
                        contenu_mark_completed(lecon);
                    }
                    while (getchar() != '\n');
                }
                break;
            }
            lecon = lecon->next;
        }

        if (!trouve) {
            printf("Numero invalide, reessayez.\n");
        }
    }
}

/* menu principal etudiant : choisir un chapitre */
void contenu_browse_course(Course *course) {
    if (course == NULL) {
        printf("Erreur : cours introuvable.\n");
        return;
    }

    int choix;
    while (1) {
        printf("\n Cours : %s \n", course->title);
        
        Chapter *chapitre = course->chapters;
        if (chapitre == NULL) {
            printf("Aucun chapitre disponible.\n");
            return;
        }

        while (chapitre != NULL) {
            printf("  %d. %s\n", chapitre->id, chapitre->title);
            chapitre = chapitre->next;
        }

        contenu_show_progress(course);

        printf("  0. Quitter l'espace etudiant\n");
        printf("Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choix == 0) {
            break;
        }

        chapitre = course->chapters;
        int trouve = 0;
        while (chapitre != NULL) {
            if (chapitre->id == choix) {
                trouve = 1;
                contenu_browse_chapter(chapitre);
                break;
            }
            chapitre = chapitre->next;
        }

        if (!trouve) {
            printf("Numero invalide, reessayez.\n");
        }
    }
}
