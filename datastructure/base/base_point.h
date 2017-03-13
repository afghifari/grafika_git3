#ifndef BASE_POINT_H
#define BASE_POINT_H

class BasePoint{
	private:
		double x, y;
	public:
		BasePoint();
		BasePoint(double, double);
		BasePoint(const BasePoint&);

		double getX() const;
		double getY() const;
		void setX(double);
		void setY(double);
};

#endif
