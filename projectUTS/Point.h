#ifndef _POINT_H
#define _POINT_H
class Point {
    public:
      	//Constructor
      	// Set titik mula - mula ke (0, 0)
        Point();
        Point(int x, int y);
        
        //Getter
        int GetAbsis();
        int GetOrdinat();

        //setter
        void SetAbsis (int _X);
        void SetOrdinat (int _Y);

        //predikat
        //menghasilkan 1 jika titik (x, y) berada di (0,0)  dan 0 
        // apabila sebaliknya
        int IsOrigin();

        //Operator Relasional 
        // Menghasilkan 1 jika titik pada argumen sama dengan dirinya
        // (nilainya x dan y sama) dan - apabila sebaliknya
        int IsEqual(Point P);

        //Operator aritmetika, operator overloading
        Point Add(Point P1, Point P2);

        // menghasilkan current objek+P
        Point Add(Point P);

        // Menghasilkan sebuah point dengan translasi (x, y)
        Point Add(int x, int y);

        //Mengubah titik dengan penambahan POint argumen
        void AddToMe(Point P);

        //Mentranslasikan titik sebesar (x, y)
        void AddToMe(int x, int y);

        //mengubah titik yang merupakan hasil mirror dengan
        // garis y = x
        void Mirror();

        // Fungsi lain
        // Menghasilkan nomor kuadran dari titik sekarang
        // Sebuah titik yang berada pada sumbu x atau y tidak akan dicoba
        int Kuadran();

        // Menghasilkan sebuah titik yang merupakan hasil mirror dengan garis
        Point MirrorOfMe();
        
        Point& operator= (const Point&);
        
    private:
        int x; //absis
        int y; //ordinat

};
#endif
