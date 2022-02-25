// Realizzazione con side-effect

#include <stdlib.h>
#include <stdio.h>
#include "esercizio.h"

int main(){

	/* Creazione albero binario:   */
	/*		 13	       */
	/*	     /       \	       */
	/*	    7        32	       */
	/*	  /   \         \      */
	/*	 -2    8         40    */
	/*              \       /      */
	/*               11    36      */

	TipoAlbero A = creaAlbBin( 11  , albBinVuoto(), albBinVuoto() ) ;
	TipoAlbero B = creaAlbBin( 36 , albBinVuoto(), albBinVuoto() ) ;

	TipoAlbero C = creaAlbBin( -2 , albBinVuoto(), albBinVuoto() ) ;
	TipoAlbero D = creaAlbBin( 8 , albBinVuoto(), A);
	TipoAlbero E = creaAlbBin( 40  , B, albBinVuoto());

	TipoAlbero F = creaAlbBin( 7 , C, D);
	TipoAlbero G = creaAlbBin( 32  , albBinVuoto(), E);

	TipoAlbero H = creaAlbBin( 13  , F, G);
	TipoAlbero albero = H;

	/* ---------------------------------------------- */
        /*            test ricercaLivello()               */
	/* ---------------------------------------------- */
	//printf("\nricercaLivello(albero, 7, 0) = %d\n\n", ricercaLivello(albero, 7, 0));
	//printf("ricercaLivello(albero, 36, 0) = %d\n\n", ricercaLivello(albero, 36, 0));


	/* ---------------------------------------------- */
        /*            test verificaNodi()                 */
	/* ---------------------------------------------- */
	//printf("verificaNodi  %d\n\n", verificaNodi(albero, 0));


	/* ---------------------------------------------- */
        /*            test singleChildSum()               */
	/* ---------------------------------------------- */
	//printf("singleChildSum  %d\n\n", singleChildSum(albero));


	/* ---------------------------------------------- */
        /*            test listaNodiFoglia()              */
	/* ---------------------------------------------- */
	//Lista lf1 = listaNodiFoglia(albero);
	//printf("listaNodiFoglia : ");
	//stampaLista(lf1);
	//printf("\n");


	/* ---------------------------------------------- */
        /*            test codaNodiDueFigli()             */
	/* ---------------------------------------------- */
	//Coda* c1 = codaNodiDueFigli(albero);
	//printf("\ncodaNodiDueFigli : ");
	//stampaCoda(c1);
	//printf("\n");


	/* ---------------------------------------------- */
        /*            test listaPercorso()                */
	/* ---------------------------------------------- */
	//Lista lf3 = listaPercorso(albero);
	//printf("listaPercorso : ");
	//stampaLista(lf3);
	//printf("\n");

	/* ---------------------------------------------- */
        /*            test aggiungiFratello()             */
	/* ---------------------------------------------- */
	//aggiungiFratello(albero);
        //stampaAlbero("albero:" , albero);
	//printf("\n");

}
