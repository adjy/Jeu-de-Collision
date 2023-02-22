#include <iostream>
#include <ctime>
#include <cmath>
#include <unistd.h>

using namespace std;
const int NBR_CASE = 10; //Nbre de case total
const int RAYON_A = 2; // Rayon du 1er cercle : 1
const int RAYON_B = 1; // Rayon du 2eme cercle : 2


int alea(int a, int b);
int deplacer ( int Position, int sensDeplacement,int NBR_CASE);
int sensDeplacer(int sensDeplacement, int Position, int NBR_CASE);
void nouvellePosition(int *lig, int *col, int *sensLig, int *sensCol);
void initGrille(int Grille[NBR_CASE][NBR_CASE]);
bool existeAB(int Grille[NBR_CASE][NBR_CASE]);
int trouverLigne( int Grille[NBR_CASE][NBR_CASE], int objet);
int trouverCol( int Grille[NBR_CASE][NBR_CASE], int objet);
float calculerDistance( int Grille[NBR_CASE][NBR_CASE], float x1, float x2, float y1, float y2);
bool estEnCollision(int Grille[NBR_CASE][NBR_CASE],float x1, float x2, float y1, float y2);
void affiche(int Grille[NBR_CASE][NBR_CASE]); // Affiche la grille



int main() {
	srand(time(NULL));
	int Grille[NBR_CASE][NBR_CASE];
	int lig_A, lig_B, col_A, col_B, sensLig_A, sensLig_B, sensCol_A,sensCol_B ;
	int objet_1 = 1;
	int objet_2 = 2;

	initGrille( Grille); //initialise une grille avec un placement aléatoire des objets A et B;
	// Coordonnees de A
	lig_A =  trouverLigne(  Grille,objet_1); // x 
	col_A = trouverCol(  Grille,objet_1); // y

		// Coordonnees de B
	lig_B=  trouverLigne(  Grille,objet_2); // x
	col_B = trouverCol(  Grille,objet_2); // y

	
	sensLig_A =  2*alea(0, 1) -1; // Valeur aleatoire entre -1 et 1
	sensLig_B = 2*alea(0, 1) -1;

	sensCol_A = 2*alea(0, 1) -1;
	sensCol_B = 2*alea(0, 1) -1;
	
	int tour = 0;
	affiche(Grille);

	bool partie = true;

	while( partie){
		

		Grille[lig_A][col_A]=0;
		Grille[lig_B][col_B]=0;
		
		nouvellePosition( &lig_A, &col_A, &sensLig_A, &sensCol_A);
		nouvellePosition( &lig_B, &col_B, &sensLig_B, &sensCol_B);

		

		Grille[lig_A][col_A]=1;
		Grille[lig_B][col_B]=2;
		

		usleep(110000); // faire une pause

		if (estEnCollision(Grille,lig_A,lig_B,col_A,col_B)==true){
			cout<<"\n A en ("<<lig_A<<","<<col_A<<") sens "<<sensLig_A<<" B en ("<<lig_B<<","<<col_B<<") sens "<<sensLig_B<<endl;
			affiche(Grille);
			cout<<"\nColision!!! \n";
			
			partie = false;
		}
			
		else if( !existeAB(Grille)) {
			cout<<"\n A en ("<<lig_A<<","<<col_A<<") sens "<<sensLig_A<<" B en ("<<lig_B<<","<<col_B<<") sens "<<sensLig_B<<endl;
			affiche(Grille);
			cout<<"\n Nexiste pas";
			partie = false;
		}
			
		else{
			if(tour==3){
				
				cout<<"\n A en ("<<lig_A<<","<<col_A<<") sens "<<sensLig_A<<" B en ("<<lig_B<<","<<col_B<<") sens "<<sensLig_B<<endl;
				affiche(Grille);
				tour = 0;
			}
			tour++;
		}		
	}
	cout<<"\nLa distance entre A et B est: "<< calculerDistance( Grille,  lig_A,  lig_B,  col_A, col_B);
}

