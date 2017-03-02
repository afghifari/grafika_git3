#ifndef COLOR_H
#define COLOR_H

class color {
	public :
		//default inisiasi dengan 0 (black)
		color();
		color(int r, int g, int b);
		~color();
		color(color&);

		color& operator= (const color&);

		color getColor();

		void setColor(int r, int g, int b);

		int getR();
		int getG();
		int getB();

	private :
		int R;
		int G;
		int B;
};
#endif
