#include "projet.h"

/* FONCTION GLOBAL : Elle charge 4 tableaux et une liste et gère les fonction du menu */

void global (void)
{
	Liste lRes;
	Jeux* tJeux;
	Jeux* tJeuxDisp;
	Emprunts tEmpr[100];
	Adherents* tAd[100];
	Reservations res;
	int nbRes=0, nbEmp, nbAdh, nbAdhAide=0, nbJeux,nbJeuxDisp,choix;
	char g;
	char nomFichJ[20];
	char sauv[4];
	strcpy(nomFichJ,"fJeuxb.bin");
	
	printf("Voulez vous les dernières sauvegardes (oui/non) : ");
	scanf("%s%*c",sauv);
	if(strcmp(sauv,"oui")==0)
	{
		tJeux=restaureTJeux(&nbJeux);
		if(tJeux==NULL)
			return;
		tJeuxDisp=restaureTJeux(&nbJeuxDisp);
		if(tJeuxDisp==NULL)
			return;
	}
	if(strcmp(sauv,"non")==0)
	{
		tJeux=chargeJeux(&nbJeux);
		if(tJeux==NULL)
			return;
		tJeuxDisp=chargeJeux(&nbJeuxDisp);
		if(tJeuxDisp==NULL)
			return;
	}
	nbEmp=chargeEmprunts(tEmpr, 100);
	nbJeuxDisp=JeuxDisp (tEmpr, tJeuxDisp, nbJeuxDisp, nbEmp);    // JeuxDisp permet d'emlever les jeux qui sont empruntés
	nbAdh=chargeAdherents(tAd, 100);
	lRes=listenouv();
	lRes=chargeReservations(lRes, &nbRes);

	choix=choixMenu();

	while(choix<17)
	{
		switch(choix)
		{	
			case 1:AffichageJeuxDispParType( tEmpr, nbEmp, tJeuxDisp, nbJeuxDisp);break;
			case 2:affJeuxAlph(tEmpr, nbEmp, tJeuxDisp, nbJeuxDisp );break;
			case 3:afficherEmpruntsEnCours(tEmpr, nbEmp, tJeux, nbJeux);break;
			case 4:AffListeResers(lRes,tJeux, nbJeux);break;
			case 5:nbAdh=insererAdherent(tAd, nbAdh);break;
			case 6:nbAdh=supprimerAdherents(tAd, nbAdh, tEmpr, nbEmp, lRes, nbRes);nbAdhAide=nbAdh;break;
			case 7:afficherTAdherents( tAd,  nbAdh);break;
			case 8:nbEmp=insererEmprunts(tEmpr, nbEmp, tJeuxDisp, nbJeuxDisp, tJeux, nbJeux, tAd, nbAdh, &nbAdhAide);break;
			case 9:nbRes=insererReservation(lRes, nbRes, tAd, nbAdh, tJeuxDisp, nbJeuxDisp, tJeux, nbJeux, &nbAdhAide);break;
			case 10:nbEmp=retourJeu(lRes, &nbRes, tJeuxDisp, nbJeuxDisp, tEmpr, nbEmp, tJeux, nbJeux);break;
			case 11:lRes=annRes(lRes,&nbRes);break;
			case 12:verificationDateInsc_Emp(tAd, nbAdh,tEmpr, nbEmp);break;
			case 13:printf("{\n");afficherRes(lRes);printf("}\n"); break;
			case 14:nbJeux=insererJeux(tJeux,nbJeux);
				actualiserTJeuxDisp(nomFichJ, tJeux, nbJeux); break;
			case 15:nbJeux=suppressionJeux(tJeux, nbJeux,tJeuxDisp, nbJeuxDisp);
				actualiserTJeuxDisp(nomFichJ, tJeux, nbJeux); break;
			case 16:sauve(tAd, nbAdh, tEmpr,nbEmp, tJeux, nomFichJ, nbJeux, lRes,nbRes); break;	
		}
		if(nbAdhAide!=0)
			nbAdh=nbAdhAide;
		if(strcmp(sauv,"oui")==0)
			tJeuxDisp=restaureTJeux(&nbJeuxDisp);
		else 
			tJeuxDisp=chargeJeux(&nbJeuxDisp);
		if(tJeuxDisp==NULL)
			return;			
		nbJeuxDisp=JeuxDisp (tEmpr, tJeuxDisp, nbJeuxDisp, nbEmp);
		printf("tapez la touche entrée pour continuer");
		g=getchar();
		choix=choixMenu();
	}
	free(tJeux);
	free(tJeuxDisp);
	free(*tAd);
			
}

/*************************************************************************/

void affichageMenu(void)
{
	system("clear");
	printf("\t------------Menu-------------\n");
	printf("(1)  Affichage des Jeux par type\n");
 	printf("(2)  Affichage des Jeux par ordre alphabétique\n");
	printf("(3)  Affichage des emprunts en cours\n"); // Avec nom du jeu, identité de l'emprunteur et la date d'emprunt.
	printf("(4)  Affichage des réservations pour un jeux\n");
	printf("(5)  Création d'un nouvel adhérent\n");
	printf("(6)  Supprimer un adhérent de la ludothèque\n");
	printf("(7)  Affichage des adherents\n");
	printf("(8)  Enregistrement d'un emprunt \n");
	printf("(9)  Enregistrement d'une réservation \n");
	printf("(10) Retourner un jeu\n");
	printf("(11) Annulation d'une réservation\n");
	printf("(12) Vérification des dates d'inscriptions des adhérents et des dates d'emprunts\n");
	printf("(13) Afficher les réservations\n");
	printf("(14) Inserer un nouveau jeux dans la ludothèque\n");
	printf("(15) Supprimer un jeux de la ludothèque\n\n");
	printf("(16) Sauvegarder les fichiers\n");
	printf("(17) Quitter\n\n");

}

/*************************************************************************/

int choixMenu(void)
{

	int choix;
	affichageMenu();
	printf("Quelle est votre choix :");
	scanf("%d%*c",&choix);
	system("clear");
	while(choix <1 || choix > 17)
	{
		printf("Désolé votre choix n'est pas compris entre 1 et 17\n");
		printf("Veuillez retaper votre choix:");
		scanf("%d%*c",&choix);
	}
	return choix;
}


/*************************************************************************/

int verificationDate(int dd, int mm, int yy)
{ 
    //check année
    if(yy>=1900 && yy<=9999)
    {
        //check mois
        if(mm>=1 && mm<=12)
        {
            //check jours
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                printf("Date est valide.\n");
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                printf("Date est valide.\n");
            else if((dd>=1 && dd<=28) && (mm==2))
                printf("Date est valide.\n");
            else if(dd==29 && mm==2 && (yy%400==0 || (yy%4==0 && yy%100!=0)))
                printf("Date est valide.\n");
            else
            {
                printf("Date n'est pas valide.\n");
                return -1;
            }
        }
        else
        {
            printf("Mois n'est pas valide.\n");
            return -1;
        }
    }
    else
    {
        printf("L'année n'est pas valide.\n");
        return -1;
    }
 
    return 0;
}

/*******************************************Chargement des réservations************************************************/

/* Cette fonction charge un tableau de structure Jeux par allocation du fichier "jeux.txt" */

Jeux* chargeJeux(int* nbJeux)
{
	Jeux *tJeux;
	FILE *flot;
	int i;
	flot=fopen("jeux.txt","r");
	if(flot==NULL)
	{
		printf("Pb dans l'ouverture du fichier jeux en lecture\n");
		*nbJeux = -1;
		return NULL;
	}
	fscanf(flot,"%d%*c",nbJeux);
	tJeux=(Jeux*)malloc(*nbJeux*sizeof(Jeux));
	if(tJeux==NULL)
	{
		printf("pb malloc\n");
		return NULL;
	}
	for(i=0;i<*nbJeux;i++)
		tJeux[i]=lireJeux(flot);
	fclose(flot);
	return tJeux;
}

/*********************************************Chargement des Emprunts***********************************************************/

