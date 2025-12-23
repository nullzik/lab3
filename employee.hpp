#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>

class Employee
{
private:
	std::string m_fullName;			// ФИО
	int m_age;						// Возраст
	std::string m_contactNumber;	// Контактный номер
	std::string m_address;			// Адрес
	std::string m_position;			// Должность
	double m_hoursWorked;			// Отработанные часы
	double m_hourlyRate;			// Почасовая ставка
	std::string m_login;			// Логин
	std::string m_password;			// Пароль
	double m_salaryBalance;			// Баланс з/п (для штрафов, премий, списаний)
	int m_salesCount;				// Количество продаж (для метода добавления продаж)

public:
	// Конструкторы и деструктор
	Employee();
	Employee(const std::string& fullName, int age, const std::string& contactNumber,
			 const std::string& address, const std::string& position,
			 double hourlyRate, const std::string& login, const std::string& password);
	~Employee() = default;

	// Публичные методы
	double CalculateSalary() const;					// Расчет заработной платы
	void AddSales(int salesCount);					// Добавить продажи
	bool OpenShift(const std::string& login, const std::string& password);	// Открыть смену (проверка логина/пароля)
	bool ChangeCredentials(const std::string& oldLogin, const std::string& oldPassword,
						   const std::string& newLogin, const std::string& newPassword);	// Сменить логин/пароль

	// Геттеры
	std::string GetFullName() const;
	int GetAge() const;
	std::string GetContactNumber() const;
	std::string GetAddress() const;
	std::string GetPosition() const;
	double GetHoursWorked() const;
	double GetHourlyRate() const;
	std::string GetLogin() const;
	double GetSalaryBalance() const;
	int GetSalesCount() const;

	// Сеттеры
	void SetFullName(const std::string& fullName);
	void SetAge(int age);
	void SetContactNumber(const std::string& contactNumber);
	void SetAddress(const std::string& address);
	void SetPosition(const std::string& position);
	void SetHoursWorked(double hoursWorked);
	void SetHourlyRate(double hourlyRate);
	void SetSalaryBalance(double salaryBalance);
};

#endif // EMPLOYEE_HPP

