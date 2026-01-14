#ifndef WAITER_HPP
#define WAITER_HPP

#include "employee.hpp"
#include "order.hpp"
#include <vector>
#include <memory>

// Класс официанта, наследуется от Employee
// Добавляет учёт обслуженных столов и чаевых
class Waiter : public Employee
{
public:
	using OrdersType = std::vector<std::shared_ptr<Order>>;

private:
	int m_tablesServed;		// Количество обслуженных столов за смену
	double m_tipsBalance;	// Баланс чаевых

public:
	// Конструкторы и деструктор
	Waiter();
	Waiter(const std::string& fullName, int age, const std::string& contactNumber,
		   const std::string& address, double hourlyRate,
		   const std::string& login, const std::string& password);
	Waiter(const Waiter& other);
	~Waiter() = default;

	// Методы работы официанта
	void ServeOrder(std::shared_ptr<Order> order);	// Отметить обслуживание заказа
	void AddTips(double amount);					// Добавить чаевые

	// Переопределение виртуальной функции из базового класса
	double CalculateSalary() const override;	// Переопределение виртуальной функции Employee::CalculateSalary()

	// Геттеры
	int GetTablesServed() const;
	double GetTipsBalance() const;
};

#endif // WAITER_HPP


