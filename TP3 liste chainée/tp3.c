
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp3.h"

T_Note *creerNote(float note, char *matiere)
{
    T_Note *nouveauNote = malloc(sizeof(struct Note));
    if (nouveauNote == NULL)
        return NULL;
    
        nouveauNote->note = note;
        nouveauNote->matiere = matiere;
        nouveauNote->suivant = NULL; 
    
    return nouveauNote;
}

T_Etudiant *creerEtudiant(int idEtu, char *nom, char *prenom)
{
    T_Etudiant *nouveauEtu = malloc(sizeof(struct Etudiant));
    if (nouveauEtu == NULL)
        return NULL;
    
    nouveauEtu->idEtu = idEtu;
    nouveauEtu->nom = nom;
    nouveauEtu->prenom = prenom;
    nouveauEtu->nbreNote = 0;
    nouveauEtu->moy = 0;
    nouveauEtu->Liste_Note = NULL;
    nouveauEtu->suivant = NULL;
    
    return nouveauEtu;
}

T_ListeNotes ajouterNote(float note, char *matiere, T_ListeNotes listeNotes)
{
    T_Note *nouveauNote = creerNote(note, matiere); 
   
    nouveauNote->suivant = listeNotes;
  
    return nouveauNote;
  
}

T_ListeEtu ajouterNoteEtu(float note, char *matiere, int idEtu, T_ListeEtu listeEtu)
{
    
    if((idEtu < 0) || (note > 20.0) || (note < 0.0||strlen(matiere)!=4)) // on considère à l'utc le code d'uv sont 4 lettres
    {
        printf("Veuillez saisir des valeur valide \n");
        return listeEtu; 
    }
    
    T_ListeEtu tmp;
    tmp = listeEtu;
    while(tmp->idEtu != idEtu)
    {
        tmp = tmp->suivant;
        if(tmp == NULL)
            break;
    }
    
    if(tmp == NULL)
    { //au cas ou l'etudiant concernant l'idEtu n'existe pas
        char *nom = malloc(MAX*sizeof(char));
        char *prenom = malloc(MAX*sizeof(char));
        printf("l'etudiant n'existe pas, donnez le nom:\t");
        scanf("%s",nom);
        printf("donnez le prenom:\t");
        scanf("%s",prenom);
        listeEtu =  ajouterEtu(idEtu, nom, prenom, listeEtu);
        tmp = listeEtu;
    }
  
    tmp->Liste_Note = ajouterNote(note, matiere, tmp->Liste_Note);
    tmp->nbreNote ++;
    tmp->moy = calculMoyenne(idEtu, listeEtu);
    
    return listeEtu;
   

}

void afficheListeEtu(T_ListeEtu listeEtu)
{
    T_ListeEtu tmp = listeEtu;
    
    while(tmp != NULL)
    {
        printf("l'etudiant numero %d : %s %s\n",tmp->idEtu,tmp->nom,tmp->prenom);
        
        T_ListeNotes tmp_note = tmp->Liste_Note;

        while (tmp_note != NULL) 
        {
            printf("UV : %s  -  note : %.2f\n", tmp_note->matiere,tmp_note->note);
            tmp_note = tmp_note->suivant;
        }
        printf("\n");
        tmp = tmp->suivant;
    }

    
}

T_ListeEtu supprimerNoteEtu(char *matiere, int idEtu, T_ListeEtu listeEtu)
{
    
    if(idEtu < 0)
    {   
        printf("erreur\n");
        return listeEtu;
    }
           
    T_ListeEtu tmp  = listeEtu;
    while(tmp->idEtu != idEtu )
         tmp = tmp->suivant;
    
    T_ListeNotes tmp_note = tmp->Liste_Note; 
      
        while(strcmp(tmp_note->matiere,matiere) !=0)
            tmp_note = tmp_note->suivant;
    
    if (tmp_note == tmp->Liste_Note) // supprimer en tete
    { 
        tmp->Liste_Note = tmp_note->suivant;
         tmp->nbreNote --;
         tmp->moy = calculMoyenne(idEtu, listeEtu);
         free(tmp_note);
    }
    
    else // supprimer au milieu et en fin
    {
   
        T_ListeNotes pre_note = tmp->Liste_Note;
         tmp->nbreNote --;
         tmp->moy = calculMoyenne(idEtu, listeEtu);
        
        while(pre_note->suivant != tmp_note)
            pre_note = pre_note->suivant;// on cherche le predecesseur 
       
        pre_note->suivant = tmp_note->suivant;
        free(tmp_note);
    }
      
    //On veillera à retirer l’étudiant de la liste si celui-ci n’a plus aucune note
    if (tmp->nbreNote == 0)
       listeEtu = supprimerEtu(idEtu, listeEtu);
   
    return listeEtu;
    
}

