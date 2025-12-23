#include "inventory.hpp"
#include <iostream>
#include <algorithm>

Inventory::Inventory()
	: m_warehouseName("")
	, m_products()
{
}

Inventory::Inventory(const std::string& warehouseName)
	: m_warehouseName(warehouseName)
	, m_products()
{
}

void Inventory::AddProduct(const Product& product)
{
	m_products.push_back(product);
}

bool Inventory::RemoveProduct(const std::string& productName)
{
	auto it = std::find_if(m_products.begin(), m_products.end(),
		[&productName](const Product& p) {
			return p.GetName() == productName;
		});

	if (it != m_products.end())
	{
		m_products.erase(it);
		return true;
	}
	return false;
}

Product* Inventory::FindProduct(const std::string& productName)
{
	for (auto& product : m_products)
	{
		if (product.GetName() == productName)
		{
			return &product;
		}
	}
	return nullptr;	// Продукт не найден
}

void Inventory::PrintExpiryDates() const
{
	std::cout << "=== Сроки годности продуктов на складе: " << m_warehouseName << " ===" << std::endl;
	
	bool hasExpiredProducts = false;
	
	for (const auto& product : m_products)
	{
		if (!product.CheckExpiryDate())
		{
			hasExpiredProducts = true;
			std::cout << "ВНИМАНИЕ! Продукт '" << product.GetName() 
					  << "' просрочен!" << std::endl;
		}
		else
		{
			int daysLeft = product.GetDaysUntilExpiry();
			std::cout << "Продукт: " << product.GetName() 
					  << " - дней до истечения: " << daysLeft << std::endl;
		}
	}
	
	if (!hasExpiredProducts && m_products.empty())
	{
		std::cout << "Склад пуст." << std::endl;
	}
	else if (!hasExpiredProducts)
	{
		std::cout << "Все продукты в сроке." << std::endl;
	}
	
	std::cout << "===========================================================" << std::endl;
}

void Inventory::PrintInventoryReport() const
{
	std::cout << "=== Отчет о складе: " << m_warehouseName << " ===" << std::endl;
	std::cout << "Количество продуктов на складе: " << m_products.size() << std::endl;
	std::cout << std::endl;
	
	if (m_products.empty())
	{
		std::cout << "Склад пуст." << std::endl;
	}
	else
	{
		for (size_t i = 0; i < m_products.size(); ++i)
		{
			std::cout << "--- Продукт #" << (i + 1) << " ---" << std::endl;
			m_products[i].PrintInfo();
			std::cout << std::endl;
		}
	}
	
	std::cout << "===================================================" << std::endl;
}

std::string Inventory::GetWarehouseName() const
{
	return m_warehouseName;
}

Inventory::ProductsType Inventory::GetProducts() const
{
	return m_products;
}

int Inventory::GetProductsCount() const
{
	return static_cast<int>(m_products.size());
}

void Inventory::SetWarehouseName(const std::string& warehouseName)
{
	m_warehouseName = warehouseName;
}


