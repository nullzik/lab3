#ifndef CHEF_HPP
#define CHEF_HPP

#include "employee.hpp"
#include "product.hpp"
#include "menuItem.hpp"
#include "inventory.hpp"
#include <vector>
#include <ctime>
#include <memory>

// Класс шеф-повара, наследуется от Employee
// Предоставляет доступ к управлению продуктами, технологическими картами и складом
class Chef : public Employee
{
public:
	using WriteOffsType = std::vector<std::pair<std::shared_ptr<Product>, double>>;	// Вектор списаний (продукт и количество)

private:
	WriteOffsType m_writeOffs;		// История списаний продуктов
	std::time_t m_shiftStartTime;	// Время начала текущей смены

public:
	// Конструкторы и деструктор
	Chef();
	Chef(const std::string& fullName, int age, const std::string& contactNumber,
		 const std::string& address, double hourlyRate,
		 const std::string& login, const std::string& password);
	~Chef() = default;

	// Методы работы с продуктами и складом
	void AddProduct(std::shared_ptr<Inventory> inventory, const Product& product);	// Добавить продукт на склад
	void WriteOffProduct(std::shared_ptr<Product> product, double quantity, const std::string& reason = "");	// Списать продукт (вызывается из класса Product)
	
	// Методы работы с технологическими картами
	void AddTechCard(std::shared_ptr<MenuItem> menuItem, const MenuItem::TechCardType& techCard);	// Добавить технологическую карту для блюда
	
	// Методы отчетности
	void PrintWriteOffsReport(std::time_t startTime, std::time_t endTime) const;	// Вывести отчет о списаниях за период
	void PrintShiftWriteOffsReport() const;	// Вывести отчет о списаниях за текущую смену
	
	// Методы управления складом
	void ManageInventory(std::shared_ptr<Inventory> inventory);	// Управление складом (просмотр отчетов)
	
	// Метод для начала смены (обновляет время начала смены)
	void StartShift();
};

#endif // CHEF_HPP

