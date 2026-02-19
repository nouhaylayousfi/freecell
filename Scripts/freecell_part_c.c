#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "freecell_part1.h"
#include <windows.h>

// Définition des codes de couleur ANSI
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"
#define BLACK   "\x1b[30m"
#define WHITE   "\x1b[47m"
#define black  "\x1b[30;47m"
#define red    "\x1b[31;47m"

// Fonction pour activer la prise en charge des séquences ANSI sur Windows
void enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode))
        {
            SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        }
    }
}

char test_couleur(Carte *cart){
	if(strcmp(cart->couleur ,"black")==0){
		return 'b';
	}
	return 'r';
}

char test_type(Carte *cart){
	if (strcmp(cart->type ,"♥") == 0){
		return 'h';
	}
	else if (strcmp(cart->type , "♣") == 0){
		return 't';
	}	
	else if (strcmp(cart->type , "♠") == 0){
		return 'p';
	}
	else if (strcmp(cart->type , "♦") == 0){
		return 'c';
	}	
	
}

Element *Create_element(Carte *cart){
	Element *neew=(Element*)malloc(sizeof(Element));
	neew->ct=cart;
	neew->next=NULL;
	return neew;
}

void push (Carte *carte ,Element **pile){
	if ((*pile) == NULL){
		(*pile) = Create_element(carte);
		return ;
	}
	Element *neew=Create_element(carte);
	neew->next=(*pile);
	(*pile)=neew;	
}

Carte* peek(Element *pile){
	return (pile->ct);
}

void pop(Element **pile){
	if (*pile != NULL) {
        Element *temp = *pile;
        *pile = (*pile)->next;
        free(temp);
    }
}

int nombre_de_case_vide(Carte *zone2[4]){
	int i,count=0;
	for(i=0;i<4;i++){
		if (zone2[i] == NULL){
			count++;
		}
	}
	return count ;
}

Carte *Create_carte (const char *nom , const char *couleur ,const char *type ){
	Carte *neew=(Carte*)malloc (sizeof(Carte));
	neew->couleur=strdup(couleur);
	neew->nom=strdup(nom);
	neew->type=strdup(type);
	return neew;
}

void display_carte(Carte *carte){
	enableANSI(); 
	SetConsoleOutputCP(CP_UTF8); // Définir le code page de la console sur UTF-8
	if (test_couleur(carte) == 'r' ){
		printf(red "%s      %s" RESET , carte->nom,carte->type);
		printf("\t ");
		
	}
	else {
		printf(black "%s      %s" RESET , carte->nom,carte->type);
		printf("\t ");
	}
	
}

void display_pile(Element **pile,int i){
	printf("\n___ colonne %d ___\n",i);
	//printf("\n");
	Element *pile_inter = NULL ;
	Element **p;
	for(p=pile;*p!=NULL;p=&(*p)->next){
		push (((*p)->ct),&pile_inter);
	}

	for(p=&pile_inter;*p!=NULL;p=&(*p)->next){
		display_carte((*p)->ct);

	}
	printf(RESET".\n");
}

int scan(Element *current_pile , Element *destination_pile){
	if (current_pile != NULL && destination_pile != NULL){
		int condition1 = (atoi(peek(current_pile)->nom) == (atoi(peek(destination_pile)->nom)-1));
		int condition2 = (strcmp((peek(current_pile)->nom),"Q") == 0 && strcmp((peek(destination_pile)->nom),"K") == 0);
		int condition3 = (strcmp((peek(current_pile)->nom),"J") == 0 && strcmp((peek(destination_pile)->nom),"Q") == 0);
		int condition4 = ((atoi(peek(current_pile)->nom) == 10)      && (strcmp((peek(destination_pile)->nom),"J") == 0));
		int condition5 = (strcmp((peek(current_pile)->nom),"A") == 0 && (atoi(peek(destination_pile)->nom) == 2)) ;
		int condition6 = (test_couleur(peek(current_pile)) != test_couleur(peek(destination_pile)));
		//printf("%d %d %d %d %d %d\t",condition1,condition2,condition3,condition4,condition5,condition6);
		if ((condition1 == 1  || condition2 ==1 || condition3 == 1 || condition4 == 1 || condition5 == 1) && condition6 == 1){
			return 1;
		}
		else if ((condition1 == 1  || condition2 ==1 || condition3 == 1 || condition4 == 1 || condition5 == 1) && condition6 == 0){
			return 2;
		}
		return 0;
	}
	return 0;

}

