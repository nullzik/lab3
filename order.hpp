#ifndef ORDER_HPP
#define ORDER_HPP

#include "menuItem.hpp"
#include "employee.hpp"
#include <vector>
#include <ctime>

// Класс заказа
// Связывает блюда из меню с сотрудником, который создал заказ
class Order
{
public:
	using MenuItemsType = std::vector<MenuItem*>;

private:
	static int s_nextOrderId;		// Статическая переменная для генерации уникальных ID заказов
	int m_orderId;					// ID заказа
	MenuItemsType m_menuItems;		// Блюда в заказе
	double m_totalAmount;			// Сумма заказа
	std::time_t m_orderTime;		// Время создания заказа
	Employee* m_employee;			// Сотрудник, добавивший заказ

public:
	// Конструкторы и деструктор
	Order();
	Order(Employee* employee);
	~Order() = default;

	// Публичные методы
	bool AddMenuItem(MenuItem* menuItem);			// Добавить блюдо в заказ
	bool RemoveMenuItem(const std::string& menuItemName);	// Удалить блюдо из заказа
	double CalculateTotalAmount();					// Рассчитать сумму заказа
	void PrintOrder() const;						// Вывести информацию о заказе
	
	// Метод для завершения заказа (обновляет счетчики продаж)
	void CompleteOrder();

	// Геттеры
	int GetOrderId() const;
	MenuItemsType GetMenuItems() const;
	double GetTotalAmount() const;
	std::time_t GetOrderTime() const;
	Employee* GetEmployee() const;
	int GetMenuItemsCount() const;

	// Сеттеры
	void SetEmployee(Employee* employee);
};

#endif // ORDER_HPP

