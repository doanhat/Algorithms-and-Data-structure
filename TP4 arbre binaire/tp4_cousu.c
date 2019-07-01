/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include "tp4_cousu.h"

T_Noeud_C *cousu_creer_noeud(int valeur){
     T_Noeud_C *nouveau = (T_Noeud_C *)malloc(sizeof (T_Noeud_C));
     if (nouveau == NULL)
        return NULL;
    
        nouveau->val = valeur;
        nouveau->gauche = NULL;
        nouveau->droit = NULL; 
        nouveau->gauchePre = 1;
        nouveau->droitSuc = 1;
    return nouveau;
}

T_Noeud_C *chercher_valeur_C(int valeur,T_Arbre_C abr){
    if (abr!= NULL){
        if  (abr->val<valeur)
            return chercher_valeur_C(valeur,abr->droit);
        if  (abr->val>valeur)
            return chercher_valeur_C(valeur,abr->gauche); 
    
        if  (abr->val==valeur)
            return abr;
    }
    else    {             
        return NULL;
    }
}

int chercherPre(int valeur,T_Arbre_C arbre){
    T_Arbre_C arbreTmp=arbre;
    int min=arbreTmp->val;//la valeur minimum dans l'abr

    while (arbreTmp->gauche!=NULL){//on cherche la valeur minimum dans l'abr
        min=arbreTmp->gauche->val;
        arbreTmp=arbreTmp->gauche;
    }
    while (valeur>=min){//on cherche le predecesseur du "valeur"
        valeur--;// car ici on a un abr avec des entiers
        if (chercher_valeur_C(valeur,arbre)!=NULL){
            return  chercher_valeur_C(valeur,arbre)->val;
            break;
        }
    }
    if (valeur<min)
        return  -1;
}

int chercherSuc(int valeur,T_Arbre_C arbre){
    T_Arbre_C arbreTmp=arbre;
    int max=arbreTmp->val;

    while (arbreTmp->droit!=NULL){
        max=arbreTmp->droit->val;
        arbreTmp=arbreTmp->droit;
    }

    while (valeur<=max){
        valeur++;
        if (chercher_valeur_C(valeur,arbre)!=NULL){
            return  chercher_valeur_C(valeur,arbre)->val;
            break;
        }
    }
    if (valeur>max)
        return  -1;
}
void sous_cousu_prefixe(T_Arbre_C arbreT,int pre,int suc, T_Arbre_C arbre){
    T_Arbre_C abrTmp = arbreT;
    pre = chercherPre(abrTmp->val,arbre);
    suc = chercherSuc(abrTmp->val,arbre);


    if (abrTmp!=NULL){
        if (abrTmp->gauche != NULL && abrTmp->droit != NULL)
            printf("Noeud --> %d\n "
                     "     --> FG(0) : %d -- FD(0) : %d\n",abrTmp->val,abrTmp->gauche->val,abrTmp->droit->val);
        if (abrTmp->gauche == NULL && abrTmp->droit != NULL){
            if (pre!=-1)
                printf("Noeud --> %d\n "
                     "     --> FG(%d) : %d -- FD(%d) : %d\n",abrTmp->val,abrTmp->gauchePre,pre,abrTmp->droitSuc,abrTmp->droit->val);
            else
                printf("Noeud --> %d\n "
                     "     --> FG(%d) : NULL -- FD(%d) : %d\n",abrTmp->val,abrTmp->gauchePre,abrTmp->droitSuc,abrTmp->droit->val);                
        }
        if (abrTmp->gauche != NULL && abrTmp->droit == NULL){
            if (suc!=-1)
                printf("Noeud --> %d\n "
                     "     --> FG(%d) : %d -- FD(%d) : %d\n",abrTmp->val,abrTmp->gauchePre,abrTmp->gauche->val,abrTmp->droitSuc,suc);
            else
                printf("Noeud --> %d\n "
                     "     --> FG(%d) : %d -- FD(%d) : NULL\n",abrTmp->val,abrTmp->gauchePre,abrTmp->gauche->val,abrTmp->droitSuc);
        }   
        if (abrTmp->gauche == NULL && abrTmp->droit == NULL){
            if (pre!=-1 && suc!=-1)    
                printf("Noeud --> %d\n "
                        "     --> FG(%d) : %d -- FD(%d) : %d\n",abrTmp->val,abrTmp->gauchePre,pre,abrTmp->droitSuc,suc);
            if (pre==-1 && suc!=-1)    
                printf("Noeud --> %d\n "
                        "     --> FG(%d) : NULL -- FD(%d) : %d\n",abrTmp->val,abrTmp->gauchePre,abrTmp->droitSuc,suc);
            if (pre!=-1 && suc==-1)    
                printf("Noeud --> %d\n "
                        "     --> FG(%d) : %d -- FD(%d) : NULL\n",abrTmp->val,abrTmp->gauchePre,pre,abrTmp->droitSuc);
            if (pre==-1 && suc==-1)    
                printf("Noeud --> %d\n "
                        "     --> FG(%d) : NULL -- FD(%d) : NULL\n",abrTmp->val,abrTmp->gauchePre,abrTmp->droitSuc);    
        }    
           
           
    }
    
    if  (abrTmp->gauche != NULL)
        sous_cousu_prefixe(abrTmp->gauche,chercherPre(abrTmp->gauche->val,arbre),chercherSuc(abrTmp->gauche->val,arbre),arbre);
    if  (abrTmp->droit != NULL)
        sous_cousu_prefixe(abrTmp->droit,chercherPre(abrTmp->droit->val,arbre),chercherSuc(abrTmp->droit->val,arbre),arbre);
}
void cousu_prefixe(T_Arbre_C arbre){
    if (arbre==NULL)
        printf("rien à afficher\n");
    else{
        T_Arbre_C abrTmp = arbre;
        int pre;
        int suc;
        sous_cousu_prefixe(abrTmp,pre,suc,arbre);
    }
    
}


