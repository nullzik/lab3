import java.util.ArrayList;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Order {
    // Тип для списка позиций меню
    public static class MenuItemsType extends ArrayList<MenuItem> {
        // Наследуемся от ArrayList для удобства работы
    }

    // Статическая переменная для генерации уникальных ID заказов
    private static int nextOrderId = 1;

    // Приватные поля
    private int orderId;                  // ID заказа
    private MenuItemsType menuItems;      // Блюда в заказе
    private double totalAmount;           // Сумма заказа
    private long orderTime;               // Время создания заказа (в миллисекундах)
    private Employee employee;            // Сотрудник, добавивший заказ

    // Конструктор по умолчанию
    public Order() {
        this.orderId = nextOrderId++;
        this.menuItems = new MenuItemsType();
        this.totalAmount = 0.0;
        this.orderTime = System.currentTimeMillis();
        this.employee = null;
    }

    // Конструктор с параметрами
    public Order(Employee employee) {
        this.orderId = nextOrderId++;
        this.menuItems = new MenuItemsType();
        this.totalAmount = 0.0;
        this.orderTime = System.currentTimeMillis();
        this.employee = employee;
    }

    // Добавить блюдо в заказ
    public boolean addMenuItem(MenuItem menuItem) {
        if (menuItem != null) {
            // Проверяем, доступно ли блюдо к продаже
            if (menuItem.isAvailable()) {
                menuItems.add(menuItem);
                calculateTotalAmount(); // Пересчитываем сумму после добавления
                System.out.println("Блюдо '" + menuItem.getName() + "' добавлено в заказ #" + orderId);
                return true;
            } else {
                System.out.println("Блюдо '" + menuItem.getName() + "' недоступно к продаже!");
                return false;
            }
        }
        return false;
    }

    // Удалить блюдо из заказа
    public boolean removeMenuItem(String menuItemName) {
        for (int i = 0; i < menuItems.size(); i++) {
            MenuItem item = menuItems.get(i);
            if (item != null && item.getName().equals(menuItemName)) {
                menuItems.remove(i);
                calculateTotalAmount(); // Пересчитываем сумму после удаления
                System.out.println("Блюдо '" + menuItemName + "' удалено из заказа #" + orderId);
                return true;
            }
        }
        
        System.out.println("Блюдо '" + menuItemName + "' не найдено в заказе #" + orderId);
        return false;
    }

    // Рассчитать сумму заказа
    public double calculateTotalAmount() {
        totalAmount = 0.0;
        
        for (MenuItem menuItem : menuItems) {
            if (menuItem != null) {
                totalAmount += menuItem.getSellingPrice();
            }
        }
        
        return totalAmount;
    }

    // Вывести информацию о заказе
    public void printOrder() {
        System.out.println("=== Заказ #" + orderId + " ===");
        
        // Вывод времени заказа
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss");
        System.out.println("Время создания: " + dateFormat.format(new Date(orderTime)));
        
        // Вывод информации о сотруднике
        if (employee != null) {
            System.out.println("Сотрудник: " + employee.getFullName() + " (" + employee.getPosition() + ")");
        } else {
            System.out.println("Сотрудник: не указан");
        }
        
        System.out.println();
        System.out.println("Блюда в заказе:");
        
        if (menuItems.isEmpty()) {
            System.out.println("  Заказ пуст.");
        } else {
            int index = 1;
            for (MenuItem menuItem : menuItems) {
                if (menuItem != null) {
                    System.out.printf("  %d. %s - %.2f руб.%n", index, 
                                     menuItem.getName(), menuItem.getSellingPrice());
                    index++;
                }
            }
        }
        
        System.out.println();
        System.out.printf("Итого: %.2f руб.%n", totalAmount);
        System.out.println("==========================");
    }

    // Метод для завершения заказа (обновляет счетчики продаж)
    public void completeOrder() {
        // Обновляем счетчики продаж для каждого блюда в заказе
        for (MenuItem menuItem : menuItems) {
            if (menuItem != null) {
                // Используем метод incrementSalesCount из MenuItem
                menuItem.incrementSalesCount();
            }
        }
        
        // Добавляем продажу сотруднику
        if (employee != null) {
            employee.addSales(menuItems.size());
        }
        
        System.out.println("Заказ #" + orderId + " завершен. Продажи обновлены.");
    }

    // Геттеры
    public int getOrderId() {
        return orderId;
    }

    public MenuItemsType getMenuItems() {
        return menuItems;
    }

    public double getTotalAmount() {
        return totalAmount;
    }

    public long getOrderTime() {
        return orderTime;
    }

    public Employee getEmployee() {
        return employee;
    }

    public int getMenuItemsCount() {
        return menuItems.size();
    }

    // Сеттеры
    public void setEmployee(Employee employee) {
        this.employee = employee;
    }
}

