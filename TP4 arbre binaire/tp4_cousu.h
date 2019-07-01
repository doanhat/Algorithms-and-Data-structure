/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tp4_cousu.h
 * Author: dnminh
 *
 * Created on 18 décembre 2018, 19:22
 */

#ifndef TP4_COUSU_H
#define TP4_COUSU_H

#include <stdlib.h>
#include <stdio.h>
#include "tp4_abr.h"
typedef struct Noeud_C{
    int val;
    struct Noeud_C *gauche;
    struct Noeud_C *droit;
    int gauchePre;// 0 vrai 1 faux
    int droitSuc; // 0 vrai 1 faux
}T_Noeud_C;

typedef T_Noeud_C *T_Arbre_C;

void cousu_prefixe(T_Arbre_C arbre);
void cousu_inserer(int valeur,T_Arbre_C *arbre);
void cousu_infixe(T_Arbre_C *arbre);
void abr_to_cousu(T_Arbre abr, T_Arbre_C *clone, T_Noeud_C* parent) ;
T_Noeud_C *cousu_creer_noeud(int valeur);
T_Noeud_C *chercher_valeur_C(int valeur,T_Arbre_C abr);
int chercherPre(int valeur,T_Arbre_C arbre);
int chercherSuc(int valeur,T_Arbre_C arbre);
void sous_cousu_prefixe(T_Arbre_C arbreT,int pre,int suc, T_Arbre_C arbre);

#endif /* TP4_COUSU_H */