/*######################## Mes fonctions ########################*/


int alea(int a, int b){
	/*Fonction qui retourne une valeur aleatoire entre 2 nombres
	Parametre attendu : a, b : entier
	Valeur de retour rand()% (b-a+1)+a : entier*/
	return  rand()% (b-a+1)+a ;
}

int deplacer ( int Position, int sensDeplacement,int NBR_CASE){
	/*Fonction deplacer qui retourne la nouvelle ligne (ou colonne) d’un objet à partir de la position int Position, int sensDeplacement,int NBR_CASE
	Valeur de retour val, NBR_CASE-1, 1: entier*/

	int val = (Position  +  alea(1, 3) * sensDeplacement);
		
	if( val > (NBR_CASE-1) ){ //Verifie si la nouvelle position depasse le nombre de case
		return NBR_CASE-1; 
	}

	if (val<0){
		return  1; // Verifie si la nouvelle position ne quitte pas le plan
	}
	return val; // retourne la nouvelle valeur	
}

int sensDeplacer(int sensDeplacement, int Position, int NBR_CASE){
	/*Fonction sensDeplacer qui retourne le nouveau sens de déplacement en fonction du sens initial, d’une position
	parametre attendu : int sensDeplacement, int Position, int NBR_CASE
	valeur de retour : 1, -1, sensDeplacement : entier*/
	if( (sensDeplacement == 1) && (Position == NBR_CASE-1 ) ){ //Verifie si l'objet hurle le bord
		return -1;
	}
	if( (sensDeplacement == -1) && (Position == 0 ) ) //Verifie si l'objet hurle le bord
	{
		return 1;
	}
	return sensDeplacement;
}

void nouvellePosition(int *lig, int *col, int *sensLig, int *sensCol){

	/*Fonction qui retourne la nouvelle position de l’objet ainsi que les nouvelles valeurs du sens de déplacement
	Parametre attendu: int *lig, int *col, int *sensLig, int *sensCol
	Valeur de retour: pas de valeur*/
	
	*lig = deplacer (   *lig,  *sensLig ,NBR_CASE); 
	*col = deplacer ( *col,  *sensCol, NBR_CASE );

	*sensLig = sensDeplacer( *sensLig, *lig,  NBR_CASE);
	*sensCol = sensDeplacer( *sensCol, *col, NBR_CASE);

}

void initGrille(int Grille[NBR_CASE][NBR_CASE]){
	/*Fonction qui retourne une grille 
		Parametre attendu : int Grille
		Valeur de retour: pas de valeur*/

	for( int i=0; i<NBR_CASE; i++){
		for( int j= 0; j<NBR_CASE; j++){
			Grille[i][j]=0; // initialise tout a 0
		}
	}
	for(int t=0; t<2;t++){ // Place 2 points aleatoirement

		int i=alea(0, NBR_CASE-1);
		int j=alea(0, NBR_CASE-1);

		Grille[i][j]=t+1; // la valeur de 1 pour A, la valeur de 2 pour B
	}
}

bool existeAB(int Grille[NBR_CASE][NBR_CASE]){
	/*Fonction qui verifie si les objets A et B existent
		Parametre qttendu: int GRILLE
		Valeur de retour: true, false*/
	int test = 0;
	for( int i=0; i<NBR_CASE; i++){
		for( int j= 0; j<NBR_CASE; j++){
			if( (Grille[i][j]==1) || (Grille[i][j]==2) ){ // Verifie si A et B existent
				test++;
		}
	}
	}
	if(test == 2){
		return true;
	}
	return false;
}

int trouverLigne( int Grille[NBR_CASE][NBR_CASE], int objet) { 
	/*Fonction qui retourne la ligne où se trouve un objet à partir de son numéro et de la grille.
		Parametre attendu: int GRILLE, objet
		Valeur de retour: int i*/
	if(existeAB( Grille)){ // Si l'objet existe
		for( int i=0; i<NBR_CASE; i++){
			for( int j= 0; j<NBR_CASE; j++){
				if( Grille[i][j] == objet){
					return i;
				}
			}
		}
	}
}

