#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 2.4
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*  Nom :MAKANI                       Prénom :    Destiné                 */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		*(rep->tab + rep->nb_elts) = enr; /*definition du dernier elerment de la liste*/
		rep->nb_elts++;                   /*augmentation du npmbre d'element*/
		rep->est_trie = false;            /* la liste n'est pas triee*/
		modif = true;                     
		return(OK);
	}
	else {
		return(ERROR);
	}


#else
#ifdef IMPL_LIST
	// compléter code ici pour Liste
	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		int i = 0;
		while ((i < rep->nb_elts) && (est_sup(enr, (GetElementAt(rep->liste, i)->pers)))) { i++; } /*augmentation d'un compteur tant qu'on est dans la liste et que enr >eletcompteur*/
		InsertElementAt(rep->liste, i, enr); /*insertion de l'element*/
		rep->nb_elts++;                      
		modif = true;                       
		rep->est_trie = true;                 /* la liste est triee*/
		return(OK);

	}


#endif

#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* le tableau possède au moins un élément*/
	{					

		if (indice < rep->nb_elts) {             /* indice présent  dans le tableau*/
			for (int i = indice; i < rep->nb_elts - 1; i++) {   /*decalage de chaque element vers la gauche à partir de celui seletionné*/
				*(rep->tab + i) = *(rep->tab + i + 1);
			}
		}

		rep->nb_elts -= 1;	
		modif = true;
	}

	return;
}

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

int supprimer_un_contact_dans_rep_liste(Repertoire* rep, SingleLinkedListElem* elem) {

	int ret = DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0);
}
#endif
#endif


/**********************************************************************/
/*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
/* ex Dupont, Jean                 0320304050                         */
/**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici
	printf("%s, %s                 %s", enr.nom, enr.prenom, enr.tel); 

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	
	printf("\n| %-30s|%-30s|%-20s", enr.nom, enr.prenom, enr.tel); /*forçage de l'affichage pours 30 caractères*/

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code à compléter ici
	if (_stricmp(enr1.nom, enr2.nom) > 0) { return(true); } /* comparaison des noms*/
	if (_stricmp(enr1.nom, enr2.nom) < 0) { return(false); } /*on retourne faux sinon*/
	if (_stricmp(enr1.prenom, enr2.prenom) > 0) { return(true); } 
	if (_stricmp(enr1.prenom, enr2.prenom) < 0) { return(false); }

}

/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire* rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	int Drapeau = 1; /*le drapeau  sert à compter le nombres de permutations par repetition*/
	while (Drapeau != 0) { 
		Drapeau = 0; /* on remet le Drapeau à zéro*/
		for (int i = 0; i < rep->nb_elts - 1; i++) { 
			if (est_sup(*(rep->tab + i), *(rep->tab + i + 1))) { 
				Enregistrement tmp = *(rep->tab + i);
				*(rep->tab + i) = *(rep->tab + i + 1);            /*permutation*/
				*(rep->tab + i + 1) = tmp;
				Drapeau++;                                           /*augmentation xdu drapeau*/
			}
		}
	}



#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire* rep, char nom[], int ind)
{
	int i= ind;		    /* position (indice) de début de recherche */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;


#ifdef IMPL_TAB
	strcpy_s(tmp_nom, MAX_NOM, nom);
	_strupr_s(tmp_nom, _countof(tmp_nom)); /*mise en majuscule de la valeur copié*/
	ind_fin = rep->nb_elts;       
	for (int i = ind; i < ind_fin; i++) {
		strcpy_s(tmp_nom2, MAX_NOM, rep->tab + i);  /*les elements du tableau sont stockés dans des variables temporaires*/
		_strupr_s(tmp_nom2, _countof(tmp_nom2));    /*mise en majuscule*/
		if (strcmp(tmp_nom, tmp_nom2) == 0) { return i; } /*retour de l'indice correspondant*/
	}

#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	strcpy_s(tmp_nom, MAX_NOM, nom);
	_strupr_s(tmp_nom, _countof(tmp_nom));
	ind_fin = rep->nb_elts;
	for (int i = ind; i < ind_fin; i++) {
		// on utilise la même manière que la liste à l'exeption de la manière dont on recupère les élément
		strcpy_s(tmp_nom2, MAX_NOM, GetElementAt(rep->liste, i)->pers.nom);
		_strupr_s(tmp_nom2, _countof(tmp_nom2));
		if (strcmp(tmp_nom, tmp_nom2) == 0) { return i; }
	}
#endif
#endif


	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{
	// compléter code ici

	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau

#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char* char_nw_line;

	_set_errno(0);
	if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */