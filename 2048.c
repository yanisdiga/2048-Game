// ldd: -lncurses
#include <ncursesw/ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
	BACKSPACE
} key;

//Variable / Tableau global
int board[4][4];
uint score;
uint max_score;
uint lignes = 4;
uint colonnes = 4;
int moved;

void INIT_2048 () {
    score = 0;
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    srand(time(NULL));
}
//Initialisation du tableau par 0
void init_board(){
    for(uint i=0; i<lignes; i++){
        for(uint j=0; j<colonnes; j++){
            board[i][j] = 0;
        }
    }
}

void display_board(){
    //Initialisation des couleurs
    int n;
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_BLUE, COLOR_WHITE);
    init_pair(9, COLOR_GREEN, COLOR_WHITE);
    init_pair(10, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(11, COLOR_RED, COLOR_WHITE);

  	// Place le tableau en haut a gauche
    move(0,0);
    // Variables pour les cases //
    char* plus = "+";
    char* tiret = "-";
    char* barre  = "|";
    // Variables pour le titre //
    char* egal = "=";
    char* titre = "Jeu 2048";
    char* t_score = "Score =";
    char* m_score = "Score maximal =";
    // Variable pour les boucles //
    uint i,j,l,c;
    // Titre //
    for(uint k=0; k<27; k++){
        printw("%s", egal);
    }
    printw(" %s ", titre);
    for(uint k=0; k<28; k++){
        printw("%s", egal);
    }
    printw("\n");
    // Score //
    for(uint k=0; k<24; k++){
        printw("%s", egal);
    }
    printw("    %s %i    ", t_score, score);
    for(uint k=0; k<24; k++){
        printw("%s", egal);
    }
    printw("\n");
    //Score max
    for(uint k=0; k<20; k++){
        printw("%s", egal);
    }
    printw("    %s %i    ", m_score, max_score);
    for(uint k=0; k<20; k++){
        printw("%s", egal);
    }
    printw("\n");
    /////////////////////////////////////////////////////////////////
    // Boucle permettant d'afficher toutes les cases
    for(l=0; l<4; l++){
        // Boucles l'affichage des lignes
        for(i=0; i<=4; i++){
            printw("%s", plus);
            for(j=0; j<15; j++){
                if(i<4){
                    printw("%s", tiret);
                }
            }
        }
        printw("\n");
        //Affiche les colonnes
        for(i=0; i<4; i++){
            printw("%s", barre);
            //Si il y'a un chiffre dans la colonnes alors la surligner
            if (board[l][i]) {
                //Choisi la couleur en fonction du nombre dans la case
                n = choose_color(board[l][i]);
                attron(A_STANDOUT | COLOR_PAIR(n));
                printw("               ");
                attroff(COLOR_PAIR(n) | A_STANDOUT);
            } else {
                printw("               ");
            }
        }
        printw("%s", barre);
        printw("\n");
        for(i=0; i<4; i++){
            printw("%s", barre);
            //Si il y'a un chiffre dans la colonnes alors la surligner
            if (board[l][i]) {
                //Choisi la couleur en fonction du nombre dans la case
                n = choose_color(board[l][i]);
                attron(A_STANDOUT | COLOR_PAIR(n));
                printw("               ");
                attroff(COLOR_PAIR(n) | A_STANDOUT);
            } else {
                printw("               ");
            }
        }
        printw("%s", barre);
        printw("\n");
        printw("%s", barre);
        // Boucle pour afficher les nombres dans les cases
        for(c=0; c<4; c++){
            if (board[l][c]) {
                //Choisi la couleur en fonction du nombre dans la case
                n = choose_color(board[l][c]);
                attron(A_STANDOUT | COLOR_PAIR(n));
                printw("%8i       ", board[l][c]);
                attroff(COLOR_PAIR(n) | A_STANDOUT);
                printw("%s", barre);
            } else {
                printw("               %s", barre);
            }
        }
            printw("\n");
        //Affiche les colonnes
        for(i=0; i<4; i++){
            printw("%s", barre);
            //Si il y'a un chiffre dans la colonnes alors la surligner
            if (board[l][i]) {
                //Choisi la couleur en fonction du nombre dans la case
                n = choose_color(board[l][i]);
                attron(A_STANDOUT | COLOR_PAIR(n));
                printw("               ");
                attroff(COLOR_PAIR(n) | A_STANDOUT);
            } else {
                printw("               ");
            }
        }
        printw("%s", barre);
        printw("\n");
        for(i=0; i<4; i++){
            printw("%s", barre);
            //Si il y'a un chiffre dans la colonnes alors la surligner
            if (board[l][i]) {
                //Choisi la couleur en fonction du nombre dans la case
                n = choose_color(board[l][i]);
                attron(A_STANDOUT | COLOR_PAIR(n));
                printw("               ");
                attroff(COLOR_PAIR(n) | A_STANDOUT);
            } else {
                printw("               ");
            }
        }
        printw("%s", barre);
        printw("\n");
    }
    /////////////////////////////////////////////////////////////////
    // Boucle pour la dernière lignes du bas (fermeture)
    if(l==4){
        for(i=0; i<=4; i++){
            printw("%s", plus);
            for(j=0; j<15; j++){
                if(i<4){
                    printw("%s", tiret);
                }
            }
        }
    }
    printw("\n");
    refresh();
}

