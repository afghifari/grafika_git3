#include "itbmap.h"

void read_file_bangunan(std::vector<Shape*>& bangunan, std::vector<Shape*>& bangunan_besar, std::string file_bangunan){
	FILE * filePointer = fopen(file_bangunan.c_str(), "r");
	// Remove the old S
	for(int i = 0;i < (int)bangunan.size(); ++i){
		delete bangunan[i];
	}
	for(int i = 0;i < (int)bangunan_besar.size(); ++i){
		delete bangunan_besar[i];
	}
	bangunan.clear();
	bangunan_besar.clear();
	int n;
	while(fscanf(filePointer, "%d", &n) != EOF){
		Shape *Sh = new Shape(n + 1);

		Shape *Sh_besar = new Shape(n+1);

		for(int i = 0;i < n; ++i){
			int x, y;
			fscanf(filePointer, "%d%d", &x, &y);
			Point P = Point(x, y);
			Point P_besar = Point(x+640, y);
			Sh->setPoint(i, P);
			Sh_besar->setPoint(i, P_besar);
		}
		Point P = Sh->getPoint(0);
		Sh->setPoint(n, P);

		Point P_besar = Sh_besar->getPoint(0);
		Sh_besar->setPoint(n, P_besar);

		bangunan.push_back(Sh);
		bangunan_besar.push_back(Sh_besar);
	}
}

void read_file_jalan(std::vector<Shape*>& jalan, std::vector<Shape*>& jalan_besar, std::string file_jalan){
	FILE * filePointer = fopen(file_jalan.c_str(), "r");
	// Remove the old S
	for(int i = 0;i < (int)jalan.size(); ++i){
		delete jalan[i];
	}
	for(int i = 0;i < (int)jalan_besar.size(); ++i){
		delete jalan_besar[i];
	}
	jalan.clear();
	jalan_besar.clear();
	int n;
	while(fscanf(filePointer, "%d", &n) != EOF){
		Shape *Sh = new Shape(n);
		Shape *Sh_besar = new Shape(n);
		for(int i = 0;i < n; ++i){
			int x, y;
			fscanf(filePointer, "%d%d", &x, &y);
			Point P = Point(x*137/100, y*137/100);
			Point P_besar = Point((x*137/100)+640, y*137/100);
			Sh->setPoint(i, P);
			Sh_besar->setPoint(i, P_besar);
		}
		jalan.push_back(Sh);
		jalan_besar.push_back(Sh_besar);
	}
}

void read_file_pohon(std::vector<Shape*>& pohon, std::vector<Shape*>& pohon_besar, std::string file_pohon){
	FILE * filePointer = fopen(file_pohon.c_str(), "r");
	// Remove the old S
	for(int i = 0;i < (int)pohon.size(); ++i){
		delete pohon[i];
	}
	for(int i = 0;i < (int)pohon_besar.size(); ++i){
		delete pohon_besar[i];
	}
	pohon.clear();
	pohon_besar.clear();
	int n;
	while(fscanf(filePointer, "%d", &n) != EOF){
		for(int i = 0;i < n; ++i){

			int total_titik = 3;
			int x, y;
			fscanf(filePointer, "%d%d", &x, &y);
			Point pusat = Point(x * 137 / 100, y * 137 / 100);
			Point pusat_besar = Point((x * 137 / 100)+640, y * 137 / 100);
			Shape *Sh = new Shape(total_titik + 1);
			Shape *Sh_besar = new Shape(total_titik + 1);
			for(int j = 0;j < total_titik; ++j){
				Point P = Point(pusat);
				Point P_besar = Point(pusat_besar);
				switch(j){
					case 0:
						P.setY(P.getY() - 2);
						P_besar.setY(P_besar.getY() - 2);
						break;
					case 1:
						P.setX(P.getX() - 2);
						P_besar.setX(P_besar.getX() - 2);
						break;
					case 2:
						P.setX(P.getX() + 2);
						P_besar.setX(P_besar.getX() + 2);
						break;
				}
				Sh->setPoint(j, P);
				Sh_besar->setPoint(j, P_besar);
			}
			Sh->setPoint(total_titik, Sh->getPoint(0));
			Sh_besar->setPoint(total_titik, Sh_besar->getPoint(0));

			pohon.push_back(Sh);
			pohon_besar.push_back(Sh_besar);
		}
	}
}

ITBMap::ITBMap(std::string file_bangunan, std::string file_jalan, std::string file_pohon) {
	read_file_bangunan(bangunan, bangunan_besar, file_bangunan);
	read_file_jalan(jalan, jalan_besar, file_jalan);
	read_file_pohon(pohon, pohon_besar, file_pohon);
	size_bangunan = bangunan.size();
	size_jalan = jalan.size();
	size_pohon = pohon.size();
	size_bangunan_besar = bangunan_besar.size();

	size_jalan_besar = jalan_besar.size();
	size_pohon_besar = pohon_besar.size();
}

ITBMap::~ITBMap() {
	for(int i = 0;i < size_bangunan; ++i){
		delete bangunan[i];
	}
	bangunan.clear();

	for(int i = 0;i < size_jalan; ++i){
		delete jalan[i];
	}
	jalan.clear();

	for(int i = 0;i < size_pohon; ++i){
		delete pohon[i];
	}
	pohon.clear();
}

std::vector<Shape*> ITBMap::get_all_bangunan() const {
	return bangunan;
}

std::vector<Shape*> ITBMap::get_all_jalan() const {
	return jalan;
}

std::vector<Shape*> ITBMap::get_all_pohon() const {
	return pohon;
}

std::vector<Shape*> ITBMap::get_all_drawn_shapes() const {
	std::vector<Shape*> result;

	if (b){
		result.insert(result.end(), bangunan.begin(), bangunan.end());
	}
	if (p) {
		result.insert(result.end(), pohon.begin(), pohon.end());
	}
	if (j) {
		result.insert(result.end(), jalan.begin(), jalan.end());
	}

	return result;
}

Shape* ITBMap::get_bangunan(int idx) const{
	return bangunan[idx];
}
Shape* ITBMap::get_jalan(int idx) const{
	return jalan[idx];
}
Shape* ITBMap::get_pohon(int idx) const{
	return pohon[idx];
}

int ITBMap::get_bangunan_size() const{
	return size_bangunan;
}
int ITBMap::get_jalan_size() const{
	return size_jalan;
}
int ITBMap::get_pohon_size() const{
	return size_pohon;
}

int ITBMap::get_bangunan_besar_size() const{
	return size_bangunan_besar;
}
int ITBMap::get_jalan_besar_size() const{
	return size_jalan_besar;
}
int ITBMap::get_pohon_besar_size() const{
	return size_pohon_besar;
}

void ITBMap::setArg(bool p, bool b, bool j){
	this->p = p;
	this->b = b;
	this->j = j;
}
