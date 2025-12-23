#include "employee.hpp"
#include <iostream>

Employee::Employee()
	: m_fullName("")
	, m_age(0)
	, m_contactNumber("")
	, m_address("")
	, m_position("")
	, m_hoursWorked(0.0)
	, m_hourlyRate(0.0)
	, m_login("")
	, m_password("")
	, m_salaryBalance(0.0)
	, m_salesCount(0)
{
}

Employee::Employee(const std::string& fullName, int age, const std::string& contactNumber,
				   const std::string& address, const std::string& position,
				   double hourlyRate, const std::string& login, const std::string& password)
	: m_fullName(fullName)
	, m_age(age)
	, m_contactNumber(contactNumber)
	, m_address(address)
	, m_position(position)
	, m_hoursWorked(0.0)
	, m_hourlyRate(hourlyRate)
	, m_login(login)
	, m_password(password)
	, m_salaryBalance(0.0)
	, m_salesCount(0)
{
}

double Employee::CalculateSalary() const
{
	// Расчет з/п = отработанные часы * почасовая ставка + баланс (премии/штрафы)
	return m_hoursWorked * m_hourlyRate + m_salaryBalance;
}

void Employee::AddSales(int salesCount)
{
	if (salesCount > 0)
	{
		m_salesCount += salesCount;
	}
}

bool Employee::OpenShift(const std::string& login, const std::string& password)
{
	// Проверка логина и пароля для открытия смены
	if (login == m_login && password == m_password)
	{
		std::cout << "Смена открыта для сотрудника: " << m_fullName << std::endl;
		return true;
	}
	else
	{
		std::cout << "Неверный логин или пароль!" << std::endl;
		return false;
	}
}

bool Employee::ChangeCredentials(const std::string& oldLogin, const std::string& oldPassword,
								 const std::string& newLogin, const std::string& newPassword)
{
	// Проверка старых учетных данных перед изменением
	if (oldLogin == m_login && oldPassword == m_password)
	{
		m_login = newLogin;
		m_password = newPassword;
		std::cout << "Учетные данные успешно изменены." << std::endl;
		return true;
	}
	else
	{
		std::cout << "Неверный текущий логин или пароль!" << std::endl;
		return false;
	}
}

std::string Employee::GetFullName() const
{
	return m_fullName;
}

int Employee::GetAge() const
{
	return m_age;
}

std::string Employee::GetContactNumber() const
{
	return m_contactNumber;
}

std::string Employee::GetAddress() const
{
	return m_address;
}

std::string Employee::GetPosition() const
{
	return m_position;
}

double Employee::GetHoursWorked() const
{
	return m_hoursWorked;
}

double Employee::GetHourlyRate() const
{
	return m_hourlyRate;
}

std::string Employee::GetLogin() const
{
	return m_login;
}

double Employee::GetSalaryBalance() const
{
	return m_salaryBalance;
}

int Employee::GetSalesCount() const
{
	return m_salesCount;
}

void Employee::SetFullName(const std::string& fullName)
{
	m_fullName = fullName;
}

void Employee::SetAge(int age)
{
	if (age >= 0)
	{
		m_age = age;
	}
}

void Employee::SetContactNumber(const std::string& contactNumber)
{
	m_contactNumber = contactNumber;
}

void Employee::SetAddress(const std::string& address)
{
	m_address = address;
}

void Employee::SetPosition(const std::string& position)
{
	m_position = position;
}

void Employee::SetHoursWorked(double hoursWorked)
{
	if (hoursWorked >= 0.0)
	{
		m_hoursWorked = hoursWorked;
	}
}

void Employee::SetHourlyRate(double hourlyRate)
{
	if (hourlyRate >= 0.0)
	{
		m_hourlyRate = hourlyRate;
	}
}

void Employee::SetSalaryBalance(double salaryBalance)
{
	m_salaryBalance = salaryBalance;
}

