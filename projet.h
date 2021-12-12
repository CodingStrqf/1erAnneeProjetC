#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/************ DEFENITION D'UNE STRUCTURE DATE ************/

typedef struct {
	int jour;
	int mois;
	int annee;
} Date;

/************ DEFENITION D'UNE STRUCTURE JEUX ************/

typedef struct {
	char idJeux[7];
	char type[13];
	int nb;
	char nom[31];
} Jeux;

/********* DEFENITION D'UNE STRUCTURE ADHERENTS *********/

typedef struct {
	char idAdherent[6];
	char civilite[4];
	char nom[31];
	char prenom[31];
	Date dateInsc;
} Adherents;

/********* DEFENITION D'UNE STRUCTURE EMPRUNTS *********/

typedef struct {
	char idEmprunt[6];
	char idAdherent[6];
	char idJeux[7];
	Date dateEmpr;
} Emprunts;

/****** DEFENITION D'UNE STRUCTURE RESERVATIONS ******/

typedef struct {
	char idResa[6];
	char idAdherent[6];
	char idJeux[7];
	Date dateResa;
} Reservations;

/****** DEFENITION D'UNE STRUCTURE MAILLON ******/

typedef struct maillon
{
	Reservations v;
	struct maillon *suiv;
}Maillon,*Liste;

typedef enum {faux,vrai}Booleen;


/************** DEFENITION DES FONCTIONS **************/

void global(void);
int choixMenu(void);
void menu(void);
int verificationDate(int dd, int mm, int yy);

/*********** CHARGEMENT DES FICHIER EN MEMOIRE ********/

Jeux* chargeJeux(int* nbJeux);
int chargeEmprunts(Emprunts tempr[], int tmax);
int chargeAdherents (Adherents* tAd[], int taillemax);
Liste chargeReservations(Liste lRes, int* nbRes);

int JeuxDisp (Emprunts tEmpr[], Jeux* tJeuxDisp, int nbJeuxDisp, int nbEmp);
/*********** FONCTION LIRE ***************/

Reservations lireRes(FILE *flot);
Emprunts lireEmprunts(FILE *flot);
Adherents lireAdherents(FILE *flot);
Jeux lireJeux(FILE *flot);

void afficherAdherents(Adherents ad);
void afficherTAdherents(Adherents** tAd, int nbAdh);
void afficherEmprunts(Emprunts emp);
void afficherTEmprunts(Emprunts* tEmpr, int nbEmpr);
void afficherJeux(Jeux j);
void afficherTJeux(Jeux* tJeux, int nbJeux);
void afficherRes(Liste l);

/*****FONCTIONS LISTE*****/

Liste listenouv(void);
Liste insertionEnTete(Liste l,Reservations x);
Booleen vide(Liste l);
int rechListe(Liste l, char choix[] );
int rechListe2(Liste lRes, char choix[]);
int rechListe3(Liste lRes, char choix[]);
Liste suppressionEnTete(Liste l);
Liste supprimer(Liste l,char x[]);
Liste inserer(Liste l,Reservations x);
int comparerDate(Date d1, Date d2);

/******************************/


int rech (char code[], Jeux *tJeuxDisp, int nbJeuxDisp);
int suppJeux(Jeux tJeuxDisp[],int nbJeuxDisp,char code[]);
void decaGauche(Jeux tJeuxDisp[], int nb, int i);


/************** AFFICHAGE DES JEUX DISPO TRIEES PAR TYPE ***********/

void AffichageJeuxDispParType(Emprunts tEmpr[], int nbEmp, Jeux* tJeuxDisp, int nbJeuxDisp);
void triDico(Jeux* tJeuxDisp, int nbJeuxDisp);
void copier(Jeux* tJeuxDisp, int i, int j, Jeux R[]);
void fusion(Jeux R[], int n, Jeux S[], int m,Jeux* tJeuxDisp);
void afficherJeuxDisp(Jeux* tJeuxDisp, int nbJeuxDisp);