void deplacement_entre_piles(Element **current_pile , Element **destination_pile, Carte **zone2){
	int count1,count2=0 ,i;
	Element *interme_pile =NULL;
	printf("entrez le nombre des cartes a deplacer:\t");
	scanf("%d",&count1);
	//printf("%d",scan((*current_pile),(*destination_pile)));
	Element *p;p=*current_pile;
	do {
			push(p->ct,&interme_pile);
			p=p->next;
			count2++;
		}while (count2 < count1);
		
	if ((scan((interme_pile),(*destination_pile)) == 1 ||(*destination_pile) == NULL ) && count1 <= nombre_de_case_vide(zone2) + 1){
		for(i=0 ; i<count2 ;i++){
			push(peek(interme_pile),(destination_pile));
			pop(&interme_pile);
			pop(current_pile);
		}
	}
	return;
}

Pile **mettre_pile_en_tab(Pile *p1,Pile *p2,Pile *p3,Pile *p4,Pile *p5,Pile *p6,Pile *p7,Pile *p8){
	
	Pile **tab_piles=(Pile**)malloc(sizeof(Pile*)*8);
	tab_piles[0]=p1;
	tab_piles[1]=p2;
	tab_piles[2]=p3;
	tab_piles[3]=p4;
	tab_piles[4]=p5;
	tab_piles[5]=p6;
	tab_piles[6]=p7;
	tab_piles[7]=p8;
	return tab_piles;
}

Pile *initialiser_pile(Element *pile,char *nom_pile){
	Pile *P=(Pile*)malloc(sizeof(Pile));
	P->elmt=pile;
	P->nom_pile=nom_pile;
	return P ;
}

Element **get_pile(char *nom,Pile **tab_piles){
	int i ;
	for(i=0;i<8;i++){
		if (strcmp(nom,tab_piles[i]->nom_pile)==0){
			return &(tab_piles[i]->elmt);
		}
	}
	printf("Veuillez entrez un nom de colonne valide !!");
	return NULL;
}