/* Cette fonction charge un tableau basique de structure Emprunts du fichier "emprunts.txt" */

int chargeEmprunts(Emprunts tEmpr[], int tmax)
{
	FILE *flot;
	Emprunts emp;
	int i=0;
	flot=fopen("emprunts.txt","r");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier emprunts en lecture\n");
		return -1;
	}
	emp=lireEmprunts(flot);// mnt c ici
	while(!feof(flot))
	{
		if(i==tmax)
		{
			printf("Tableau d'emprunt plein\n");
			return -2;
		}
		tEmpr[i]=emp;
		i=i+1;
		emp=lireEmprunts(flot);
	}
	fclose(flot);
	return i;
}


/*************************************************chargement des adhérents*******************************************************/

/* Cette fonction charge un tableau de pointeur de structure Adherents du fichier "adherents.txt" */

int chargeAdherents (Adherents* tAd[], int taillemax)
{
	int i=0;
	FILE* flot;
	Adherents ad;
	flot=fopen("adherents.txt","r");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier adherents en lecture\n");
		return -1;
	}
	ad=lireAdherents(flot);
	while(!feof(flot))
	{
		if(i==taillemax)
		{
			printf("Tableau trop petit\n");
			return -2;
		}
		tAd[i]=(Adherents*)malloc(sizeof(Adherents));
		if(tAd[i]==NULL)
		{
			printf("Pb de malloc\n");
			return -3;
		}
		*tAd[i]=ad;
		i=i+1;
		ad=lireAdherents(flot);
	}

	fclose(flot);
	return i;
}

/*******************************************chargement des jeux******************************************************************/

/* Cette fonction charge une liste de structure Reservations du fichier "reservations.txt" */

Liste chargeReservations(Liste lRes, int* nbRes)
{
	
	Reservations res;
	FILE* flot;
	flot=fopen("reservations.txt","r");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier Reservations en lecture\n");
		exit (-1);
	}
	res=lireRes(flot);
	while(!feof(flot))
	{
		lRes=inserer(lRes,res);
		*nbRes=*nbRes+1;
		res=lireRes(flot);
	}
	
	fclose(flot);
	return lRes;
}


/*************************************FONCTION DE LECTURE**************************************/
/**********************************************************************************************/

Date lireDate(FILE *flot)
{
	Date d;
	fscanf(flot,"%d/%d/%d",&d.jour,&d.mois,&d.annee);
	return d;
}

/**********************************************************************************************/

Jeux lireJeux(FILE *flot)
{
	Jeux j;
	fscanf(flot,"%s%s%d%*c",j.idJeux,j.type,&j.nb);
	fgets(j.nom,31,flot);
	j.nom[strlen(j.nom)-1]='\0';
	return j;
}

/********************************************************************************************/

Emprunts lireEmprunts(FILE *flot)
{
	Emprunts emp;
	fscanf(flot,"%s%s%s%*c", emp.idEmprunt, emp.idAdherent, emp.idJeux);
	emp.dateEmpr=lireDate(flot);
	return emp;
}

/********************************************************************************************/

Adherents lireAdherents(FILE *flot)
{
	Adherents ad;
	fscanf(flot,"%s%s%*c", ad.idAdherent, ad.civilite);
	fgets(ad.nom, 31, flot);
	ad.nom[strlen(ad.nom)-1]='\0';
	fgets(ad.prenom, 31, flot);
	ad.prenom[strlen(ad.prenom)-1]='\0';
	ad.dateInsc=lireDate(flot);
	return ad;
}

/********************************************************************************************/

Reservations lireRes(FILE *flot)
{
	Reservations res;
	fscanf(flot,"%s%s%s%*c",res.idResa,res.idAdherent,res.idJeux);
	res.dateResa=lireDate(flot);
	return res;
}

/********************************** FONCTIONS D'AFFICHAGES **********************************/
/********************************************************************************************/

void afficherAdherents(Adherents ad)
{
	printf("%s\t%s\t%s\t%s\t%d/%d/%d\n",ad.idAdherent,ad.civilite,ad.nom,ad.prenom,ad.dateInsc.jour,ad.dateInsc.mois,ad.dateInsc.annee);
}

/********************************************************************************************/

void afficherTAdherents(Adherents** tAd, int nbAdh)
{
	int i;
	for(i=0;i<nbAdh;i++)
		afficherAdherents(*tAd[i]);
	printf("\n");
}

/******************************************************************************************/

void afficherEmprunts(Emprunts emp)
{
	printf("%s\t\t%s\t\t%s\t\t%d/%d/%d\n",emp.idEmprunt,emp.idAdherent,emp.idJeux,emp.dateEmpr.jour,emp.dateEmpr.mois,emp.dateEmpr.annee);
}

/********************************************************************************************/

void afficherTEmprunts(Emprunts* tEmpr, int nbEmp)
{
	int i;
	for(i=0;i<nbEmp;i++)
		afficherEmprunts(tEmpr[i]);
	printf("\n");
}
/********************************************************************************************/

void afficherJeux(Jeux j)
{
	printf("%s\t\t%s\t\t%d\t\t%s\n",j.idJeux,j.type,j.nb,j.nom);
}

/********************************************************************************************/

void afficherTJeux(Jeux* tJeux, int nbJeux)
{
	printf("\t\tLISTE DES JEUX DE LA LUDOTEQUE :\n\n");
	printf(" IDJEUX\t\tTYPE\t\tNB D'EXEMPLAIRE\t\tNOM DU JEUX\n\n");
	int i;
	for(i=0;i<nbJeux;i++)
		afficherJeux(tJeux[i]);
	printf("\n");
}

/**************************** Affichage recursif **************************************************/

void afficherRes(Liste lRes)
{
	if(vide(lRes))
	{
		return;
	}	
	printf("%s\t%s\t%s\t%d/%d/%d\n",lRes->v.idResa,lRes->v.idAdherent,lRes->v.idJeux,lRes->v.dateResa.jour,lRes->v.dateResa.mois,lRes->v.dateResa.annee);
	afficherRes(lRes->suiv);
}

/**************************** Affichage recursif ******************************************************/ 

void afficherJeuxDisp(Jeux* tJeuxDisp, int nbJeuxDisp)
{
	if(nbJeuxDisp==0)
		return;
	printf("%s\t\t%s\t\t%d\t\t%s\n",tJeuxDisp[0].idJeux,tJeuxDisp[0].type,tJeuxDisp[0].nb,tJeuxDisp[0].nom);
	afficherJeuxDisp(tJeuxDisp+1, nbJeuxDisp-1);
}
	

/*************************************FONCTIONS LISTE****************************************/
/********************************************************************************************/

Liste listenouv(void)
{
    return NULL;
}

/********************************************************************************************/

Liste insertionEnTete(Liste lRes,Reservations resSup)
{
   Maillon *lReserv;
   lReserv=(Maillon *)malloc(sizeof(Maillon));
   if(lReserv==NULL)
   {
       printf("pb malloc");
       exit (1);
   }
   lReserv->v=resSup;
   lReserv->suiv=lRes;
   return lReserv;
}


/********************************************************************************************/ 

Booleen vide(Liste lRes)
{
    return lRes==NULL;
}

/***************************** Fonction recherche par l'idJeux *******************************/

int rechListe(Liste lRes, char choix[])
{
	if(lRes==NULL)
		return -1;
	if(strcmp(choix,lRes->v.idJeux)==0)
		{
		printf("%s\t%s\t%s\t%d/%d/%d\n",lRes->v.idResa,lRes->v.idAdherent,lRes->v.idJeux,lRes->v.dateResa.jour,lRes->v.dateResa.mois,lRes->v.dateResa.annee);
		return 1;
		}
	return rechListe(lRes->suiv, choix);
} 

/***************************** Fonction recherche par l'idResa *******************************/

int rechListe2(Liste lRes, char choix[])
{
	if(lRes==NULL)
		return -1;
	if(strcmp(choix,lRes->v.idResa)==0)
	{
		printf("%s\t%s\t%s\t%d/%d/%d\n",lRes->v.idResa,lRes->v.idAdherent,lRes->v.idJeux,lRes->v.dateResa.jour,lRes->v.dateResa.mois,lRes->v.dateResa.annee);
		return 1;
	}
	return rechListe2(lRes->suiv, choix);
} 