//Fonction permettant de choisir la couleur a mettre dans la case en fonction du chiffre à l'interieur
int choose_color(int number){
    switch(number){
        case 2:
            return 1;
        case 4:
            return 2;
        case 8:
            return 3;
        case 16:
            return 4;
        case 32:
            return 5;
        case 64:
            return 6;
        case 128:
            return 7;
        case 256:
            return 8;
        case 512:
            return 9;
        case 1024:
            return 10;
        case 2048:
            return 11;
    }
}


void DONE_2048() {
    endwin();
    exit(0);
}

//Fonction comptant le nb de case vide dans le tableau
int count_empty(){
    int empty = 0;
    // Parcours le board et on cherche si une case est vide
    for(uint i=0; i<lignes; i++){
        for(uint j=0; j<colonnes; j++){
            // Si une case est vide on la compte
            if(board[i][j] == 0){
                empty++;
            }
        }
    }
    return empty;
}

//Ajoute un 2 aléatoirement dans le tableau
void add_two(int empty){
    int n = rand()%empty+1;
    int count = 0;
    uint i,j;
    // Parcours le board et compte les case vide jusqu'à que count = place aléatoire
    while(count<n){
        for(i=0; i<lignes; i++){
            for(j=0; j<colonnes; j++){
                if(board[i][j] == 0){
                    count++;
                }
                if(count == n){
                    break;
                }
            }
            if(count == n){
                break;
            }
        }
    }
    board[i][j]=2;
}

//Fonction permettant de savoir si des additions sont encores possible
int more_add(){
    for(uint i=0; i<lignes-1; i++){
        for(uint j=0; j<colonnes-1; j++){
            if(board[i][j]==board[i][j+1] || board[i][j]==board[i+1][j]){
                return 1;
            }
        }
    }
    return 0;
}

int game_over(int add){
    char* egal = "=";
    char* over = "GAME OVER";
    char* key = "(appuyer sur BACKSPACE pour quitter)";
    char* restart = "(appuyer sur une touche pour relancer)";
    int c = count_empty();
    if(c == 0 && more_add()==0){
        move(10, 65);
        ///////////////////////////
        // Game Over
        for(uint k=0; k<21; k++){
            printw("%s", egal);
        }
        printw(" %s ", over);
        for(uint k=0; k<21; k++){
            printw("%s", egal);
        }
        printw("\n");
        // Press a key
        move(11, 65);
        for(uint k=0; k<8; k++){
            printw("%s", egal);
        }
        printw(" %s ", key);
        for(uint k=0; k<7; k++){
            printw("%s", egal);
        }
        printw("\n");
        //Restart
        move(12, 65);
        for(uint k=0; k<7; k++){
            printw("%s", egal);
        }
        printw(" %s ", restart);
        for(uint k=0; k<6; k++){
            printw("%s", egal);
        }
        printw("\n");
        ///////////////////////////
        getch();
        return 1;
    }
    if(c >= 1){
        add_two(c);
        display_board();
        return 0;
    }
    else{
        return 0;
    }
}

