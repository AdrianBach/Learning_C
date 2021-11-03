# include <stdio.h>
# include <stdlib.h>

int main(int argc, char const *argv[])
{
	/* declarer une variable nombre entier */
	//int var;

	/* Si on veut eviter de creer un nouvel espace integer chaque fois qu'on compile 
	on peut creer une variable pointer, plus facile a gerer pour C */
	int *pointer_var;

	// et lui allouer un espace dans la memoire
	pointer_var = malloc(1 * sizeof(int)); 

	/* normalement elle a deja une adresse
	on y accede avec le prefixe & 
	on va la stocker dans une nouvelle variable de type adresse (prefixe) * */
	//double *adr = &var;
	//double *var;

	/* l'afficher dans la console */
	//printf("l'adresse du premier bit de la variable dans le registre de memoire est %p \n", &var);
	printf("l'adresse du premier bit de la variable dans le registre  de memoire est %p \n", &pointer_var);
	/* tema le %p (pointer) qui respecte le type de variable qu'est &var
	%d pour integer, etc, go https://fr.wikipedia.org/wiki/Printf#C pour plus de details */

	/* les infos necessaires sont : l'adresse du premier bit de la variable et son type defini le nombre de bits consecutifs qui lui sont reserves */
	//printf("la variable est de type integer, donc elle occupe %lu bits, a partir du bit %p \n", sizeof(int), &var);
	/* %lu permet de rappeler le retour de sizeof() */
	printf("la variable est de type integer, donc elle occupe %lu bits, a partir du bit %p \n", sizeof(int), &pointer_var);

	/* mettre une valeur a cette adresse */
	//var = 10;
	*pointer_var = 10;

	//printf("la valeur %d est maintenant stockee a l'adresse %p \n", var, &var);
	printf("la valeur %d est maintenant stockee a l'adresse %p \n", *pointer_var, &pointer_var);

	/* quand t'es un vrai tu liberes la memoire que t'a utilise plus haut car personne ne le fera pour toi */
	//free(var);
	/* la ca marche pas car c'est un integer je crois, mais jsais pas pourquoue */
	free(pointer_var);
	// j'ai essayé avec '*' et '&' et c'est sans rien que ça marche, peut-être que c'est parce que c'est a pointer_var qu'on a fait malloc
	// en plus '&' renvoit a l'adresse du premier bit de la serie donc ca pouvait pas marcher
	// '*' c'est l'adresse du premier bit + l'info sur la longueur (int, char, etc...)
	// c'est ce qu'il y a a cette adresse (pointer_var) qu'on veut effacer, on ne veut pas effacer l'emplacement, on veut le vider

	return 0;
}