/***************************** Fonction recherche par l'idAdhérent *******************************/

int rechListe3(Liste lRes, char choix[])
{
	if(lRes==NULL)
		return -1;
	if(strcmp(choix,lRes->v.idAdherent)==0)
		{
		printf("%s\t%s\t%s\t%d/%d/%d\n",lRes->v.idResa,lRes->v.idAdherent,lRes->v.idJeux,lRes->v.dateResa.jour,lRes->v.dateResa.mois,lRes->v.dateResa.annee);
		return 1;
		}
	return rechListe3(lRes->suiv, choix);
} 

/*******************************************************************************************/

Liste suppressionEnTete(Liste lRes)
{
	Maillon *lReserv;
	if (lRes==NULL)
	{
		printf("op interdite\n");
		exit (1);
	}
	lReserv=lRes;
	lRes=lRes->suiv;
	free(lReserv);
	return lRes;
}

/*********************** Fonction de suppression par idReservation ***************************/

Liste supprimer(Liste lRes,char id[])
{
    if(lRes==NULL)
    	{
    		printf("L'id n'a pas été trouvé\n");
    		return lRes;
    	}
	if(strcmp(id,(lRes->v).idResa)==0)
		return suppressionEnTete(lRes);
	lRes->suiv=supprimer(lRes->suiv,id);
	return lRes;    
}

/*********************** Fonction de d'insersion  **************************************/

Liste inserer(Liste l,Reservations x)
{

	if(l==NULL)
	{
		return insertionEnTete(l, x);
	}
	if(comparerDate(x.dateResa,l->v.dateResa)<=0)
	{
		return insertionEnTete(l, x);
	}

	l->suiv=inserer(l->suiv, x);
	return l;
}

/************************************************************************************************************/

int comparerDate(Date d1, Date d2) 
{	
		int date1,date2;

		date1=d1.annee*10000;
		date1=date1+d1.mois*100;
		date1=date1+d1.jour;
		
		date2=d2.annee*10000;
		date2=date2+d2.mois*100;
		date2=date2+d2.jour;

		if(date1<date2)
			return 0; //retourne 0 donc la date va etre inseré
		return 1;
} 
/***********************************************Recherche******************************************************/
/************************** Fonction recherche dans un tableau par idJeux *************************************/ 

int rech (char code[], Jeux *tJeuxDisp, int nbJeuxDisp)
{
	int i;
	for(i=0;i<nbJeuxDisp;i++)
		if(strcmp(code, tJeuxDisp[i].idJeux)==0)
			return i;
	return -1;
}

/************************* Fonction de recherche si un adherents existe déjà *************************/

int rechAdherents(char code[],Adherents** tAd, int nbAd)
{
	int i;
	for(i=0;i<nbAd;i++)
		if(strcmp(code,tAd[i]->idAdherent)==0)
			return i;
	return -1;
}

/************************** Fonction de recherche si un adhérent possède des réservations ************************/

int rechEmpruntAdherent(char code[],Emprunts tEmp[], int nbEmpr)
{
	int i;
	for(i=0;i<nbEmpr;i++)
		if(strcmp(code,tEmp[i].idAdherent)==0)
			return i;
	return -1;
}

/************************** Fonction de recherche si un emprunt existe déjà************************/

int rechEmprunts(char code[],Emprunts tEmpr[], int nbEmpr)
{
	int i;
	for(i=0;i<nbEmpr;i++)
		if(strcmp(code,tEmpr[i].idEmprunt)==0)
			return i;
	return -1;
}

/************************** Fonction de recherche d'un jeu emprunté ************************/

int rechJeuxEmprunts(char code[],Emprunts tEmpr[], int nbEmpr)
{
	int i;
	for(i=0;i<nbEmpr;i++)
		if(strcmp(code,tEmpr[i].idJeux)==0)
			return i;
	return -1;
}





/**************************** Supprimer jeux **********************************************/ 

int suppJeux(Jeux tJeuxDisp[],int nbJeuxDisp,char code[])
{
	int i;

	i=rech(code,tJeuxDisp,nbJeuxDisp);
	
	if (i==-1)
		return nbJeuxDisp;
	if (tJeuxDisp[i].nb == 1)
	{
		decaGauche(tJeuxDisp, nbJeuxDisp, i);
		return nbJeuxDisp-1;
	}

	if (tJeuxDisp[i].nb > 1)
	{	
		tJeuxDisp[i].nb=tJeuxDisp[i].nb-1;
		return nbJeuxDisp;
	}
}

/*******************************************************************************************************/

int JeuxDisp (Emprunts tEmpr[], Jeux* tJeuxDisp, int nbJeuxDisp, int nbEmp)
{
	int i;
	char code[7];
	for(i=0;i<nbEmp;i++)
	{
		strcpy(code,tEmpr[i].idJeux);
		nbJeuxDisp=suppJeux(tJeuxDisp, nbJeuxDisp, code);
	}
	return nbJeuxDisp;
}

/***************************** Décaler à gauche *******************************/ 

void decaGauche(Jeux tJeuxDisp[], int nb, int i)
{
	int j;
	for (j = i; j <= nb-2; j++)
		tJeuxDisp[j]=tJeuxDisp[j+1];
}

/***************************** Décaler à gauche *******************************/ 

void decaGauche2(Adherents *tAd[], int nbAd, int i)
{
	int j;
	for (j = i; j <= nbAd-2; j++)
		*tAd[j]=*tAd[j+1];
}
/********************************************** Q2 *****************************************************/ 
/************************* Affichage des jeux disponibles triées par type de jeux **********************/
/*******************************************************************************************************/ 

/* Fonction d'affichage des jeux triés grace à un triDichotomique qui utilise un nouveau tableau tJeuxDisp pour afficher les tous les jeux sauf ceux qui sont empuntés grace à la fonction suppJeux */ 

void AffichageJeuxDispParType(Emprunts tEmpr[], int nbEmp, Jeux* tJeuxDisp, int nbJeuxDisp)
{
	char code[7];
	int i;
	printf("\t\tLISTE DES JEUX DISPO TRIEES PAR TYPE DE JEUX :\n\n" );
	printf(" IDJEUX\t\tTYPE\t\tNB D'EXEMPLAIRE\t\tNOM DU JEUX\n\n");
	triDico(tJeuxDisp, nbJeuxDisp);
	afficherJeuxDisp(tJeuxDisp, nbJeuxDisp);
}

/*******************************************************************************************************/ 

void triDico(Jeux* tJeuxDisp, int nbJeuxDisp)
{
	Jeux *R,*S;
	if(nbJeuxDisp<=1)
		return;
	R=(Jeux*)malloc((nbJeuxDisp/2)*sizeof(Jeux));
	S=(Jeux*)malloc((nbJeuxDisp-(nbJeuxDisp/2))*sizeof(Jeux));
	if(R==NULL || S==NULL)
	{
		printf("Problème de malloc\n");
		return;
	}
	copier(tJeuxDisp,0,nbJeuxDisp/2,R);
	copier(tJeuxDisp,nbJeuxDisp/2,nbJeuxDisp,S);
	triDico(R,nbJeuxDisp/2);
	triDico(S,nbJeuxDisp-nbJeuxDisp/2);
	fusion(R,nbJeuxDisp/2,S,nbJeuxDisp-nbJeuxDisp/2,tJeuxDisp);
	free(R);
	free(S);
}

/*******************************************************************************************************/ 

void copier(Jeux* tJeuxDisp, int i, int j, Jeux* R)
{
	int k=0;
	while(i<j)
	{
		R[k]=tJeuxDisp[i];
		i=i+1;
		k=k+1;
	}
}

/*******************************************************************************************************/ 

