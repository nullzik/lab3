#include "waiter.hpp"
#include <iostream>

Waiter::Waiter()
	: Employee()
	, m_tablesServed(0)
	, m_tipsBalance(0.0)
{
	// Устанавливаем должность по умолчанию для официанта
	SetPosition("Официант");
}

Waiter::Waiter(const std::string& fullName, int age, const std::string& contactNumber,
			   const std::string& address, double hourlyRate,
			   const std::string& login, const std::string& password)
	: Employee(fullName, age, contactNumber, address, "Официант", hourlyRate, login, password)
	, m_tablesServed(0)
	, m_tipsBalance(0.0)
{
}

Waiter::Waiter(const Waiter& other)
	: Employee(other)
	, m_tablesServed(other.m_tablesServed)
	, m_tipsBalance(other.m_tipsBalance)
{
}

void Waiter::ServeOrder(std::shared_ptr<Order> order)
{
	if (order)
	{
		++m_tablesServed;
		std::cout << "Официант " << GetFullName()
				  << " обслужил заказ #" << order->GetOrderId()
				  << ". Всего обслужено столов: " << m_tablesServed << std::endl;
	}
}

void Waiter::AddTips(double amount)
{
	if (amount > 0.0)
	{
		m_tipsBalance += amount;
		std::cout << "Официант " << GetFullName()
				  << " получил чаевые: " << amount
				  << " руб. (всего: " << m_tipsBalance << " руб.)" << std::endl;
	}
}

int Waiter::GetTablesServed() const
{
	return m_tablesServed;
}

double Waiter::GetTipsBalance() const
{
	return m_tipsBalance;
}

double Waiter::CalculateSalary() const
{
	// Используем protected‑поля из базового класса:
	// m_hoursWorked, m_hourlyRate, m_salaryBalance, m_salesCount.
	double base = Employee::CalculateSalary(); // базовый расчет

	// Дополнительный бонус официанту: фикс + % от чаевых + премия за обслуженные столы.
	double tipsBonus = m_tipsBalance * 0.3;		 // 30% чаевых остаётся официанту
	double tablesBonus = m_tablesServed * 50.0;	 // 50 руб. за стол
	double salesBonus = m_salesCount * 10.0;	 // 10 руб. за каждую продажу/позицию

	std::cout << "[Waiter] Расчет зарплаты: базовая = " << base
			  << ", бонус от чаевых = " << tipsBonus
			  << ", бонус за столы = " << tablesBonus
			  << ", бонус за продажи = " << salesBonus << std::endl;

	return base + tipsBonus + tablesBonus + salesBonus;
}


