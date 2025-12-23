#include "manager.hpp"
#include <iostream>
#include <iomanip>

Manager::Manager()
	: Employee()
{
	// Устанавливаем должность менеджера
	SetPosition("Менеджер");
}

Manager::Manager(const std::string& fullName, int age, const std::string& contactNumber,
				 const std::string& address, double hourlyRate,
				 const std::string& login, const std::string& password)
	: Employee(fullName, age, contactNumber, address, "Менеджер", hourlyRate, login, password)
{
}

void Manager::AddPenalty(Employee* employee, double amount)
{
	if (employee != nullptr && amount > 0.0)
	{
		double currentBalance = employee->GetSalaryBalance();
		employee->SetSalaryBalance(currentBalance - amount);	// Штраф вычитается из баланса
		std::cout << "Штраф в размере " << amount 
				  << " руб. добавлен сотруднику: " << employee->GetFullName() << std::endl;
	}
}

void Manager::AddBonus(Employee* employee, double amount)
{
	if (employee != nullptr && amount > 0.0)
	{
		double currentBalance = employee->GetSalaryBalance();
		employee->SetSalaryBalance(currentBalance + amount);	// Премия добавляется к балансу
		std::cout << "Премия в размере " << amount 
				  << " руб. добавлена сотруднику: " << employee->GetFullName() << std::endl;
	}
}

void Manager::ChangeHourlyRate(Employee* employee, double newRate)
{
	if (employee != nullptr && newRate >= 0.0)
	{
		employee->SetHourlyRate(newRate);
		std::cout << "Почасовая ставка изменена для сотрудника: " 
				  << employee->GetFullName() << " на " << newRate << " руб./час" << std::endl;
	}
}

void Manager::ChangeHoursWorked(Employee* employee, double hours)
{
	if (employee != nullptr && hours >= 0.0)
	{
		employee->SetHoursWorked(hours);
		std::cout << "Отработанные часы изменены для сотрудника: " 
				  << employee->GetFullName() << " на " << hours << " часов" << std::endl;
	}
}

void Manager::ResetHoursWorked(Employee* employee)
{
	if (employee != nullptr)
	{
		employee->SetHoursWorked(0.0);
		std::cout << "Отработанные часы сброшены для сотрудника: " 
				  << employee->GetFullName() << std::endl;
	}
}

void Manager::ChangeSellingPrice(MenuItem* menuItem, double newPrice)
{
	if (menuItem != nullptr && newPrice >= 0.0)
	{
		menuItem->SetSellingPrice(newPrice);
		std::cout << "Цена продажи изменена для позиции '" << menuItem->GetName() 
				  << "' на " << newPrice << " руб." << std::endl;
	}
}

MenuItem* Manager::CreateMenuItem(const std::string& name, double costPrice,
								  double sellingPrice, bool isAvailable)
{
	MenuItem* newItem = new MenuItem(name, costPrice, sellingPrice, isAvailable);
	std::cout << "Создана новая позиция в меню: " << name << std::endl;
	return newItem;
}

void Manager::EditMenuItem(MenuItem* menuItem, const std::string& newName,
						   double newCostPrice, double newSellingPrice)
{
	if (menuItem != nullptr)
	{
		menuItem->SetName(newName);
		menuItem->SetCostPrice(newCostPrice);
		menuItem->SetSellingPrice(newSellingPrice);
		std::cout << "Позиция меню отредактирована: " << newName << std::endl;
	}
}

void Manager::ViewSalesReport(const MenuItemsType& menuItems) const
{
	std::cout << "=== Отчет по продажам ===" << std::endl;
	std::cout << "Отчет создан менеджером: " << GetFullName() << std::endl;
	std::cout << std::endl;

	if (menuItems.empty())
	{
		std::cout << "Меню пусто." << std::endl;
	}
	else
	{
		double totalProfit = 0.0;
		int totalSales = 0;

		for (const auto* item : menuItems)
		{
			if (item != nullptr)
			{
				int sales = item->GetSalesCount();
				double profit = item->CalculateTotalProfit();
				totalSales += sales;
				totalProfit += profit;

				std::cout << "Позиция: " << item->GetName() 
						  << " | Продаж: " << sales 
						  << " | Прибыль: " << std::fixed << std::setprecision(2) 
						  << profit << " руб." << std::endl;
			}
		}

		std::cout << std::endl;
		std::cout << "Итого продаж: " << totalSales << std::endl;
		std::cout << "Общая прибыль: " << totalProfit << " руб." << std::endl;
	}

	std::cout << "=========================" << std::endl;
}

void Manager::ManageInventory(Inventory* inventory)
{
	if (inventory != nullptr)
	{
		std::cout << "Управление складом менеджером: " << GetFullName() << std::endl;
		inventory->PrintInventoryReport();
		std::cout << std::endl;
		inventory->PrintExpiryDates();
	}
}

