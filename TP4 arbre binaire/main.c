/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dnminh
 *
 * Created on 5 décembre 2018, 22:39
 */

#include <stdio.h>
#include <stdlib.h>
#include "tp4_abr.h"
#include "tp4_cousu.h"

int main(int argc, char** argv) {

    T_Arbre abr=NULL;
    T_Arbre clon=NULL;
    T_Arbre_C arbre=NULL;
    T_Arbre_C clon_C=NULL;
    int x;
    int cont_inserer=1;
    int opt=1;
    int sup;

//    abr_inserer(11,&abr);   
//    abr_inserer(2,&abr);  
//    abr_inserer(2,&abr); 
//    
//    abr_inserer(2,&abr); 
//    
//    abr_inserer(11,&abr); 
////
////
//    abr_inserer(1,&abr);
////
//    abr_inserer(6,&abr);
////    abr_inserer(2,&abr); 
//    abr_inserer(14,&abr);
//    abr_inserer(17,&abr);
//    abr_inserer(15,&abr);
//    abr_inserer(13,&abr);
//    abr_inserer(16,&abr);
//    abr_inserer(18,&abr);
//    abr_inserer(12,&abr);
    
    int c=0;

    while (opt!=0){
        printf("ouvrir la liste d'options ? [OUI---1]  /  [NON---0]\n");
        scanf("%d",&opt);
        int cont=1;
        if (opt==0)
            break;

        printf("\n");
        printf("1. Créer un ABR\n");
        printf("2. Afficher l’ABR en préfixe\n");
        printf("3. Insérer une valeur dans l’ABR\n");
        printf("4. Supprimer une valeur de l’ABR\n");
        printf("5. Cloner l’ABR\n");
        printf("6. Afficher le clone en préfixe\n");
        printf("7. Créer un arbre binaire cousu à partir d’un ABR\n");
        printf("8. Afficher l’arbre binaire cousu en préfixe\n");
        printf("9. Afficher l’arbre binaire cousu en infixe\n");
        printf("10. Insérer une valeur dans l’arbre binaire cousu\n");
        printf("11. Quitter\n");
        printf("===========================================\n");
        scanf("%d",&c);

        switch (c) {
            case 1:
                printf("===========================================\n");
                printf("l'ABR a été crée\n");
                printf("===========================================\n");
                abr=NULL;
                break;
            case 2:
                printf("=========Afficher l’ABR en préfixe=========\n");
                abr_prefixe(abr);
                printf("===========================================\n");
                break;
            case 3:
                printf("===========================================\n");
                do{
                    printf("inserez la valeur (0 pour finir):\n");
                    scanf("%d",&x);
                    if (x!=0)
                        abr_inserer(x,&abr);

                    if (x==0)
                        break;
                }while (x!=0);
                printf("===========================================\n");
                break;
            case 4:
                printf("===========================================\n");
                printf("donnez la valeur à supprimer :\n");
                
                scanf("%d",&sup);
                abr_supprimer(sup,&abr);
                printf("===========================================\n");
                break;
            case 5:
                printf("=================Cloner l’ ABR================\n");
                abr_clone(abr,&clon,NULL);
                printf("l'ABR a été cloné\n");
                printf("===========================================\n");
                break;
            case 6:
                printf("=============Afficher le clone en préfixe==========\n");
                abr_prefixe(clon);
                printf("===========================================\n");
                break;
            case 7:
                printf("===========================================\n");
                abr_to_cousu(abr,&arbre,NULL);
                printf("l'arbre binaire cousu a été crée\n");
                printf("===========================================\n");
                break;
            case 8:
                printf("======Afficher l'arbre binaire cousu en préfixe=======\n");
                cousu_prefixe(arbre);             
                
                printf("===========================================\n");
                break;
            case 9:
                printf("======Afficher l’arbre binaire cousu en infixe========\n");
                cousu_infixe(&arbre);             
                printf("===========================================\n");
                break;
            case 10:
                printf("===========================================\n");

                do{
                    printf("inserez la valeur (0 pour finir) :\n");
                    scanf("%d",&x);
                    if (x!=0)
                        cousu_inserer(x,&arbre);
                    if (x==0)
                        break;
                }while (x!=0);
                printf("===========================================\n");
                break;
            case 11:
                opt=0;
                free(abr);
                free(arbre);
                free(clon);
                free(clon_C);
                break;

            default:
                break;
        }

    }
   
    return (EXIT_SUCCESS);
}

