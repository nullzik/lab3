import java.util.ArrayList;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Chef extends Employee {
    // Класс для хранения информации о списании (продукт и количество)
    public static class WriteOff {
        public Product product;
        public double quantity;
        
        public WriteOff(Product product, double quantity) {
            this.product = product;
            this.quantity = quantity;
        }
    }

    // Тип для списка списаний
    public static class WriteOffsType extends ArrayList<WriteOff> {
        // Наследуемся от ArrayList для удобства работы
    }

    // Приватные поля
    private WriteOffsType writeOffs;      // История списаний продуктов
    private long shiftStartTime;          // Время начала текущей смены (в миллисекундах)

    // Конструктор по умолчанию
    public Chef() {
        super();
        this.writeOffs = new WriteOffsType();
        this.shiftStartTime = 0;
        // Устанавливаем должность шеф-повара
        setPosition("Шеф-повар");
    }

    // Конструктор с параметрами
    public Chef(String fullName, int age, String contactNumber,
                String address, double hourlyRate,
                String login, String password) {
        super(fullName, age, contactNumber, address, "Шеф-повар", hourlyRate, login, password);
        this.writeOffs = new WriteOffsType();
        this.shiftStartTime = 0;
    }

    // Добавить продукт на склад
    public void addProduct(Inventory inventory, Product product) {
        if (inventory != null) {
            inventory.addProduct(product);
            System.out.println("Шеф-повар " + getFullName() + " добавил продукт '" + 
                             product.getName() + "' на склад '" + 
                             inventory.getWarehouseName() + "'");
        }
    }

    // Списать продукт (вызывается из класса Product)
    public void writeOffProduct(Product product, double quantity, String reason) {
        if (product != null && quantity > 0.0) {
            // Проверяем, достаточно ли продукта для списания
            if (product.getWeight() >= quantity) {
                product.removeProduct(quantity);
                writeOffs.add(new WriteOff(product, quantity));
                
                System.out.print("Списание продукта: " + product.getName() + 
                               " в количестве " + quantity + " кг");
                if (reason != null && !reason.isEmpty()) {
                    System.out.print(" (причина: " + reason + ")");
                }
                System.out.println();
            } else {
                System.out.println("Ошибка: недостаточно продукта '" + product.getName() + 
                                 "' для списания. Доступно: " + product.getWeight() + 
                                 " кг, требуется: " + quantity + " кг");
            }
        }
    }

    // Перегрузка метода без причины
    public void writeOffProduct(Product product, double quantity) {
        writeOffProduct(product, quantity, "");
    }

    // Добавить технологическую карту для блюда
    public void addTechCard(MenuItem menuItem, MenuItem.TechCardType techCard) {
        if (menuItem != null) {
            menuItem.setTechCard(techCard);
            System.out.println("Технологическая карта добавлена для блюда '" + 
                             menuItem.getName() + "' шеф-поваром " + getFullName());
        }
    }

    // Вывести отчет о списаниях за период
    public void printWriteOffsReport(long startTime, long endTime) {
        System.out.println("=== Отчет о списаниях за период ===");
        System.out.println("Шеф-повар: " + getFullName());
        
        // Форматируем даты
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy HH:mm");
        System.out.println("Период: с " + dateFormat.format(new Date(startTime)) + 
                         " по " + dateFormat.format(new Date(endTime)));
        System.out.println();

        if (writeOffs.isEmpty()) {
            System.out.println("Списаний за указанный период не было.");
        } else {
            double totalQuantity = 0.0;
            int count = 0;

            for (WriteOff writeOff : writeOffs) {
                Product product = writeOff.product;
                double quantity = writeOff.quantity;
                
                if (product != null) {
                    System.out.printf("Продукт: %s | Количество: %.2f кг%n", 
                                    product.getName(), quantity);
                    totalQuantity += quantity;
                    count++;
                }
            }

            System.out.println();
            System.out.println("Итого списаний: " + count);
            System.out.printf("Общее количество списанного: %.2f кг%n", totalQuantity);
        }

        System.out.println("===================================");
    }

    // Вывести отчет о списаниях за текущую смену
    public void printShiftWriteOffsReport() {
        System.out.println("=== Отчет о списаниях за смену ===");
        System.out.println("Шеф-повар: " + getFullName());
        
        if (shiftStartTime == 0) {
            System.out.println("Смена не была начата.");
            System.out.println("================================");
            return;
        }

        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy HH:mm");
        System.out.println("Начало смены: " + dateFormat.format(new Date(shiftStartTime)));
        System.out.println();

        // Фильтруем списания за текущую смену
        // Для упрощения считаем все списания из списка (в реальной системе нужна фильтрация по времени)
        double totalQuantity = 0.0;
        int count = 0;

        for (WriteOff writeOff : writeOffs) {
            Product product = writeOff.product;
            double quantity = writeOff.quantity;
            
            if (product != null) {
                System.out.printf("Продукт: %s | Количество: %.2f кг%n", 
                                product.getName(), quantity);
                totalQuantity += quantity;
                count++;
            }
        }

        if (count == 0) {
            System.out.println("Списаний за смену не было.");
        } else {
            System.out.println();
            System.out.println("Итого списаний: " + count);
            System.out.printf("Общее количество списанного: %.2f кг%n", totalQuantity);
        }

        System.out.println("================================");
    }

    // Управление складом (просмотр отчетов)
    public void manageInventory(Inventory inventory) {
        if (inventory != null) {
            System.out.println("Просмотр склада шеф-поваром: " + getFullName());
            inventory.printInventoryReport();
            System.out.println();
            inventory.printExpiryDates();
        }
    }

    // Метод для начала смены (обновляет время начала смены)
    public void startShift() {
        shiftStartTime = System.currentTimeMillis();
        System.out.println("Смена начата шеф-поваром: " + getFullName());
    }
}

