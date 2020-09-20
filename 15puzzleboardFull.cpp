//CS 154
//Author: Prof. R. K. Joshi
//Exercise: Fix the errors in this program and make it work
//when the board is solved, flag a message
//add a randomize button to shuffle pieces into a valid initial problem position
//Modified by : Battepati Karthikeya

#include <iostream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

using namespace std;

int k = 0;

char *int2charstar (int v) {
	char *s = new char[sizeof(int)];
	sprintf(s,"%d",v);
	return s;
};

class Board;
class Piece;

class Piece: public Fl_Button {
	Fl_Button *button;
	Board *parent;
	int xpos, ypos;
 public:
	int lbl;
	Piece(Board *b, int xp, int yp, int x, int y, int pw, int ph); 
	int handle (int);
	int mylabel() { return lbl;}
};

class Board {
	Piece* pieces[4][4];
 	int ex, ey; // position of empty piece
 public:
	Board(int, int, int, int);
	int move(int,int,int);
	void randomize();
	int isSolved();
};

int Board::isSolved() {
   	for (int x=0; x<4;x++){
        for (int y=0; y<4;y++) {
			if (pieces[x][y]->mylabel() != x+y*4+1) return 0;
	    }
	}
	return 1;
}

Piece::Piece(Board *b, int xp, int yp, int x, int y, int pw, int ph): 
	Fl_Button(x,y,pw,ph,((lbl=xp+yp*4+1)==16)?(char*)" ":int2charstar(lbl)) {;
		parent = b;
		xpos = xp; ypos=yp;
	}

int Piece::handle(int event) {  
	if (event==FL_PUSH) {
		cout << "mouse pushed on " << xpos << " " << ypos << endl;
		parent->move(xpos,ypos,lbl);	
	}
	return 1;
};

Board::Board(int x0, int y0, int pw, int ph){ 
   	for (int x=0; x<4;x++){
    	for (int y=0; y<4;y++){ 
			pieces [x][y] = new Piece(this,x,y,x0+x*pw,y0+y*ph, pw, ph);
		}
	}
	 ex=ey=3; // current empty position
	}

int Board:: move(int x, int y, int mylabl) {
	//cout << "move request " << x << " "<< y << " " << mylabl << ex << " " << ey << " " << endl;
	if (((ex==x) && (abs(y-ey)==1))||(ey==y)&&(abs(x-ex)==1)) {  // valid, swap the pieces
		pieces[x][y]->label((char *)"");
		pieces[x][y]->lbl=pieces[ex][ey]->lbl;
		pieces[ex][ey]->label(int2charstar(mylabl));
		pieces[ex][ey]->lbl=mylabl;
		ex=x; 
 		ey=y;

		if ((isSolved())&&(k==0)) {cout << "Solved\n";}
		return 1; //success
		}
		
	if ((isSolved())&&(k==0)) {cout << "Solved\n";}
	return 0;
}

void Board::randomize() {
	int x,y;
	srand(time(NULL));
	for(int i=0;i<1000;i++){
		k = 1;
		x=rand()%4;
		y=rand()%4;		
		move(x,y,pieces[x][y]->lbl);
	}
	k = 0;
}

int main(int argc, char *argv[]) {

   int X=400, Y=400;  // height width of actual puzzle
   int bx=150, by=50; // border margins from x and y axis
   int pw=X/4, ph=X/4; // height width of pieces

   int emptyx=3, emptyy=3;
   Fl_Button* buttons[4][4];

   Fl_Window* w = new Fl_Window(X+2*by, Y+2*bx); // board is 25% larger
   w->label("CS 757 15 Puzzle Lecture 2");

   Board b(by, bx, pw, ph);
   b.randomize();

   w->end();
   w->show(argc, argv);
   return Fl::run();
}