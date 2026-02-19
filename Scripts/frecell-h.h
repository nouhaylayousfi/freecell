#include <stdio.h>
#ifndef CARTE_H
#define CARTE_H

typedef struct {
	char  *nom ;
	char *couleur ;
	char *type ;
}Carte;

typedef struct element {
	Carte *ct;
	struct element *next ;
}Element ;

typedef struct pile{
	char *nom_pile;
	Element *elmt;
}Pile;

//fonction qui teste la couleur de chaque carte 
char test_couleur(Carte *cart);

//fonction qui teste le type de chaque carte (coeur , carreau , trèfle ,pique ) 
char test_type(Carte *cart);

//fonction qui crée une pile de carte 
Element *Create_element(Carte *cart);

// fonction qui permet d'ajouter un élement au tête de la pile
void push (Carte *carte ,Element **pile);

// fonction qui retourne la tête de la pile
Carte* peek(Element *pile);

// fonction qui supprime la tête de la pile
void pop(Element **pile);

// fonction qui calcule le nombre de case vide dans la zone 2
int nombre_de_case_vide(Carte *zone2[4]);

// fonction qui crée une carte 
Carte *Create_carte (const char *nom , const char *couleur ,const char *type );

// fonction qui affiche une carte 
void display_carte(Carte *carte);

// fonction qui affiche la pile composée des cartes 
void display_pile(Element **pile,int i);

//fonction qui vérifie si le mouvement entre deux piles de cartes est possible ou non 
int scan(Element *current_pile , Element *destination_pile);

//fonction qui déplace un nombre de carte d'une pile à une autre 
void deplacement_entre_piles(Element **current_pile , Element **destination_pile, Carte **zone2);

// fonction stocke le nom d'une pile et son adresse dans une structure Pile 
Pile *initialiser_pile(Element *pile,char *nom_pile);

// fonction qui stocke les adresses des Pile (structures) dans un tableau 
Pile **mettre_pile_en_tab(Pile *p1,Pile *p2,Pile *p3,Pile *p4,Pile *p5,Pile *p6,Pile *p7,Pile *p8);

// fonction qui cherche par nom de pile son adresse 
Element **get_pile(char *nom,Pile **tab_piles);

// fonction qui initialise les cartes (dans un tableau de Carte )
Carte **initialiser_cartes();

// mélanger le tableau des cartes dans un ordre aléatoire 
void *melanger_cartes (Carte **Cartes);

// distribuer les cartes sur les 8 piles 
Element *mettre_cartes_dans_piles(Carte **cartes, int num_pile);

// initialiser les cases de la zone2 à NULL
void initialiser_zone2(Carte ***cartes);

// initialiser les cases de la zone3 à NULL
void initialiser_zone3(Element ***zone3);

//fonction qui déplace une carte d'une pile vers la zone 2
void deplacement_vers_zone2(Carte **zone2,Pile **tab_piles);

// fonction qui déplace une carte de la zone2 vers une pile 
void importer_du_zone2_vers_pile(Carte **zone2 ,Pile **tab_piles);

// fonction qui déplace une carte  d'une pile vers la zone3
void deplacer_vers_zone3(Element **zone3,Pile **tab_piles);

// afficher le tableau des piles
void display(Pile **tab_piles );

// afficher la zone2
void display_zone2(Carte **zone2);

// afficher la zone3
void display_zone3(Element **zone3);

// déplacer une carte de la zone2 vers la zone3
void from_zone2_to_zone3(Carte **zone2,Element **zone3);

// fonction qui compte le nombre des cartes dans une pile 
int count_pile(Element *pile);

// fonction qui détécte l'impossibilité de déplacer les cartes entre les piles 
int blocage_collone (Pile **tab_piles);

// fonction qui teste la possibilité de déplacer de ou vers la zone2
int possibilite_zone2(Carte **zone2 , Pile **tab_piles);

// fonction qui détécte la situation de blocage du jeu 
int blocage ( Pile **tab_piles, Carte **zone2 );

// fonction qui lance la fin du jeu par gagne 
int gagne (Element **zone3);

#endif 
 
