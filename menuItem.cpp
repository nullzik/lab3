#include "menuItem.hpp"
#include <iostream>
#include <iomanip>

MenuItem::MenuItem()
	: m_name("")
	, m_costPrice(0.0)
	, m_sellingPrice(0.0)
	, m_techCard()
	, m_salesCount(0)
	, m_isAvailable(true)
{
}

MenuItem::MenuItem(const std::string& name, double costPrice, double sellingPrice, bool isAvailable)
	: m_name(name)
	, m_costPrice(costPrice)
	, m_sellingPrice(sellingPrice)
	, m_techCard()
	, m_salesCount(0)
	, m_isAvailable(isAvailable)
{
}

double MenuItem::CalculateProfitPerUnit() const
{
	return m_sellingPrice - m_costPrice;
}

double MenuItem::CalculateTotalProfit() const
{
	return CalculateProfitPerUnit() * m_salesCount;
}

double MenuItem::CalculateMargin() const
{
	if (m_sellingPrice == 0.0)
	{
		return 0.0;
	}
	return (CalculateProfitPerUnit() / m_sellingPrice) * 100.0;
}

void MenuItem::PrintInfo() const
{
	std::cout << "=== Информация о блюде ===" << std::endl;
	std::cout << "Наименование: " << m_name << std::endl;
	std::cout << "Себестоимость: " << std::fixed << std::setprecision(2) << m_costPrice << std::endl;
	std::cout << "Цена продажи: " << m_sellingPrice << std::endl;
	std::cout << "Количество продаж: " << m_salesCount << std::endl;
	std::cout << "Доступно к продаже: " << (m_isAvailable ? "Да" : "Нет") << std::endl;
	std::cout << "Прибыль с единицы: " << CalculateProfitPerUnit() << std::endl;
	std::cout << "Общая прибыль: " << CalculateTotalProfit() << std::endl;
	std::cout << "Маржинальность: " << CalculateMargin() << "%" << std::endl;
	std::cout << "=========================" << std::endl;
}

void MenuItem::SetAvailability(bool isAvailable)
{
	m_isAvailable = isAvailable;
}

std::string MenuItem::GetName() const
{
	return m_name;
}

double MenuItem::GetCostPrice() const
{
	return m_costPrice;
}

double MenuItem::GetSellingPrice() const
{
	return m_sellingPrice;
}

MenuItem::TechCardType MenuItem::GetTechCard() const
{
	return m_techCard;
}

int MenuItem::GetSalesCount() const
{
	return m_salesCount;
}

bool MenuItem::IsAvailable() const
{
	return m_isAvailable;
}

void MenuItem::SetName(const std::string& name)
{
	m_name = name;
}

void MenuItem::SetCostPrice(double costPrice)
{
	m_costPrice = costPrice;
}

void MenuItem::SetSellingPrice(double sellingPrice)
{
	m_sellingPrice = sellingPrice;
}

void MenuItem::SetTechCard(const TechCardType& techCard)
{
	m_techCard = techCard;
}

void MenuItem::SetSalesCount(int salesCount)
{
	m_salesCount = salesCount;
}

