#include "chef.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <stdexcept>
#include <sstream>

Chef::Chef()
	: Employee()
	, m_writeOffs()
	, m_shiftStartTime(0)
{
	// Устанавливаем должность шеф-повара
	SetPosition("Шеф-повар");
}

Chef::Chef(const std::string& fullName, int age, const std::string& contactNumber,
		   const std::string& address, double hourlyRate,
		   const std::string& login, const std::string& password)
	: Employee(fullName, age, contactNumber, address, "Шеф-повар", hourlyRate, login, password)
	, m_writeOffs()
	, m_shiftStartTime(0)
{
}

// Конструктор копирования: вызывает конструктор копирования базового класса Employee
Chef::Chef(const Chef& other)
	: Employee(other)  // Вызов конструктора копирования базового класса
	, m_writeOffs(other.m_writeOffs)
	, m_shiftStartTime(other.m_shiftStartTime)
{
}

void Chef::AddProduct(std::shared_ptr<Inventory> inventory, const Product& product)
{
	if (inventory != nullptr)
	{
		inventory->AddProduct(product);
		std::cout << "Шеф-повар " << GetFullName() 
				  << " добавил продукт '" << product.GetName() 
				  << "' на склад '" << inventory->GetWarehouseName() << "'" << std::endl;
	}
}

void Chef::WriteOffProduct(std::shared_ptr<Product> product, double quantity, const std::string& reason)
{
	if (!product)
	{
		throw std::invalid_argument("Указатель на продукт равен nullptr");
	}

	if (quantity <= 0.0)
	{
		throw std::invalid_argument("Количество для списания должно быть положительным");
	}

	// Проверяем, достаточно ли продукта для списания
	if (product->GetWeight() >= quantity)
	{
		product->RemoveProduct(quantity);
		m_writeOffs.push_back({product, quantity});
		
		std::cout << "Списание продукта: " << product->GetName() 
				  << " в количестве " << quantity << " кг";
		if (!reason.empty())
		{
			std::cout << " (причина: " << reason << ")";
		}
		std::cout << std::endl;
	}
	else
	{
		// Демонстрация генерации исключения с сообщением
		throw std::runtime_error("Недостаточно продукта '" + product->GetName() + "' для списания");
	}
}

void Chef::AddTechCard(std::shared_ptr<MenuItem> menuItem, const MenuItem::TechCardType& techCard)
{
	if (menuItem != nullptr)
	{
		menuItem->SetTechCard(techCard);
		std::cout << "Технологическая карта добавлена для блюда '" 
				  << menuItem->GetName() << "' шеф-поваром " << GetFullName() << std::endl;
	}
}

void Chef::PrintWriteOffsReport(std::time_t startTime, std::time_t endTime) const
{
	std::cout << "=== Отчет о списаниях за период ===" << std::endl;
	std::cout << "Шеф-повар: " << GetFullName() << std::endl;
	
	// Форматируем даты (использование std::string вместо массива char)
	std::string startDateStr(100, '\0');
	std::string endDateStr(100, '\0');
	std::strftime(&startDateStr[0], startDateStr.size(), "%d.%m.%Y %H:%M", std::localtime(&startTime));
	std::strftime(&endDateStr[0], endDateStr.size(), "%d.%m.%Y %H:%M", std::localtime(&endTime));
	startDateStr.resize(std::strlen(startDateStr.c_str()));  // Обрезаем до реальной длины
	endDateStr.resize(std::strlen(endDateStr.c_str()));  // Обрезаем до реальной длины
	
	std::cout << "Период: с " << startDateStr << " по " << endDateStr << std::endl;
	std::cout << std::endl;

	if (m_writeOffs.empty())
	{
		std::cout << "Списаний за указанный период не было." << std::endl;
	}
	else
	{
		double totalQuantity = 0.0;
		int count = 0;

		for (const auto& writeOff : m_writeOffs)
		{
			const auto& product = writeOff.first;
			double quantity = writeOff.second;
			
			if (product != nullptr)
			{
				std::cout << "Продукт: " << product->GetName() 
						  << " | Количество: " << std::fixed << std::setprecision(2) 
						  << quantity << " кг" << std::endl;
				totalQuantity += quantity;
				count++;
			}
		}

		std::cout << std::endl;
		std::cout << "Итого списаний: " << count << std::endl;
		std::cout << "Общее количество списанного: " << totalQuantity << " кг" << std::endl;
	}

	std::cout << "===================================" << std::endl;
}

