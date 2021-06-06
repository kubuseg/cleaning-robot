#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>      
#include <ctime>  
#include <string>
#include <sstream>
#include <thread>

using namespace std;
using time_point = chrono::system_clock::time_point;

//Z4.Klasa Interpreter
// Zaimplementować klasę Interpreter, będącą kolekcją która przechowuje listę instrukcji 
// bazujących na interfejsie IOrder w tym rozkazy definiowane przez użytkownika.
// Instrukcje mogą być różne (Włącz, Wyłącz, Przesuń do pozycji x, y) i dotyczyć różnych 
// elementów wykonawczych(LED, silnik, serwomechanizm).
// Instrukcje będą wykonane o zadanym czasie(wykorzystać std::chrono).
// Klasa powinna umożliwić przeglądanie zapisanych instrukcji oraz ich wypisywanie na dowolny 
// strumień wyjściowy. Należy zaimplementować odpowiedni iterator, który umożliwia 
// np.poruszanie się po instrukcjach dotyczących konkretnego urządzenia, 
// czy przegląd wycinka programu w zadanym przedziale czasowym.


// Converts time given as string in format "hh:mm:ss" to time point
// day, month, year is the same as system clock's from now
time_point getTimePoint(const string time_str)
{
	stringstream ss(time_str);
	tm tm1 = { 0 }; ss >> get_time(&tm1, "%H:%M:%S");
	time_t t = time(nullptr); tm tm = *localtime(&t);
	tm.tm_hour = tm1.tm_hour; tm.tm_min = tm1.tm_min; tm.tm_sec = tm1.tm_sec;
	time_t time_c = mktime(&tm);
	return chrono::system_clock::from_time_t(time_c);
}

pair<time_point, time_point> getTimePoints(const string time_str1, const string time_str2)
{
	auto tp1 = getTimePoint(time_str1);
	auto tp2 = getTimePoint(time_str2);
	return make_pair(tp1, tp2);
}

class IOrder {
public:
	time_point exeTime; // Order's execution time
	IOrder(const string time) {
		// getting execution time
		this->exeTime = getTimePoint(time);
	}
	virtual void doOrder() = 0; // calling this fuction executes order
	virtual ostringstream getOrderText() const = 0; // text of the Order
	// comparing orders is equal to compering their time_points
	friend bool operator==(const IOrder& o1, const IOrder& o2) {
		return o1.exeTime == o2.exeTime;
	}
	friend bool operator> (const IOrder& o1, const IOrder& o2) {
		return o1.exeTime > o2.exeTime;
	}
	friend bool operator>=(const IOrder& o1, const time_point tp) {
		return o1.exeTime >= tp;
	}
	friend bool operator<=(const IOrder& o1, const time_point tp) {
		return o1.exeTime <= tp;
	}
	friend bool operator> (const IOrder& o1, const time_point tp) {
		return o1.exeTime > tp;
	}
	friend bool operator< (const IOrder& o1, const IOrder& o2) {
		return o1.exeTime < o2.exeTime;
	}
	friend chrono::seconds operator- (const IOrder& o1, const time_point tp) {
		return chrono::duration_cast<chrono::seconds>(o1.exeTime - tp);
	}
	friend ostream& operator<<(ostream& os, const IOrder& o)
	{
		time_t time_c = chrono::system_clock::to_time_t(o.exeTime);
		os << typeid(o).name() << ": " << o.getOrderText().str() << " - " << ctime(&time_c);
		return os;
	}
};


class Interpreter : public vector<IOrder*>
{
private:
	// Executing orders
	void exeOrders(const time_point startT, const time_point endT)
	{
		for (auto n = this->myBegin(startT); n != this->myEnd(endT); ++n)
		{
			auto exeTime = n.operator*()->exeTime;
			auto now = chrono::system_clock::now();
			if (now > exeTime)
			{
				n.operator*()->doOrder();
				continue;
			}
			auto duration = chrono::duration_cast<chrono::milliseconds>(exeTime - now);
			while (duration >= chrono::milliseconds(100)) {
				this_thread::sleep_for(chrono::milliseconds(100));
				now = chrono::system_clock::now();
				duration = chrono::duration_cast<chrono::milliseconds>(exeTime - now);
			}
			n.operator*()->doOrder();
		}
	}
public:

