#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VMIN 5
#define VMAX 30

//----------------------------------- STRUCTURE -----------------------------------//
typedef struct
{
  int ligne;
  int colonne;
} T_Case;

typedef struct
{
  T_Case voisins[4];
  int nb_vois;
  T_Case voisinsO[4];
  int nb_voisO;
} T_Tab_Case;

typedef struct
{
  int nbligne;
  int nbcolonne;
  T_Case pion;
  T_Case pionO;
  T_Case voisin;
} Grille;

Grille plateau;

//----------------------------------- AFFICHER GRILLE -----------------------------------//
void afficherGrille()
{
    int i, j;
    printf("   ");
    for (i = 0; i < plateau.nbcolonne; i++)
    {
        printf("\e[1;31m%d \e[0m", i);
    }
    printf("\n");

    for (i = 0; i < plateau.nbligne; i++)
    {
        printf("\e[1;31m%d \e[0m", i);
        printf("|");
        for (j = 0; j < plateau.nbcolonne; j++)
        {
            if (plateau.pion.ligne == i && plateau.pion.colonne == j)
            {
                printf("\e[1;37m0\e[0m|");
            }
            else
            {
                printf("-|");
            }
        }
        printf("\n");
    }
}

//----------------------------------- AFFICHER GRILLE Ordi -----------------------------------//
void afficherGrilleO()
{
    int i, j;
    printf("   ");
    for (i = 0; i < plateau.nbcolonne; i++)
    {
        printf("\e[1;31m%d \e[0m", i);
    }
    printf("\n");

    for (i = 0; i < plateau.nbligne; i++)
    {
        printf("\e[1;31m%d \e[0m", i);
        printf("|");
        for (j = 0; j < plateau.nbcolonne; j++)
        {
            if (plateau.pionO.ligne == i && plateau.pionO.colonne == j)
            {
                printf("\e[1;37m0\e[0m|");
            }
            else
            {
                printf("-|");
            }
        }
        printf("\n");
    }
}

//----------------------------------- RECHERCHER LES CASES JOUABLE-----------------------------------//
T_Tab_Case Voisins()
{
  T_Tab_Case vois;
  vois.nb_vois = 0;

  // Vérifier si le pion peut se déplacer vers la droite
  if (plateau.pion.ligne + 1 < plateau.nbligne)
  {
    vois.voisins[vois.nb_vois].colonne = plateau.pion.colonne;
    vois.voisins[vois.nb_vois].ligne = plateau.pion.ligne + 1;
    vois.nb_vois++;
  }
  // Vérifier si le pion peut se déplacer vers la droite 2x
  if (plateau.pion.ligne + 2 < plateau.nbligne)
  {
    vois.voisins[vois.nb_vois].colonne = plateau.pion.colonne;
    vois.voisins[vois.nb_vois].ligne = plateau.pion.ligne + 2;
    vois.nb_vois++;
  }

  // Vérifier si le pion peut se déplacer vers le bas
  if (plateau.pion.colonne + 1 < plateau.nbcolonne)
  {
    vois.voisins[vois.nb_vois].colonne = plateau.pion.colonne + 1;
    vois.voisins[vois.nb_vois].ligne = plateau.pion.ligne;
    vois.nb_vois++;
  }
  // Vérifier si le pion peut se déplacer vers le bas 2x
  if (plateau.pion.colonne + 2 < plateau.nbcolonne)
  {
    vois.voisins[vois.nb_vois].colonne = plateau.pion.colonne + 2;
    vois.voisins[vois.nb_vois].ligne = plateau.pion.ligne;
    vois.nb_vois++;
  }

  return vois;
}

