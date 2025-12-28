import java.util.ArrayList;

public class Manager extends Employee {
    // Тип для списка сотрудников
    public static class EmployeesType extends ArrayList<Employee> {
        // Наследуемся от ArrayList для удобства работы
    }

    // Тип для списка позиций меню
    public static class MenuItemsType extends ArrayList<MenuItem> {
        // Наследуемся от ArrayList для удобства работы
    }

    // Тип для списка заказов
    public static class OrdersType extends ArrayList<Order> {
        // Наследуемся от ArrayList для удобства работы
    }

    // Конструктор по умолчанию
    public Manager() {
        super();
        // Устанавливаем должность менеджера
        setPosition("Менеджер");
    }

    // Конструктор с параметрами
    public Manager(String fullName, int age, String contactNumber,
                  String address, double hourlyRate,
                  String login, String password) {
        super(fullName, age, contactNumber, address, "Менеджер", hourlyRate, login, password);
    }

    // Добавить штраф сотруднику
    public void addPenalty(Employee employee, double amount) {
        if (employee != null && amount > 0.0) {
            double currentBalance = employee.getSalaryBalance();
            employee.setSalaryBalance(currentBalance - amount); // Штраф вычитается из баланса
            System.out.println("Штраф в размере " + amount + " руб. добавлен сотруднику: " + 
                             employee.getFullName());
        }
    }

    // Добавить премию сотруднику
    public void addBonus(Employee employee, double amount) {
        if (employee != null && amount > 0.0) {
            double currentBalance = employee.getSalaryBalance();
            employee.setSalaryBalance(currentBalance + amount); // Премия добавляется к балансу
            System.out.println("Премия в размере " + amount + " руб. добавлена сотруднику: " + 
                             employee.getFullName());
        }
    }

    // Изменить почасовую ставку
    public void changeHourlyRate(Employee employee, double newRate) {
        if (employee != null && newRate >= 0.0) {
            employee.setHourlyRate(newRate);
            System.out.println("Почасовая ставка изменена для сотрудника: " + 
                             employee.getFullName() + " на " + newRate + " руб./час");
        }
    }

    // Изменить отработанные часы
    public void changeHoursWorked(Employee employee, double hours) {
        if (employee != null && hours >= 0.0) {
            employee.setHoursWorked(hours);
            System.out.println("Отработанные часы изменены для сотрудника: " + 
                             employee.getFullName() + " на " + hours + " часов");
        }
    }

    // Сбросить отработанные часы
    public void resetHoursWorked(Employee employee) {
        if (employee != null) {
            employee.setHoursWorked(0.0);
            System.out.println("Отработанные часы сброшены для сотрудника: " + 
                             employee.getFullName());
        }
    }

    // Изменить цену продажи
    public void changeSellingPrice(MenuItem menuItem, double newPrice) {
        if (menuItem != null && newPrice >= 0.0) {
            menuItem.setSellingPrice(newPrice);
            System.out.println("Цена продажи изменена для позиции '" + menuItem.getName() + 
                             "' на " + newPrice + " руб.");
        }
    }

    // Создать позицию в меню
    public MenuItem createMenuItem(String name, double costPrice,
                                   double sellingPrice, boolean isAvailable) {
        MenuItem newItem = new MenuItem(name, costPrice, sellingPrice, isAvailable);
        System.out.println("Создана новая позиция в меню: " + name);
        return newItem;
    }

    // Редактировать позицию в меню
    public void editMenuItem(MenuItem menuItem, String newName,
                            double newCostPrice, double newSellingPrice) {
        if (menuItem != null) {
            menuItem.setName(newName);
            menuItem.setCostPrice(newCostPrice);
            menuItem.setSellingPrice(newSellingPrice);
            System.out.println("Позиция меню отредактирована: " + newName);
        }
    }

    // Просмотр отчетов по продажам по позициям меню
    public void viewSalesReport(MenuItemsType menuItems) {
        System.out.println("=== Отчет по продажам ===");
        System.out.println("Отчет создан менеджером: " + getFullName());
        System.out.println();

        if (menuItems.isEmpty()) {
            System.out.println("Меню пусто.");
        } else {
            double totalProfit = 0.0;
            int totalSales = 0;

            for (MenuItem item : menuItems) {
                if (item != null) {
                    int sales = item.getSalesCount();
                    double profit = item.calculateTotalProfit();
                    totalSales += sales;
                    totalProfit += profit;

                    System.out.printf("Позиция: %s | Продаж: %d | Прибыль: %.2f руб.%n", 
                                    item.getName(), sales, profit);
                }
            }

            System.out.println();
            System.out.println("Итого продаж: " + totalSales);
            System.out.printf("Общая прибыль: %.2f руб.%n", totalProfit);
        }

        System.out.println("=========================");
    }

    // Просмотр отчетов по заказам
    public void viewOrdersReport(OrdersType orders) {
        System.out.println("=== Отчет по заказам ===");
        System.out.println("Отчет создан менеджером: " + getFullName());
        System.out.println();

        if (orders.isEmpty()) {
            System.out.println("Заказов нет.");
        } else {
            double totalRevenue = 0.0;
            int totalOrders = 0;

            for (Order order : orders) {
                if (order != null) {
                    totalRevenue += order.getTotalAmount();
                    totalOrders++;
                }
            }

            System.out.println("Общее количество заказов: " + totalOrders);
            System.out.printf("Общая выручка: %.2f руб.%n", totalRevenue);
            
            if (totalOrders > 0) {
                System.out.printf("Средний чек: %.2f руб.%n", (totalRevenue / totalOrders));
            }

            System.out.println();
            System.out.println("Детали заказов:");
            
            for (Order order : orders) {
                if (order != null) {
                    System.out.println("  Заказ #" + order.getOrderId() + 
                                     " - Сумма: " + order.getTotalAmount() + " руб." +
                                     " - Блюд: " + order.getMenuItemsCount());
                }
            }
        }

        System.out.println("=========================");
    }

    // Управление складом (вызов отчета)
    public void manageInventory(Inventory inventory) {
        if (inventory != null) {
            System.out.println("Управление складом менеджером: " + getFullName());
            inventory.printInventoryReport();
            System.out.println();
            inventory.printExpiryDates();
        }
    }
}

