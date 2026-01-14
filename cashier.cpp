#include "cashier.hpp"
#include <iostream>

Cashier::Cashier()
	: Employee()
	, m_cashRegisterTotal(0.0)
{
	SetPosition("Кассир");
}

Cashier::Cashier(const std::string& fullName, int age, const std::string& contactNumber,
				 const std::string& address, double hourlyRate,
				 const std::string& login, const std::string& password)
	: Employee(fullName, age, contactNumber, address, "Кассир", hourlyRate, login, password)
	, m_cashRegisterTotal(0.0)
{
}

Cashier::Cashier(const Cashier& other)
	: Employee(other)
	, m_cashRegisterTotal(other.m_cashRegisterTotal)
{
}

void Cashier::ProcessPayment(std::shared_ptr<Order> order)
{
	if (order)
	{
		double amount = order->GetTotalAmount();
		m_cashRegisterTotal += amount;

		std::cout << "Кассир " << GetFullName()
				  << " провёл оплату заказа #" << order->GetOrderId()
				  << " на сумму " << amount << " руб."
				  << " (выручка за смену: " << m_cashRegisterTotal << " руб.)" << std::endl;
	}
}

double Cashier::GetCashRegisterTotal() const
{
	return m_cashRegisterTotal;
}

double Cashier::CalculateSalary() const
{
	// Перегрузка без вызова Employee::CalculateSalary().
	// Используем protected‑поля: m_hoursWorked, m_hourlyRate, m_salaryBalance.
	double base = m_hoursWorked * m_hourlyRate;
	double performanceBonus = m_cashRegisterTotal * 0.02; // 2% от проведенной выручки
	double total = base + performanceBonus + m_salaryBalance;

	std::cout << "[Cashier] Расчет зарплаты: базовая = " << base
			  << ", бонус от выручки = " << performanceBonus
			  << ", баланс = " << m_salaryBalance << std::endl;

	return total;
}


