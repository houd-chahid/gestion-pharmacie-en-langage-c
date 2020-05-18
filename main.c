#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
//projet de gestion de pharmacie realisé par CHAHID Houd


struct medicament{
    char nom[50],codebar[50];
    int quantite;
	float prix;};
int main(int argc, char *argv[]) {
	FILE *fichierenregistre;
	fichierenregistre = fopen ("stock-pharmacie.dat", "r"); 
	struct medicament tab[1000],medajoute[1000];//commande[1000],
	struct medicament unitem;
	char options[5][40],key,key2,identifiantduproduit[50],headline[72];
	char linebreak[73]="+-------+---------------------+-----------------+-----------+---------+\n";
    int i = 0,k = 0,selection = 0,selectionouinon = 1,medicaments=0, autremedicament=1,trouveoupas=-1,inferieura=-1,quantite_a_acheter=0,x,nomexiste=0,codebarexiste=0;
	float totaldelacommande=0,sommedonnee=0,rendudelasommedonne=0;
	void enreg(){
	printf("\nEnregistrement des fichiers... \n");
	fichierenregistre = fopen("stock-pharmacie.dat", "w"); 
	for(i=0;i<medicaments;i++)fwrite(&tab[i], sizeof(struct medicament), 1, fichierenregistre);
	fclose(fichierenregistre);
	printf("Enregistre avec succes.\n");}
	printf("Bienvenue!\n");
	if (fichierenregistre == NULL){
		fclose(fichierenregistre); 
		printf("Creation de fichier de base de donnes... "); 
        fichierenregistre = fopen("stock-pharmacie.dat", "w");
        fclose (fichierenregistre);
        printf("Base de donnees cree avec succes.\n");} 
    else {while(fread(&unitem, sizeof(struct medicament), 1, fichierenregistre)){
    	 	strcpy(tab[medicaments].nom,unitem.nom);
			strcpy(tab[medicaments].codebar,unitem.codebar);
			tab[medicaments].quantite = unitem.quantite;
			tab[medicaments].prix = unitem.prix;
			medicaments++;}
			fclose(fichierenregistre);} 
	printf("%d medicaments dans la base de donnees.\n",medicaments);
    system("PAUSE");
    while(1){//grande boucle
	strcpy(options[0], "Ajouter un nouveau medicament  [X]");
    strcpy(options[1], "Passer une nouvelle commande   [ ]");
    strcpy(options[2], "Verifier le stock disponible   [ ]");
    strcpy(options[3], "Gerer le stock                 [ ]");
    strcpy(options[4], "Sortir du programme            [ ]");
    options[0][32] = ' ';
    options[1][32] = ' ';
    options[2][32] = ' ';
    options[3][32] = ' ';
    options[4][32] = ' ';
    options[selection][32] = 'X';
    while(1)
    {   system("cls");
        printf("  Que voulez vous faire?\n\n");
        printf("-%s\n-%s\n-%s\n-%s\n-%s", options[0], options[1], options[2], options[3], options[4]);
        key = getch();
        key2 = 0;
        if(key == -32)          key2 = getch();  
        else if(key == 13)     	break;     
        else                    continue; 
        if(key2 == 80)          selection++;
        else if(key2 == 72)     selection--;    
        if(selection < 0)       selection = 4;
        else if(selection > 4)       selection = 0;
        options[0][32] = ' ';
        options[1][32] = ' ';
        options[2][32] = ' ';
        options[3][32] = ' ';
        options[4][32] = ' ';
        options[selection][32] = 'X';}
 	int ouinon(char question[50]) {
	    char reponse[2][12];
	    selectionouinon = 1;
    	strcpy(reponse[0], "Non    [ ]");
		strcpy(reponse[1], "Oui    [X]");
        while(1){
			system("cls");
        	printf("  %s\n",question);
      		printf("%s\n%s", reponse[1], reponse[0]);
        	key = getch();
        	key2 = 0;
        	if(key == -32)          key2 = getch();  
        	else if(key == 13)     	break;     
        	else                    continue; 
        	if(key2 == 80)          selectionouinon--;
        	else if(key2 == 72)     selectionouinon++;    
        	if(selectionouinon < 0)       selectionouinon = 0;
        	else if(selectionouinon > 1)       selectionouinon = 1;
        	reponse[0][8] = ' ';
        	reponse[1][8] = ' ';
        	reponse[selectionouinon][8] = 'X';}
		return selectionouinon;}  
	 	int gererstockquestion(char question[50]) {
	    char reponse[4][40];
	    selectionouinon = 0;
    	strcpy(reponse[0], "Modifier quantite [X]");
		strcpy(reponse[1], "Modifier prix     [ ]");
		strcpy(reponse[2], "Supprimer produit [ ]");
		strcpy(reponse[3], "Annuler           [ ]");
        while(1){
			system("cls");
        	printf("\tVous avez selectionne '%s'. Que voulez-faire du choix: ",question);
      		printf("\n%s\t%s\t%s\t%s", reponse[0], reponse[1], reponse[2], reponse[3]);
        	key = getch();
        	key2 = 0;
        	if(key == -32)          key2 = getch();  
        	else if(key == 13)     	break;     
        	else                    continue; 
        	if(key2 == 75)          selectionouinon--;
        	else if(key2 == 77)     selectionouinon++;    
        	if(selectionouinon < 0)       selectionouinon = 3;
        	else if(selectionouinon > 3)       selectionouinon = 0;
        	reponse[0][19] = ' ';
        	reponse[1][19] = ' ';
        	reponse[2][19] = ' ';
        	reponse[3][19] = ' ';
        	reponse[selectionouinon][19] = 'X';}
		return selectionouinon;}  	
    system("cls");
    system("color A");
    printf("%s",options[selection]);
    for(i=0;i<3;i++){
 	printf(" ."); 
    Sleep(200);}
    system("cls");
  	system("color 7");
  	switch(selection){
        case 0:
		k=0; 
        while(1){
            do{printf("(Pour annuler l'ajout veuillez saisir annuler)\nVeuillez saisir le nom du medicament: ");
			fflush(stdin);scanf("%s",tab[medicaments].nom);
			nomexiste=0;
			for(i=0;i<medicaments;i++){
        	if(strcmp(tab[i].nom,tab[medicaments].nom)==0){nomexiste=1;system("cls");printf("Un medicament ayant le meme nom '%s' existe deja dans la base de donnees.\n",tab[medicaments].nom);break;}}
        	}while(nomexiste);
        if(strcmp(tab[medicaments].nom,"annuler")==0){strcpy(tab[medicaments].nom,"");
		printf("Ajout annule.\n");system("PAUSE");system("cls");break;}
        strcpy(medajoute[k].nom,tab[medicaments].nom);
			do{printf("(Pour annuler l'ajout veuillez saisir annuler)\nVeuillez saisir le code bar du medicament: ");
        	fflush(stdin);scanf("%s",tab[medicaments].codebar);
       		codebarexiste=0;
        	for(i=0;i<medicaments;i++){
       		if(strcmp(tab[i].codebar,tab[medicaments].codebar)==0){codebarexiste=1;system("cls");printf("Un medicament ayant le meme code-bar '%s' existe deja dans la base de donnees.\n",tab[medicaments].codebar);break;}}
        	}while(codebarexiste);
        if(strcmp(tab[medicaments].codebar,"annuler")==0){strcpy(tab[medicaments].nom,"");
		printf("Ajout annule.\n");system("PAUSE");system("cls");break;}
        strcpy(medajoute[k].codebar,tab[medicaments].codebar);
        while(tab[medicaments].prix<=0){
		printf("Veuillez saisir le prix du medicament (DH): ");
		fflush(stdin);scanf("%f",&tab[medicaments].prix);
       	if(tab[medicaments].prix<=0) printf("Erreur. Veuillez reessayer.\n");}
       	medajoute[k].prix=tab[medicaments].prix;
       	while(tab[medicaments].quantite<=0){
       	printf("Veuillez saisir la quantite de ce medicament: ");
       	fflush(stdin);scanf("%d",&tab[medicaments].quantite);
		if(tab[medicaments].quantite<=0) printf("Erreur. Veuillez reessayer.\n");}
       	medajoute[k].quantite=tab[medicaments].quantite;
       	medicaments++;k++;
       	if(ouinon("Medicament ajoute! Voulez-vous ajouter un autre medicament?")!=1) {system("cls");break;}
       	system("cls");}
		printf("%s",linebreak);
		printf("|  Liste des medicaments ajoutes:%-37s|\n"," ");
		printf("%s",linebreak);
		printf("|Index  |Nom                  |CodeBar          |Prix       |Quantite |\n");
		printf("%s",linebreak);
		for(i=0;i<k;i++)printf("|%-6d |%-20s |%-15s  |%-9.2f  |%-9d|\n",i ,medajoute[i].nom,medajoute[i].codebar,medajoute[i].prix,medajoute[i].quantite);
		printf("%s",linebreak);
		enreg();
		system("PAUSE");
       	break;
        case 1:
        totaldelacommande=0,quantite_a_acheter=-1,rendudelasommedonne=-1,sommedonnee=0;
        while(1){		
        	printf("Veuillez saisir le nom ou le code bar du medicament: ");
        	fflush(stdin);
        	scanf("%s",identifiantduproduit);
        	trouveoupas=-1;
        	if(strcmp(identifiantduproduit, "annuler")==0){break;}
        	for(i=0;i<medicaments;i++){
        	if(strcmp(tab[i].nom,identifiantduproduit)==0||strcmp(tab[i].codebar,identifiantduproduit)==0){
        	trouveoupas=1;break;}}
			if(trouveoupas==1&tab[i].quantite>0) break; 
			else if(trouveoupas==1&tab[i].quantite<=0) {printf("La quantite restante du '%s' dans le stock est %d\n",tab[i].nom,tab[i].quantite);}
			else if(trouveoupas==-1){printf("Produit introuvable dans la base de donnees.\n");}	
			system("PAUSE");system("cls");printf("(Pour annuler la commande taper annuler)\n");}
		if(strcmp(identifiantduproduit, "annuler")==0){strcpy(identifiantduproduit,"");system("cls");printf("Commande annulee. Redirection vers le menu principal.\n");system("PAUSE");break;}
        while(quantite_a_acheter<1 || quantite_a_acheter>tab[i].quantite) {
        printf("Veuillez saisir la quantite du medicament '%s' (max=%d): ",tab[i].nom,tab[i].quantite);
        fflush(stdin);
        scanf("%d",&quantite_a_acheter);
		if(quantite_a_acheter<1 || quantite_a_acheter>tab[i].quantite)printf("Erreur. Veuillez reessayer.\n");}
        totaldelacommande=quantite_a_acheter*tab[i].prix;
        tab[i].quantite-=quantite_a_acheter;
        printf("Saisir la somme donnee par le client: ");
		while(rendudelasommedonne<0){
		fflush(stdin);scanf("%f",&sommedonnee);
        rendudelasommedonne=sommedonnee-totaldelacommande;
		if(rendudelasommedonne<0)printf("Rendu negatif Reessayer: ");}
        time_t t; time(&t);
  	    char * time_str = ctime(&t);
    	time_str[strlen(time_str)-1] = '\0';
		char linebreak2[73]="+-------------------------------+--------------------+----------------+\n";
		printf("\n%s",linebreak2);
		printf("|  Bon de commande %51s|\n",time_str);
		printf("%s",linebreak2);
		printf("|Nom                            |Quantite            |Somme           |\n");
		printf("%s",linebreak2);
		printf("|%-31s|%-20d|%-16.2f|\n",tab[i].nom,quantite_a_acheter,quantite_a_acheter*tab[i].prix);
		printf("%s",linebreak2);
		printf("|TOTAL DE LA COMMANDE %48.2f|\n",totaldelacommande);
		printf("|ESPECES%62.2f|\n",sommedonnee);
		printf("|RENDU(ESPECES)%55.2f|\n",rendudelasommedonne);
		printf("%s",linebreak2);
		enreg();
		system("PAUSE");
        break;
        case 2:
        inferieura=-1;	
        if(ouinon("Afficher tout les medicaments?")==1){system("cls");printf("%s",linebreak);printf("|  Tout les medicaments dans le stock:%-32s|\n"," ");}
        else {printf("\n  Afficher les medicaments dont le stock est inferieur a: ");fflush(stdin);
		scanf("%d",&inferieura);
		system("cls");printf("%s",linebreak);
		if(inferieura<0) printf("|  Medicaments dont le stock est inferieur a: %-24s|\n","MAX");
		else printf("|  Medicaments dont le stock est inferieur a: %-24d|\n",inferieura);}
        printf("%s",linebreak);
		printf("|Index  |Nom                  |CodeBar          |Prix       |Quantite |\n");
		printf("%s",linebreak);
		for(i=0;i<medicaments;i++){
			if(inferieura<0)    printf("|%-6d |%-20s |%-15s  |%-9.2f  |%-9d|\n",i ,tab[i].nom,tab[i].codebar,tab[i].prix,tab[i].quantite);
			else if(tab[i].quantite<inferieura&&tab[i].prix!=0)printf("|%-6d |%-20s |%-15s  |%-9.2f  |%-9d|\n",i ,tab[i].nom,tab[i].codebar,tab[i].prix,tab[i].quantite);}
		printf("%s",linebreak);
        printf("\n");
        system("PAUSE");
        break;
		case 3:
		while(1){
		printf("Veuillez saisir le nom ou le code bar du medicament: ");
   		fflush(stdin);
        scanf("%s",identifiantduproduit);
       	trouveoupas=-1;
        if(strcmp(identifiantduproduit, "annuler")==0)break;//danger
       	for(i=0;i<medicaments;i++){
       	if(strcmp(tab[i].nom,identifiantduproduit)==0||strcmp(tab[i].codebar,identifiantduproduit)==0){trouveoupas=1;k=i;break;}}
       	system("cls");
		if(trouveoupas==-1) printf("Produit introuvable dans la base de donnees.\n(Pour annuler la recherche veuillez saisir annuler)\n");	
		else break;}
		if(strcmp(identifiantduproduit, "annuler")==0){strcpy(identifiantduproduit,"");printf("Redirection vers le menu principal.\n");system("PAUSE");break;}
		x = gererstockquestion(tab[i].nom);
		sommedonnee=-1;quantite_a_acheter=-1;
		system("cls");
		if(x==0){
			while(quantite_a_acheter<0){
			printf("Veuillez saisir la nouvelle quantite du medicament '%s': ",tab[i].nom);
			fflush(stdin);scanf("%d",&quantite_a_acheter);}
      		tab[i].quantite=quantite_a_acheter;
      		printf("La nouvelle quantite du '%s' est %d",tab[i].nom,tab[i].quantite);enreg();}
		if(x==1){
			while(sommedonnee<0) {
			printf("Veuillez saisir le nouveau prix de medicament '%s': ",tab[i].nom);
			fflush(stdin);scanf("%f",&sommedonnee);}
      		tab[i].prix=sommedonnee;
			printf("Le nouveau prix de '%s' est %.2f",tab[i].nom,tab[i].prix);enreg();}
		if(x==2){
			char upward[200];
			strcpy(upward, "Voulez-vous supprimer ");
			strcat(upward, tab[i].nom);
			strcat(upward, " du stock?");
			if(ouinon(upward)==1){
				for(k=i;k<medicaments-1;k++){
					strcpy(tab[k].nom,tab[k+1].nom);
					strcpy(tab[k].codebar,tab[k+1].codebar);
					tab[k].prix=tab[k+1].prix;
					tab[k].quantite=tab[k+1].quantite;}
				strcpy(tab[medicaments-1].nom,"");
				strcpy(tab[medicaments-1].codebar,"");
			 	tab[medicaments-1].prix=-5;
				tab[medicaments-1].quantite=-5;
				medicaments--;enreg();
				printf("Medicament supprime de la base de donnees avec succes.\n");}}
		if(x==3){break;}
   		system("PAUSE");
		break;
		case 4:
        //enreg();
		printf("A bientot!");
		exit(0);
		break;
        default:
		printf("Erreur.\n");
		system("PAUSE");
    	break;}//fin switch
       						}//fin de grande boucle
    return 0;
}