/************** AFFICHAGE DES JEUX DISPO TRIEES PAR NOM ****************/

void triAlpha (Jeux *tJeuxDisp,int nbJeuxDisp);
void affJeuxAlph(Emprunts tEmpr[], int nbEmp, Jeux tJeuxDisp[], int nbJeuxDisp );

/****************** AFFICHAGE DES EMPRUNTS EN COURS *****************/

void afficherEmpruntsEnCours(Emprunts tEmpr[], int nbEmpr, Jeux* tJeux, int nbJeux);

/****************** AFFICHAGE DES RESERVATION PAR NOM Q4 *****************/
void AffListeResers(Liste lRes, Jeux* tJeux, int nbJeux);

/****************** INSERER/SUPPRIMER UN ADHERENT *****************/

int insererAdherent(Adherents** tAd, int nbAd);
Adherents saisieAdherents(Adherents** tAd, int nbAd);
int rechAdherents(char code[],Adherents** tAd, int nbAd);
int rechEmpruntAdherent(char code[],Emprunts tEmp[], int nbEmpr);
int supprimerAdherents(Adherents* tAd[], int nbAd, Emprunts tEmp[], int nbEmp, Liste lRes, int nbRes);
void decaGauche2(Adherents *tAd[], int nbAd, int i);

/****************** INSERER UN NOUVEL EMPRUNT OU RESERVATION *****************/

int insererEmprunts(Emprunts tEmpr[], int nbEmpr, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux, Adherents** tAd, int nbAdh, int *nbAdhAide);
Emprunts saisieEmprunts(Emprunts tEmpr[], int nbEmpr, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux, Adherents** tAd, int nbAdh, int *nbAdhAide);
int insererReservation(Liste lRes, int nbRes, Adherents** tAd, int nbAd, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux, int *nbAdhAide);
Reservations saisieReservations(Liste lRes, Adherents** tAd, int nbAd, Jeux* tJeuxDisp, int nbJeuxDisp, Jeux* tJeux, int nbJeux, int *nbAdhAide);
int rechEmprunts(char code[],Emprunts tEmpr[], int nbEmpr);
int triParDate(int nbEmp, Emprunts tEmp, Date date2);
void decalerADroite(FILE *flot, int i, int nb);

/****************** RETOUR D'UN JEU Q6*****************/

int rechJeuxEmprunts(char code[],Emprunts tEmpr[], int nbEmpr);
int supressionEmprunts(Emprunts tEmpr[], int i, int nbEmpr);
int retourJeu(Liste lRes, int* nbRes, Jeux* tJeuxDisp, int nbJeuxDisp, Emprunts tEmpr[], int nbEmpr,Jeux* tJeux, int nbJeux);

/****************** ANNULATION D'UNE RESERVATION Q7 *****************/

Liste annRes (Liste lRes,int *nbRes);

/****************** SAUVEGARDER EN FICHIER BINAIRE Q8 *****************/

void sauve(Adherents **tAd, int nbAdh, Emprunts tEmpr[],int nbEmp, Jeux* tJeux, char* nomFichJ, int nbJeux, Liste lRes,int nbRes);
int chargeAdherents2 (Adherents* tAd[], int taillemax);
Emprunts *restaureTEmprunt(int* nbEmp);
Jeux *restaureTJeux(int* nbJeux);
Liste chargeReservations2(Liste lRes, int* nbRes);
void ecrireRes(Liste lRes,FILE *flot);
void actualiserTJeuxDisp(char nomFichJ[], Jeux* tJeux, int nbJeux);

/***************** INSERER/SUPPRIMER UN JEUX ************************/

int insererJeux(Jeux* tJeux, int nbJeux);
Jeux saisieJeux(Jeux* tJeux, int nbJeux);
int suppressionJeux(Jeux* tJeux, int nbJeux,Jeux* tJeuxDisp, int nbJeuxDisp);

/***************** vérification date ************************/

void verificationDateInsc_Emp(Adherents *tAd[], int nbAd,Emprunts tEmp[], int nbEmp);