void fusion(Jeux* R, int n, Jeux* S, int m,Jeux* tJeuxDisp)
{
	int i=0, j=0, k=0;
	while(i<n && j<m)
	{
		if(strcmp(R[i].type,S[j].type)<0)
		{
			tJeuxDisp[k]=R[i];
			i=i+1;
			k=k+1;
		}
		else
		{
			tJeuxDisp[k]=S[j];
			j=j+1;
			k=k+1;
		}
	}
	while(j<m)
	{
		tJeuxDisp[k]=S[j];
		j=j+1;
		k=k+1;
	}
	while(i<n)
	{
		tJeuxDisp[k]=R[i];
		i=i+1;
		k=k+1;
	}
}


/********************************************** Q2.b **************************************************/ 
/****** Affichage des jeux dispo triée par ordre alphabétique de leur nom *****************************/
/******************************************************************************************************/ 


void triAlpha (Jeux *tJeuxDisp,int nbJeuxDisp)
{
	int i,j,k;
	Jeux c;
	printf("\t\tLISTE DES JEUX DISPO TRIEES PAR ORDRE ALPHABETIQUE DES NOMS :\n\n");
	printf(" IDJEUX\t\tTYPE\t\tNB D'EXEMPLAIRE\t\tNOM DU JEUX\n\n");
	for(i=1;i<nbJeuxDisp;i++)
	{
    		if ( strcmp(tJeuxDisp[i].nom ,tJeuxDisp[i-1].nom)<0 )
		{                                                         							// si l’élément est mal placé
			j = 0;
			while ( strcmp(tJeuxDisp[j].nom ,tJeuxDisp[i].nom)<0 )
				j++;                                             							// cette boucle sort par j = la nouvelle position de l’élément
 				c = tJeuxDisp[i];        													// ces 2 lignes servent a translater les cases en avant pour pouvoir insérer l’élément a sa nouvelle position
        			for( k = i-1 ; k >= j ; k-- ) tJeuxDisp[k+1] = tJeuxDisp[k];
 					tJeuxDisp[j] = c;                                                    	// l'insertion
    		}
	}
}

/*********************************************************************************************/ 

/* Fonction d'affichage des jeux triés grace à un tri qui utilise le tableau tJeuxDisp pour afficher les tous les jeux sauf ceux qui sont empuntés */ 

void affJeuxAlph(Emprunts tEmpr[], int nbEmp, Jeux tJeuxDisp[], int nbJeuxDisp )
{
	int i;
	char code[7];
	
	triAlpha (tJeuxDisp,nbJeuxDisp);
	afficherJeuxDisp(tJeuxDisp, nbJeuxDisp);

}

/*********************************************** Q3 ***************************************************/ 
/************* Affichage des emprunts en cours (Nom du jeux, idAdherent, Date d'emprunt) ***************/
/******************************************************************************************************/ 

/* Fonction qui affiche les emprunts en cours avec le non du jeux récupéré par la recherche */

void afficherEmpruntsEnCours(Emprunts tEmpr[], int nbEmpr, Jeux* tJeux, int nbJeux)
{
	int i,j;
	printf("\t\tLISTE DES EMPRUNTS DE LA LUDOTEQUE :\n\n");
	printf("    NOM DU JEU\t  IDENTITE DE L'ADHERENT\tDATE D'EMPRUNT\n\n");
	for(i=0;i<nbEmpr;i++)
	{
		j=rech (tEmpr[i].idJeux, tJeux, nbJeux);
		printf("%s\t\t%s\t\t%d/%d/%d\n",tJeux[j].nom,tEmpr[i].idAdherent,tEmpr[i].dateEmpr.jour,tEmpr[i].dateEmpr.mois,tEmpr[i].dateEmpr.annee);
	}
}

/********************************************** Q4 **************************************************/ 
/********* Affichage de la liste des réservations pour un jeu donné *********************************/
/****************************************************************************************************/ 

/* Fonction d'affichage des réservations pour un jeux donné avec vérification de idJeux grace à une recherche puis un affichage recursif si idJeux du jeux est dans les réservation */

void AffListeResers(Liste lRes, Jeux* tJeux, int nbJeux)
{
	char choix[7];
	int i,j,k=0;
	afficherTJeux(tJeux, nbJeux);
	printf("Choissisez un id de jeu à chercher dans les réservations :");
	scanf("%s%*c",choix);
	printf("\n\t\tLISTE DES RESERVATION POUR LE JEU %s : \n\n",choix);
	j=rech (choix, tJeux, nbJeux);
	if(j==-1)
	{
		printf("Vous avez mal orthographier l'idJeux\n");
		return;
	}
	printf("{\n");
	while(!vide(lRes))
	{
		if(strcmp(choix,lRes->v.idJeux)==0)
		{
			printf("%s\t%s\t%s\t%d/%d/%d\n",lRes->v.idResa,lRes->v.idAdherent,lRes->v.idJeux,lRes->v.dateResa.jour,lRes->v.dateResa.mois,lRes->v.dateResa.annee);
			k=k+1;
		}	
		lRes=lRes->suiv;
	}
	printf("}\n");
	if(k==0)
		printf("Il n'existe pas de réservation pour le jeux %s\n",choix);
}

/********************************************** Q5 **************************************************/ 
/************************** ENREGISTREMENT D'EMPRUNT ET DE RESERVATION ******************************/
/****************************************************************************************************/


/*********************************** Insersion d'Adhérents *****************************************/

int insererAdherent(Adherents** tAd, int nbAd)
{
	Adherents ad;
	char c;
	afficherTAdherents( tAd,  nbAd);
	ad = saisieAdherents(tAd, nbAd);
	if(strcmp(ad.idAdherent,"erreur")==0)
		return nbAd;
	tAd[nbAd]=(Adherents*)malloc(sizeof(Adherents)+1);
	strcpy(tAd[nbAd]->idAdherent,ad.idAdherent);
	strcpy(tAd[nbAd]->civilite,ad.civilite);
	strcpy(tAd[nbAd]->nom,ad.nom);
	strcpy(tAd[nbAd]->prenom,ad.prenom);
	tAd[nbAd]->dateInsc.jour=ad.dateInsc.jour;
	tAd[nbAd]->dateInsc.mois=ad.dateInsc.mois;
	tAd[nbAd]->dateInsc.annee=ad.dateInsc.annee;
	nbAd=nbAd+1;
	printf("L'adhérent %s a été intégrée dans le tableau\n\nTapez sur entrée pour afficher le tableau mise à jour\n",ad.idAdherent);
	c=getchar();
	afficherTAdherents( tAd,  nbAd);
	return nbAd;
}

/****************************************************************************************************/

/* Fonction qui saisie un adherents avec vérification si l'idAdherent existe déjà et possibilitée de réecrire en cas d'erreur */

