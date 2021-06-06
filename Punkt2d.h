#pragma once
class Punkt2d
{
private:
	double horizontal;
	double vertical;
public:
	Punkt2d() noexcept;
	Punkt2d(double horizontal, double vertical) noexcept;
	double getHorizontal() const noexcept;
	double getVertical() const noexcept;
	void setHorizontal(double const horizontal) noexcept;
	void setVertical(double const vertical) noexcept;
	double magnitude() const noexcept;
	double direction() const noexcept;

	Punkt2d operator+(Punkt2d const& c) const noexcept;
	Punkt2d operator-(Punkt2d const& c) const noexcept;
	Punkt2d operator+(double v) const noexcept;
	Punkt2d operator-(double v) const noexcept;

	void operator+=(Punkt2d const& c) noexcept;
	void operator+=(double v) noexcept;
	void operator-=(Punkt2d const& c) noexcept;
	void operator-=(double v) noexcept;

	bool operator==(Punkt2d const& c) const noexcept;
	bool operator==(double v) const noexcept;
	bool operator!=(Punkt2d const& c) const noexcept;
	bool operator!=(double v) const noexcept;
};

Punkt2d operator+(double v, Punkt2d const& c);
Punkt2d operator-(double v, Punkt2d const& c);
bool operator==(double v, Punkt2d const& c);
bool operator!=(double v, Punkt2d const& c);

#pragma once
