#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "employee.hpp"
#include "menuItem.hpp"
#include "inventory.hpp"
#include <vector>

// Класс управляющего, наследуется от Employee
// Предоставляет расширенные права доступа для управления рестораном
class Manager : public Employee
{
public:
	using EmployeesType = std::vector<Employee*>;
	using MenuItemsType = std::vector<MenuItem*>;

private:
	// Дополнительные поля для менеджера при необходимости
	// (на данный момент все поля наследуются от Employee)

public:
	// Конструкторы и деструктор
	Manager();
	Manager(const std::string& fullName, int age, const std::string& contactNumber,
			const std::string& address, double hourlyRate,
			const std::string& login, const std::string& password);
	~Manager() = default;

	// Методы управления сотрудниками
	void AddPenalty(Employee* employee, double amount);		// Добавить штраф сотруднику
	void AddBonus(Employee* employee, double amount);			// Добавить премию сотруднику
	void ChangeHourlyRate(Employee* employee, double newRate);	// Изменить почасовую ставку
	void ChangeHoursWorked(Employee* employee, double hours);	// Изменить отработанные часы
	void ResetHoursWorked(Employee* employee);					// Сбросить отработанные часы

	// Методы управления меню
	void ChangeSellingPrice(MenuItem* menuItem, double newPrice);	// Изменить цену продажи
	MenuItem* CreateMenuItem(const std::string& name, double costPrice, 
							 double sellingPrice, bool isAvailable = true);	// Создать позицию в меню
	void EditMenuItem(MenuItem* menuItem, const std::string& newName,
					  double newCostPrice, double newSellingPrice);	// Редактировать позицию в меню

	// Методы просмотра отчетов (базовая версия, будет расширена при создании Order)
	void ViewSalesReport(const MenuItemsType& menuItems) const;	// Просмотр отчетов по продажам

	// Методы управления складом
	void ManageInventory(Inventory* inventory);					// Управление складом (вызов отчета)
};

#endif // MANAGER_HPP