void Chef::PrintShiftWriteOffsReport() const
{
	std::cout << "=== Отчет о списаниях за смену ===" << std::endl;
	std::cout << "Шеф-повар: " << GetFullName() << std::endl;
	
	if (m_shiftStartTime == 0)
	{
		std::cout << "Смена не была начата." << std::endl;
		std::cout << "================================" << std::endl;
		return;
	}

	// Использование std::string вместо массива char
	std::string shiftStartStr(100, '\0');
	std::strftime(&shiftStartStr[0], shiftStartStr.size(), "%d.%m.%Y %H:%M", std::localtime(&m_shiftStartTime));
	shiftStartStr.resize(std::strlen(shiftStartStr.c_str()));  // Обрезаем до реальной длины
	std::cout << "Начало смены: " << shiftStartStr << std::endl;
	std::cout << std::endl;

	// Фильтруем списания за текущую смену
	// Для упрощения считаем все списания из списка (в реальной системе нужна фильтрация по времени)
	double totalQuantity = 0.0;
	int count = 0;

	for (const auto& writeOff : m_writeOffs)
	{
		const auto& product = writeOff.first;
		double quantity = writeOff.second;
		
		if (product != nullptr)
		{
			std::cout << "Продукт: " << product->GetName() 
					  << " | Количество: " << std::fixed << std::setprecision(2) 
					  << quantity << " кг" << std::endl;
			totalQuantity += quantity;
			count++;
		}
	}

	if (count == 0)
	{
		std::cout << "Списаний за смену не было." << std::endl;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "Итого списаний: " << count << std::endl;
		std::cout << "Общее количество списанного: " << totalQuantity << " кг" << std::endl;
	}

	std::cout << "================================" << std::endl;
}

void Chef::ManageInventory(std::shared_ptr<Inventory> inventory)
{
	if (inventory != nullptr)
	{
		std::cout << "Просмотр склада шеф-поваром: " << GetFullName() << std::endl;
		inventory->PrintInventoryReport();
		std::cout << std::endl;
		inventory->PrintExpiryDates();
	}
}

void Chef::StartShift()
{
	m_shiftStartTime = std::time(nullptr);
	std::cout << "Смена начата шеф-поваром: " << GetFullName() << std::endl;
}

double Chef::CalculateSalary() const
{
	// Переопределение виртуальной функции: используем базовый расчет + бонус шеф-повара
	double baseSalary = Employee::CalculateSalary();  // Вызов базовой реализации
	double chefBonus = m_salesCount * 50.0;  // Бонус за продажи (50 руб. за каждую продажу)
	
	std::cout << "[Chef] Расчет зарплаты: базовая = " << baseSalary
			  << ", бонус шеф-повара = " << chefBonus << std::endl;
	
	return baseSalary + chefBonus;
}

std::string Chef::GenerateReport() const
{
	// Реализация абстрактного метода: генерирует отчет шеф-повара
	std::ostringstream oss;
	oss << "Отчет шеф-повара: " << GetFullName() << "\n";
	oss << "Должность: " << GetPosition() << "\n";
	oss << "Отработано часов: " << GetHoursWorked() << "\n";
	oss << "Почасовая ставка: " << GetHourlyRate() << " руб./час\n";
	oss << "Зарплата: " << CalculateSalary() << " руб.\n";
	oss << "Количество списаний продуктов: " << m_writeOffs.size() << "\n";
	oss << "Количество продаж: " << GetSalesCount();
	return oss.str();
}

std::string Chef::GetReportType() const
{
	// Реализация абстрактного метода: возвращает тип отчета
	return "Отчет шеф-повара";
}

