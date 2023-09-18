#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
  char nom[20];
  char pre[20];
  char cn[10];
  char tel[10];
  int sal;
  int an;
};
struct wrdlist {
  char wrdl[1000];
};
void affiche(struct person *per, struct person per1, int i);
int rechercher(struct person *p, struct person p1, int c, char CN[10]);
char generateRandomChar();

//   rechercher sur une donnée entrer par l'utilisateur
int rechercher(struct person *p, struct person p1, int c, char CN[10]) {
  struct person *P;
  P = &p1;
  int i = 0;
  for (p = P; p < P + c - 1; p++) {
    if (strcmp(p->cn, CN) == 0) {
      return i;
    }
    i++;
  }
  return i = 999;
}
//   supprimer une donnée entrer par l'utilisateur
/*struct person *suprimer(struct person *p, int c, int t) {
  struct person *p11;
  p11 = p + c;
  for (p = p11; p < p11 + t - 1; p++) {
    *p = *(p + 1);
  }

  return p;
}*/

int main() {
  int n, r, a, wd = 1, t = 1, id = 1;
  struct person per1, *per, *per2;
  struct wrdlist per3, *wdl3;

  char C[10], rest[100];
  char temp[100];
  FILE *wordlist;

  printf("Menu :\n  [1] afficher les données\n  [2] ajouter une donnée\n  [3] "
         "rechercher sur une donnée\n  [4] supprimer une donnée\n  [5] "
         "supprimer les données répètes\n  [6] génère le wordlist\n  [7] "
         "génère le wordlist dans un fichier .txt\n  [8] afficher les données "
         "de type entier \n  [0] Quite \n");
  do {
    per = &per1;
    per = (struct person *)malloc(t * sizeof(struct person));
    wdl3 = &per3;
    wdl3 = (struct wrdlist *)malloc(wd * sizeof(struct wrdlist));
    per2 = &per1;
    printf("Entrez votre chois :");
    scanf("%d", &n);
    switch (n) {
    case 1:
      for (per = &per1; per < &per1 + t - 1; per++) {
        printf("nom :%s prenom :%s CN°:%s N°tel:%s salyre :%d  annes de "
               "naissance :%d",
               per->nom, per->pre, per->cn, per->tel, per->sal, per->an);
        printf("\n");
      }
      break;

    case 2:
      per = &per1 + t - 1;
      printf("entrez votre information :");
      scanf("%s %s %s %s %d %d", per->nom, per->pre, per->cn, per->tel,
            &per->sal, &per->an);

      t++;
      break;

    case 3:
      printf("entrez le CN° de la personne :");
      scanf("%s", C);
      if (rechercher(per, per1, t, C) < 999) {
        affiche(per, per1, rechercher(per, per1, t, C));
      } else {
        printf("personne introuvable \n");
      }

      break;

    case 4:
      printf("Saisissez le numéro de contact de la personne à supprimer : ");
      scanf("%s", C);

      int index = rechercher(per, per1, t, C);

      if (index != 999) {
        printf("Person found:\n");
        affiche(per, per1, rechercher(per, per1, t, C));
        printf("\n");
        printf("Êtes-vous sûr de vouloir supprimer cette personne ? (Y/N): ");
        char choice;
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
          for (per = &per1 + index; per < &per1 + t - 1; per++) {
            *per = *(per + 1);
          }
          t--;
          printf("Personne supprimée avec succès.\n");
        } else {
          printf("Suppression annulée.\n");
        }
      } else {
        printf("Personne introuvable.\n");
      }
      break;

    case 5:
      for (per = &per1; per < &per1 + t - 1; per++) {
        for (per2 = per + 1; per2 < &per1 + t - 1; per2++) {
          if (strcmp(per->nom, per2->nom) == 0 &&
              strcmp(per->pre, per2->pre) == 0 &&
              strcmp(per->cn, per2->cn) == 0 &&
              strcmp(per->tel, per2->tel) == 0 && per->sal == per2->sal &&
              per->an == per2->an) {
            for (per2 = per; per2 < &per1 + t - 1; per2++) {
              *per2 = *(per2 + 1);
            }
            t--;
            per--;
          }
        }
      }
      printf(" les données répètes est supprimer");
      break;
    case 6:
      per = &per1 + wd - 1;
      wdl3 = &per3 + wd - 1;
      int choi;
      printf("Entree le nombre de wordlist :");
      scanf("%d", &choi);
      do {
        for (int j = 0; j < choi; j++) {
          int RC = rand() % 2;
          for (int i = 0; i < 2; i++) {
            r = rand() % 6;
            switch (r) {
            case 0:
              strcat(rest, per->nom);
              break;
            case 1:
              strcat(rest, per->cn);
              break;
            case 2:
              strcat(rest, per->pre);
              break;
            case 3:
              strcat(rest, per->tel);
              break;
            case 4:
              sprintf(temp, "%d", per->sal);
              strcat(rest, temp);
              break;
            default:
              sprintf(temp, "%d", per->an);
              strcat(rest, temp);
              break;
            }
            if (i == RC) {
              char randomChar[2];
              randomChar[0] = generateRandomChar();
              randomChar[1] = '\0';
              strcat(rest, randomChar);
            }
          }
          strcat(wdl3->wrdl, rest);

          strcat(wdl3->wrdl, " ");
          strcpy(rest, "");
        }
        wd++;
        wdl3++;
        per++;
      } while (wd < t);

      break;

    case 7:
      fopen("C:\\wordlist.txt", "w");
      if (wordlist == NULL) {
        printf("Error!");
        exit(1);
      }
      for (wdl3 = &per3; wdl3 < &per3 + wd - 1; wdl3++) {
        fprintf(wordlist, "%s\n", wdl3->wrdl);
      }
      fclose(wordlist);
      break;
    case 8:
      printf("8");
      break;

    default:
      return 0;
      break;
    }
  } while (n != 0);
}
void affiche(struct person *per, struct person per1, int i) {
  per = &per1 + i;
  printf(
      "nom :%s prenom :%s CN°:%s N°tel:%s salyre :%d  annes de naissance :%d",
      per->nom, per->pre, per->cn, per->tel, per->sal, per->an);
  printf("\n");
}
char generateRandomChar() {
  char characters[] = {'@', '$', '&', '#'};

  int randc = random() % 4;

  char randchar = characters[randc];

  return randchar;
}
