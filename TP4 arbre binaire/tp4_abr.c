/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdlib.h>
#include <stdio.h>
#include "tp4_abr.h"

T_Noeud *abr_creer_noeud(int valeur){
    T_Noeud *nouveau = (T_Noeud *)malloc(sizeof (T_Noeud));
     if (nouveau == NULL)
        return NULL;
    
        nouveau->val = valeur;
        nouveau->gauche = NULL;
        nouveau->droit = NULL; 
    
    return nouveau;
}

void abr_prefixe(T_Arbre abr){
    if (abr==NULL)
        printf("rien à afficher\n");
    else{
        T_Arbre abrTmp = abr;
        if (abrTmp!=NULL){
            if (abrTmp->gauche != NULL && abrTmp->droit != NULL){
                printf("Noeud --> %d\n "//,abrTmp->val);
                         "     --> FG : %d -- FD : %d\n",abrTmp->val,abrTmp->gauche->val,abrTmp->droit->val);
            }
            if (abrTmp->gauche == NULL && abrTmp->droit != NULL){
                printf("Noeud --> %d\n "//,abrTmp->val);
                         "     --> FG : NULL -- FD : %d\n",abrTmp->val,abrTmp->droit->val);
            }
            if (abrTmp->gauche != NULL && abrTmp->droit == NULL){
                printf("Noeud --> %d\n "//,abrTmp->val);
                         "     --> FG : %d -- FD : NULL\n",abrTmp->val,abrTmp->gauche->val);
            }
            if (abrTmp->gauche == NULL && abrTmp->droit == NULL){
                printf("Noeud --> %d\n "//,abrTmp->val);
                         "     --> FG : NULL -- FD : NULL\n",abrTmp->val);
            }
        }

        if  (abrTmp->gauche != NULL)
            abr_prefixe(abrTmp->gauche);
        if  (abrTmp->droit != NULL)
            abr_prefixe(abrTmp->droit);
    }
    

}


void abr_inserer(int valeur,T_Arbre *abr){    

    if (*abr == NULL){// si l'abr est NULL on le cree
        *abr = abr_creer_noeud(valeur);          
    } 
    if  ((*abr)->val<valeur)// on parcours jusqu'a obtenir la vraie position a ajouter
        abr_inserer(valeur,&(*abr)->droit);
    if  ((*abr)->val>valeur)
        abr_inserer(valeur,&(*abr)->gauche);      
    if ((*abr)->droit == NULL && (*abr)->val < valeur){
        T_Noeud *nouveau = abr_creer_noeud(valeur);
        (*abr)->droit = nouveau;
    }
    if ((*abr)->gauche == NULL && (*abr)->val > valeur){
        T_Noeud *nouveau = abr_creer_noeud(valeur);
        (*abr)->gauche = nouveau;
    }
}
T_Noeud *chercher_valeur(int valeur,T_Arbre abr){
    if (abr!= NULL){
        if  (abr->val<valeur)
            return chercher_valeur(valeur,abr->droit);
        if  (abr->val>valeur)
            return chercher_valeur(valeur,abr->gauche); 
    
        if  (abr->val==valeur)
            //printf("val %d\n",abr->val);   
            return abr;
    }
    else    {
        
        
        //printf(" valeur n'existe pas !\n");
        return (NULL);
    }
}
void abr_supprimer(int valeur,T_Arbre *abr){       
    if (*abr==NULL)
        printf("rien à supprimer ! ");
    T_Arbre abrTmp;
    int racine=1;
    abrTmp=chercher_valeur(valeur,*abr);
    if (abrTmp!=*abr)
        racine=0;// on verifie si la position a supprimer est la racine ou pas
    if (abrTmp==NULL)
        printf("il n'y a pas valeur correspondant\n");
    
    else{
        T_Arbre maxfils;//le noeud le plus grand du sous-arbre gauche du neoud a supprimer
        if (racine == 1){//si c'est la racine
            if (abrTmp->gauche!=NULL && abrTmp->droit!=NULL){
                maxfils=abrTmp->gauche;
                while   (maxfils->droit!=NULL){
                    maxfils=maxfils->droit;
                }
                maxfils->droit=abrTmp->droit;
                *abr=abrTmp->gauche;
                free(abrTmp);
            }
            if (abrTmp->gauche==NULL && abrTmp->droit!=NULL){
                *abr=abrTmp->droit;
                 free(abrTmp);
            }
            if (abrTmp->gauche!=NULL && abrTmp->droit==NULL){
                *abr=abrTmp->gauche;
                 free(abrTmp);
            }
            if (abrTmp->gauche==NULL && abrTmp->droit==NULL){
                *abr=NULL;
                 free(abrTmp);
            }            
            
        }
        else{// si c'est pas la racine
            T_Arbre pereTmp=NULL;
                pereTmp=*abr;
            if  (abrTmp->val==valeur){

                //abr_prefixe(*abr);
                while (pereTmp->gauche!=abrTmp && pereTmp->droit!=abrTmp){
                            if (pereTmp->val<abrTmp->val)
                                pereTmp=pereTmp->droit;
                            else
                                pereTmp=pereTmp->gauche;
                        }

                //abr_prefixe(*abr);

                int p;
                if  (abrTmp->droit == NULL && abrTmp->gauche==NULL)
                    p=0;
                if  (abrTmp->droit != NULL && abrTmp->gauche!=NULL)
                    p=1;
                if  (abrTmp->droit != NULL && abrTmp->gauche==NULL)
                    p=2;
                if  (abrTmp->droit == NULL && abrTmp->gauche!=NULL)
                    p=3;
                switch (p){
                    case 0  :   
                        if (pereTmp->gauche==abrTmp){
                            pereTmp->gauche=NULL;
                        }
                        if (pereTmp->droit==abrTmp){
                            pereTmp->droit=NULL;
                        }
                        free(abrTmp);
                        break;
                    case 1  :
                        maxfils=abrTmp->gauche;
                        while   (maxfils->droit!=NULL){
                            maxfils=maxfils->droit;
                        }

                        if (pereTmp->gauche==abrTmp){
                            pereTmp->gauche=abrTmp->gauche;
                        }
                        if (pereTmp->droit==abrTmp){
                            pereTmp->droit=abrTmp->gauche;
                        }
                        maxfils->droit=abrTmp->droit;
                        free(abrTmp);

                        break;
                    case 2  :   
                        //T_Arbre pereTmp= abr;

                        if (pereTmp->gauche==abrTmp){
                            pereTmp->gauche=abrTmp->droit;
                        }
                        if (pereTmp->droit==abrTmp){
                            pereTmp->droit=abrTmp->droit;
                        }
                        free(abrTmp);
                        break;
                    case 3  :

                        if (pereTmp->gauche==abrTmp){
                            pereTmp->gauche=abrTmp->gauche;
                        }
                        if (pereTmp->droit==abrTmp){
                            pereTmp->droit=abrTmp->gauche;
                        }
                        break;
                    default :
                        printf("erreur\n");
                        break;

                }       
            }
        }    
    }

}



void abr_clone(T_Arbre original, T_Arbre *clone, T_Noeud* parent){
    if (original == NULL)
            return;
    *clone = abr_creer_noeud(original->val);
    if (parent != NULL)
        if (parent->val > (*clone)->val)
            parent->gauche = *clone;
        else
            parent->droit = *clone;

    if (original->gauche != NULL) {
        abr_clone(original->gauche, &((*clone)->gauche), *clone);
    }

    if (original->droit != NULL) {
       abr_clone(original->droit, &((*clone)->droit), *clone);
    }
}
