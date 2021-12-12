#include"projet.h"

void testAdherents(void)
{
	Adherents* tAd[100];
	int nbAdh;
	nbAdh=chargeAdherents(tAd, 100);
	if(nbAdh<0)
		return;

	afficherTAdherents( tAd,  nbAdh);
	free(*tAd);
}

/****************************************************************************/

void testEmprunts(void)
{
	Emprunts tEmpr[50];
	int nbEmp;
	nbEmp=chargeEmprunts(tEmpr, 50);
	if(nbEmp<0)
		return;
	afficherTEmprunts(tEmpr, nbEmp);
}

/****************************************************************************/

void testJeux(void)
{
	Jeux* tJeux;
	int nbJeux;
	tJeux=chargeJeux(&nbJeux);
	if(tJeux==NULL)
		return;
	afficherTJeux(tJeux, nbJeux);
	free(tJeux);
	Jeux* tJeuxDisp;
	tJeuxDisp=chargeJeux(&nbJeux);
	if(tJeuxDisp==NULL)
		return;
	afficherTJeux(tJeuxDisp, nbJeux);
	free(tJeuxDisp);
}


/****************************************************************************/

void testLReservations(void)
{
	Liste lRes;
	Booleen B;
	int nbRes=0;
	lRes=listenouv();
	lRes=chargeReservations(lRes, &nbRes);
	afficherRes(lRes);
	printf("}\n");
	printf("nb Res : %d \n",nbRes);
	free(lRes);
}

/****************************************************************************/

void testRech (void)
{
	char code[7];
	int nbJeuxDisp,pos;
	Jeux* tJeuxDisp;
	tJeuxDisp=chargeJeux(&nbJeuxDisp);
	if(tJeuxDisp==NULL)
		return;
	afficherTJeux(tJeuxDisp, nbJeuxDisp);
	printf("Bonjour quelle jeux rechercher vous : ");
	scanf("%s%*c",code);
	pos=rech (code, tJeuxDisp, nbJeuxDisp);
	while(pos==-1)
	{
		printf("Désoler mais je jeu n'est pas disponible\n");
		printf("Retaper un jeu a chercher : ");
		scanf("%s%*c",code);
		pos=rech (code, tJeuxDisp, nbJeuxDisp);
	}
	printf("Le jeu %s  de code %s est a la position %d\n",tJeuxDisp[pos].nom,tJeuxDisp[pos].idJeux,pos);
	free(tJeuxDisp);
}

/****************************************************************************/
void testSupp(void)
{
	char code[7];
	int nbJeuxDisp,i;
	Jeux* tJeuxDisp;
	Emprunts tEmpr[50];
	int nbEmp;
	tJeuxDisp=chargeJeux(&nbJeuxDisp);
	if(tJeuxDisp==NULL)
		return;

	nbEmp=chargeEmprunts(tEmpr, 50);
	if(nbEmp<0)
		return;
	afficherTJeux(tJeuxDisp, nbJeuxDisp);
	afficherTEmprunts(tEmpr, nbEmp);
	for(i=0;i<nbEmp;i++)
		{
			strcpy(code,tEmpr[i].idJeux);
			nbJeuxDisp=suppJeux(tJeuxDisp, nbJeuxDisp, code);
		}
	afficherTJeux(tJeuxDisp, nbJeuxDisp);
}
/****************************************************************************/

void testAfficherJeuxDispType(void)
{
	char code[7];
	int nbJeuxDisp,i;
	Jeux* tJeuxDisp;
	Emprunts tEmpr[50];
	int nbEmp;
	tJeuxDisp=chargeJeux(&nbJeuxDisp);
	if(tJeuxDisp==NULL)
		return;

	nbEmp=chargeEmprunts(tEmpr, 50);
	if(nbEmp<0)
		return;
	for(i=0;i<nbEmp;i++)
		{
			strcpy(code,tEmpr[i].idJeux);
			nbJeuxDisp=suppJeux(tJeuxDisp, nbJeuxDisp, code);
		}	
	afficherTJeux(tJeuxDisp, nbJeuxDisp);
	triDico(tJeuxDisp, nbJeuxDisp);
	afficherJeuxDisp(tJeuxDisp, nbJeuxDisp);
}

/****************************************************************************/
void testAffJeuxAlph(void)
{
	char code[7];
	int nbJeuxDisp,i;
	Jeux* tJeuxDisp;
	Emprunts tEmpr[50];
	int nbEmp;
	tJeuxDisp=chargeJeux(&nbJeuxDisp);
	if(tJeuxDisp==NULL)
		return;

	nbEmp=chargeEmprunts(tEmpr, 50);
	if(nbEmp<0)
		return;
	for(i=0;i<nbEmp;i++)
		{
			strcpy(code,tEmpr[i].idJeux);
			nbJeuxDisp=suppJeux(tJeuxDisp, nbJeuxDisp, code);
		}	
	afficherTJeux(tJeuxDisp, nbJeuxDisp);
	triAlpha (tJeuxDisp,nbJeuxDisp);
	afficherJeuxDisp(tJeuxDisp, nbJeuxDisp);

	
}

/****************************************************************************/

int main(void)
{
	//testRech();
	//testLReservations();
	//testAdherents();
	//testEmprunts();
	//testJeux();
	global();
	//testSupp();
	//testAffJeuxAlph();
	return 0;
}


