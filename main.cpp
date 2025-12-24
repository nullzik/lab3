#include <iostream>
#include "menuItem.hpp"
#include "product.hpp"
#include "inventory.hpp"
#include "employee.hpp"
#include "manager.hpp"
#include "chef.hpp"
#include "order.hpp"
#include <ctime>

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
	std::cout << std::endl;

	// ============================================================
	// 2. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ (new, delete)
	// ============================================================
	std::cout << "--- 2. Динамическая инициализация объектов (new, delete) ---" << std::endl;
	
	MenuItem* dynamicMenuItem = new MenuItem("Салат Цезарь", 80.0, 250.0, true);
	Manager* dynamicManager = new Manager("Петров Петр Петрович", 35, "+7-900-765-43-21",
										  "г. Москва, ул. Пушкина, д. 10", 1000.0,
										  "manager1", "admin123");
	
	std::cout << "Создан динамический объект MenuItem: " << dynamicMenuItem->GetName() << std::endl;
	std::cout << "Создан динамический объект Manager: " << dynamicManager->GetFullName() << std::endl;
	
	// Используем динамические объекты
	dynamicManager->ChangeSellingPrice(dynamicMenuItem, 280.0);
	std::cout << "Новая цена после изменения: " << dynamicMenuItem->GetSellingPrice() << " руб." << std::endl;
	
	// Освобождаем память
	delete dynamicMenuItem;
	delete dynamicManager;
	std::cout << "Динамические объекты удалены (delete)" << std::endl;
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
	
	// Передача указателя в функции других классов
	Inventory inventory("Склад №1");
	Chef chef("Сидоров Сидор Сидорович", 40, "+7-900-555-55-55",
			  "г. Москва, ул. Кулинарная, д. 5", 800.0,
			  "chef1", "cook123");
	
	chef.AddProduct(&inventory, product1);
	std::cout << "Продукт добавлен на склад через указатель" << std::endl;
	std::cout << std::endl;

	// ============================================================
	// 4. ДИНАМИЧЕСКИЙ МАССИВ ОБЪЕКТОВ КЛАССА
	// ============================================================
	std::cout << "--- 4. Динамический массив объектов класса ---" << std::endl;
	
	int menuSize = 3;
	MenuItem* menuArray = new MenuItem[menuSize];
	
	// Инициализация элементов массива
	menuArray[0] = MenuItem("Пицца Маргарита", 150.0, 450.0, true);
	menuArray[1] = MenuItem("Паста Карбонара", 120.0, 380.0, true);
	menuArray[2] = MenuItem("Ризотто", 100.0, 320.0, false);
	
	std::cout << "Создан динамический массив MenuItem (размер: " << menuSize << "):" << std::endl;
	for (int i = 0; i < menuSize; ++i)
	{
		std::cout << "  " << (i + 1) << ". " << menuArray[i].GetName() 
				  << " - " << menuArray[i].GetSellingPrice() << " руб." << std::endl;
	}
	
	// Изменение элементов через индекс
	menuArray[2].SetAvailability(true);
	std::cout << "Доступность блюда 'Ризотто' изменена на: " 
			  << (menuArray[2].IsAvailable() ? "Доступно" : "Недоступно") << std::endl;
	
	delete[] menuArray;
	std::cout << "Динамический массив удален (delete[])" << std::endl;
	std::cout << std::endl;

	// ============================================================
	// 5. МАССИВ ДИНАМИЧЕСКИХ ОБЪЕКТОВ КЛАССА
	// ============================================================
	std::cout << "--- 5. Массив динамических объектов класса ---" << std::endl;
	
	int employeesCount = 3;
	Employee** employeesArray = new Employee*[employeesCount];
	
	// Создание динамических объектов и сохранение указателей в массив
	employeesArray[0] = new Employee("Кузнецов Кузьма Кузьмич", 28, "+7-900-111-22-33",
									 "г. Москва, ул. Рабочая, д. 20", "Официант",
									 450.0, "waiter1", "pass1");
	employeesArray[1] = new Chef("Поваров Повар Поварович", 32, "+7-900-222-33-44",
								 "г. Москва, ул. Кухонная, д. 15", 750.0,
								 "chef2", "pass2");
	employeesArray[2] = new Manager("Директоров Директор Директорович", 45, "+7-900-333-44-55",
									"г. Москва, ул. Управленческая, д. 1", 1500.0,
									"director", "admin");
	
	std::cout << "Создан массив указателей на динамические объекты Employee (размер: " << employeesCount << "):" << std::endl;
	for (int i = 0; i < employeesCount; ++i)
	{
		std::cout << "  " << (i + 1) << ". " << employeesArray[i]->GetFullName() 
				  << " (" << employeesArray[i]->GetPosition() << ")" << std::endl;
	}
	
	// Вызов методов через указатели
	employeesArray[0]->SetHoursWorked(160.0);
	std::cout << "Отработанные часы первого сотрудника: " 
			  << employeesArray[0]->GetHoursWorked() << std::endl;
	std::cout << "Зарплата первого сотрудника: " 
			  << employeesArray[0]->CalculateSalary() << " руб." << std::endl;
	
	// Удаление динамических объектов и массива указателей
	for (int i = 0; i < employeesCount; ++i)
	{
		delete employeesArray[i];
	}
	delete[] employeesArray;
	std::cout << "Динамические объекты и массив указателей удалены" << std::endl;
	std::cout << std::endl;

	// ============================================================
	// 6. КОМПЛЕКСНАЯ ДЕМОНСТРАЦИЯ ВЗАИМОДЕЙСТВИЯ КЛАССОВ
	// ============================================================
	std::cout << "--- 6. Комплексная демонстрация взаимодействия классов ---" << std::endl;
	
	// Создаем менеджер
	Manager manager("Главный Менеджер", 40, "+7-900-999-99-99",
					"г. Москва, ул. Главная, д. 1", 1200.0,
					"main_manager", "secure_pass");
	
	// Создаем блюда через менеджера
	MenuItem* pizza = manager.CreateMenuItem("Пицца Пепперони", 200.0, 550.0, true);
	MenuItem* pasta = manager.CreateMenuItem("Лазанья", 180.0, 480.0, true);
	
	// Создаем сотрудника-официанта
	Employee* waiter = new Employee("Официант Тестовый", 22, "+7-900-000-00-00",
									"г. Москва", "Официант",
									400.0, "waiter_test", "test");
	
	// Создаем заказы
	Order order1(waiter);
	order1.AddMenuItem(pizza);
	order1.AddMenuItem(pasta);
	order1.PrintOrder();
	
	// Завершаем заказ (обновляются счетчики продаж)
	order1.CompleteOrder();
	
	// Создаем шеф-повара и работаем со складом
	Chef* chefPtr = new Chef("Шеф Тестовый", 38, "+7-900-777-77-77",
							 "г. Москва", 900.0,
							 "chef_test", "chef_pass");
	
	// Создаем продукты и добавляем на склад
	std::time_t now = std::time(nullptr);
	Product tomato("Помидоры", 30.0, "Ферма", 80.0, now + 86400 * 7, now);
	Product cheese("Сыр", 20.0, "Молокозавод", 350.0, now + 86400 * 14, now);
	
	chefPtr->AddProduct(&inventory, tomato);
	chefPtr->AddProduct(&inventory, cheese);
	
	// Шеф-повар списывает продукты
	Product* tomatoOnWarehouse = inventory.FindProduct("Помидоры");
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
	std::vector<MenuItem*> menuItems = {pizza, pasta};
	manager.ViewSalesReport(menuItems);
	
	std::vector<Order*> orders = {&order1};
	manager.ViewOrdersReport(orders);
	
	// Менеджер управляет сотрудником
	manager.AddBonus(waiter, 1000.0);
	manager.ChangeHourlyRate(waiter, 450.0);
	
	std::cout << "Баланс зарплаты официанта: " << waiter->GetSalaryBalance() << " руб." << std::endl;
	std::cout << "Новая почасовая ставка официанта: " << waiter->GetHourlyRate() << " руб./час" << std::endl;
	
	// Просмотр склада
	chefPtr->ManageInventory(&inventory);
	
	// Отчет о списаниях
	chefPtr->PrintShiftWriteOffsReport();
	
	// Освобождение памяти
	delete waiter;
	delete chefPtr;
	delete pizza;
	delete pasta;
	
	std::cout << "\n=== Демонстрация завершена ===" << std::endl;
	
	return 0;
}

