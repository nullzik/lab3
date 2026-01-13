#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "employee.hpp"
#include "menuItem.hpp"
#include "inventory.hpp"
#include "order.hpp"
#include <vector>
#include <memory>

// Класс управляющего, наследуется от Employee
// Предоставляет расширенные права доступа для управления рестораном
class Manager : public Employee
{
public:
	using EmployeesType = std::vector<std::shared_ptr<Employee>>;
	using MenuItemsType = std::vector<std::shared_ptr<MenuItem>>;
	using OrdersType = std::vector<std::shared_ptr<Order>>;

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
	void AddPenalty(std::shared_ptr<Employee> employee, double amount);		// Добавить штраф сотруднику
	void AddBonus(std::shared_ptr<Employee> employee, double amount);			// Добавить премию сотруднику
	void ChangeHourlyRate(std::shared_ptr<Employee> employee, double newRate);	// Изменить почасовую ставку
	void ChangeHoursWorked(std::shared_ptr<Employee> employee, double hours);	// Изменить отработанные часы
	void ResetHoursWorked(std::shared_ptr<Employee> employee);					// Сбросить отработанные часы

	// Методы управления меню
	void ChangeSellingPrice(std::shared_ptr<MenuItem> menuItem, double newPrice);	// Изменить цену продажи
	std::shared_ptr<MenuItem> CreateMenuItem(const std::string& name, double costPrice, 
							 double sellingPrice, bool isAvailable = true);	// Создать позицию в меню
	void EditMenuItem(std::shared_ptr<MenuItem> menuItem, const std::string& newName,
					  double newCostPrice, double newSellingPrice);	// Редактировать позицию в меню

	// Методы просмотра отчетов
	void ViewSalesReport(const MenuItemsType& menuItems) const;	// Просмотр отчетов по продажам по позициям меню
	void ViewOrdersReport(const OrdersType& orders) const;		// Просмотр отчетов по заказам

	// Методы управления складом
	void ManageInventory(std::shared_ptr<Inventory> inventory);					// Управление складом (вызов отчета)
};

#endif // MANAGER_HPP