Adherents saisieAdherents(Adherents** tAd, int nbAd)
{
	Adherents ad;
	int pos,err;
	char validation[4],a,g;
	printf("Saisie de l'identifiant du nouvel adhérent\nIdentifiant:\t");
	scanf("%s%*c",ad.idAdherent);
	pos=rechAdherents(ad.idAdherent,tAd, nbAd);
	while(pos!=-1)
	{
		printf("L'adherent %s se trouve dans le tableau\n",ad.idAdherent);
		printf("retapez :");
		scanf("%s%*c",ad.idAdherent);
		pos=rechAdherents(ad.idAdherent,tAd, nbAd);
	}
	if(strlen(ad.idAdherent)>5 || (strlen(ad.idAdherent)<5))
	{
		printf("Identifiant adherent doit contenir 5 lettre/chiffre\n");
		strcpy(ad.idAdherent,"erreur");
		return ad;
	}
	printf("Donnez votre civilité (Mme/Mr) :\t");
	scanf("%s%*c",ad.civilite);
	while(strcmp(ad.civilite, "Mme")!=0 && strcmp(ad.civilite, "Mr")!=0)
	{	
		printf("\nErreur, veuillez resaisir la civilitée de l'étudiant (Mr/Mme) : ");
		scanf("%s%*c",ad.civilite);
	}
	printf("Donnez votre nom :\t");
	fgets(ad.nom,31,stdin);
	ad.nom[strlen(ad.nom)-1]='\0';
	printf("Donnez votre prenom :\t");
	fgets(ad.prenom,31,stdin);
	ad.prenom[strlen(ad.prenom)-1]='\0';
	printf("Entrez la date d'inscription (format JJ/MM/AAAA): ");
	scanf("%d/%d/%d",&ad.dateInsc.jour,&ad.dateInsc.mois,&ad.dateInsc.annee);
	err=verificationDate(ad.dateInsc.jour,ad.dateInsc.mois,ad.dateInsc.annee);
	if(err==-1)
	{
		a=getchar();
		strcpy(ad.idAdherent,"erreur");
		return ad;
	}
	printf("Voici les informations renseignées pour le nouvel adherent :\n\n");
	afficherAdherents(ad);
	printf("Voulez vous valider l'ajout du nouvel adherent, si il y a une erreur tapez non (oui/non) :\t");
	scanf("%s%*c",validation);
	if(strcmp(validation,"oui")==0)
		return ad;
	else
	{
		printf("Donnez votre civilité (Mme/Mr) :\t");
		scanf("%s%*c",ad.civilite);
		while(strcmp(ad.civilite, "Mme")!=0 && strcmp(ad.civilite, "Mr")!=0)
		{	
			printf("\nErreur, veuillez resaisir la civilitée de l'étudiant (Mr/Mme) : ");
			scanf("%s%*c",ad.civilite);
		}
		printf("Donnez votre nom :\t");
		fgets(ad.nom,31,stdin);
		ad.nom[strlen(ad.nom)-1]='\0';
		printf("Donnez votre prenom :\t");
		fgets(ad.prenom,31,stdin);
		ad.prenom[strlen(ad.prenom)-1]='\0';
		printf("Entrez la date d'inscription (format JJ/MM/AAAA): ");
		scanf("%d/%d/%d",&ad.dateInsc.jour,&ad.dateInsc.mois,&ad.dateInsc.annee);
		err=verificationDate(ad.dateInsc.jour,ad.dateInsc.mois,ad.dateInsc.annee);
		if(err==-1)
		{
			g=getchar();
			strcpy(ad.idAdherent,"erreur");
			return ad;
		}
		printf("Voici les informations renseignées pour le nouvel adherent :\n\n");
		afficherAdherents(ad);
		return ad;
	}
}

/**************************************************************************************************************/

int supprimerAdherents(Adherents* tAd[], int nbAd, Emprunts tEmp[], int nbEmp, Liste lRes, int nbRes)
{
	int exist,emp,res;
	char code[6],g;
	afficherTAdherents(tAd, nbAd);
	printf("Quel est l'identifiant d'adhérent a supprimer : ");
	scanf("%s%*c",code);
	exist=rechAdherents(code,tAd, nbAd);
	while(exist==-1)
	{
		printf("L'adhérent n'est pas enregistré dans la ludothèque\nRetapez l'identifiant: ");
		scanf("%s%*c",code);
		exist=rechAdherents(code,tAd, nbAd);
	}
	emp=rechEmpruntAdherent(code,tEmp, nbEmp);
	if(emp!=-1)
	{
		printf("L'adhérent %s possède au moin un jeux, il ne peut pas être supprimé\n",code);
		return nbAd;
	}
	res=rechListe3(lRes,code);
	if(res==1)
	{
		printf("L'adhérent %s possède au moin une réservation, supprimé avant ses réservations\n",code);
		lRes=annRes(lRes, &nbRes);
	}
	decaGauche2(tAd, nbAd, exist);
	nbAd=nbAd-1;
	printf("L'adhérent %s a bien été suprimé de la ludothèque\nTapez entrée pour afficher la tableau mis à jour\n",code);
	g=getchar();
	afficherTAdherents(tAd, nbAd);
	return nbAd;
}


/************************************************************************************************************************************************/
/************************************************************************************************************************************************/

// FONCTION DE SAISIE D'UN EMPRUNT : 

Emprunts saisieEmprunts(Emprunts tEmpr[], int nbEmpr, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux, Adherents** tAd, int nbAdh ,int *nbAdhAide)
{
	int pos,pos2,pos3,pos4,err;
	char reserv,g;
	Emprunts emp;
	afficherTJeux(tJeux, nbJeux);       		// AFFICHAGE DU TABLEAU DES JEUX DE LA LUDOTHEQUE
	printf("\nQuel est l'identifiant du jeux que vous voulez emprunter \nIdentifiant:\t");
	scanf("%s%*c",emp.idJeux);
	pos3=rech (emp.idJeux, tJeuxDisp, nbJeuxDisp);  // VERIFICATION SI LE JEUX EST DISPO
	pos4=rech (emp.idJeux, tJeux, nbJeux);		// VERIFICATION SI JE JEU EXISTE DANS LA LUDOTHEQUE
	while(pos4==-1)					// Tant qu'il n'existe pas on le redemande
	{
		printf("La ludothèque ne possède pas le jeux de code %s\nVeuillez repater l'identifiant du jeux que vous voulez emprunter \nIdentifiant:\t",emp.idJeux);
		scanf("%s%*c",emp.idJeux);
		pos3=rech (emp.idJeux, tJeuxDisp, nbJeuxDisp);
		pos4=rech (emp.idJeux, tJeux, nbJeux);
	}
	if(pos3==-1 && pos4!=-1)			// Si le jeux existe mais qu'il n'est pas dipo
	{
		printf("\nDésolé mais le jeux de code %s n'est pas disponible\nPassez sur une réservation\n");
		strcpy(emp.idEmprunt,"err");
		return emp;
	}
	printf("Donnez le nouvel identifiant de l'emprunt :\t");
	scanf("%s%*c",emp.idEmprunt);
	pos2=rechEmprunts(emp.idEmprunt,tEmpr,  nbEmpr);
	while(pos2!=-1)
	{
		printf("L'identifiant d'emprunt existe déjà\nRetaper l'identifiant de l'emprunt :\t");
		scanf("%s%*c",emp.idEmprunt);
		pos2=rechEmprunts(emp.idEmprunt,tEmpr,  nbEmpr);
	}
	if(strlen(emp.idEmprunt)>5 || strlen(emp.idEmprunt)<5)
	{
		printf("Identifiant d'emprunt doit contenir 5 lettre/chiffre\n");
		strcpy(emp.idEmprunt,"err");
		return emp;
	}
	printf("Donnez l'identifiant de l'adherent :\t");
	scanf("%s%*c",emp.idAdherent);
	pos=rechAdherents(emp.idAdherent,tAd, nbAdh);
	if(pos==-1)
	{
		nbAdh=insererAdherent(tAd, nbAdh);
		*nbAdhAide=nbAdh;
	}
	printf("Entrez la date de réservation (format JJ/MM/AAAA): ");
	scanf("%d/%d/%d",&emp.dateEmpr.jour,&emp.dateEmpr.mois,&emp.dateEmpr.annee);
	err=verificationDate(emp.dateEmpr.jour,emp.dateEmpr.mois,emp.dateEmpr.annee);
	if(err==-1)
	{
		g=getchar();
		strcpy(emp.idEmprunt,"err");
		return emp;
	}
	printf("Voici les informations renseignées pour le nouvel emprunt :\n\n");
	afficherEmprunts(emp);
	return emp;
}

/************************************* Insersion d'Emprunts *************************************************/

int insererEmprunts(Emprunts tEmpr[], int nbEmpr, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux, Adherents** tAd, int nbAdh, int *nbAdhAide)
{
	Emprunts emp;
	char a;
	afficherEmpruntsEnCours(tEmpr, nbEmpr, tJeux, nbJeux);
	emp=saisieEmprunts(tEmpr, nbEmpr, tJeuxDisp, nbJeuxDisp, tJeux, nbJeux, tAd, nbAdh, nbAdhAide);
	if(strcmp(emp.idEmprunt,"err")==0)
		return nbEmpr;
	tEmpr[nbEmpr]=emp;
	nbEmpr=nbEmpr+1;
	printf("L'emprunt %s a été intégrée dans le tableau\n\nTapez entrée pour afficher le tableau mise à jour\n",emp.idEmprunt);
	a=getchar();
	afficherEmpruntsEnCours(tEmpr, nbEmpr, tJeux, nbJeux);

	return nbEmpr;
}

