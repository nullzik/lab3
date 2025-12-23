#include "order.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

// Инициализация статической переменной для генерации ID заказов
int Order::s_nextOrderId = 1;

Order::Order()
	: m_orderId(s_nextOrderId++)
	, m_menuItems()
	, m_totalAmount(0.0)
	, m_orderTime(std::time(nullptr))
	, m_employee(nullptr)
{
}

Order::Order(Employee* employee)
	: m_orderId(s_nextOrderId++)
	, m_menuItems()
	, m_totalAmount(0.0)
	, m_orderTime(std::time(nullptr))
	, m_employee(employee)
{
}

bool Order::AddMenuItem(MenuItem* menuItem)
{
	if (menuItem != nullptr)
	{
		// Проверяем, доступно ли блюдо к продаже
		if (menuItem->IsAvailable())
		{
			m_menuItems.push_back(menuItem);
			CalculateTotalAmount();	// Пересчитываем сумму после добавления
			std::cout << "Блюдо '" << menuItem->GetName() 
					  << "' добавлено в заказ #" << m_orderId << std::endl;
			return true;
		}
		else
		{
			std::cout << "Блюдо '" << menuItem->GetName() 
					  << "' недоступно к продаже!" << std::endl;
			return false;
		}
	}
	return false;
}

bool Order::RemoveMenuItem(const std::string& menuItemName)
{
	auto it = std::find_if(m_menuItems.begin(), m_menuItems.end(),
		[&menuItemName](MenuItem* item) {
			return item != nullptr && item->GetName() == menuItemName;
		});

	if (it != m_menuItems.end())
	{
		m_menuItems.erase(it);
		CalculateTotalAmount();	// Пересчитываем сумму после удаления
		std::cout << "Блюдо '" << menuItemName 
				  << "' удалено из заказа #" << m_orderId << std::endl;
		return true;
	}
	
	std::cout << "Блюдо '" << menuItemName 
			  << "' не найдено в заказе #" << m_orderId << std::endl;
	return false;
}

double Order::CalculateTotalAmount()
{
	m_totalAmount = 0.0;
	
	for (const auto* menuItem : m_menuItems)
	{
		if (menuItem != nullptr)
		{
			m_totalAmount += menuItem->GetSellingPrice();
		}
	}
	
	return m_totalAmount;
}

void Order::PrintOrder() const
{
	std::cout << "=== Заказ #" << m_orderId << " ===" << std::endl;
	
	// Вывод времени заказа
	char timeStr[100];
	std::strftime(timeStr, sizeof(timeStr), "%d.%m.%Y %H:%M:%S", std::localtime(&m_orderTime));
	std::cout << "Время создания: " << timeStr << std::endl;
	
	// Вывод информации о сотруднике
	if (m_employee != nullptr)
	{
		std::cout << "Сотрудник: " << m_employee->GetFullName() 
				  << " (" << m_employee->GetPosition() << ")" << std::endl;
	}
	else
	{
		std::cout << "Сотрудник: не указан" << std::endl;
	}
	
	std::cout << std::endl;
	std::cout << "Блюда в заказе:" << std::endl;
	
	if (m_menuItems.empty())
	{
		std::cout << "  Заказ пуст." << std::endl;
	}
	else
	{
		int index = 1;
		for (const auto* menuItem : m_menuItems)
		{
			if (menuItem != nullptr)
			{
				std::cout << "  " << index << ". " << menuItem->GetName() 
						  << " - " << std::fixed << std::setprecision(2) 
						  << menuItem->GetSellingPrice() << " руб." << std::endl;
				index++;
			}
		}
	}
	
	std::cout << std::endl;
	std::cout << "Итого: " << std::fixed << std::setprecision(2) 
			  << m_totalAmount << " руб." << std::endl;
	std::cout << "==========================" << std::endl;
}

void Order::CompleteOrder()
{
	// Обновляем счетчики продаж для каждого блюда в заказе
	for (auto* menuItem : m_menuItems)
	{
		if (menuItem != nullptr)
		{
			int currentSales = menuItem->GetSalesCount();
			menuItem->SetSalesCount(currentSales + 1);
		}
	}
	
	// Добавляем продажу сотруднику
	if (m_employee != nullptr)
	{
		m_employee->AddSales(static_cast<int>(m_menuItems.size()));
	}
	
	std::cout << "Заказ #" << m_orderId << " завершен. Продажи обновлены." << std::endl;
}

int Order::GetOrderId() const
{
	return m_orderId;
}

Order::MenuItemsType Order::GetMenuItems() const
{
	return m_menuItems;
}

double Order::GetTotalAmount() const
{
	return m_totalAmount;
}

std::time_t Order::GetOrderTime() const
{
	return m_orderTime;
}

Employee* Order::GetEmployee() const
{
	return m_employee;
}

int Order::GetMenuItemsCount() const
{
	return static_cast<int>(m_menuItems.size());
}

void Order::SetEmployee(Employee* employee)
{
	m_employee = employee;
}