//----------------------------------- RECHERCHER LES CASES JOUABLE-----------------------------------//
T_Tab_Case VoisinsO()
{
  T_Tab_Case voisO;
  voisO.nb_voisO = 0;

  // Vérifier si le pion peut se déplacer vers la droite
  if (plateau.pionO.ligne + 1 < plateau.nbligne)
  {
    voisO.voisinsO[voisO.nb_voisO].colonne = plateau.pionO.colonne;
    voisO.voisinsO[voisO.nb_voisO].ligne = plateau.pionO.ligne + 1;
    voisO.nb_voisO++;
  }
  // Vérifier si le pionO peut se déplacer vers la droite 2x
  if (plateau.pionO.ligne + 2 < plateau.nbligne)
  {
    voisO.voisinsO[voisO.nb_voisO].colonne = plateau.pionO.colonne;
    voisO.voisinsO[voisO.nb_voisO].ligne = plateau.pionO.ligne + 2;
    voisO.nb_voisO++;
  }

  // Vérifier si le pionO peut se déplacer vers le bas
  if (plateau.pionO.colonne + 1 < plateau.nbcolonne)
  {
    voisO.voisinsO[voisO.nb_voisO].colonne = plateau.pionO.colonne + 1;
    voisO.voisinsO[voisO.nb_voisO].ligne = plateau.pionO.ligne;
    voisO.nb_voisO++;
  }
  // Vérifier si le pionO peut se déplacer vers le bas 2x
  if (plateau.pionO.colonne + 2 < plateau.nbcolonne)
  {
    voisO.voisinsO[voisO.nb_voisO].colonne = plateau.pionO.colonne + 2;
    voisO.voisinsO[voisO.nb_voisO].ligne = plateau.pionO.ligne;
    voisO.nb_voisO++;
  }

  return voisO;
}

//----------------------------------- AFFICHER LES CASES JOUABLE-----------------------------------//
void afficherVoisins(T_Tab_Case vois)
{
  int i;
  if (vois.nb_vois == 0)
  {
    printf("Aucun coup n'est jouable.\n");
    return;
  }
  printf("\nA toi de jouer !\n");
  printf("choisir la destination parmi les %d disponible :\n", vois.nb_vois);
  for (i = 0; i < vois.nb_vois; i++)
  {
    printf(" %d:(%d,%d) ", i + 1, vois.voisins[i].ligne, vois.voisins[i].colonne);
  }
  printf("\n");
}

//----------------------------------- DEPLACER PION J -----------------------------------//
void Coup_joueur(T_Tab_Case vois)
{
  int valide = false;
  int choix;
  printf("---> ");
  while (valide == false)
  {
    scanf("%d", &choix);
    if (choix <= vois.nb_vois && choix >= 1)
    {
      plateau.pion.ligne = vois.voisins[choix - 1].ligne;
      plateau.pion.colonne = vois.voisins[choix - 1].colonne;
      valide = true;
    }
    else
      printf("Saisissez une valeur correcte : ");
  }
}

//----------------------------------- NIMBER -----------------------------------//
int Nimber(int ligne, int colonne)
{
  int nimber = 0;
  if (((ligne * plateau.nbligne + colonne) % 3) == 0)
  {
    nimber = 0;
  }
  else
  {
    nimber = 1;
  }
  return nimber;
}

//----------------------------------- COUP ALEATOIRE -----------------------------------//
void Coup_Ordi_Hasard(T_Tab_Case voisinsO)
{
  int coup = ((rand() % voisinsO.nb_voisO));
  plateau.pionO.ligne = voisinsO.voisinsO[coup].ligne;
  plateau.pionO.colonne = voisinsO.voisinsO[coup].colonne;
  printf("L'ordinateur s'est déplacé en (%d,%d)\n", plateau.pionO.ligne, plateau.pionO.colonne);
}

//----------------------------------- CoupParfait -----------------------------------//
void Coup_Ordi_Gagnant(T_Tab_Case voisinsO)
{
  int moveJl = (int) NULL, moveJC = (int) NULL;
  int i, nimber;
  for (i = 0; i < voisinsO.nb_voisO; i++)
  {
    nimber = Nimber(voisinsO.voisinsO[i].ligne, voisinsO.voisinsO[i].colonne);
    if (nimber == 0)
    {
      moveJl = voisinsO.voisinsO[i].ligne;
      moveJC = voisinsO.voisinsO[i].colonne;
    }
  }
  if (moveJl == (int) NULL && moveJC == (int) NULL)
  {
    Coup_Ordi_Hasard(voisinsO);
  }
  else
  {
    plateau.pionO.ligne = moveJl;
    plateau.pionO.colonne = moveJC;
  }
  printf("L'ordinateur s'est déplacé en (%d,%d)\n\n", plateau.pionO.ligne, plateau.pionO.colonne);
}