/************************************************************************************************************************************************/
/************************************************************************************************************************************************/

// FONCTION DE SAISIE D'UNE RESERVATION : 

Reservations saisieReservations(Liste lRes, Adherents** tAd, int nbAd, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux,int *nbAdhAide)
{
	int testIdResa,pos2,pos3,testAd,err;
	Reservations res;
	char reserv,g;
	afficherTJeux(tJeux, nbJeux);       		// AFFICHAGE DU TABLEAU DES JEUX DE LA LUDOTHEQUE
	printf("\nQuel est l'identifiant du jeux que vous voulez réserver \nIdentifiant:\t");
	scanf("%s%*c",res.idJeux);
	pos2=rech (res.idJeux, tJeuxDisp, nbJeuxDisp);  // VERIFICATION SI LE JEUX EST DISPO
	pos3=rech (res.idJeux, tJeux, nbJeux);		// VERIFICATION SI JE JEU EXISTE DANS LA LUDOTHEQUE
	while(pos3==-1)					// Tant qu'il n'existe pas on le redemande
	{
		printf("La ludothèque ne possède pas le jeux de code %s\nVeuillez repater l'identifiant du jeux que vous voulez emprunter \nIdentifiant:\t",res.idJeux);
		scanf("%s%*c",res.idJeux);
		pos2=rech (res.idJeux, tJeuxDisp, nbJeuxDisp);
		pos3=rech (res.idJeux, tJeux, nbJeux);
	}
	if(pos2!=-1 && pos3!=-1)			// Si le jeux existe et qu'il est dispo
	{
		printf("\nLe jeux de code %s est disponible\nPassez sur un emprunt\n");
		strcpy(res.idResa,"err");
		return res;
	}			
	printf("Donnez l'identifiant de la nouvelle réservation :\t");
	scanf("%s%*c",res.idResa);
	testIdResa=rechListe2(lRes, res.idResa);		// VERIFICATION SI L'IDENTIFIANT EXISTE DEJA
	while(testIdResa==1)					// Il le retape tant qu'il existe dans le tableau de réservations
	{
		printf("L'identifiant de réservation existe déjà\nRetaper l'identifiant de l'emprunt :\t");
		scanf("%s%*c",res.idResa);
		testIdResa=rechListe2(lRes,res.idResa);
	}
	if(strlen(res.idResa)>5 || strlen(res.idResa)<5)	// VERIFICATION SI L'IDENTIFIANT EST PAS PLUS GRAND OU PLUS PETIT QUE 5
	{
		printf("Identifiant de réservation doit contenir 5 lettre/chiffre\n");
		strcpy(res.idResa,"err");
		return res;
	}
	printf("Identifiant de réservation : %s\n",res.idResa);
	printf("Donnez l'identifiant de l'adherent :\t");
	scanf("%s%*c",res.idAdherent);
	testAd=rechAdherents(res.idAdherent,tAd, nbAd);		// ON CHERCHE SI ADHERENT EXISTE
	if(testAd==-1)
	{
		nbAd=insererAdherent(tAd,nbAd);		// Si il n'existe pas on l'ajoute dans le tableau adherent
		*nbAdhAide=nbAd;
	}
	printf("Entrez la date de réservation (format JJ/MM/AAAA): ");
	scanf("%d/%d/%d",&res.dateResa.jour,&res.dateResa.mois,&res.dateResa.annee);
	err=verificationDate(res.dateResa.jour,res.dateResa.mois,res.dateResa.annee);		// On vérifie la date
	if(err==-1)
	{	
		g=getchar();				
		strcpy(res.idResa,"err");
		return res;
	}				// Si erreur on exit
	printf("Voici les informations renseignées pour la nouvelle reservation :\n\n");
	printf("%s\t%s\t%s\t%d/%d/%d\n",res.idResa,res.idAdherent,res.idJeux,res.dateResa.jour,res.dateResa.mois,res.dateResa.annee);
	return res;
}



/************************************* Insersion de Réservations *************************************************/


int insererReservation(Liste lRes, int nbRes, Adherents** tAd, int nbAd, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux, int *nbAdhAide)
{
	Reservations res;
	char s;
	res=saisieReservations(lRes, tAd, nbAd, tJeuxDisp, nbJeuxDisp, tJeux, nbJeux, nbAdhAide);
	if(strcmp(res.idResa,"err")==0)
		return nbRes;
	lRes=inserer(lRes, res);
	printf("La réservation %s a été intégrée dans le tableau\n\n",res.idResa);
	s=getchar();
	printf("{\n");
	afficherRes(lRes);
	printf("}\n");
	return nbRes;
}

/********************************************** Q6 **************************************************/ 
/**************************************  Retour d'un jeu  *******************************************/
/****************************************************************************************************/