//Fonction qui déplace les case != 0 vers la gauche
int shift_board(){
    int move = 0;
    int tmp[4][4]={0};
    for(uint i=0; i<lignes; i++){
        // for(uint j,k=0; j<colonnes; k++,j++) impossible en C alors on initialise k=0 à chaque nouvelle ligne
        uint k = 0;
        for(uint j=0; j<colonnes; j++){
            // Si la case n'est pas vide
            if(board[i][j]!=0){
                // On la copie dans le tableau tmp à l'index k
                tmp[i][k] = board[i][j];
                //Si j!=k alors un déplacement a été effectué
                if(j != k){
                    move = 1;
                }
                // for(uint j,k=0; j<colonnes; k++,j++) impossible en C alors on incrémente k après chaque colonnes
                k++;
            }
        }
    }
    // On remplace maintenant le tableau par le tmp
    for(uint i=0; i<lignes; i++){
        for(uint j=0; j<colonnes; j++){
            board[i][j] = tmp[i][j];
        }
    }
    return move;
}

//Fonction mettant à jour le plateau en ajoutant les cases collé ayant la meme valeur
int update_board(){
    shift_board();
    int result = 0;
    for(uint i=0; i<lignes; i++){
        for(uint j=0; j<colonnes-1; j++){
            if(board[i][j]==board[i][j+1]){
                board[i][j] *= 2;
                board[i][j+1] = 0;
				score+= board[i][j];
                result = 1;
            }
        }
    }
    //On modifie le score max
    if(score >= max_score){
            max_score = score;
    }
    shift_board();
    return result;
}

//Fonction permettant de savoir quel touche est pressée pour le jeu
key get_key(){
    //On attend que l'utilisateur choisissent une touche
	int result = getch();
    //On identifie la touche et on return le mouvement effectué
	switch(result){
		case KEY_UP:
			return UP;
		case KEY_DOWN:
			return DOWN;
		case KEY_LEFT:
			return LEFT;
		case KEY_RIGHT:
			return RIGHT;
		case KEY_BACKSPACE:
			return BACKSPACE;
		default:
			break;
	}
    // return 0 car si le joueur n'appuye pas sur la bonne touche on ne renvoie rien
	return 0;	
}

//Fonction échangent les valeurs entre deux pointeurs
void swap(int* a, int* b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

//Fonction inversant le tableau (renvoie son mirroir)
void mirror_board(){
	for (uint i = 0; i < lignes; i++) {
		// Colonnes/2 car on échange les éléments du tableau entre eux
        for (uint j = 0; j < colonnes / 2; j++) {
            //Swap échange les premiers élément du tableau par les derniers ce qui permet d'obtenir un "mirroir"
            swap(&board[i][j], &board[i][colonnes-1-j]);
        }
    }
}

//Fonction transformant les lignes en colonnes et les colonnes en ligne
void pivot_board(){
	for(uint i=0; i<lignes; i++){
		for(uint j=i+1; j<colonnes; j++){
            //Swap échange les colonnes et les lignes
			swap(&board[i][j], &board[j][i]);
		}
	}
}

//Fonction permettant de choisir une direction et d'effectué le déplacement
int play(key dir) {
    //On initialise une variable "moved" à 0 elle nous permettera de compter le nombre de case qui ont bougé
    moved = 0;
    //On remet le tableau dans sa position initial après la modification
    switch (dir) {
        case UP:
        	pivot_board();
            moved = update_board();
            pivot_board();
            break;
        case DOWN:
            pivot_board();
            mirror_board();
            moved = update_board();
            mirror_board();
            pivot_board();
            break;
        case LEFT:
            moved = update_board();
            break;
        case RIGHT:
            mirror_board();
            moved = update_board();
            mirror_board();
            break;
        default:
            break;
    }
    return moved;
}

int main(){
    INIT_2048();
    //Initialisation du jeu
    init_board();
    //Activation des couleur
    start_color();
    //On initialise la variable add à 1
    moved = 1;
    while(!game_over(moved) || more_add()){
      	key k = get_key();
        if(play(k)) {
			display_board();
        }
    }
    //Si le jeu est fini on appuye sur BACKSPACE (supprimer) pour quitter et sinon on relance une nouvelle partie
	if(get_key() != BACKSPACE){
        //Remet score à 0
        score = 0;
        //Supprime le game over
        clear();
        //Relance le jeu
        main();
	}
    else{
        //On ferme le jeu
        DONE_2048();
        endwin();
    }
}