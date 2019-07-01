/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tp4_abr.h
 * Author: dnminh
 *
 * Created on 5 décembre 2018, 22:40
 */

#ifndef TP4_ABR_H
#define TP4_ABR_H

#include <stdlib.h>
#include <stdio.h>
typedef struct Noeud{
    int val;
    struct Noeud *gauche;
    struct Noeud *droit;    
}T_Noeud;

typedef T_Noeud *T_Arbre;

T_Noeud *abr_creer_noeud(int valeur);
void abr_prefixe(T_Arbre abr);
void abr_inserer(int valeur,T_Arbre *abr);
T_Noeud *chercher_valeur(int valeur,T_Arbre abr);
void abr_supprimer(int valeur,T_Arbre *abr);
void abr_clone(T_Arbre original, T_Arbre *clone, T_Noeud* parent);


#endif /* TP4_ABR_H */