	void getOrders(const string time_str1, const string time_str2)
	{ // Get orders from given timeframe
		auto tps = getTimePoints(time_str1, time_str2);
		auto startT = get<0>(tps); auto endT = get<1>(tps);
		if (startT > endT) {
			startT = getTimePoint("00:00:00"); endT = getTimePoint("23:59:59");
		}
		for (auto n = this->myBegin(startT); n != this->myEnd(endT); ++n)
			cout << **n << endl;
		this->exeOrders(startT, endT);
	}
	void getOrders()
	{   // Get all orders
		auto startT = getTimePoint("00:00:00"); auto endT = getTimePoint("23:59:59");
		for (auto n = this->myBegin(startT); n != this->myEnd(endT); ++n)
			cout << **n << endl;
		this->exeOrders(startT, endT);
	}
	void getOrders(const string object)
	{   // Get orders from given class name
		string typeId = "class " + object;
		auto startT = getTimePoint("00:00:00"); auto endT = getTimePoint("23:59:59");
		for (auto n = this->myBegin(startT); n != this->myEnd(endT); ++n)
			if (typeid(**n).name() == typeId)
				cout << **n << endl;
		this->exeOrders(startT, endT);
	}
	class MyIterator
	{
		friend Interpreter;
	private:
		vector<IOrder*>::iterator current;
		vector<IOrder*>& collection;
		MyIterator(vector<IOrder*>& col, vector<IOrder*>::iterator const i) : collection(col)
		{
			current = i;
		}

	public:
		IOrder* operator*() const
		{
			return *current;
		}

		MyIterator& operator++()
		{
			for (auto i = current + 1; i != collection.end(); ++i)
				if (**i == **current)
				{
					current = i;
					return *this;
				}
			auto min = collection.end();
			for (auto i = collection.begin(); i != collection.end(); ++i)
				if (**i > **current && (min == collection.end() || **i < **min))
					min = i;
			this->current = min;
			return *this;
		}

		bool operator!=(MyIterator const& i) const
		{
			return current != i.current;
		}
	};

	MyIterator myBegin(time_point startT)
	{
		if (startT > chrono::system_clock::now()) {
			return MyIterator(*this, this->end());
		}
		vector<IOrder*>::iterator min = this->begin();
		for (auto i = this->begin(); i != this->end(); ++i)
			if (**i < **min && **i >= startT)
				min = i;
		return MyIterator(*this, min);
	}

	MyIterator myEnd(time_point endT)
	{
		vector<IOrder*>::iterator end = this->end();
		chrono::seconds shortest = chrono::hours(24);
		for (auto i = this->begin(); i != this->end(); ++i) {
			if (**i > endT && **i - endT <= shortest) {
				shortest = **i - endT;
				end = i;
			}
		}
		return MyIterator(*this, end);
	}
};

//Derived classes
class Led : public IOrder {
public:
	Led(const string time_str, bool tOn) : IOrder(time_str) {
		On = false;
		this->turnOn = tOn;
	}
	void doOrder() { On = turnOn; }
	ostringstream getOrderText() const
	{
		ostringstream os;
		string state;
		if (turnOn) state = "ON"; else state = "OFF";
		os << "Turn " << state << " Led";
		return os;
	}
private:
	bool On, turnOn;
};

class Location : public IOrder {
public:
	Location(const string time_str, const pair<double, double> nLocation) : IOrder(time_str)
	{
		this->location = make_pair(0.0, 0.0);
		this->newLocation = nLocation;
	}
	void doOrder() { this->location = newLocation; }
	ostringstream getOrderText() const
	{
		ostringstream os;
		os << "Change Location to (x, y) = " << "(" << get<0>(newLocation) << ", " << get<1>(newLocation) << ")";
		return os;
	}
private:
	pair<double, double> location, newLocation;
};

int main()
{
	Interpreter i;
	i.push_back(new Led("11:23:30", true));
	i.push_back(new Location("11:23:45", make_pair(5.7, 10.3)));
	i.push_back(new Led("11:24:00", false));
	i.push_back(new Location("11:24:30", make_pair(2.21, 6.72)));

	//i.getOrders();
	i.getOrders("10:00:00", "18:00:00");
	//i.getOrders("Led");
}