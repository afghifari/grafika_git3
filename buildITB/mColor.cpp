#include "color.h"
#include <iostream>

using namespace std;

int main() {
	color c;
	color cc(1,2,3);
	color temp;
	


	cout << "get r : " << c.getR() << endl;
	cout << "get g : " << c.getG() << endl;
	cout << "get b : " << c.getB() << endl;

	cout << endl;

	cout << "get r : " << cc.getR() << endl;
	cout << "get g : " << cc.getG() << endl;
	cout << "get b : " << cc.getB() << endl;

	cout << "get r temp : " << temp.getR() << endl;
	cout << "get g temp : " << temp.getG() << endl;
	cout << "get b temp : " << temp.getB() << endl;

	c = cc;
	// temp = cc.getColor();

	cout << endl;

	cout << "get r : " << c.getR() << endl;
	cout << "get g : " << c.getG() << endl;
	cout << "get b : " << c.getB() << endl;

	cout << "get r temp : " << temp.getR() << endl;
	cout << "get g temp : " << temp.getG() << endl;
	cout << "get b temp : " << temp.getB() << endl;


	return 0;
}
