
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp3.h"

int main(int argc, const char * argv[]) 
{
    
    T_ListeEtu listeEtu = NULL;
    // on ajoute queques etudants et ses notes
    listeEtu = ajouterEtu(27, "DOAN","NhatMinh", listeEtu);
    listeEtu = ajouterNoteEtu(20, "NF16", 27, listeEtu);
    
    listeEtu = ajouterEtu(18, "WAYNE","Bruce", listeEtu);        
    listeEtu = ajouterNoteEtu(15, "SR01", 18, listeEtu);

    listeEtu = ajouterEtu(4, "KENT","CLARK", listeEtu); 
    listeEtu = ajouterNoteEtu(14, "SY02", 4, listeEtu);
 
    printf("----------------------TP3 Liste Chainées--------------------- \n");
  
    int choix =0; //entier qui nous sert pour notre menu de séléction des actions
    int cont=1;
    while(cont)
    {
        printf("Choissiez-vous l'option [tappez un numero]?\n");
        printf("1. Creer la liste d'étudiants\n");
        printf("2. Ajouter une note pour un etudiant\n");
        printf("3. Supprimer une note pour un étudiant\n");
        printf("4. Afficher la liste des étudiants\n");
        printf("6. Afficher les sous-listes pour une épreuve\n");
        printf("5. Afficher le classement \n");
        printf("7. Quitter :\n");
        scanf("%d",&choix);
        
        switch(choix)
        {
            case 1:
            {
                    int idEtu= 0;
                    char* nom = (char*)malloc(MAX*sizeof(char));
                    char* prenom = (char*)malloc(MAX*sizeof(char));
                    
                    printf("Saisissez l'idEtu, le nom et le prenom de l'etudiant :\t");
                    scanf("%d %s %s",&idEtu, nom, prenom);
                    
                    listeEtu = ajouterEtu(idEtu, nom, prenom, listeEtu);
    
                    break;
            }
                
            case 2 :
            {
                float note;
                char* matiere = (char*)malloc(4*sizeof(char));
                int idEtu = 0;
                
                printf("Saisissez l'idEtu  :\t");
                scanf("%d", &idEtu);
                printf("Saisissez l'UV :\t");
                scanf("%s", matiere);
                printf("Saissez la note :\t");
                scanf("%f", &note);
                
                listeEtu = ajouterNoteEtu(note, matiere, idEtu, listeEtu);
                free(matiere);
                break;
            }
                
            case 3 :
            {
                int idEtu = 0;
                char* matiere = (char*)malloc(4*sizeof(char));
                
                printf("Saisissez l'idEtu et la matiere  :\t");
                scanf("%d %s", &idEtu, matiere);
         
                listeEtu = supprimerNoteEtu(matiere, idEtu, listeEtu);
                free(matiere);
                break;
            }
                
            case 4 :
               afficheListeEtu(listeEtu);
                break;
                                         
            case 5 :
                afficherClassement(listeEtu);
                break;
                
            case 6 :
            {
                char* matiere = (char*)malloc(4*sizeof(char));
                printf("Entrez la matière :\t");
                scanf("%s", matiere);                
                sousListes(matiere, listeEtu);
                free(matiere);
                break;
            }
                
             default:
            {
                T_ListeEtu tmp = NULL;
                T_ListeNotes tmp_note = NULL;
                while (listeEtu != NULL)
                {
                    tmp = listeEtu;
                    while (listeEtu->Liste_Note != NULL) 
                    {
                        tmp_note = listeEtu->Liste_Note;
                        listeEtu->Liste_Note = listeEtu->Liste_Note->suivant;
                        free(tmp_note);
                    }
                    listeEtu = listeEtu->suivant;
                    free(tmp);
                }
    
                cont=0; 
            }
            
        }
                
    } 
    
    return 0;
}
