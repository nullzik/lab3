#ifndef ORDER_HPP
#define ORDER_HPP

#include "menuItem.hpp"
#include "employee.hpp"
#include <vector>
#include <ctime>
#include <memory>

// Класс заказа
// Связывает блюда из меню с сотрудником, который создал заказ
class Order
{
public:
	using MenuItemsType = std::vector<std::shared_ptr<MenuItem>>;

private:
	static int s_nextOrderId;		// Статическая переменная для генерации уникальных ID заказов
	int m_orderId;					// ID заказа
	MenuItemsType m_menuItems;		// Блюда в заказе
	double m_totalAmount;			// Сумма заказа
	std::time_t m_orderTime;		// Время создания заказа
	std::shared_ptr<Employee> m_employee;			// Сотрудник, добавивший заказ

public:
	// Конструкторы и деструктор
	Order();
	Order(std::shared_ptr<Employee> employee);
	Order(const Order& other);		// Конструктор копирования
	~Order() = default;

	// Публичные методы
	bool AddMenuItem(std::shared_ptr<MenuItem> menuItem);			// Добавить блюдо в заказ
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
	std::shared_ptr<Employee> GetEmployee() const;
	int GetMenuItemsCount() const;
	// Клонирование
	std::shared_ptr<Order> CloneShallow() const;	// Поверхностное копирование (shared_ptr разделяют объекты меню)
	std::shared_ptr<Order> CloneDeep() const;		// Глубокое копирование (новые объекты MenuItem)

	// Сеттеры
	void SetEmployee(std::shared_ptr<Employee> employee);

	// Перегрузка операторов
	Order& operator+=(std::shared_ptr<MenuItem> menuItem);	// Оператор += для добавления блюда в заказ
};

#endif // ORDER_HPP

