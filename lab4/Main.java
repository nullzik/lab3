import java.util.Date;
import java.util.ArrayList;
import java.util.List;
import java.util.Calendar;

/**
 * Главный класс для демонстрации работы классов ресторанной системы
 */
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
        System.out.println();

        // ============================================================
        // 2. ДИНАМИЧЕСКАЯ ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ
        // ============================================================
        System.out.println("--- 2. Динамическая инициализация объектов ---");
        
        MenuItem dynamicMenuItem = new MenuItem("Салат Цезарь", 80.0, 250.0, true);
        Manager dynamicManager = new Manager("Петров Петр Петрович", 35, "+7-900-765-43-21",
                                              "г. Москва, ул. Пушкина, д. 10", 1000.0,
                                              "manager1", "admin123");
        
        System.out.println("Создан динамический объект MenuItem: " + dynamicMenuItem.getName());
        System.out.println("Создан динамический объект Manager: " + dynamicManager.getFullName());
        
        // Используем динамические объекты
        dynamicManager.changeSellingPrice(dynamicMenuItem, 280.0);
        System.out.println("Новая цена после изменения: " + dynamicMenuItem.getSellingPrice() + " руб.");
        System.out.println();

        // ============================================================
        // 3. РАБОТА С ССЫЛКАМИ И ОБЪЕКТАМИ
        // ============================================================
        System.out.println("--- 3. Работа со ссылками и объектами ---");
        
        Calendar cal = Calendar.getInstance();
        Date now = cal.getTime();
        cal.add(Calendar.DAY_OF_MONTH, 30);
        Date expiryDate = cal.getTime();
        
        Product product1 = new Product("Мука", 50.0, "ООО Поставщик", 45.0, expiryDate, now);
        
        // Работа по ссылке (в Java все объекты передаются по ссылке)
        Product productRef = product1;
        productRef.setWeight(100.0);
        System.out.println("Изменение через ссылку - вес продукта: " + productRef.getWeight() + " кг");
        
        // Работа с объектом
        product1.setPurchasePrice(50.0);
        System.out.println("Изменение через объект - цена закупки: " + product1.getPurchasePrice() + " руб.");
        
        // Передача объекта в методы других классов
        Inventory inventory = new Inventory("Склад №1");
        Chef chef = new Chef("Сидоров Сидор Сидорович", 40, "+7-900-555-55-55",
                             "г. Москва, ул. Кулинарная, д. 5", 800.0,
                             "chef1", "cook123");
        
        chef.addProduct(inventory, product1);
        System.out.println("Продукт добавлен на склад");
        System.out.println();

        // ============================================================
        // 4. МАССИВ ОБЪЕКТОВ КЛАССА
        // ============================================================
        System.out.println("--- 4. Массив объектов класса ---");
        
        MenuItem[] menuArray = new MenuItem[3];
        
        // Инициализация элементов массива
        menuArray[0] = new MenuItem("Пицца Маргарита", 150.0, 450.0, true);
        menuArray[1] = new MenuItem("Паста Карбонара", 120.0, 380.0, true);
        menuArray[2] = new MenuItem("Ризотто", 100.0, 320.0, false);
        
        System.out.println("Создан массив MenuItem (размер: " + menuArray.length + "):");
        for (int i = 0; i < menuArray.length; i++) {
            System.out.println("  " + (i + 1) + ". " + menuArray[i].getName() 
                             + " - " + menuArray[i].getSellingPrice() + " руб.");
        }
        
        // Изменение элементов через индекс
        menuArray[2].setAvailability(true);
        System.out.println("Доступность блюда 'Ризотто' изменена на: " 
                         + (menuArray[2].isAvailable() ? "Доступно" : "Недоступно"));
        System.out.println();

        // ============================================================
        // 5. СПИСОК ДИНАМИЧЕСКИХ ОБЪЕКТОВ КЛАССА
        // ============================================================
        System.out.println("--- 5. Список динамических объектов класса ---");
        
        List<Employee> employeesList = new ArrayList<>();
        
        // Создание объектов и добавление в список
        employeesList.add(new Employee("Кузнецов Кузьма Кузьмич", 28, "+7-900-111-22-33",
                                       "г. Москва, ул. Рабочая, д. 20", "Официант",
                                       450.0, "waiter1", "pass1"));
        employeesList.add(new Chef("Поваров Повар Поварович", 32, "+7-900-222-33-44",
                                   "г. Москва, ул. Кухонная, д. 15", 750.0,
                                   "chef2", "pass2"));
        employeesList.add(new Manager("Директоров Директор Директорович", 45, "+7-900-333-44-55",
                                      "г. Москва, ул. Управленческая, д. 1", 1500.0,
                                      "director", "admin"));
        
        System.out.println("Создан список объектов Employee (размер: " + employeesList.size() + "):");
        for (int i = 0; i < employeesList.size(); i++) {
            Employee emp = employeesList.get(i);
            System.out.println("  " + (i + 1) + ". " + emp.getFullName() 
                             + " (" + emp.getPosition() + ")");
        }
        
        // Вызов методов через ссылки
        Employee firstEmployee = employeesList.get(0);
        firstEmployee.setHoursWorked(160.0);
        System.out.println("Отработанные часы первого сотрудника: " 
                         + firstEmployee.getHoursWorked());
        System.out.println("Зарплата первого сотрудника: " 
                         + firstEmployee.calculateSalary() + " руб.");
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
        
        // Создаем шеф-повара и работаем со складом
        Chef chefPtr = new Chef("Шеф Тестовый", 38, "+7-900-777-77-77",
                                 "г. Москва", 900.0,
                                 "chef_test", "chef_pass");
        
        // Создаем продукты и добавляем на склад
        Calendar cal2 = Calendar.getInstance();
        Date now2 = cal2.getTime();
        cal2.add(Calendar.DAY_OF_MONTH, 7);
        Date expiryDate2 = cal2.getTime();
        cal2.add(Calendar.DAY_OF_MONTH, -7);
        cal2.add(Calendar.DAY_OF_MONTH, 14);
        Date expiryDate3 = cal2.getTime();
        
        Product tomato = new Product("Помидоры", 30.0, "Ферма", 80.0, expiryDate2, now2);
        Product cheese = new Product("Сыр", 20.0, "Молокозавод", 350.0, expiryDate3, now2);
        
        chefPtr.addProduct(inventory, tomato);
        chefPtr.addProduct(inventory, cheese);
        
        // Шеф-повар списывает продукты
        Product tomatoOnWarehouse = inventory.findProduct("Помидоры");
        if (tomatoOnWarehouse != null) {
            chefPtr.writeOffProduct(tomatoOnWarehouse, 5.0, "Приготовление пиццы");
        }
        
        // Шеф-повар добавляет технологическую карту
        List<List<String>> techCard = new ArrayList<>();
        List<String> header = new ArrayList<>();
        header.add("Ингредиент");
        header.add("Количество");
        techCard.add(header);
        
        List<String> row1 = new ArrayList<>();
        row1.add("Помидоры");
        row1.add("200г");
        techCard.add(row1);
        
        List<String> row2 = new ArrayList<>();
        row2.add("Сыр");
        row2.add("150г");
        techCard.add(row2);
        
        List<String> row3 = new ArrayList<>();
        row3.add("Тесто");
        row3.add("300г");
        techCard.add(row3);
        
        chefPtr.addTechCard(pizza, techCard);
        
        // Менеджер просматривает отчеты
        List<MenuItem> menuItems = new ArrayList<>();
        menuItems.add(pizza);
        menuItems.add(pasta);
        manager.viewSalesReport(menuItems);
        
        List<Order> orders = new ArrayList<>();
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

