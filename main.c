#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define JOKER '*'
#define TRUE 1
#define FALSE 0
#define FIC_NAME "dico.txt"

char lire_caractere()
{
      char caractere = 0;

      caractere = getchar();
      caractere = toupper(caractere);

      while (getchar() != '\n')
            ;

      return caractere;
}

int nouvelle_lettre(char nouvelle_lettre, char *mot_secret, char *mot)
{
      int size = strlen(mot);
      int i;
      int result = FALSE;
      for (i = 0; i < size; i++)
      {
            if (mot[i] == nouvelle_lettre)
            {
                  mot_secret[i] = nouvelle_lettre;
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

void victoire_ou_defaite(int nb_essai, char *mot_secret, char *mot)
{
      if (nb_essai == 0)
      {
            printf("==========================\n");
            printf("======= T'ES MORT ========\n");
            printf("==========================\n");
            printf("%s\n", mot);
            printf("\a");
      }
      else if (!contains_char(JOKER, mot_secret))
      {
            printf("==========================\n");
            printf("=======C'EST GAGNE========\n");
            printf("==========================\n");
            printf("%s\n", mot);
            printf("\a");
      }
}

int compter_lignes(FILE *dico)
{
      int count = 0;
      char s[100];
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
      if (fgets(ligne, 100, dico) == NULL)
      {
            printf("Failed to read line %d\n", n);
      }

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

int main(int argc, const char *argv[])
{
      char mot[100];
      strcpy(mot, piocher_mot());
      char mot_secret[100];
      int i;
      for (i = 0; i < strlen(mot); i++)
      {
            mot_secret[i] = '*';
      }
      mot_secret[strlen(mot)] = '\0';

      int nb_essai = 10;

      while (strcmp(mot, mot_secret) && nb_essai > 0)
      {
            system("clear");
            printf("==========================\n");
            printf("=======   PENDU   ========\n");
            printf("==========================\n");
            printf("Il vous reste %d essais avant une mort certaine\n", nb_essai);
            printf("Saisissez un lettre\n");

            printf("mot secret %s\n", mot_secret);
            char lettre = lire_caractere();
            if (!nouvelle_lettre(lettre, mot_secret, mot))
            {
                  nb_essai--;
            }
            victoire_ou_defaite(nb_essai, mot_secret, mot);
      }
}
