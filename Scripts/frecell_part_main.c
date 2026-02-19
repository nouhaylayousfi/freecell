#include<stdio.h>
#include "freecell_part_c.c"
#include "freecell_part1.h"

int main (){
	printf("___________________________________________________Freecell___________________________________________________\n");
	
	Carte **cartes = initialiser_cartes();
	melanger_cartes (cartes);
	
	//création des piles 
	Element *pile1=mettre_cartes_dans_piles(cartes, 1);
	Element *pile2=mettre_cartes_dans_piles(cartes, 2);
	Element *pile3=mettre_cartes_dans_piles(cartes, 3);
	Element *pile4=mettre_cartes_dans_piles(cartes, 4);
	Element *pile5=mettre_cartes_dans_piles(cartes, 5);
	Element *pile6=mettre_cartes_dans_piles(cartes, 6);
	Element *pile7=mettre_cartes_dans_piles(cartes, 7);
	Element *pile8=mettre_cartes_dans_piles(cartes, 8);
	
	//initialiser les piles comme étant des structures 
	Pile* p1=initialiser_pile(pile1,"pile1");
	Pile* p2=initialiser_pile(pile2,"pile2");
	Pile* p3=initialiser_pile(pile3,"pile3");
	Pile* p4=initialiser_pile(pile4,"pile4");
	Pile* p5=initialiser_pile(pile5,"pile5");
	Pile* p6=initialiser_pile(pile6,"pile6");
	Pile* p7=initialiser_pile(pile7,"pile7");
	Pile* p8=initialiser_pile(pile8,"pile8");
	
	//stocker les piles dans un tableau 
	Pile **tab_piles;
	tab_piles=mettre_pile_en_tab(p1,p2,p3,p4,p5,p6,p7,p8);
	
	//initialiser les zones 
	Carte **zone2;initialiser_zone2(&zone2);
	Element **zone3;initialiser_zone3(&zone3);
	
	//les opérations sur les piles
	char op;
	
	do {
		display(tab_piles);
		display_zone2(zone2);
		display_zone3(zone3);
		printf(RED"_______________________________________________________________________________________________________\n"RESET);
		printf("\nPour deplacer entre les piles : 'd' \n");
		printf("Pour deplacer vers l une des zones : 'z'\n");
		printf("Pour importer de la zone 2 : 'i' \n");
		printf("Pour deplacer de la zone 2 vers 3 : 'f' \n");
		printf("Lorsque le nom la pile est demande taper pilei tq i le numero de la colonne !! \n");
		printf("Pour quitter le jeu : 'x' \n");
		printf(RED"_______________________________________________________________________________________________________\n"RESET);
		printf("\nentrez la lettre de l operation :\t");
		scanf(" %c",&op);
		switch (op){
			case 'd':{
				//déplacement_entre_piles
				char current[6],destination[6];
				printf("Entrez cuurent pile : \t");
				scanf("%s",current);
				printf("\nEntrez destination pile : \t");
				scanf("%s",destination);
				if (get_pile(current,tab_piles) == NULL || get_pile(destination,tab_piles) ==NULL){
					break;
				}
				deplacement_entre_piles((get_pile(current,tab_piles)),(get_pile(destination,tab_piles)),zone2);
				break;
			}
			case 'z':{
				//déplacer vers zone i
				int i;
				printf("entrez num de la zone");
				scanf("%d",&i);
				switch (i){
					case 2:{ 
						//déplacement vers zone2 
						deplacement_vers_zone2(zone2,tab_piles);
						break;
					}
					case 3:
						//déplacement vers zone3
						deplacer_vers_zone3(zone3,tab_piles);
						break;
				}
				break;
			}
			case 'i':{
				//importer de zone2 
				importer_du_zone2_vers_pile(zone2,tab_piles);
				break;
			}
			case 'f':{
				//déplacement de la zone 2 vers la zone 3
				from_zone2_to_zone3(zone2,zone3);
				break;
			}				
				break;
		}	
	}while (op != 'x' || blocage ( tab_piles, zone2 ) == 1 || gagne (zone3) == 1);
	
	if (blocage ( tab_piles, zone2 ) == 1){
		printf("\n ___partie bloquee___!!!\n");
	}
	if (gagne (zone3) == 1){
		printf("\nBravo !! Vous avez gagne le jeu !!\n");
	}
	
	
	return 0;
	  
}