int retourJeu(Liste lRes, int* nbRes, Jeux* tJeuxDisp, int nbJeuxDisp, Emprunts tEmpr[], int nbEmpr,Jeux* tJeux, int nbJeux)
{
	Reservations res;
	Emprunts emp;
	int pos, pos2, verif, err, reponse=1;
	char a,g, oui[4]="oui", choix[4];
	printf("\t\tLISTE DES EMPRUNTS DE LA LUDOTEQUE :\n\n");
	printf("IDEMPRUNT\tIDADHERENT\tIDJEUX\t     DATE EMPRUNT\n\n");
	afficherTEmprunts(tEmpr, nbEmpr);
	// SAISIE DE L'EMPRUNT A SUPRIMMER //
	printf("Quel est l'identifiant du jeu que vous voulez rendre ?\n");
	scanf("%s%*c",emp.idJeux);
	pos2=rechJeuxEmprunts(emp.idJeux, tEmpr, nbEmpr);			// VERIFICATION SI JE JEU EXISTE DANS LES EMPRUNTS
	while(pos2==-1)												// Tant qu'il n'existe pas on le redemande
	{
		printf("L'identifiant de jeu que vous venez d'entrer n'a jamais été emprunté %s.\nVeuillez retaper l'identifiant du jeux que vous souhaitez rendre\nIdentifiant du jeux:\t",emp.idJeux);
		scanf("%s%*c",emp.idJeux);
		pos2=rechJeuxEmprunts(emp.idJeux, tEmpr, nbEmpr);
	}

	printf("\nQuel est l'identifiant d'Emprunt que vous voulez arrêter ?\n");
	scanf("%s%*c",emp.idEmprunt);
	if(strlen(emp.idEmprunt)>5 || strlen(emp.idEmprunt)<5)
	{
		printf("L'identifiant doit contenir 5 lettre/chiffre\n");
		return nbEmpr;
	}

	pos=rechEmprunts(emp.idEmprunt, tEmpr, nbEmpr);
	while(pos==-1)
	{
		printf("Cet emprunt n'existe pas, veuillez le resaisir :\t");
		scanf("%s%*c", emp.idEmprunt);
		pos=rechEmprunts(emp.idEmprunt, tEmpr, nbEmpr);
	}

	// SUPRESSION DE L'EMPRUNT //
	if(pos!=-1)
		nbEmpr=supressionEmprunts(tEmpr, pos, nbEmpr);

	// VERIFICATION SI LE JEU QUI A ETE RENDU ETAIT RESERVE //
	verif=rechListe(lRes, emp.idJeux);

	// SI LE JEU EST BIEN RESERVER ALORS ON L'AJOUTE A TEMPRUNT
	if(verif==1)
	{
		while(reponse!=0)
		{
			printf("\n");
			afficherRes(lRes);

			printf("\n\t\t!!! - Veuillez bien vérifier de prendre la dernière réservation - !!!");

			printf("\nQuel réservation voulez-vous changer en emprunts ?\n");
			scanf("%s%*c",res.idResa);
			pos2=rechListe2(lRes, res.idResa);      // Vérification si la réservation existe
			while(pos2!=1)
			{
				printf("L'identifiant de réservation n'existe pas\nRetaper l'identifiant de la réservation à remplacer :\t\n");
				scanf("%s%*c",res.idResa);
				pos2=rechListe2(lRes, res.idResa);
			}

			printf("\nDonnez l'identifiant du futur emprunt :\t");
			scanf("%s%*c",emp.idEmprunt);

			pos2=rechEmprunts(emp.idEmprunt,tEmpr, nbEmpr);
			while(pos2!=-1)
			{
				printf("L'identifiant d'emprunt existe déjà\nRetaper l'identifiant du futur emprunt :\t\n");
				scanf("%s%*c",emp.idEmprunt);
				pos2=rechEmprunts(emp.idEmprunt,tEmpr,  nbEmpr);
			}
			if(strlen(emp.idEmprunt)>5 || strlen(emp.idEmprunt)<5)
			{
				printf("Identifiant d'emprunt doit contenir 5 lettre/chiffre\n");
				return nbEmpr;
			}

			printf("\nDonnez l'identifiant de l'adherent qui a reservé ce jeu :\t");
			scanf("%s%*c",emp.idAdherent);

			if(strlen(emp.idAdherent)>5 || strlen(emp.idAdherent)<5)
			{
				printf("Identifiant d'Adherent doit contenir 5 lettre/chiffre\n");
				return nbEmpr;
			}
			pos=rechListe3(lRes, emp.idAdherent);      // Recherche si un adhérent possède des réservations
			while(pos==-1)
			{
				printf("Cet adherent n'a fait aucune réservation, veuillez le resaisir :\t");
				scanf("%s%*c", emp.idAdherent);
				pos=rechListe3(lRes, emp.idAdherent);
			}
	
			printf("\nEntrez la date d'aujourd'hui (format JJ/MM/AAAA): ");
			scanf("%d/%d/%d",&emp.dateEmpr.jour,&emp.dateEmpr.mois,&emp.dateEmpr.annee);

			err=verificationDate(emp.dateEmpr.jour,emp.dateEmpr.mois,emp.dateEmpr.annee);
			if(err==-1)
			{
				g=getchar();
				printf("La date n'est pas valide\n");
				return nbEmpr;
			}

			printf("Voici les informations renseignées pour le nouvel emprunt :\n\n");
			afficherEmprunts(emp);

			printf("\n\nEtes-vous sur des données rentrées ? ( oui / non )\n");
			scanf("%s%*c", &choix);
			reponse=strcmp(oui,choix);
		}

		tEmpr[nbEmpr]=emp;
		nbEmpr=nbEmpr+1;

		printf("L'emprunt %s a été intégrée dans le tableau\n\nTapez entrée pour afficher le tableau mise à jour\n",emp.idEmprunt);
		a=getchar();
		afficherEmpruntsEnCours(tEmpr, nbEmpr, tJeux, nbJeux);

		lRes=supprimer(lRes,res.idResa);  //supprime le choix
		*nbRes=*nbRes-1;

		printf("\nLa suppression s'est bien passé, la liste est donc bien mise à jour\n\nTaper entrer pour l'afficher !");
		a=getchar();
		printf("{\n");
		afficherRes(lRes);
		printf("}\n");
	}

	// SI LE JEU N'ETAIT PAS RESERVE DONC ON LE RAJOUTE DANS LES JEUX DISPONIBLES
	if(verif!=1)
	{
		nbJeuxDisp=JeuxDisp(tEmpr, tJeuxDisp, nbJeuxDisp, nbEmpr);
		printf("Le jeu a bien été retourner ! Merci beaucoup !\n");
	}

	return nbEmpr;
}

int supressionEmprunts(Emprunts tEmpr[], int i, int nbEmpr)
{
	int j;
	for(j=i;j<=nbEmpr-2;j++)
	{
		tEmpr[j]=tEmpr[j+1];
	}
	nbEmpr=nbEmpr-1;
	return nbEmpr;
}


/********************************************** Q7 **************************************************/ 
/******************************** ANNULATION D'UNE RESERVATION **************************************/
/****************************************************************************************************/

Liste annRes (Liste lRes, int *nbRes)
{
	char choix[7],ON[4],g;
	int i,j;
	afficherRes(lRes);
	printf("}\n");
	printf("Saisir l'id de la réservations (RE00?):");
	scanf("%s%*c",choix);
	lRes=supprimer(lRes,choix);
	printf("La réservation %s à bien été supprimée\n",choix);
	return lRes;
	
}


/********************************************** Q8 **************************************************/ 
/******************************** SAUVEGARDE EN FICHIER BINAIRE**************************************/
/****************************************************************************************************/

void sauve(Adherents **tAd, int nbAd, Emprunts tEmp[],int nbEmp, Jeux* tJeux, char* nomFichJ, int nbJeux, Liste lRes,int nbRes)
{
	int i=0,j=0;
	char a,b,c,d;
	Jeux* tJeuxB;
	FILE*flotJeux;
	FILE*flotEmpr;
	FILE* flotAdh;
	FILE* flotRes;
	Emprunts emp;
	Adherents ad;
	Reservations res;
	flotJeux=fopen( nomFichJ,"wb");
	flotEmpr=fopen("emprunts.txt","w");
	flotAdh=fopen("adherents.txt","w");
	flotRes=fopen("reservations.txt","w");
	if(flotJeux==NULL)
	{
		printf("problème dans l’ouverture du fichier jeux\n");
		exit(1);
	}
	if(flotEmpr==NULL)
	{
		printf("problème dans l’ouverture du fichier emprunts\n");
		exit(1);
	}
	if(flotAdh==NULL)
	{
		printf("problème dans l’ouverture du fichier adherents\n");
		exit(1);
	}
	if(flotRes==NULL)
	{
		printf("Problème d'ouverture du fichier Reservations en écriture\n");
		exit (-1);
	}
	fprintf(flotJeux,"%d\n",nbJeux);
	fwrite(tJeux,sizeof(Jeux),nbJeux,flotJeux);
	fclose(flotJeux);
	
	while(i<nbEmp)
	{
		emp=tEmp[i];
		fprintf(flotEmpr,"%s\t\t%s\t\t%s\t\t%d/%d/%d\n",emp.idEmprunt,emp.idAdherent,emp.idJeux,emp.dateEmpr.jour,emp.dateEmpr.mois,emp.dateEmpr.annee);
		i=i+1;
	}
	fclose(flotEmpr);
	
	while(j<nbAd)
	{
		ad=*tAd[j];
		
		fprintf(flotAdh,"%s\n%s\n%s\n%s\n%d/%d/%d\n",ad.idAdherent,ad.civilite,ad.nom,ad.prenom,ad.dateInsc.jour,ad.dateInsc.mois,ad.dateInsc.annee);
		j=j+1;
	}
	fclose(flotAdh);
	
	ecrireRes(lRes,flotRes);
	fclose(flotRes);
	
	tJeuxB=restaureTJeux(&nbJeux);
	printf("Sauvegarde des jeux effectuée\n\ntapez la touche entrée pour restaurer le fichier binaire");
	c=getchar();
	printf("\n----------------Tableau tJeux restauré à partir d'un fichier binaire-----------\n\n");
	afficherTJeux(tJeuxB, nbJeux);
	
	printf("Sauvegarde des emprunts effectuée\n\ntapez la touche entrée pour restaurer le fichier");
	a=getchar();
	printf("\n----------------Tableau tEmp restauré à partir d'un fichier -----------\n\n");
	afficherTEmprunts(tEmp, nbEmp);
	
	printf("Sauvegarde des adherents effectuée\n\ntapez la touche entrée pour restaurer le fichier");
	b=getchar();
	printf("\n----------------Tableau tAdh restauré à partir d'un fichier -----------\n\n");
	afficherTAdherents(tAd, nbAd);
	
	printf("Sauvegarde des réservations effectuée\n\ntapez la touche entrée pour restaurer le fichier");
	d=getchar();
	printf("\n----------------Tableau tRes restauré à partir d'un fichier -----------\n\n");
	afficherRes(lRes);
}

