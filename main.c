#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define JOKER '*'
#define TRUE 1
#define FALSE 0
#define FIC_NAME "dico.txt"

typedef struct mot_pendu mot_pendu;
struct mot_pendu
{
      char mot[100];
      char mot_secret[100];
};

void dessiner_pendu(int nb_essai)
{
      switch (nb_essai)
      {
      case 0:
            printf("   _______     \n");
            printf("   |/    |     \n");
            printf("   |     O     \n");
            printf("   |    /|\\   \n");
            printf("   |     /\\   \n");
            printf("___|___        \n");
            break;
      case 1:
            printf("   _______     \n");
            printf("   |/    |     \n");
            printf("   |     O     \n");
            printf("   |    /|\\   \n");
            printf("   |     /     \n");
            printf("___|___        \n");
            break;
      case 2:
            printf("   _______     \n");
            printf("   |/    |     \n");
            printf("   |     O     \n");
            printf("   |    /|\\   \n");
            printf("   |           \n");
            printf("___|___        \n");
            break;
      case 3:
            printf("   _______     \n");
            printf("   |/    |     \n");
            printf("   |     O     \n");
            printf("   |    /|     \n");
            printf("   |           \n");
            printf("___|___        \n");
            break;
      case 4:
            printf("   _______     \n");
            printf("   |/    |     \n");
            printf("   |     O     \n");
            printf("   |     |     \n");
            printf("   |           \n");
            printf("___|___        \n");
            break;
      case 5:
            printf("   _______     \n");
            printf("   |/    |     \n");
            printf("   |     O     \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("___|___        \n");
            break;
      case 6:
            printf("   _______     \n");
            printf("   |/    |     \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("___|___        \n");
            break;
      case 7:
            printf("   _______     \n");
            printf("   |/          \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("___|___        \n");
            break;
      case 8:
            printf("               \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("   |           \n");
            printf("___|___        \n");
            break;
      case 9:
            printf("               \n");
            printf("               \n");
            printf("               \n");
            printf("               \n");
            printf("               \n");
            printf("_______        \n");
            break;
      case 10:
            printf("               \n");
            printf("               \n");
            printf("               \n");
            printf("               \n");
            printf("               \n");
            printf("               \n");
            break;
      }
}

char lire_caractere()
{
      char caractere = 0;

      caractere = getchar();
      caractere = toupper(caractere);

      while (getchar() != '\n')
            ;

      return caractere;
}

int nouvelle_lettre(char nouvelle_lettre, mot_pendu *pendu)
{
      int size = strlen(pendu->mot);
      int i;
      int result = FALSE;
      for (i = 0; i < size; i++)
      {
            if (pendu->mot[i] == nouvelle_lettre)
            {
                  pendu->mot_secret[i] = nouvelle_lettre;
                  result = TRUE;
            }
      }
      return result;
}

int contains_char(char c, char *s)
{
      int i;
      for (i = 0; i < strlen(s); i++)
      {
            if (s[i] == c)
            {
                  return TRUE;
            }
      }
      return FALSE;
}

void victoire_ou_defaite(int nb_essai, mot_pendu *pendu)
{
      if (nb_essai == 0)
      {
            system("clear");
            printf("==========================\n");
            printf("======= T'ES MORT ========\n");
            printf("==========================\n");
            printf("%s\n", pendu->mot);
            printf("\a");
            dessiner_pendu(nb_essai);
      }
      else if (!contains_char(JOKER, pendu->mot_secret))
      {
            system("clear");
            printf("==========================\n");
            printf("=======C'EST GAGNE========\n");
            printf("==========================\n");
            printf("%s\n", pendu->mot);
            printf("\a");
            dessiner_pendu(nb_essai);
      }
      
}

int compter_lignes(FILE *dico)
{
      int count = 0;
      char s[100];
      rewind(dico);
      while (fgets(s, 100, dico) != NULL)
      {
            count++;
      }

      return count;
}

char *lire_ligne(int n, FILE *dico)
{
      char ligne[100];

      rewind(dico);
      while (n > 0)
      {
            fgets(ligne, 100, dico);
            n--;
      }
      fgets(ligne, 100, dico);

      ligne[strlen(ligne) - 1] = '\0';
      return ligne;
}

char *piocher_mot()
{
      char mot[100];

      FILE *dico = fopen(FIC_NAME, "r");
      if (dico == NULL)
      {
            printf("File %s does not exist or cannot be opened.\n", dico);
            exit(1);
      }

      int compte_lignes = compter_lignes(dico);

      srand(time(NULL));

      int n = rand() % (compte_lignes);

      printf("Reading line %d\n", n);
      strcpy(mot, lire_ligne(n, dico));
      fclose(dico);

      return mot;
}

void print_header(int nb_essai)
{
      printf("==========================\n");
      printf("=======   PENDU   ========\n");
      printf("==========================\n");
      printf("Il vous reste %d essais avant une mort certaine\n", nb_essai);
      printf("Saisissez un lettre\n");
}

int main(int argc, const char *argv[])
{
      char c;
      do
      {
            mot_pendu pendu;
            strcpy(pendu.mot, piocher_mot());
            int i;
            for (i = 0; i < strlen(pendu.mot); i++)
            {
                  pendu.mot_secret[i] = '*';
            }
            pendu.mot_secret[strlen(pendu.mot)] = '\0';

            int nb_essai = 10;

            while (strcmp(pendu.mot, pendu.mot_secret) && nb_essai > 0)
            {
                  system("clear");
                  print_header(nb_essai);
                  dessiner_pendu(nb_essai);
                  printf("mot secret %s\n", pendu.mot_secret);
                  char lettre = lire_caractere();
                  if (!nouvelle_lettre(lettre, &pendu))
                  {
                        nb_essai--;
                  }
                  victoire_ou_defaite(nb_essai, &pendu);
            }

            printf("\nRejouer ?\n");
            c = lire_caractere();
      } while (c == 'Y' || c == 'O');
}
