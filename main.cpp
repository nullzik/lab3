#include <iostream>
#include "menuItem.hpp"
#include "product.hpp"
#include "inventory.hpp"
#include "employee.hpp"
#include "manager.hpp"
#include "chef.hpp"
#include "order.hpp"
#include <ctime>
#include <memory>
#include <vector>

int main()
{
	std::cout << "=== Демонстрация работы классов ресторанной системы ===\n" << std::endl;

	// ============================================================
	// 1. СТАТИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ
	// ============================================================
	std::cout << "--- 1. Статическая инициализация объектов ---" << std::endl;
	
	MenuItem staticMenuItem("Борщ", 50.0, 150.0, true);
	Employee staticEmployee("Иванов Иван Иванович", 25, "+7-900-123-45-67",
							"г. Москва, ул. Ленина, д. 1", "Официант",
							500.0, "ivanov", "password123");
	
	std::cout << "Создан статический объект MenuItem: " << staticMenuItem.GetName() << std::endl;
	std::cout << "Создан статический объект Employee: " << staticEmployee.GetFullName() << std::endl;
	
	// Демонстрация работы с std::string: конкатенация и поиск
	std::string employeeInfo = "Сотрудник: ";
	employeeInfo += staticEmployee.GetFullName();  // Конкатенация через оператор +=
	employeeInfo += " (" + staticEmployee.GetPosition() + ")";  // Конкатенация через оператор +
	std::cout << employeeInfo << std::endl;
	
	// Поиск подстроки в строке
	std::string fullName = staticEmployee.GetFullName();
	size_t pos = fullName.find("Иван");  // Поиск подстроки
	if (pos != std::string::npos)
	{
		std::cout << "Найдено имя 'Иван' в позиции: " << pos << std::endl;
	}
	
	// Замена подстроки
	std::string address = staticEmployee.GetAddress();
	std::string newAddress = address;
	size_t replacePos = newAddress.find("Ленина");
	if (replacePos != std::string::npos)
	{
		newAddress.replace(replacePos, 6, "Пушкина");  // Замена подстроки
		std::cout << "Старый адрес: " << address << std::endl;
		std::cout << "Новый адрес: " << newAddress << std::endl;
	}
	
	std::cout << std::endl;

	// ============================================================
	// 2. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ (смарт-указатели)
	// ============================================================
	std::cout << "--- 2. Динамическая инициализация объектов (смарт-указатели) ---" << std::endl;
	
	std::shared_ptr<MenuItem> dynamicMenuItem = std::make_shared<MenuItem>("Салат Цезарь", 80.0, 250.0, true);
	std::shared_ptr<Manager> dynamicManager = std::make_shared<Manager>("Петров Петр Петрович", 35, "+7-900-765-43-21",
										  "г. Москва, ул. Пушкина, д. 10", 1000.0,
										  "manager1", "admin123");
	
	std::cout << "Создан динамический объект MenuItem: " << dynamicMenuItem->GetName() << std::endl;
	std::cout << "Создан динамический объект Manager: " << dynamicManager->GetFullName() << std::endl;
	
	// Используем динамические объекты
	dynamicManager->ChangeSellingPrice(dynamicMenuItem, 280.0);
	std::cout << "Новая цена после изменения: " << dynamicMenuItem->GetSellingPrice() << " руб." << std::endl;
	
	// Память автоматически освобождается смарт-указателями
	std::cout << "Динамические объекты будут автоматически удалены (смарт-указатели)" << std::endl;
	std::cout << std::endl;

	// ============================================================
	// 3. РАБОТА С ССЫЛКАМИ И УКАЗАТЕЛЯМИ
	// ============================================================
	std::cout << "--- 3. Работа со ссылками и указателями ---" << std::endl;
	
	Product product1("Мука", 50.0, "ООО Поставщик", 45.0, std::time(nullptr) + 86400 * 30, std::time(nullptr));
	
	// Работа по ссылке
	Product& productRef = product1;
	productRef.SetWeight(100.0);
	std::cout << "Изменение через ссылку - вес продукта: " << productRef.GetWeight() << " кг" << std::endl;
	
	// Работа по указателю
	Product* productPtr = &product1;
	productPtr->SetPurchasePrice(50.0);
	std::cout << "Изменение через указатель - цена закупки: " << productPtr->GetPurchasePrice() << " руб." << std::endl;
	
	// Демонстрация дружественной функции: сравнение продуктов по цене
	Product product2("Сахар", 100.0, "ООО Поставщик", 60.0, std::time(nullptr) + 86400 * 60, std::time(nullptr));
	if (CompareProductsByPrice(product1, product2))
	{
		std::cout << "Продукт '" << product1.GetName() << "' дешевле продукта '" << product2.GetName() << "'" << std::endl;
	}
	else
	{
		std::cout << "Продукт '" << product2.GetName() << "' дешевле продукта '" << product1.GetName() << "'" << std::endl;
	}
	
	// Демонстрация перегрузки операторов для Product
	std::cout << "Вес продукта до оператора +=: " << product1.GetWeight() << " кг" << std::endl;
	product1 += 25.0;  // Использование оператора +=
	std::cout << "Вес продукта после оператора += 25.0: " << product1.GetWeight() << " кг" << std::endl;
	
	Product product3("Мука", 50.0, "Другой поставщик", 45.0, std::time(nullptr) + 86400 * 30, std::time(nullptr));
	if (product1 == product3)  // Использование оператора ==
	{
		std::cout << "Продукты '" << product1.GetName() << "' и '" << product3.GetName() << "' одинаковые (по имени)" << std::endl;
	}
	
	// Передача смарт-указателя в функции других классов
	std::shared_ptr<Inventory> inventory = std::make_shared<Inventory>("Склад №1");
	Chef chef("Сидоров Сидор Сидорович", 40, "+7-900-555-55-55",
			  "г. Москва, ул. Кулинарная, д. 5", 800.0,
			  "chef1", "cook123");
	
	chef.AddProduct(inventory, product1);
	std::cout << "Продукт добавлен на склад через смарт-указатель" << std::endl;
	std::cout << std::endl;

	// ============================================================
	// 4. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ КЛАССА (вектор смарт-указателей)
	// ============================================================
	std::cout << "--- 4. Динамический массив объектов класса (вектор смарт-указателей) ---" << std::endl;
	
	int menuSize = 3;
	std::vector<std::shared_ptr<MenuItem>> menuArray;
	
	// Инициализация элементов массива
	menuArray.push_back(std::make_shared<MenuItem>("Пицца Маргарита", 150.0, 450.0, true));
	menuArray.push_back(std::make_shared<MenuItem>("Паста Карбонара", 120.0, 380.0, true));
	menuArray.push_back(std::make_shared<MenuItem>("Ризотто", 100.0, 320.0, false));
	
	std::cout << "Создан динамический массив MenuItem (размер: " << menuSize << "):" << std::endl;
	for (size_t i = 0; i < menuArray.size(); ++i)
	{
		if (menuArray[i] != nullptr)
		{
			std::cout << "  " << (i + 1) << ". " << menuArray[i]->GetName() 
					  << " - " << menuArray[i]->GetSellingPrice() << " руб." << std::endl;
		}
	}
	
	// Изменение элементов через индекс
	if (menuArray[2] != nullptr)
	{
		menuArray[2]->SetAvailability(true);
		std::cout << "Доступность блюда 'Ризотто' изменена на: " 
				  << (menuArray[2]->IsAvailable() ? "Доступно" : "Недоступно") << std::endl;
	}
	
	// Демонстрация дружественной функции: расчет общей стоимости меню
	std::vector<MenuItem> menuItemsForCalc;
	menuItemsForCalc.push_back(MenuItem("Пицца Маргарита", 150.0, 450.0, true));
	menuItemsForCalc.push_back(MenuItem("Паста Карбонара", 120.0, 380.0, true));
	menuItemsForCalc.push_back(MenuItem("Ризотто", 100.0, 320.0, true));
	double totalCost = CalculateTotalMenuCost(menuItemsForCalc);
	std::cout << "Общая стоимость меню (дружественная функция): " << totalCost << " руб." << std::endl;
	
	// Демонстрация перегрузки операторов для MenuItem
	MenuItem item1("Борщ", 50.0, 150.0, true);
	MenuItem item2("Салат", 30.0, 100.0, true);
	std::cout << "Продаж блюда до оператора +=: " << item1.GetSalesCount() << std::endl;
	item1 += 5;  // Использование оператора +=
	std::cout << "Продаж блюда после оператора += 5: " << item1.GetSalesCount() << std::endl;
	
	if (item1 < item2)  // Использование оператора <
	{
		std::cout << "Блюдо '" << item1.GetName() << "' дешевле блюда '" << item2.GetName() << "'" << std::endl;
	}
	else if (item1 > item2)  // Использование оператора >
	{
		std::cout << "Блюдо '" << item1.GetName() << "' дороже блюда '" << item2.GetName() << "'" << std::endl;
	}
	
	// Память автоматически освобождается
	std::cout << "Динамический массив будет автоматически удален (смарт-указатели)" << std::endl;
	std::cout << std::endl;

	// ============================================================
	// 5. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ КЛАССА (вектор смарт-указателей)
	// ============================================================
	std::cout << "--- 5. Массив динамических объектов класса (вектор смарт-указателей) ---" << std::endl;
	
	std::vector<std::shared_ptr<Employee>> employeesArray;
	
	// Создание динамических объектов и сохранение смарт-указателей в вектор
	employeesArray.push_back(std::make_shared<Employee>("Кузнецов Кузьма Кузьмич", 28, "+7-900-111-22-33",
									 "г. Москва, ул. Рабочая, д. 20", "Официант",
									 450.0, "waiter1", "pass1"));
	employeesArray.push_back(std::make_shared<Chef>("Поваров Повар Поварович", 32, "+7-900-222-33-44",
								 "г. Москва, ул. Кухонная, д. 15", 750.0,
								 "chef2", "pass2"));
	employeesArray.push_back(std::make_shared<Manager>("Директоров Директор Директорович", 45, "+7-900-333-44-55",
									"г. Москва, ул. Управленческая, д. 1", 1500.0,
									"director", "admin"));
	
	std::cout << "Создан вектор смарт-указателей на динамические объекты Employee (размер: " << employeesArray.size() << "):" << std::endl;
	for (size_t i = 0; i < employeesArray.size(); ++i)
	{
		if (employeesArray[i] != nullptr)
		{
			std::cout << "  " << (i + 1) << ". " << employeesArray[i]->GetFullName() 
					  << " (" << employeesArray[i]->GetPosition() << ")" << std::endl;
		}
	}
	
	// Вызов методов через смарт-указатели
	if (employeesArray[0] != nullptr)
	{
		employeesArray[0]->SetHoursWorked(160.0);
		std::cout << "Отработанные часы первого сотрудника: " 
				  << employeesArray[0]->GetHoursWorked() << std::endl;
		// Демонстрация перегрузки оператора += для Employee
		*employeesArray[0] += 8.0;  // Использование оператора += для добавления часов
		std::cout << "Отработанные часы после оператора += 8.0: " 
				  << employeesArray[0]->GetHoursWorked() << std::endl;
		std::cout << "Зарплата первого сотрудника: " 
				  << employeesArray[0]->CalculateSalary() << " руб." << std::endl;
		
		// Демонстрация перегрузки оператора == для Employee
		if (employeesArray[0] != nullptr && employeesArray[1] != nullptr)
		{
			if (*employeesArray[0] == *employeesArray[1])
			{
				std::cout << "Сотрудники имеют одинаковый логин" << std::endl;
			}
			else
			{
				std::cout << "Сотрудники имеют разные логины" << std::endl;
			}
		}
	}
	
	// Память автоматически освобождается
	std::cout << "Динамические объекты будут автоматически удалены (смарт-указатели)" << std::endl;
	std::cout << std::endl;

	// ============================================================
	// 6. КОМПЛЕКСНАЯ ДЕМОНСТРАЦИЯ ВЗАИМОДЕЙСТВИЯ КЛАССОВ
	// ============================================================
	std::cout << "--- 6. Комплексная демонстрация взаимодействия классов ---" << std::endl;
	
	// Создаем менеджер
	Manager manager("Главный Менеджер", 40, "+7-900-999-99-99",
					"г. Москва, ул. Главная, д. 1", 1200.0,
					"main_manager", "secure_pass");
	
	// Создаем блюда через менеджера и оборачиваем в shared_ptr
	std::shared_ptr<MenuItem> pizza(manager.CreateMenuItem("Пицца Пепперони", 200.0, 550.0, true));
	std::shared_ptr<MenuItem> pasta(manager.CreateMenuItem("Лазанья", 180.0, 480.0, true));
	
	// Создаем сотрудника-официанта с использованием shared_ptr
	std::shared_ptr<Employee> waiter = std::make_shared<Employee>("Официант Тестовый", 22, "+7-900-000-00-00",
									"г. Москва", "Официант",
									400.0, "waiter_test", "test");
	
	// Создаем заказы (используем локальный объект для демонстрации)
	Order order1(waiter);
	order1.AddMenuItem(pizza);
	order1.AddMenuItem(pasta);
	order1.PrintOrder();
	
	// Завершаем заказ (обновляются счетчики продаж)
	order1.CompleteOrder();
	
	// Создаем шеф-повара и работаем со складом
	std::shared_ptr<Chef> chefPtr = std::make_shared<Chef>("Шеф Тестовый", 38, "+7-900-777-77-77",
							 "г. Москва", 900.0,
							 "chef_test", "chef_pass");
	
	// Создаем продукты и добавляем на склад
	std::time_t now = std::time(nullptr);
	Product tomato("Помидоры", 30.0, "Ферма", 80.0, now + 86400 * 7, now);
	Product cheese("Сыр", 20.0, "Молокозавод", 350.0, now + 86400 * 14, now);
	
	chefPtr->AddProduct(inventory, tomato);
	chefPtr->AddProduct(inventory, cheese);
	
	// Шеф-повар списывает продукты
	std::shared_ptr<Product> tomatoOnWarehouse = inventory->FindProduct("Помидоры");
	if (tomatoOnWarehouse != nullptr)
	{
		chefPtr->WriteOffProduct(tomatoOnWarehouse, 5.0, "Приготовление пиццы");
	}
	
	// Шеф-повар добавляет технологическую карту
	MenuItem::TechCardType techCard = {
		{"Ингредиент", "Количество"},
		{"Помидоры", "200г"},
		{"Сыр", "150г"},
		{"Тесто", "300г"}
	};
	chefPtr->AddTechCard(pizza, techCard);
	
	// Менеджер просматривает отчеты
	std::vector<std::shared_ptr<MenuItem>> menuItems = {pizza, pasta};
	manager.ViewSalesReport(menuItems);
	
	// Создаем shared_ptr для order1 (с пустым deleter, так как order1 на стеке)
	std::shared_ptr<Order> order1Ptr(&order1, [](Order*) {});
	std::vector<std::shared_ptr<Order>> orders = {order1Ptr};
	manager.ViewOrdersReport(orders);
	
	// Менеджер управляет сотрудником
	manager.AddBonus(waiter, 1000.0);
	manager.ChangeHourlyRate(waiter, 450.0);
	
	std::cout << "Баланс зарплаты официанта: " << waiter->GetSalaryBalance() << " руб." << std::endl;
	std::cout << "Новая почасовая ставка официанта: " << waiter->GetHourlyRate() << " руб./час" << std::endl;
	
	// Просмотр склада
	chefPtr->ManageInventory(inventory);
	
	// Отчет о списаниях
	chefPtr->PrintShiftWriteOffsReport();
	
	// Память автоматически освобождается смарт-указателями
	
	std::cout << "\n=== Демонстрация завершена ===" << std::endl;
	
	return 0;
}

