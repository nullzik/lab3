#include <iostream>
#include "menuItem.hpp"
#include "product.hpp"
#include "inventory.hpp"
#include "employee.hpp"
#include "manager.hpp"
#include "chef.hpp"
#include "order.hpp"
#include "waiter.hpp"
#include "cashier.hpp"
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
	std::cout << "Текущее количество сотрудников (статическое поле): " 
			  << Employee::GetTotalEmployees() << std::endl;
	
	// Демонстрация использования оператора this для цепочки вызовов методов
	std::cout << "\n--- Демонстрация использования оператора this ---" << std::endl;
	Employee testEmployee("Тестовый Сотрудник", 25, "+7-900-000-00-00",
						 "г. Москва", "Тестировщик", 500.0, "test", "pass");
	// Использование цепочки вызовов благодаря возврату *this
	testEmployee.SetFullNameWithThis("Новое Имя").SetPositionWithThis("Новая Должность");
	std::cout << "После цепочки вызовов: " << testEmployee.GetFullName() 
			  << " (" << testEmployee.GetPosition() << ")" << std::endl;
	std::cout << "Методы SetFullNameWithThis и SetPositionWithThis возвращают *this, "
			  << "что позволяет использовать цепочку вызовов" << std::endl;
	
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
	// 6. КОМПЛЕКСНАЯ ДЕМОНСТРАЦИЯ ВЗАИМОДЕЙСТВИЯ КЛАССОВ + ИСКЛЮЧЕНИЯ
	// ============================================================
	std::cout << "--- 6. Комплексная демонстрация взаимодействия классов ---" << std::endl;
	
	// Создаем менеджер
	// Демонстрация вызова конструктора базового класса из конструктора дочернего класса
	std::cout << "\n--- Демонстрация вызова конструктора базового класса для Manager ---" << std::endl;
	std::cout << "Создание объекта Manager (дочерний класс) вызывает конструктор Employee (базовый класс)" << std::endl;
	Manager manager("Главный Менеджер", 40, "+7-900-999-99-99",
					"г. Москва, ул. Главная, д. 1", 1200.0,
					"main_manager", "secure_pass");
	std::cout << "Manager создан: " << manager.GetFullName() << ", должность: " << manager.GetPosition() << std::endl;
	std::cout << "Должность 'Менеджер' установлена через конструктор базового класса Employee" << std::endl;
	
	// Демонстрация конструктора копирования дочернего класса
	Manager managerCopy(manager);  // Вызывает конструктор копирования Manager, который вызывает конструктор копирования Employee
	std::cout << "Создана копия Manager через конструктор копирования" << std::endl;
	std::cout << "Оригинал: " << manager.GetFullName() << ", Копия: " << managerCopy.GetFullName() << std::endl;
	std::cout << "Оба объекта имеют должность: " << managerCopy.GetPosition() << " (унаследовано от Employee)" << std::endl;
	
	// Создаем блюда через менеджера и оборачиваем в shared_ptr
	std::shared_ptr<MenuItem> pizza(manager.CreateMenuItem("Пицца Пепперони", 200.0, 550.0, true));
	std::shared_ptr<MenuItem> pasta(manager.CreateMenuItem("Лазанья", 180.0, 480.0, true));
	
	// Создаем сотрудника-официанта и кассира как производные классы от Employee
	std::shared_ptr<Waiter> waiter = std::make_shared<Waiter>("Официант Тестовый", 22, "+7-900-000-00-00",
									"г. Москва", 400.0, "waiter_test", "test");
	std::shared_ptr<Cashier> cashier = std::make_shared<Cashier>("Кассир Тестовый", 30, "+7-900-444-44-44",
									"г. Москва", 500.0, "cashier_test", "cash");
	
	// Создаем заказы (используем локальный объект для демонстрации)
	Order order1(waiter);
	order1.AddMenuItem(pizza);
	order1.AddMenuItem(pasta);
	order1.PrintOrder();
	
	// Демонстрация конструктора копирования для Order
	Order orderCopy(order1);
	std::cout << "\n--- Демонстрация конструктора копирования для Order ---" << std::endl;
	std::cout << "Создана копия заказа: ID оригинала = " << order1.GetOrderId() 
			  << ", ID копии = " << orderCopy.GetOrderId() << std::endl;
	std::cout << "Количество блюд в оригинале: " << order1.GetMenuItemsCount() 
			  << ", в копии: " << orderCopy.GetMenuItemsCount() << std::endl;
	
	// Завершаем заказ (обновляются счетчики продаж)
	order1.CompleteOrder();

	// Демонстрация работы новых производных классов: официант и кассир
	std::cout << "\n--- Демонстрация работы производных классов Waiter и Cashier ---" << std::endl;
	waiter->ServeOrder(std::make_shared<Order>(order1));	// официант обслуживает заказ (копия объекта)
	waiter->AddTips(350.0);								// добавляем чаевые

	// Кассир проводит оплату исходного заказа
	std::shared_ptr<Order> order1PtrForCashier(&order1, [](Order*) {});
	cashier->ProcessPayment(order1PtrForCashier);

	// Расчет зарплаты с использованием перегруженных методов в новых производных классах
	waiter->SetHoursWorked(160.0);
	waiter->SetHourlyRate(400.0);
	waiter->SetSalaryBalance(2000.0);
	waiter->AddSales(15); // увеличим продажи для бонуса

	cashier->SetHoursWorked(160.0);
	cashier->SetHourlyRate(500.0);
	cashier->SetSalaryBalance(1500.0);

	std::cout << "\nЗарплата официанта (базовый расчет Employee): "
			  << waiter->Employee::CalculateSalary() << " руб." << std::endl;
	std::cout << "Зарплата официанта (перегруженный Waiter::CalculateSalary, с вызовом базового): "
			  << waiter->CalculateSalary() << " руб." << std::endl;

	std::cout << "\nЗарплата кассира (базовый расчет Employee): "
			  << cashier->Employee::CalculateSalary() << " руб." << std::endl;
	std::cout << "Зарплата кассира (перегруженный Cashier::CalculateSalary, без вызова базового): "
			  << cashier->CalculateSalary() << " руб." << std::endl;
	
	// ============================================================
	// 7. ДЕМОНСТРАЦИЯ РАБОТЫ С ИСКЛЮЧЕНИЯМИ (try, catch, throw)
	// ============================================================
	std::cout << "\n--- 7. Демонстрация работы с исключениями (C++) ---" << std::endl;
	
	// Пример 1: попытка установить отрицательную почасовую ставку
	try
	{
		std::cout << "Пробуем установить отрицательную почасовую ставку для официанта..." << std::endl;
		manager.ChangeHourlyRate(waiter, -100.0);	// Здесь будет брошено std::invalid_argument
	}
	catch (const std::invalid_argument& ex)
	{
		std::cout << "Поймано исключение std::invalid_argument: " << ex.what() << std::endl;
	}
	
	// Пример 2: попытка списать больше продукта, чем есть на складе
	try
	{
		std::cout << "Пробуем списать слишком большое количество продукта..." << std::endl;
		std::shared_ptr<Product> cheeseOnWarehouse = inventory->FindProduct("Сыр");
		if (cheeseOnWarehouse)
		{
			// Пытаемся списать заведомо большое количество, чтобы вызвать исключение
			chefPtr->WriteOffProduct(cheeseOnWarehouse, 1000.0, "Тестовое списание");
		}
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << "Поймано исключение std::runtime_error: " << ex.what() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Поймано другое стандартное исключение: " << ex.what() << std::endl;
	}
	
	// Создаем шеф-повара и работаем со складом
	// Демонстрация вызова конструктора базового класса из конструктора дочернего класса
	std::cout << "\n--- Демонстрация вызова конструктора базового класса из дочернего ---" << std::endl;
	std::cout << "Создание объекта Chef (дочерний класс) вызывает конструктор Employee (базовый класс)" << std::endl;
	std::shared_ptr<Chef> chefPtr = std::make_shared<Chef>("Шеф Тестовый", 38, "+7-900-777-77-77",
							 "г. Москва", 900.0,
							 "chef_test", "chef_pass");
	std::cout << "Chef создан: " << chefPtr->GetFullName() << ", должность: " << chefPtr->GetPosition() << std::endl;
	std::cout << "Должность установлена через конструктор базового класса Employee" << std::endl;
	
	// Демонстрация конструктора копирования дочернего класса
	Chef chefOriginal("Оригинальный Шеф", 35, "+7-900-111-11-11",
					  "г. Москва", 850.0, "chef_orig", "pass_orig");
	Chef chefCopy(chefOriginal);  // Вызывает конструктор копирования Chef, который вызывает конструктор копирования Employee
	std::cout << "Создана копия Chef через конструктор копирования" << std::endl;
	std::cout << "Оригинал: " << chefOriginal.GetFullName() << ", Копия: " << chefCopy.GetFullName() << std::endl;
	std::cout << "Оба объекта имеют должность: " << chefCopy.GetPosition() << " (унаследовано от Employee)" << std::endl;
	
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
	
	// ============================================================
	// 8. ДЕМОНСТРАЦИЯ ВИРТУАЛЬНЫХ ФУНКЦИЙ И ПОЛИМОРФИЗМА
	// ============================================================
	std::cout << "\n--- 8. Демонстрация виртуальных функций и полиморфизма ---" << std::endl;
	
	// Подготовка данных для демонстрации
	waiter->SetHoursWorked(160.0);
	waiter->SetHourlyRate(400.0);
	waiter->SetSalaryBalance(2000.0);
	waiter->AddSales(15);
	
	cashier->SetHoursWorked(160.0);
	cashier->SetHourlyRate(500.0);
	cashier->SetSalaryBalance(1500.0);
	cashier->ProcessPayment(order1PtrForCashier);  // Увеличим выручку кассира
	
	chefPtr->SetHoursWorked(160.0);
	chefPtr->SetHourlyRate(900.0);
	chefPtr->SetSalaryBalance(3000.0);
	chefPtr->AddSales(10);
	
	manager.SetHoursWorked(160.0);
	manager.SetHourlyRate(1200.0);
	manager.SetSalaryBalance(5000.0);
	
	// Демонстрация 1: Вызов виртуальной функции через невиртуальную функцию базового класса
	std::cout << "\n--- Демонстрация 1: Вызов виртуальной функции через невиртуальную функцию ---" << std::endl;
	std::cout << "Метод PrintSalaryInfo() (невиртуальный) вызывает виртуальный CalculateSalary():" << std::endl;
	std::cout << std::endl;
	
	waiter->PrintSalaryInfo();   // Вызовет Waiter::CalculateSalary()
	cashier->PrintSalaryInfo();  // Вызовет Cashier::CalculateSalary()
	chefPtr->PrintSalaryInfo();  // Вызовет Chef::CalculateSalary()
	manager.PrintSalaryInfo();   // Вызовет Manager::CalculateSalary()
	
	// Демонстрация 2: Вызов виртуальной функции через указатель базового класса (полиморфизм)
	std::cout << "\n--- Демонстрация 2: Полиморфизм через указатель базового класса ---" << std::endl;
	std::cout << "Создаем указатели Employee* на объекты разных производных классов:" << std::endl;
	std::cout << std::endl;
	
	Employee* empPtr1 = waiter.get();   // Указатель на Waiter
	Employee* empPtr2 = cashier.get();  // Указатель на Cashier
	Employee* empPtr3 = chefPtr.get();  // Указатель на Chef
	Employee* empPtr4 = &manager;        // Указатель на Manager
	
	std::cout << "Вызов CalculateSalary() через указатель Employee*:" << std::endl;
	std::cout << "empPtr1 (Waiter):   " << empPtr1->CalculateSalary() << " руб." << std::endl;
	std::cout << "empPtr2 (Cashier): " << empPtr2->CalculateSalary() << " руб." << std::endl;
	std::cout << "empPtr3 (Chef):    " << empPtr3->CalculateSalary() << " руб." << std::endl;
	std::cout << "empPtr4 (Manager): " << empPtr4->CalculateSalary() << " руб." << std::endl;
	std::cout << std::endl;
	std::cout << "Благодаря виртуальности, вызывается правильная версия для каждого типа!" << std::endl;
	
	// Демонстрация 3: Что было бы, если функция НЕ виртуальная
	std::cout << "\n--- Демонстрация 3: Разница с невиртуальной функцией ---" << std::endl;
	std::cout << "Если бы CalculateSalary() НЕ была виртуальной, то через указатель Employee*" << std::endl;
	std::cout << "всегда вызывалась бы базовая версия Employee::CalculateSalary():" << std::endl;
	std::cout << std::endl;
	
	// Показываем базовый расчет для сравнения
	std::cout << "Базовый расчет Employee::CalculateSalary() (если бы не было virtual):" << std::endl;
	std::cout << "empPtr1 (Waiter):   " << empPtr1->Employee::CalculateSalary() << " руб. (базовая версия)" << std::endl;
	std::cout << "empPtr2 (Cashier): " << empPtr2->Employee::CalculateSalary() << " руб. (базовая версия)" << std::endl;
	std::cout << "empPtr3 (Chef):    " << empPtr3->Employee::CalculateSalary() << " руб. (базовая версия)" << std::endl;
	std::cout << "empPtr4 (Manager): " << empPtr4->Employee::CalculateSalary() << " руб. (базовая версия)" << std::endl;
	std::cout << std::endl;
	std::cout << "Как видно, все получают одинаковый базовый расчет, без учета специфики должности!" << std::endl;
	std::cout << "Виртуальные функции решают эту проблему - вызывается правильная версия." << std::endl;
	
	// Демонстрация 4: Массив указателей на базовый класс (типичный случай использования полиморфизма)
	std::cout << "\n--- Демонстрация 4: Массив указателей на базовый класс ---" << std::endl;
	std::vector<Employee*> employees = {empPtr1, empPtr2, empPtr3, empPtr4};
	
	std::cout << "Обработка массива сотрудников через указатели Employee*:" << std::endl;
	double totalSalary = 0.0;
	for (size_t i = 0; i < employees.size(); ++i)
	{
		double salary = employees[i]->CalculateSalary();  // Виртуальный вызов
		totalSalary += salary;
		std::cout << "  Сотрудник #" << (i + 1) << ": " << salary << " руб." << std::endl;
	}
	std::cout << "Общая сумма зарплат: " << totalSalary << " руб." << std::endl;
	std::cout << "Каждый сотрудник получает зарплату по своей формуле благодаря виртуальным функциям!" << std::endl;
	
	// Память автоматически освобождается смарт-указателями
	
	std::cout << "\n=== Демонстрация завершена ===" << std::endl;
	
	return 0;
}