int trouverCol( int Grille[NBR_CASE][NBR_CASE], int objet) {
	/* Fonction qui  retourne la colonne où se trouve un objet à partir de son numéro et de la grille
	Parametre attendu: int GRILLE, objet
		Valeur de retour: int j*/
	if(existeAB( Grille)){
		for( int i=0; i<NBR_CASE; i++){
			for( int j= 0; j<NBR_CASE; j++){
				if( Grille[i][j] == objet){
					return j;
				}
			}
		}
	}
}

// float calculerDistance( int Grille[NBR_CASE][NBR_CASE], int objet1, int objet2){
	
// 	float X = trouverLigne( Grille, objet1) - trouverLigne( Grille, objet2); 
// 	float Y = trouverCol(  Grille, objet1) - trouverCol(  Grille, objet2);

// 	float dist = sqrt( pow(X,2) + pow(Y,2) );
// 	return dist;
// }

float calculerDistance( int Grille[NBR_CASE][NBR_CASE], float x1, float x2, float y1, float y2){
	/*Fonction qui retourne la distance entre 2 objets, à partir de leurs positions (lignes et colonnes)
	Parametre attendu: int Grille, float x1, x2, y1, y2
	Valeur de retour: float dist*/
	
	float X = x2-x1; 
	float Y = y2-y1;

	float dist = sqrt( pow(X,2) + pow(Y,2) );
	return dist;
}

bool estEnCollision(int Grille[NBR_CASE][NBR_CASE],float x1, float x2, float y1, float y2){
	/*Fonction qui détermine si oui ou non, une collision a lieu entre 2 objets 
	Parametre attendu: int Grille,float x1, float x2, float y1, float y2
	Valeur de retour: True , False*/	

	 float distance = calculerDistance( Grille, x1,x2,y1,y2);
		
	//cout<<distance<<"------"<<RAYON_A+RAYON_B<<endl;
	 if(distance == (RAYON_A + RAYON_B) ){
		 return true;
	 }
	 return false;
}


void affiche(int Grille[NBR_CASE][NBR_CASE]){
	/*Fonction qui affiche l’espace total, avec une lettre ’A’ pour le 1er objet et la lettre ’B’ pour le
2nd.
	Parametre attendu: int Grille
	Valeur de retour: Pas de valeur*/

	int x1= trouverLigne(  Grille, 1);
	int y1 = trouverCol(  Grille, 1);
	int x2= trouverLigne(  Grille, 2);
	int y2 = trouverCol(  Grille, 2);

	cout<<"  ";
	for (int i=0; i<NBR_CASE;i++){
		cout<<i<<" ";
		}
	cout<<endl;
	for (int i=0; i<NBR_CASE;i++){
		cout<<i<<" ";
		for(int j=0; j<NBR_CASE; j++){
			
			if( calculerDistance(Grille, i, x1, j, y1) <=RAYON_A ){ // represente le rayon par a
				if(Grille[i][j] != Grille[x1][y1]){
					cout<<"a"<<" ";
				}
				else{
					cout<<Grille[x1][y1]<<" ";
				}
			}
			else if( calculerDistance(Grille, i, x2, j, y2) <= RAYON_B ){ 
				if(Grille[i][j] != Grille[x2][y2]){ // represente le rayon par b
					cout<<"b"<<" ";
				}
				else{
					cout<<Grille[x2][y2]<<" ";
				}
			}
		else{
			// Affichage des bords
			if(i==0 || j==0 || i==NBR_CASE-1 || j==NBR_CASE-1){
				cout<<"#"<<" "; 
			}
			else{
			cout<<" "<<" ";
			}
		}

		
		}cout<<endl;
	}
	
}
