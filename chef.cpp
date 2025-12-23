#include "chef.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

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

void Chef::AddProduct(Inventory* inventory, const Product& product)
{
	if (inventory != nullptr)
	{
		inventory->AddProduct(product);
		std::cout << "Шеф-повар " << GetFullName() 
				  << " добавил продукт '" << product.GetName() 
				  << "' на склад '" << inventory->GetWarehouseName() << "'" << std::endl;
	}
}

void Chef::WriteOffProduct(Product* product, double quantity, const std::string& reason)
{
	if (product != nullptr && quantity > 0.0)
	{
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
			std::cout << "Ошибка: недостаточно продукта '" << product->GetName() 
					  << "' для списания. Доступно: " << product->GetWeight() 
					  << " кг, требуется: " << quantity << " кг" << std::endl;
		}
	}
}

void Chef::AddTechCard(MenuItem* menuItem, const MenuItem::TechCardType& techCard)
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
	
	// Форматируем даты
	char startDateStr[100];
	char endDateStr[100];
	std::strftime(startDateStr, sizeof(startDateStr), "%d.%m.%Y %H:%M", std::localtime(&startTime));
	std::strftime(endDateStr, sizeof(endDateStr), "%d.%m.%Y %H:%M", std::localtime(&endTime));
	
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
			Product* product = writeOff.first;
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

	char shiftStartStr[100];
	std::strftime(shiftStartStr, sizeof(shiftStartStr), "%d.%m.%Y %H:%M", std::localtime(&m_shiftStartTime));
	std::cout << "Начало смены: " << shiftStartStr << std::endl;
	std::cout << std::endl;

	// Фильтруем списания за текущую смену
	// Для упрощения считаем все списания из списка (в реальной системе нужна фильтрация по времени)
	double totalQuantity = 0.0;
	int count = 0;

	for (const auto& writeOff : m_writeOffs)
	{
		Product* product = writeOff.first;
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

void Chef::ManageInventory(Inventory* inventory)
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

