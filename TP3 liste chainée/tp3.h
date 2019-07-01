
#ifndef tp3_h
#define tp3_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 30


typedef struct Note
{
    
    float note;
    char *matiere;
    struct Note *suivant;
    
}T_Note;


typedef  T_Note *T_ListeNotes;

typedef struct Etudiant
{ 
    
    int idEtu;
    char *nom;
    char *prenom;
    int nbreNote;
    T_ListeNotes Liste_Note;
    float moy;
    struct Etudiant *suivant;
    
}T_Etudiant;

typedef  T_Etudiant *T_ListeEtu;


T_Note *creerNote(float note, char *matiere);

T_Etudiant *creerEtudiant(int idEtu, char *nom, char *prenom);

T_ListeNotes ajouterNote(float note, char *matiere, T_ListeNotes listeNotes);

T_ListeEtu ajouterNoteEtu(float note, char *matiere, int idEtu, T_ListeEtu listeEtu);

void afficheListeEtu(T_ListeEtu listeEtu);

T_ListeEtu supprimerNoteEtu(char *matiere, int idEtu, T_ListeEtu listeEtu);

T_ListeEtu ajouterEtu(int idEtu, char *nom, char *prenom, T_ListeEtu listeEtu);

T_ListeEtu supprimerEtu(int idEtu, T_ListeEtu listeEtu);

float calculMoyenne(int idEtu, T_ListeEtu listeEtu);

void afficherClassement(T_ListeEtu listeEtu);

void sousListes(char* matiere, T_ListeEtu listeEtu);


#endif /* tp3_h */