void cousu_inserer(int valeur,T_Arbre_C *arbre){// meme principe avec abr_inserer
    if (*arbre == NULL){
        *arbre = cousu_creer_noeud(valeur);          
    } 
    if  ((*arbre)->val<valeur){
        (*arbre)->droitSuc=0;
        cousu_inserer(valeur,&(*arbre)->droit);
    }
        
    if  ((*arbre)->val>valeur){
        (*arbre)->gauchePre=0;
        cousu_inserer(valeur,&(*arbre)->gauche);      
    }
       
    if ((*arbre)->droit == NULL && (*arbre)->val < valeur){
        T_Noeud_C *nouveau = cousu_creer_noeud(valeur);
        (*arbre)->droit = nouveau;
        //(*arbre)->droitSuc=0;
    }
    if ((*arbre)->gauche == NULL && (*arbre)->val > valeur){
        T_Noeud_C *nouveau = cousu_creer_noeud(valeur);
        (*arbre)->gauche = nouveau;
        //(*arbre)->gauchePre=0;
    }
}

void cousu_infixe(T_Arbre_C *arbre){
    if (*arbre==NULL)
        printf("rien à afficher\n");
    else{
        T_Arbre_C arbreTmp=*arbre;
        int suc,pre;
        if (arbreTmp==NULL){
            printf("rien à afficher\n");
        }else{
            while (arbreTmp->gauche!=NULL){
                arbreTmp=arbreTmp->gauche;
            }

            do{
                pre = chercherPre(arbreTmp->val,*arbre);
                suc = chercherSuc(arbreTmp->val,*arbre);
    //            if (arbreTmp->gauche != NULL && arbreTmp->droit != NULL)
    //                printf("Noeud --> %d\n "
    //                         "     --> FG(0) : %d -- FD(0) : %d\n",arbreTmp->val,arbreTmp->gauche->val,arbreTmp->droit->val);
    //            else{
                    if (pre!=-1 && suc!=-1)    
                        printf("Noeud --> %d\n "
                                "     --> FG(%d) : %d -- FD(%d) : %d\n",arbreTmp->val,arbreTmp->gauchePre,pre,arbreTmp->droitSuc,suc);
                    if (pre==-1 && suc!=-1)    
                        printf("Noeud --> %d\n "
                                "     --> FG(%d) : NULL -- FD(%d) : %d\n",arbreTmp->val,arbreTmp->gauchePre,arbreTmp->droitSuc,suc);
                    if (pre!=-1 && suc==-1)    
                        printf("Noeud --> %d\n "
                                "     --> FG(%d) : %d -- FD(%d) : NULL\n",arbreTmp->val,arbreTmp->gauchePre,pre,arbreTmp->droitSuc);
                    if (pre==-1 && suc==-1)    
                        printf("Noeud --> %d\n "
                                "     --> FG(%d) : NULL -- FD(%d) : NULL\n",arbreTmp->val,arbreTmp->gauchePre,arbreTmp->droitSuc);    
                //}
                if (suc!=-1)
                    arbreTmp=chercher_valeur_C(suc,*arbre);
            }while (suc!=-1);
        }    
    }

    
}

void abr_to_cousu(T_Arbre abr, T_Arbre_C *clone, T_Noeud_C* parent){
    if (abr == NULL)
            return;

    *clone = cousu_creer_noeud(abr->val);
    if (parent != NULL)
        if (parent->val > (*clone)->val)
            parent->gauche = *clone;
        else
            parent->droit = *clone;

  
    if (abr->gauche != NULL) {
        (*clone)->gauchePre=0;
        abr_to_cousu(abr->gauche, &((*clone)->gauche), *clone);

    }

    if (abr->droit != NULL) {
        (*clone)->droitSuc=0;
        abr_to_cousu(abr->droit, &((*clone)->droit), *clone);

    }   
        
}