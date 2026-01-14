#include "product.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <sstream>

Product::Product()
	: m_name("")
	, m_weight(0.0)
	, m_supplier("")
	, m_purchasePrice(0.0)
	, m_expiryDate(0)
	, m_receiptDate(0)
{
}

Product::Product(const std::string& name, double weight, const std::string& supplier,
				 double purchasePrice, std::time_t expiryDate, std::time_t receiptDate)
	: m_name(name)
	, m_weight(weight)
	, m_supplier(supplier)
	, m_purchasePrice(purchasePrice)
	, m_expiryDate(expiryDate)
	, m_receiptDate(receiptDate)
{
}

// Конструктор копирования
Product::Product(const Product& other)
	: m_name(other.m_name)
	, m_weight(other.m_weight)
	, m_supplier(other.m_supplier)
	, m_purchasePrice(other.m_purchasePrice)
	, m_expiryDate(other.m_expiryDate)
	, m_receiptDate(other.m_receiptDate)
{
}

void Product::AddProduct(double quantity)
{
	if (quantity > 0.0)
	{
		m_weight += quantity;
	}
}

void Product::RemoveProduct(double quantity)
{
	if (quantity > 0.0 && quantity <= m_weight)
	{
		m_weight -= quantity;
	}
}

bool Product::CheckExpiryDate() const
{
	std::time_t currentTime = std::time(nullptr);
	return currentTime < m_expiryDate;
}

int Product::GetDaysUntilExpiry() const
{
	std::time_t currentTime = std::time(nullptr);
	double secondsDiff = std::difftime(m_expiryDate, currentTime);
	int daysDiff = static_cast<int>(secondsDiff / (60 * 60 * 24));
	return daysDiff;
}

void Product::PrintInfo() const
{
	std::cout << "=== Информация о продукте ===" << std::endl;
	std::cout << "Название: " << m_name << std::endl;
	std::cout << "Вес: " << std::fixed << std::setprecision(2) << m_weight << " кг" << std::endl;
	std::cout << "Поставщик: " << m_supplier << std::endl;
	std::cout << "Цена закупки: " << m_purchasePrice << " руб." << std::endl;
	
	// Вывод даты поступления (использование std::string вместо массива char)
	std::string receiptDateStr(100, '\0');
	std::strftime(&receiptDateStr[0], receiptDateStr.size(), "%d.%m.%Y", std::localtime(&m_receiptDate));
	receiptDateStr.resize(std::strlen(receiptDateStr.c_str()));  // Обрезаем до реальной длины
	std::cout << "Дата поступления: " << receiptDateStr << std::endl;
	
	// Вывод срока годности (использование std::string вместо массива char)
	std::string expiryDateStr(100, '\0');
	std::strftime(&expiryDateStr[0], expiryDateStr.size(), "%d.%m.%Y", std::localtime(&m_expiryDate));
	expiryDateStr.resize(std::strlen(expiryDateStr.c_str()));  // Обрезаем до реальной длины
	std::cout << "Срок годности: " << expiryDateStr << std::endl;
	
	// Проверка срока годности
	bool isExpired = !CheckExpiryDate();
	std::cout << "Статус срока годности: " << (isExpired ? "Истек" : "Действителен") << std::endl;
	
	if (!isExpired)
	{
		std::cout << "Дней до истечения: " << GetDaysUntilExpiry() << std::endl;
	}
	
	std::cout << "=============================" << std::endl;
}

void Product::SetPurchasePrice(double price)
{
	if (price >= 0.0)
	{
		m_purchasePrice = price;
	}
}

std::string Product::GetName() const
{
	return m_name;
}

double Product::GetWeight() const
{
	return m_weight;
}

std::string Product::GetSupplier() const
{
	return m_supplier;
}

double Product::GetPurchasePrice() const
{
	return m_purchasePrice;
}

std::time_t Product::GetExpiryDate() const
{
	return m_expiryDate;
}

std::time_t Product::GetReceiptDate() const
{
	return m_receiptDate;
}

void Product::SetName(const std::string& name)
{
	m_name = name;
}

void Product::SetWeight(double weight)
{
	if (weight >= 0.0)
	{
		m_weight = weight;
	}
}

void Product::SetSupplier(const std::string& supplier)
{
	m_supplier = supplier;
}

void Product::SetExpiryDate(std::time_t expiryDate)
{
	m_expiryDate = expiryDate;
}

void Product::SetReceiptDate(std::time_t receiptDate)
{
	m_receiptDate = receiptDate;
}

// Реализация перегруженных операторов для Product
Product& Product::operator+=(double quantity)
{
	if (quantity > 0.0)
	{
		this->m_weight += quantity;  // Использование this для доступа к полю
	}
	return *this;  // Возврат ссылки на текущий объект
}

bool Product::operator==(const Product& other) const
{
	return this->m_name == other.m_name;  // Использование this для сравнения
}

// Реализация дружественной функции: сравнение продуктов по цене закупки
bool CompareProductsByPrice(const Product& p1, const Product& p2)
{
	// Дружественная функция имеет доступ к приватным полям
	return p1.m_purchasePrice < p2.m_purchasePrice;
}


