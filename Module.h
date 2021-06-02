#pragma once
template <typename T, size_t Lt, typename U = int, size_t Lu = 0, typename V = int, size_t Lv = 0>
class Module
{
private:
	T arrT[Lt];
	U arrU[Lu];
	V arrV[Lv];
public:
	Module(T arrTT[Lt])
	{
		size_t n = 0;
		for (auto& element : arrT)
			element = arrTT[n++];
	}
	Module() {};
	void setArguments(T arrTT[Lt], U arrUU[Lu], V arrVV[Lv])
	{
		arrT = arrTT; arrU = arrUU; arrV = arrVV;
	}
	T* getArrT()
	{
		return arrT;
	}
};