Carte **initialiser_cartes(){
	Carte **cartes=(Carte**)malloc(sizeof(Carte*)*52);
	
	char *noms[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
	char *types[] = {"♠", "♣", "♦", "♥"};
	char *couleurs[] ={"black","red"};
	int index = 0,i,j;
    for (i = 0; i < 13; i++) {
        for (j = 0; j < 2; j++) {
            cartes[index++] = Create_carte(noms[i], couleurs[0], types[j]);
        }
        for (j = 2; j < 4; j++) {
            cartes[index++] = Create_carte(noms[i], couleurs[1], types[j]);
        }
    }
    return cartes;
}

Element *mettre_cartes_dans_piles(Carte **cartes, int num_pile){
	int i;
	switch (num_pile){
		case 1:{
			Element *pile1=Create_element(cartes[0]);
			for(i=1;i<7;i++){
				push(cartes[i],&pile1);
			}
			return pile1;
		}
			
		case 2:{
			Element *pile2=Create_element(cartes[7]);
			for(i=8;i<14;i++){
				push(cartes[i],&pile2);
			}
			return pile2;
		}
		case 3:{
			Element *pile3=Create_element(cartes[14]);
			for(i=15;i<21;i++){
				push(cartes[i],&pile3);
			}
			return pile3;
		}
		case 4:	{
			Element *pile4=Create_element(cartes[21]);
			for(i=22;i<28;i++){
				push(cartes[i],&pile4);
				}
			return pile4;
			
		}
			
		case 5:{
			Element *pile5=Create_element(cartes[28]);
			for(i=29;i<34;i++){
				push(cartes[i],&pile5);
			}
			return pile5;
		}		
			
		case 6:{
			Element *pile6=Create_element(cartes[34]);
			for(i=35;i<40;i++){
				push(cartes[i],&pile6);
			}
			return pile6;
		}
			
		case 7:{
			Element *pile7=Create_element(cartes[40]);
			for(i=41;i<46;i++){
				push(cartes[i],&pile7);
			}	
			return pile7;
		}
			
		case 8:{
			Element *pile8=Create_element(cartes[46]);
			for(i=47;i<52;i++){
				push(cartes[i],&pile8);
			}	
			return pile8;
		}
			
		default :
			printf("erreur");
	}
}

void *melanger_cartes (Carte **Cartes){
	srand(time(NULL));
	int i ;Carte *temp;
	for (i=51;i>0;i--){
		int j = rand() % (i+1);
		temp = Cartes[i];
        Cartes[i] = Cartes[j];
        Cartes[j] = temp;
	}
}

void initialiser_zone2(Carte ***cartes){
	int i ;
	*cartes=(Carte**)malloc(sizeof(Carte*)*4);
	for (i=0;i<4;i++){
		(*cartes)[i]=NULL;
	}
}

void deplacement_vers_zone2(Carte **zone2,Pile **tab_piles){
	char nom_pile[6];
	Element **pile = NULL;
	do {
		printf("entrez la pile dont vous souhaitez retirez le peek\n");
		scanf("%s",nom_pile);
		pile=get_pile(nom_pile,tab_piles);
	}while (pile == NULL);

	int i ;
	for(i=0;i<4;i++){
		if(zone2[i] == NULL){
			Carte *carte_temp = peek(*pile); // Stocker l'adresse de la carte en haut de la pile
            zone2[i] = carte_temp;
			pop(pile);
			return ;
		}
	}
	printf("\n la zone 2 est pleine !! \n");
}

void importer_du_zone2_vers_pile(Carte **zone2 ,Pile **tab_piles){
	int num_plage;char nom_pile[6];
	Element **pile_dest=NULL;
	do {
		printf("entrez num de la plage du zone 2 :\t");
		scanf("%d",&num_plage);
		printf("entrez la pile :\t");
		scanf("%s",nom_pile);
		pile_dest=get_pile(nom_pile,tab_piles);
	}while (pile_dest == NULL || (num_plage<1 || num_plage >4));
	printf("\n");
	int i ;
	for(i=0;i<4;i++){
		if(zone2[i] == NULL){
			printf("plage impossible");
			return; 
		}
		if(i == num_plage-1){
			Element *pil_cur=Create_element(zone2[i]);
			if (scan(pil_cur,*pile_dest) == 1) {
				deplacement_entre_piles(&pil_cur,pile_dest,zone2);
				zone2[i]=NULL;
				return ;
			}
			return ;
		}
	}
}

void deplacer_vers_zone3(Element **zone3,Pile **tab_piles){
	char nom_pile[6];	
	Element **pile= NULL;
	do {
		printf("\nentrez le nom de la pile :\t");
		scanf("%s",nom_pile);
		pile=get_pile(nom_pile,tab_piles);
	}while (pile == NULL);
	
	if (test_type(peek(*pile)) == 'h'){
		if (zone3[0] == NULL && strcmp(peek(*pile)->nom,"A") == 0 ){
			Element *pile_coeur = Create_element(peek(*pile));
			zone3[0]=pile_coeur;
			pop(pile);
		}
		
		else if (scan(zone3[0],*pile ) == 2 && zone3[0] != NULL){
			push(peek(*pile),&zone3[0]);
			pop(pile);
		}
		else{
			printf("uuuuu");
		}
	}
	else if (test_type(peek(*pile)) == 't'){
		if (zone3[1] == NULL && strcmp(peek(*pile)->nom,"A") == 0){
			Element *pile_trefle = Create_element(peek(*pile));
			zone3[1]=pile_trefle;
			pop(pile);
		}
		else if (scan(zone3[1],*pile ) == 2 && zone3[1] != NULL){
			push(peek(*pile),&zone3[1]);
			pop(pile);
		}
	}
	else if (test_type(peek(*pile)) == 'c'){
		if (zone3[2] == NULL && strcmp(peek(*pile)->nom,"A") == 0){
			Element *pile_carreau = Create_element(peek(*pile));
			zone3[2]=pile_carreau;
			pop(pile);
		}
		else if (scan(zone3[2],*pile ) == 2 && zone3[2] != NULL){
			push(peek(*pile),&zone3[2]);
			pop(pile);
		}
	}	
	else if ( test_type(peek(*pile)) == 'p'){
		if (zone3[3] == NULL && strcmp(peek(*pile)->nom,"A") == 0){
			Element *pile_pique = Create_element(peek(*pile));
			zone3[3]=pile_pique;
			pop(pile);
		}
		else if (scan(zone3[3],*pile ) == 2 && zone3[3] != NULL){
			push(peek(*pile),&zone3[3]);
			pop(pile);
		}
	}
}
	

void initialiser_zone3(Element ***zone3){
	int i ;
	*zone3=(Element**)malloc(sizeof(Element*)*4);
	for (i=0;i<4;i++){
		(*zone3)[i]=NULL;
	}
}

void display(Pile **tab_piles ){
	for (int i = 0; i < 8; i++) {
    	display_pile(&tab_piles[i]->elmt, i + 1);
	}
    
}

void display_zone2(Carte **zone2){
	int i;
	printf("\n__________________________________________________zone2__________________________________________________\n\n");
	for(i = 0 ; i<4; i++){
		if(zone2[i] == NULL){
			printf("NULL\t\t\t");
		}
		else{
			display_carte(zone2[i]);
			printf("\t\t\t");
		}
	}
	printf("\n \n");
	return;
}

void display_zone3(Element **zone3){
	int i;
	printf("\n__________________________________________________Zone3__________________________________________________\n\n");
	for(i = 0 ; i<4; i++){
		if(zone3[i] == NULL){
			printf("NULL\t\t\t");
		}
		else{
			display_carte((zone3)[i]->ct);
			printf("\t\t\t");
		}
	}
	printf("\n\n");
}

void from_zone2_to_zone3(Carte **zone2,Element **zone3){
	int d,e;
	printf("\nentrez le numero de la plage de la zone2 dont vous voulez deplacer : ");
	scanf("%d",&d);
	d=d-1;
	printf("\nentrez le numero de la plage de la zone3 dont vous voulez deplacer : ");
	scanf("%d",&e);
	e=e-1;
	if (zone2[d] == NULL){
		printf("zone vide !! \n");
		return ;
	}
	Element *tmp =Create_element(zone2[d]);
	if(scan(zone3[e],tmp) == 2){
		push(zone2[d],&zone3[e]);
		zone2[d] = NULL;
		free(tmp);
	}
}


int blocage_collone (Pile **tab_piles){
	int i , j ;
	for (i = 0; i <8 ; i++){
		for (j = 0 ;j<8 ; j++){
			if ( scan (tab_piles[i]->elmt ,tab_piles[j]->elmt) == 1){
				return 0;
			}
		}
	}
	return 1; 
}

int possibilite_zone2(Carte **zone2 , Pile **tab_piles){
	int i , j;
	for (i = 0; i < 8 ;i++){
		for (j = 0 ;j <4 ;j++){
			if (zone2[j] == NULL || tab_piles[i] == NULL){
				return 0;
			}
			Element *e=Create_element(zone2[j]);
			if (scan (e , tab_piles[i]->elmt) == 1){
				return 0;
			}
			free(e);
		}
	
	}
	return 1;
}

int blocage ( Pile **tab_piles, Carte **zone2 ){
	int cdt1 = (blocage_collone (tab_piles) == 1);
	int cdt2 = (possibilite_zone2(zone2 , tab_piles) == 1);
	if (cdt1 == 1 && cdt2 == 1 ){
		return 1;
	}
	return 0;
}

int count_pile(Element *pile){
	Element *p =NULL;
	int count = 0;
	for (p=pile ; p!=NULL ; p=p->next){
		count ++;
	}
	return count;
}

int gagne (Element **zone3){
	int i , cnt =0 ; 
	for (i=0 ; i<4 ; i++){
		if (zone3[i] != NULL && count_pile(zone3[i]) == 13){
			cnt ++;
		}
	}
	if (cnt == 4){
		return 1;
	}
	return 0;
}
	