void ecrireRes(Liste lRes,FILE* flotRes)
{
	if(vide(lRes))
	{
		return;
	}	
	fprintf(flotRes,"%s\t%s\t%s\t%d/%d/%d\n",lRes->v.idResa,lRes->v.idAdherent,lRes->v.idJeux,lRes->v.dateResa.jour,lRes->v.dateResa.mois,lRes->v.dateResa.annee);
	ecrireRes(lRes->suiv,flotRes);
}

/*************************************************************************/

void actualiserTJeuxDisp(char nomFichJ[], Jeux* tJeux, int nbJeux)
{
	FILE*flotJeux;
	flotJeux=fopen( nomFichJ,"wb");
	if(flotJeux==NULL)
	{
		printf("problème dans l’ouverture du fichier jeux\n");
		exit(1);
	}
	fprintf(flotJeux,"%d\n",nbJeux);
	fwrite(tJeux,sizeof(Jeux),nbJeux,flotJeux);
	fclose(flotJeux);
}
/****************************************************************************************************/



Jeux *restaureTJeux(int* nbJeux)
{
	Jeux *tJeux;
	FILE *fJeuxb;
	int i;
	fJeuxb = fopen("fJeuxb.bin","rb");
	if(fJeuxb==NULL)
	{
		printf("Problème d'ouverture du fichier binaire en lecture\n");
		return NULL;
	
	}
	fscanf(fJeuxb,"%d%*c",nbJeux);
	tJeux= (Jeux *) malloc(*nbJeux * sizeof(Jeux));
	if(tJeux == NULL)
	{
		printf("Problème d'allocation de tableau\n");
		fclose(fJeuxb);
		return NULL;
	}
	fread(tJeux,sizeof(Jeux),*nbJeux,fJeuxb);
	fclose(fJeuxb);
	return tJeux;
}

/************************************** Insérer Jeux ***************************************/

int insererJeux(Jeux* tJeux, int nbJeux)
{
	Jeux j;
	char a;
	j=saisieJeux(tJeux, nbJeux);
	if(strcmp(j.idJeux,"err")==0)
		return nbJeux;
	tJeux[nbJeux]=j;
	nbJeux=nbJeux+1;
	printf("Le jeux %s a été intégrée dans le tableau\n\nTapez entrée pour afficher le tableau mise à jour\n",j.idJeux);
	a=getchar();
	afficherTJeux(tJeux, nbJeux);
	return nbJeux;
}



/*******************************************************************************************/

Jeux saisieJeux(Jeux* tJeux, int nbJeux)
{
	int nouv,nbexemp;
	Jeux j;
	afficherTJeux(tJeux, nbJeux);
	printf("\nQuel est l'identifiant du jeux que vous voulez insérer \nIdentifiant:\t");
	scanf("%s%*c",j.idJeux);
	nouv=rech (j.idJeux, tJeux, nbJeux);
	if(nouv==-1)
	{
		if(strlen(j.idJeux)>6 || strlen(j.idJeux)<6)
		{
			printf("L'identifiant doit contenir 6 lettre/chiffre\n");
			strcpy(j.idJeux,"err");
			return j;
		}
		printf("Donnez le type du nouveau jeux (construction,carte,logique,plateau,tuile) : ");
		scanf("%s%*c",j.type);
		while(strcmp(j.type,"construction")!=0 && strcmp(j.type,"logique")!=0 && strcmp(j.type,"carte")!=0  && strcmp(j.type,"plateau")!=0 && strcmp(j.type,"tuile")!=0 )
		{
			printf("Le type du jeux est mal orthographié\nRetapez son type : ");
			scanf("%s%*c",j.type);
		}
		printf("Donnez le nombre d'exemplaire du nouveau jeux : ");
		scanf("%d%*c",&j.nb);
		printf("Donnez le nom du nouveau jeux : ");
		fgets(j.nom,31,stdin);
		j.nom[strlen(j.nom)-1]='\0';
		printf("Voici les informations renseignées pour le nouveau jeux :\n\n");
		afficherJeux(j);
		return j;
	}
	if(nouv!=-1)
	{
		printf("Donnez le nombre d'exemplaire que vous voulez ajouter au jeux %s : ",j.idJeux);
		scanf("%d%*c",&nbexemp);
		tJeux[nouv].nb=tJeux[nouv].nb+nbexemp;
		printf("Voici les informations renseignées pour le changement des information du jeux %s :\n\n",j.idJeux);
		afficherJeux(tJeux[nouv]);
		strcpy(j.idJeux,"err");
		return j;
	}	
}

/********************************* Suppression d'un jeux de la ludothèque ******************/

int suppressionJeux(Jeux* tJeux, int nbJeux,Jeux* tJeuxDisp, int nbJeuxDisp)
{
	char code[7],g;
	int exis,disp;
	afficherTJeux(tJeux, nbJeux);
	printf("Quel est l'identifiant du jeux que vous voulez supprimer\nIdentifiant : \t");
	scanf("%s%*c",code);
	exis=rech (code, tJeux, nbJeux);
	disp=rech (code, tJeuxDisp, nbJeuxDisp);
	if(exis==-1)
	{
		printf("Le jeux %s n'existe pas dans la ludothèque\n",code);
		return nbJeux;
	}
	if(exis!=-1 && disp==-1)
	{
		printf("Le jeux %s ne peut pas être supprimé car il est emprunté\n");
		return nbJeux;
	}
	if(disp!=-1)
	{
		nbJeux=suppJeux(tJeux,nbJeux,code);
		printf("Le jeux %s a bien été supprimé\nTapez entrée pour afficher le tableau mis à jour\n\n",code);
		g=getchar();
		afficherTJeux(tJeux, nbJeux);
		return nbJeux;
	}
}

/******************************************** Vérification des dates d'inscriptions et d'emprunts *******************************************/

void verificationDateInsc_Emp(Adherents *tAd[], int nbAd,Emprunts tEmp[], int nbEmp)
{
	int i,j;
	char renouv[4],g;
	Date dA,dI,dE;
	printf("entrer la date d’aujourd’hui : ");
	scanf("%d/%d/%d%*c",&dA.jour,&dA.mois,&dA.annee);
	for(i=0;i<nbAd;i++)
	{
		dI.jour=tAd[i]->dateInsc.jour;
		dI.mois=tAd[i]->dateInsc.mois;
		dI.annee=tAd[i]->dateInsc.annee;
	
		if(dI.annee==dA.annee-1)
			if(dI.mois==dA.mois)
				if(dI.jour==dA.jour)
				{
					printf("L’adhérent %s %s a t’il renouvellé son abonnement à la ludothèque (oui/non) : ",tAd[i]->nom,tAd[i]->prenom);
					scanf("%s%*c",renouv);
					if(strcmp(renouv,"oui")==0)
					{
						tAd[i]->dateInsc.annee=tAd[i]->dateInsc.annee+1;
						printf("La date de l’adhérent %s %s a été modifié\nTapez entrée pour voir les nouvelles informations\n\n",tAd[i]->nom,tAd[i]->prenom);
						g=getchar();
						afficherAdherents(*tAd[i]);
					}
					if(strcmp(renouv,"non")==0)
					{
						printf("Un message est envoyer à l’adhérent %s %s lui signifiant la fin de son abonnement et de rendre les potentiels jeux en sa possession\n\n", tAd[i]->nom,tAd[i]->prenom);
					}
				}
	}
	for(j=0;j<nbEmp;j++)
	{
		dE.jour=tEmp[j].dateEmpr.jour;
		dE.mois=tEmp[j].dateEmpr.mois;
		if(dE.mois==12)
			dE.mois=0;
		if(dE.mois+1==dA.mois)
			if(dE.jour==dA.jour)
			{
				printf("L’emprunt %s doit être rendu à la ludothèque par l'adhérent %s\n\n ",tEmp[j].idEmprunt,tEmp[j].idAdherent);
			}
	}
}

	

