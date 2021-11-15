//pointeurs openclassroom

#include <stdio.h>


void affichage_tab(int tableau [], int taille)  //affiche un tableau
{
for(int i=0; i<taille; i++){
printf("%d,", tableau[i]);}

printf("\n");
}

void retire_tab( int tableau[] , int ind, int newtaille, int newtab[]) //fonction d'exercice pour retirer une valeur a un tableau
{
  
  for (int i = 0; i <ind; i++)
  {
    newtab[i] = tableau[i];
  }
  for (int i = ind; i <newtaille; i++)
  {
    newtab [i] = tableau[i+1];
  }
  affichage_tab(newtab,4);

}

int main()
{
  int newtab[4];
	int tableau [5]={1,2,3,4,5};

	//retire_tab(tableau,3,4,newtab);
	//affichage_tab(newtab,4);
  int a=-1;
  int b=a+1;
  printf("%d, %d \n",b, a);
    return 0;

}
