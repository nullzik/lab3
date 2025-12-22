#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <string>
#include <vector>

class MenuItem
{
public:
	using TechCardType = std::vector<std::vector<std::string>>;

private:
	std::string m_name;
	double m_costPrice;
	double m_sellingPrice;
	TechCardType m_techCard;
	int m_salesCount;
	bool m_isAvailable;

public:
	// Конструкторы и деструктор
	MenuItem();
	MenuItem(const std::string& name, double costPrice, double sellingPrice, bool isAvailable = true);
	~MenuItem() = default;

	// Публичные методы
	double CalculateProfitPerUnit() const;
	double CalculateTotalProfit() const;
	double CalculateMargin() const;
	void PrintInfo() const;
	void SetAvailability(bool isAvailable);

	// Геттеры
	std::string GetName() const;
	double GetCostPrice() const;
	double GetSellingPrice() const;
	TechCardType GetTechCard() const;
	int GetSalesCount() const;
	bool IsAvailable() const;

	// Сеттеры
	void SetName(const std::string& name);
	void SetCostPrice(double costPrice);
	void SetSellingPrice(double sellingPrice);
	void SetTechCard(const TechCardType& techCard);
	void SetSalesCount(int salesCount);
};

#endif // MENUITEM_HPP