//----------------------------------- HASARD -----------------------------------//
int Hasard(int min_h, int max_h)
{
  srand(time(NULL));

  return rand() % (max_h - min_h + 1) + min_h;
}

//----------------------------------- AFFICHER LES CASES JOUABLE -----------------------------------//
void Coup_Ordi(T_Tab_Case voisinsO, int niveau)
{
  int NombreHasard = Hasard(0, 3);
  switch (niveau)
  {
  case 1:
    Coup_Ordi_Hasard(voisinsO);
    break;
  case 2:
    if (NombreHasard == 0)
    {
      Coup_Ordi_Gagnant(voisinsO);
    }
    else
    {
      Coup_Ordi_Hasard(voisinsO);
    }
    break;
  case 3:
    if (NombreHasard == 0)
    {
      Coup_Ordi_Hasard(voisinsO);
    }
    else
    {
      Coup_Ordi_Gagnant(voisinsO);
    }
    break;
  case 4:
    Coup_Ordi_Gagnant(voisinsO);
    break;
  default:
    printf("BUG");
    break;
  }
}

int checkWin(Grille plateau)
{
  if ((plateau.pion.colonne == plateau.nbcolonne - 1 && plateau.pion.ligne == plateau.nbligne - 1) || (plateau.pionO.colonne == plateau.nbcolonne - 1 && plateau.pionO.ligne == plateau.nbligne - 1))
    return 1;
  return 0;
}

//----------------------------------- LIRE ENTIER -----------------------------------//
int Lire_Entier(int min, int max)
{
  int entier;
  do
  {
    scanf("%d", &entier);
  } while (entier < min || entier > max);
  return entier;
}

//----------------------------------- PARAMETRES -----------------------------------//
void Parametres(int *niveau, int *next)
{
  printf("Paramètres du jeu :\n");
  printf("Saisissez un nombre de ligne compris entre %d et %d : ", VMIN, VMAX);
  plateau.nbligne = Lire_Entier(VMIN, VMAX);
  printf("Saisissez un nombre de colonnes compris entre %d et %d : ", VMIN, VMAX);
  plateau.nbcolonne = Lire_Entier(VMIN, VMAX);
  printf("Saisissez un niveau compris entre %d et %d : ", 1, 4);
  *niveau = Lire_Entier(1, 4);
  printf("Qui commence ?\n");
  printf("l’ordinateur (1) ou le joueur (2) : ");
  *next = Lire_Entier(1, 2);
  printf("\n C’est parti !\n\n");
}

//----------------------------------- MAIN -----------------------------------//
int main(void)
{
  srand(time(NULL));
  int niveau, next;
  Parametres(&niveau, &next);
  plateau.pion.ligne = 0, plateau.pion.colonne = 0;
  plateau.pionO.ligne = 0, plateau.pionO.colonne = 0;
  int game_over = 0;
  while (!game_over)
  {
    if (next == 1)
    {
      Coup_Ordi(VoisinsO(), niveau);
      printf("\n");
      afficherGrilleO();
      printf("\n\n");
      if (checkWin(plateau))
      {
        printf("L'ordinateur a gagné!\n");
        game_over = 1;
        break;
      }
      next = 0;
    }
    else
    {
      afficherGrille();
      T_Tab_Case vois = Voisins();
      if (vois.nb_vois == 0)
      {
        printf("Aucun coup possible, vous avez perdu!\n");
        game_over = 1;
        break;
      }
      afficherVoisins(vois);
      Coup_joueur(vois);
      printf("\n\n");
      if (checkWin(plateau))
      {
        afficherGrille();
        printf("\nVous avez gagné!\n");
        game_over = 1;
        break;
      }
      next = 1;
    }
  }
}
