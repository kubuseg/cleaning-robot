#include <cmath>
#include <limits>
#include "Punkt2d.h"

Punkt2d::Punkt2d() noexcept
{
	horizontal = 0.0;
	vertical = 0.0;
}



Punkt2d::Punkt2d(double horizontal, double vertical) noexcept
{
	this->horizontal = horizontal;
	this->vertical = vertical;
}

double Punkt2d::getHorizontal() const noexcept
{
	return horizontal;
}

double Punkt2d::getVertical() const noexcept
{
	return vertical;
}

void Punkt2d::setHorizontal(double const horizontal) noexcept
{
	this->horizontal = horizontal;
}

void Punkt2d::setVertical(double const vertical) noexcept
{
	this->vertical = vertical;
}

double Punkt2d::magnitude() const noexcept
{
	return sqrt(horizontal * horizontal + vertical * vertical);
}



double Punkt2d::direction() const noexcept
{
	return atan2(vertical, horizontal);
}

Punkt2d Punkt2d::operator+(Punkt2d const& c) const noexcept
{
	return Punkt2d(horizontal + c.getHorizontal(), vertical + c.getVertical());
}

Punkt2d Punkt2d::operator-(Punkt2d const& c) const noexcept
{
	return Punkt2d(horizontal - c.getHorizontal(), horizontal - c.getVertical());
}

Punkt2d Punkt2d::operator+(double v) const noexcept
{
	return Punkt2d(horizontal + v, vertical);
}

Punkt2d Punkt2d::operator-(double v) const noexcept
{
	return Punkt2d(horizontal - v, vertical);
}

void Punkt2d::operator+=(Punkt2d const& c) noexcept
{
	horizontal += c.horizontal;
	vertical += c.vertical;
}

void Punkt2d::operator+=(double v) noexcept
{
	horizontal += v;
}

void Punkt2d::operator-=(Punkt2d const& c) noexcept
{
	horizontal -= c.horizontal;
	vertical -= c.vertical;
}

void Punkt2d::operator-=(double v) noexcept
{
	horizontal -= v;
}

bool Punkt2d::operator==(Punkt2d const& c) const noexcept
{
	return abs(horizontal - c.horizontal) < std::numeric_limits<double>::epsilon() &&
		abs(vertical - c.vertical) < std::numeric_limits<double>::epsilon();
}

bool Punkt2d::operator==(double v) const noexcept
{
	return abs(horizontal - v) < std::numeric_limits<double>::epsilon() &&
		abs(vertical) < std::numeric_limits<double>::epsilon();
}

bool Punkt2d::operator!=(Punkt2d const& c) const noexcept
{
	return !(*this == c);
}

bool Punkt2d::operator!=(double v) const noexcept
{
	return !(*this == v);
}

Punkt2d operator+(double v, Punkt2d const& c)
{
	return Punkt2d(v + c.getHorizontal(), c.getVertical());
}

Punkt2d operator-(double v, Punkt2d const& c)
{
	return Punkt2d(v - c.getHorizontal(), -c.getVertical());
}

bool operator==(double v, Punkt2d const& c)
{
	return c == v;
}

bool operator!=(double v, Punkt2d const& c)
{
	return c != v;
}
