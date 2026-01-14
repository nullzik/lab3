#ifndef CASHIER_HPP
#define CASHIER_HPP

#include "employee.hpp"
#include "order.hpp"
#include <memory>

// Кассир, наследуется от Employee
// Отвечает за приём оплаты и суммарную выручку по кассе
class Cashier : public Employee
{
private:
	double m_cashRegisterTotal;	// Общая сумма, проведённая через кассу за смену

public:
	// Конструкторы и деструктор
	Cashier();
	Cashier(const std::string& fullName, int age, const std::string& contactNumber,
			const std::string& address, double hourlyRate,
			const std::string& login, const std::string& password);
	Cashier(const Cashier& other);
	~Cashier() = default;

	// Проведение оплаты заказа
	void ProcessPayment(std::shared_ptr<Order> order);

	// Переопределение виртуальной функции из базового класса
	double CalculateSalary() const override;	// Переопределение виртуальной функции Employee::CalculateSalary()

	// Геттер
	double GetCashRegisterTotal() const;
};

#endif // CASHIER_HPP