T_ListeEtu supprimerEtu(int idEtu, T_ListeEtu listeEtu)
{
        T_ListeEtu tmp = listeEtu;

        while(tmp->idEtu != idEtu )
            tmp = tmp->suivant; //on cherche l'idEtu à supprimer;
          T_ListeEtu tmp2 = listeEtu;
        
        if(tmp == listeEtu)     //supprimer en tete
            listeEtu = tmp->suivant;
                 
        else
        {       
        while(tmp2->suivant != tmp)// supprimer au milieu et en fin
            tmp2 =tmp2->suivant;
               
        tmp2->suivant  = tmp->suivant; 
        }
      
      
 return listeEtu;
}

T_ListeEtu ajouterEtu(int idEtu, char *nom, char *prenom, T_ListeEtu listeEtu)
{
    
    if(idEtu < 0)
    {
        printf("erreur\n");
        return listeEtu;
    }
    T_ListeEtu tmp = listeEtu;
    while (tmp != NULL) 
    {
        if(tmp->idEtu == idEtu)
        { 
            printf("idEtu existe deja\n"); // on vérifie l'unicité de idEtu
            return listeEtu;
            break;
        }
        tmp = tmp->suivant;
    }
    
    T_Etudiant *nouveauEtu;
   
    nouveauEtu = creerEtudiant(idEtu, nom, prenom);      
    nouveauEtu->suivant = listeEtu;   
    listeEtu = nouveauEtu;
  
    return listeEtu;
}

void afficherClassement(T_ListeEtu listeEtu)
{

    T_ListeEtu tmp = listeEtu;
    T_ListeEtu tmp1 = tmp;
    T_ListeEtu tmp_max = tmp;  
    float max = 0.0;
    
    if(tmp == NULL)
        printf("Fin\n");
    
    else 
    {
        while (tmp1 != NULL) 
        {
            if (tmp1->moy > max) 
            {
                max = tmp1->moy;
                tmp_max = tmp1;
            }

            tmp1 = tmp1->suivant;
        }

       printf("%s %s %.2f\n",tmp_max->nom, tmp_max->prenom, tmp_max->moy);
       tmp = supprimerEtu(tmp_max->idEtu, tmp);

       afficherClassement(tmp);
    }
   
}
    


float calculMoyenne(int idEtu, T_ListeEtu listeEtu)
{
    T_ListeEtu tmp = listeEtu;
    
    if(idEtu < 0)
    {
       printf("erreur\n");
       return 0;
    }
    
    while(tmp->idEtu != idEtu )
        tmp = tmp->suivant;
    
    if  (tmp->nbreNote == 0)
        return 0;
       
    else
    {
        T_ListeNotes tmp_note = tmp->Liste_Note;
        float somme =0.0;
        while (tmp_note != NULL) 
        {
            somme += tmp_note->note;          
            tmp_note = tmp_note->suivant;
        }
        tmp->moy = somme/(float)tmp->nbreNote;
      
    }
    
    return tmp->moy;
    
}

void sousListes(char* matiere, T_ListeEtu listeEtu)
{
printf(" Sous listes\n");
T_ListeEtu tmp = listeEtu;
T_ListeNotes tmp_note = tmp->Liste_Note;

     T_ListeEtu listeEtuReussi = NULL;
     T_ListeEtu listeEtuRate = NULL;
     T_ListeEtu listeEtuPasPasse = NULL;
  
while(tmp != NULL)
{
    tmp_note = tmp->Liste_Note;
    
    if(tmp_note == NULL)// etudiant qui n'a pas encore passer l'UV
    {
        listeEtuPasPasse = ajouterEtu(tmp->idEtu, tmp->nom, tmp->prenom, listeEtuPasPasse);
        tmp = tmp->suivant;
        tmp_note = tmp->Liste_Note;
    }
        
    while (strcmp(tmp_note->matiere, matiere) != 0) // pour une UV 
    { 
        tmp_note = tmp_note->suivant;
        if(tmp_note == NULL) 
            break;
    }
    if (tmp_note != NULL)
    { 
        
        if(tmp_note->note >= 10.0) 
            listeEtuReussi = ajouterEtu(tmp->idEtu, tmp->nom, tmp->prenom, listeEtuReussi); // ajouter à listeEtuReussi
    
        else
            listeEtuRate = ajouterEtu(tmp->idEtu, tmp->nom, tmp->prenom, listeEtuRate); // ajouter à listeEtuRate

    }
    else
        listeEtuPasPasse = ajouterEtu(tmp->idEtu, tmp->nom, tmp->prenom, listeEtuPasPasse); //ajouter à listePasPasse
    
    tmp = tmp->suivant;
 
}

    printf("Liste des étudiants qui ont réussi l'UV : \n");
    afficheListeEtu(listeEtuReussi);
       
    printf("Liste des étudiants qui ont raté l'UV : \n");
    afficheListeEtu(listeEtuRate);
     
    printf("Liste des étudiants qui n'ont pas passer l'UV : \n");
    afficheListeEtu(listeEtuPasPasse);
     
}







