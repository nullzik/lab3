import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== Демонстрация работы классов ресторанной системы ===\n");

        // ============================================================
        // 1. СТАТИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ
        // ============================================================
        System.out.println("--- 1. Статическая инициализация объектов ---");
        
        MenuItem staticMenuItem = new MenuItem("Борщ", 50.0, 150.0, true);
        Employee staticEmployee = new Employee("Иванов Иван Иванович", 25, "+7-900-123-45-67",
                                              "г. Москва, ул. Ленина, д. 1", "Официант",
                                              500.0, "ivanov", "password123");
        
        System.out.println("Создан статический объект MenuItem: " + staticMenuItem.getName());
        System.out.println("Создан статический объект Employee: " + staticEmployee.getFullName());
        System.out.println("Текущее количество сотрудников (статическое поле): " 
                           + Employee.getTotalEmployees());
        System.out.println();

        // ============================================================
        // 2. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ (new)
        // ============================================================
        System.out.println("--- 2. Динамическая инициализация объектов (new) ---");
        
        MenuItem dynamicMenuItem = new MenuItem("Салат Цезарь", 80.0, 250.0, true);
        Manager dynamicManager = new Manager("Петров Петр Петрович", 35, "+7-900-765-43-21",
                                            "г. Москва, ул. Пушкина, д. 10", 1000.0,
                                            "manager1", "admin123");
        
        System.out.println("Создан динамический объект MenuItem: " + dynamicMenuItem.getName());
        System.out.println("Создан динамический объект Manager: " + dynamicManager.getFullName());
        
        // Используем динамические объекты
        dynamicManager.changeSellingPrice(dynamicMenuItem, 280.0);
        System.out.println("Новая цена после изменения: " + dynamicMenuItem.getSellingPrice() + " руб.");
        
        // В Java сборщик мусора автоматически освобождает память
        System.out.println("Объекты будут автоматически удалены сборщиком мусора");
        System.out.println();

        // ============================================================
        // 3. РАБОТА СО ССЫЛКАМИ (в Java все объекты передаются по ссылке)
        // ============================================================
        System.out.println("--- 3. Работа со ссылками ---");
        
        long now = System.currentTimeMillis();
        Product product1 = new Product("Мука", 50.0, "ООО Поставщик", 45.0, 
                                      now + 86400000L * 30, now);
        
        // Работа по ссылке (в Java все объекты - ссылки)
        Product productRef = product1;
        productRef.setWeight(100.0);
        System.out.println("Изменение через ссылку - вес продукта: " + productRef.getWeight() + " кг");
        
        // Работа через другую ссылку
        Product productPtr = product1;
        productPtr.setPurchasePrice(50.0);
        System.out.println("Изменение через ссылку - цена закупки: " + productPtr.getPurchasePrice() + " руб.");
        
        // Передача ссылки в функции других классов
        Inventory inventory = new Inventory("Склад №1");
        Chef chef = new Chef("Сидоров Сидор Сидорович", 40, "+7-900-555-55-55",
                            "г. Москва, ул. Кулинарная, д. 5", 800.0,
                            "chef1", "cook123");
        
        chef.addProduct(inventory, product1);
        System.out.println("Продукт добавлен на склад через ссылку");
        System.out.println();

        // ============================================================
        // 4. МАССИВ ОБЪЕКТОВ КЛАССА
        // ============================================================
        System.out.println("--- 4. Массив объектов класса ---");
        
        int menuSize = 3;
        MenuItem[] menuArray = new MenuItem[menuSize];
        
        // Инициализация элементов массива
        menuArray[0] = new MenuItem("Пицца Маргарита", 150.0, 450.0, true);
        menuArray[1] = new MenuItem("Паста Карбонара", 120.0, 380.0, true);
        menuArray[2] = new MenuItem("Ризотто", 100.0, 320.0, false);
        
        System.out.println("Создан массив MenuItem (размер: " + menuSize + "):");
        for (int i = 0; i < menuSize; i++) {
            System.out.println("  " + (i + 1) + ". " + menuArray[i].getName() + 
                            " - " + menuArray[i].getSellingPrice() + " руб.");
        }
        
        // Изменение элементов через индекс
        menuArray[2].setAvailability(true);
        System.out.println("Доступность блюда 'Ризотто' изменена на: " + 
                         (menuArray[2].isAvailable() ? "Доступно" : "Недоступно"));
        System.out.println();

        // ============================================================
        // 5. МАССИВ ССЫЛОК НА ДИНАМИЧЕСКИЕ ОБЪЕКТЫ КЛАССА
        // ============================================================
        System.out.println("--- 5. Массив ссылок на динамические объекты класса ---");
        
        int employeesCount = 3;
        Employee[] employeesArray = new Employee[employeesCount];
        
        // Создание динамических объектов и сохранение ссылок в массив
        employeesArray[0] = new Employee("Кузнецов Кузьма Кузьмич", 28, "+7-900-111-22-33",
                                         "г. Москва, ул. Рабочая, д. 20", "Официант",
                                         450.0, "waiter1", "pass1");
        employeesArray[1] = new Chef("Поваров Повар Поварович", 32, "+7-900-222-33-44",
                                    "г. Москва, ул. Кухонная, д. 15", 750.0,
                                    "chef2", "pass2");
        employeesArray[2] = new Manager("Директоров Директор Директорович", 45, "+7-900-333-44-55",
                                       "г. Москва, ул. Управленческая, д. 1", 1500.0,
                                       "director", "admin");
        
        System.out.println("Создан массив ссылок на динамические объекты Employee (размер: " + employeesCount + "):");
        for (int i = 0; i < employeesCount; i++) {
            System.out.println("  " + (i + 1) + ". " + employeesArray[i].getFullName() + 
                            " (" + employeesArray[i].getPosition() + ")");
        }
        
        // Вызов методов через ссылки
        employeesArray[0].setHoursWorked(160.0);
        System.out.println("Отработанные часы первого сотрудника: " + 
                         employeesArray[0].getHoursWorked());
        System.out.println("Зарплата первого сотрудника: " + 
                         employeesArray[0].calculateSalary() + " руб.");

        // Демонстрация использования this через цепочку вызовов (фактически через методы, возвращающие this)
        System.out.println("\n--- Демонстрация использования this (Java) ---");
        Employee testEmployee = new Employee(staticEmployee); // копирующий конструктор
        // Имитация fluent-интерфейса: методы set* возвращали бы this (здесь просто демонстрация this в сеттерах)
        testEmployee.setFullName("Тестовый ФИО");
        testEmployee.setPosition("Тестовая должность");
        System.out.println("Сотрудник после изменения с использованием this в сеттерах: "
                           + testEmployee.getFullName() + " (" + testEmployee.getPosition() + ")");
        System.out.println();

        // ============================================================
        // 6. КОМПЛЕКСНАЯ ДЕМОНСТРАЦИЯ ВЗАИМОДЕЙСТВИЯ КЛАССОВ
        // ============================================================
        System.out.println("--- 6. Комплексная демонстрация взаимодействия классов ---");
        
        // Создаем менеджер
        Manager manager = new Manager("Главный Менеджер", 40, "+7-900-999-99-99",
                                     "г. Москва, ул. Главная, д. 1", 1200.0,
                                     "main_manager", "secure_pass");
        
        // Создаем блюда через менеджера
        MenuItem pizza = manager.createMenuItem("Пицца Пепперони", 200.0, 550.0, true);
        MenuItem pasta = manager.createMenuItem("Лазанья", 180.0, 480.0, true);
        
        // Создаем сотрудника-официанта
        Employee waiter = new Employee("Официант Тестовый", 22, "+7-900-000-00-00",
                                      "г. Москва", "Официант",
                                      400.0, "waiter_test", "test");
        
        // Создаем заказы
        Order order1 = new Order(waiter);
        order1.addMenuItem(pizza);
        order1.addMenuItem(pasta);
        order1.printOrder();
        
        // Завершаем заказ (обновляются счетчики продаж)
        order1.completeOrder();

        // ============================================================
        // 7. ДЕМОНСТРАЦИЯ РАБОТЫ С ИСКЛЮЧЕНИЯМИ (try, catch, throw) В JAVA
        // ============================================================
        System.out.println("\n--- 7. Демонстрация работы с исключениями (Java) ---");

        // Пример 1: попытка установить отрицательную почасовую ставку
        try {
            System.out.println("Пробуем установить отрицательную почасовую ставку для официанта...");
            manager.changeHourlyRate(waiter, -100.0); // Здесь будет брошен IllegalArgumentException
        } catch (IllegalArgumentException ex) {
            System.out.println("Поймано исключение IllegalArgumentException: " + ex.getMessage());
        }

        // Пример 2: попытка списать больше продукта, чем есть на складе
        try {
            System.out.println("Пробуем списать слишком большое количество продукта...");
            Product cheeseOnWarehouse = inventory.findProduct("Сыр");
            if (cheeseOnWarehouse != null) {
                chefPtr.writeOffProduct(cheeseOnWarehouse, 1000.0, "Тестовое списание");
            }
        } catch (RuntimeException ex) {
            System.out.println("Поймано исключение RuntimeException: " + ex.getMessage());
        } catch (Exception ex) {
            System.out.println("Поймано другое исключение: " + ex.getMessage());
        }
        
        // Создаем шеф-повара и работаем со складом
        Chef chefPtr = new Chef("Шеф Тестовый", 38, "+7-900-777-77-77",
                               "г. Москва", 900.0,
                               "chef_test", "chef_pass");
        
        // Создаем продукты и добавляем на склад
        long currentTime = System.currentTimeMillis();
        Product tomato = new Product("Помидоры", 30.0, "Ферма", 80.0, 
                                    currentTime + 86400000L * 7, currentTime);
        Product cheese = new Product("Сыр", 20.0, "Молокозавод", 350.0, 
                                    currentTime + 86400000L * 14, currentTime);
        
        chefPtr.addProduct(inventory, tomato);
        chefPtr.addProduct(inventory, cheese);
        
        // Шеф-повар списывает продукты
        Product tomatoOnWarehouse = inventory.findProduct("Помидоры");
        if (tomatoOnWarehouse != null) {
            chefPtr.writeOffProduct(tomatoOnWarehouse, 5.0, "Приготовление пиццы");
        }
        
        // Шеф-повар добавляет технологическую карту
        MenuItem.TechCardType techCard = new MenuItem.TechCardType();
        List<String> header = Arrays.asList("Ингредиент", "Количество");
        List<String> row1 = Arrays.asList("Помидоры", "200г");
        List<String> row2 = Arrays.asList("Сыр", "150г");
        List<String> row3 = Arrays.asList("Тесто", "300г");
        techCard.add(header);
        techCard.add(row1);
        techCard.add(row2);
        techCard.add(row3);
        chefPtr.addTechCard(pizza, techCard);
        
        // Менеджер просматривает отчеты
        Manager.MenuItemsType menuItems = new Manager.MenuItemsType();
        menuItems.add(pizza);
        menuItems.add(pasta);
        manager.viewSalesReport(menuItems);
        
        Manager.OrdersType orders = new Manager.OrdersType();
        orders.add(order1);
        manager.viewOrdersReport(orders);
        
        // Менеджер управляет сотрудником
        manager.addBonus(waiter, 1000.0);
        manager.changeHourlyRate(waiter, 450.0);
        
        System.out.println("Баланс зарплаты официанта: " + waiter.getSalaryBalance() + " руб.");
        System.out.println("Новая почасовая ставка официанта: " + waiter.getHourlyRate() + " руб./час");
        
        // Просмотр склада
        chefPtr.manageInventory(inventory);
        
        // Отчет о списаниях
        chefPtr.printShiftWriteOffsReport();
        
        System.out.println("\n=== Демонстрация завершена ===");
    }
}
