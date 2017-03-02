#include "Point.h"
#include <math.h>
//Constructor
// Set titik mula - mula ke (0, 0)
Point::Point (){
	x = 0;
	y = 0;
}

Point::Point (int _x, int _y){
	x = _x;
	y = _y;
}

//Getter
int Point::GetAbsis(){
	return x;
}

int Point::GetOrdinat(){
	return y;
}

//setter
void Point::SetAbsis (int _X){
	x = _X;
}
void Point::SetOrdinat (int _Y){
	y = _Y;
}

//predikat
//menghasilkan 1 jika titik (x, y) berada di (0,0)  dan 0 
// apabila sebaliknya
int Point::IsOrigin(){
	return (x==0 && y==0);
}

//Operator Relasional 
// Menghasilkan 1 jika titik pada argumen sama dengan dirinya
// (nilainya x dan y sama) dan - apabila sebaliknya
int Point::IsEqual(Point P){
	return (x==y);
}

//Operator aritmetika, operator overloading
Point Point::Add(Point P1, Point P2){
	Point P3;
	P3.x = P1.x + P2.x;
	P3.y = P1.y + P2.y;
	return P3;
}

// menghasilkan current objek+P
Point Point::Add(Point P){
	Point P1;
	P1.x = x;
	P1.y = y;
	P1.x+= P.x;
	P1.y+= P.y;
	return P1;
}

// Menghasilkan sebuah point dengan translasi (x, y)
Point Point::Add(int x, int y){
	Point P1;
	P1.x = x;
	P1.y = y;
	P1.x+= x;
	P1.y+= y;
	return P1;
}

//Mengubah titik dengan penambahan POint argumen
void Point::AddToMe(Point P){	
	x+= P.x;
	y+= P.y;
}

//Mentranslasikan titik sebesar (x, y)
void Point::AddToMe(int x, int y){
	this->x+=x;
	this->y+=y;
}

//mengubah titik yang merupakan hasil mirror dengan
// garis y = x
void Point::Mirror(){
	y*=-1;
}

// Fungsi lain
// Menghasilkan nomor kuadran dari titik sekarang
// Sebuah titik yang berada pada sumbu x atau y tidak akan dicoba
int Point::Kuadran(){
	if (x>0 && y>0){
		return 1;
	}else if (x<0 && y>0){
		return 2;
	}else if (x<0 && y<0){
		return 3;
	}else if (x>0 && y<0){
		return 4;
	}
}
        
// Menghasilkan sebuah titik yang merupakan hasil mirror dengan garis y = x
       
Point Point::MirrorOfMe(){
	Point P;
	P.y*=-1;
	return P;
}

Point& Point::operator= (const Point &p) {
	x = p.x;
	y = p.y;
	return *this;	
}
