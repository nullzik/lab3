import java.util.ArrayList;
import java.text.SimpleDateFormat;
import java.util.Date;

// Класс шеф-повара, наследуется от Employee и реализует множественное наследование
// Наследуется от Employee и реализует интерфейсы IReportGenerator и ICloneable
// Также использует AbstractReportGenerator через композицию для демонстрации абстрактного класса
public class Chef extends Employee implements IReportGenerator, ICloneable<Chef> {
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
    
    // Композиция: используем AbstractReportGenerator для демонстрации абстрактного класса
    private AbstractReportGenerator reportGenerator;
    
    // Конструктор по умолчанию
    public Chef() {
        super();  // Вызов конструктора базового класса Employee
        this.writeOffs = new WriteOffsType();
        this.shiftStartTime = 0;
        // Устанавливаем должность шеф-повара
        setPosition("Шеф-повар");
        // Создаем объект абстрактного класса через анонимный класс
        this.reportGenerator = new AbstractReportGenerator("Шеф-повар") {
            @Override
            public String generateReport() {
                return Chef.this.generateReport();
            }
            
            @Override
            public String getReportType() {
                return Chef.this.getReportType();
            }
        };
    }

    // Конструктор с параметрами - демонстрация вызова конструктора базового класса
    public Chef(String fullName, int age, String contactNumber,
                String address, double hourlyRate,
                String login, String password) {
        // Вызов конструктора базового класса Employee с параметрами
        super(fullName, age, contactNumber, address, "Шеф-повар", hourlyRate, login, password);
        this.writeOffs = new WriteOffsType();
        this.shiftStartTime = 0;
        // Создаем объект абстрактного класса через анонимный класс
        this.reportGenerator = new AbstractReportGenerator("Шеф-повар") {
            @Override
            public String generateReport() {
                return Chef.this.generateReport();
            }
            
            @Override
            public String getReportType() {
                return Chef.this.getReportType();
            }
        };
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
        if (product == null) {
            throw new IllegalArgumentException("Продукт не может быть null");
        }
        if (quantity <= 0.0) {
            throw new IllegalArgumentException("Количество для списания должно быть положительным");
        }

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
            // Демонстрация генерации исключения
            throw new RuntimeException("Недостаточно продукта '" + product.getName() + 
                                     "' для списания. Доступно: " + product.getWeight() + 
                                     " кг, требуется: " + quantity + " кг");
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
    
    // Переопределение метода расчета зарплаты (с вызовом базового метода)
    @Override
    public double calculateSalary() {
        // Используем protected-поля из базового класса напрямую
        // Вызываем базовый метод для расчета базовой части
        double baseSalary = super.calculateSalary();  // Вызов базового метода Employee
        double chefBonus = salesCount * 50.0;  // Бонус за продажи (используем protected поле)
        
        System.out.println("[Chef] Расчет зарплаты: базовая = " + baseSalary
                + ", бонус шеф-повара = " + chefBonus);
        
        return baseSalary + chefBonus;
    }
    
    // Реализация методов интерфейса IReportGenerator
    @Override
    public String generateReport() {
        StringBuilder sb = new StringBuilder();
        sb.append("Отчет шеф-повара: ").append(fullName).append("\n");  // Используем protected поле
        sb.append("Должность: ").append(position).append("\n");
        sb.append("Отработано часов: ").append(hoursWorked).append("\n");
        sb.append("Почасовая ставка: ").append(hourlyRate).append(" руб./час\n");
        sb.append("Зарплата: ").append(calculateSalary()).append(" руб.\n");
        sb.append("Количество списаний продуктов: ").append(writeOffs.size()).append("\n");
        sb.append("Количество продаж: ").append(salesCount);
        return sb.toString();
    }
    
    @Override
    public String getReportType() {
        return "Отчет шеф-повара";
    }
    
    // Реализация методов интерфейса ICloneable
    @Override
    public Chef cloneShallow() {
        // Поверхностное клонирование: создаем новый объект, но ссылки на продукты остаются те же
        Chef cloned = new Chef();
        // Копируем поля Employee через конструктор копирования
        cloned.fullName = this.fullName;
        cloned.age = this.age;
        cloned.contactNumber = this.contactNumber;
        cloned.address = this.address;
        cloned.position = this.position;
        cloned.hoursWorked = this.hoursWorked;
        cloned.hourlyRate = this.hourlyRate;
        cloned.salaryBalance = this.salaryBalance;
        cloned.salesCount = this.salesCount;
        cloned.writeOffs = this.writeOffs;  // Разделяем ссылку на список списаний (shallow)
        cloned.shiftStartTime = this.shiftStartTime;
        return cloned;
    }
    
    @Override
    public Chef cloneDeep() {
        // Глубокое клонирование: создаем полностью независимую копию
        Chef cloned = new Chef();
        // Копируем поля Employee
        cloned.fullName = this.fullName;
        cloned.age = this.age;
        cloned.contactNumber = this.contactNumber;
        cloned.address = this.address;
        cloned.position = this.position;
        cloned.hoursWorked = this.hoursWorked;
        cloned.hourlyRate = this.hourlyRate;
        cloned.salaryBalance = this.salaryBalance;
        cloned.salesCount = this.salesCount;
        cloned.writeOffs = new WriteOffsType();
        // Копируем каждое списание отдельно
        for (WriteOff writeOff : this.writeOffs) {
            // Создаем новый объект Product для глубокого клонирования
            Product clonedProduct = new Product(
                writeOff.product.getName(),
                writeOff.product.getWeight(),
                writeOff.product.getSupplier(),
                writeOff.product.getPurchasePrice(),
                writeOff.product.getExpiryDate(),
                writeOff.product.getReceiptDate()
            );
            cloned.writeOffs.add(new WriteOff(clonedProduct, writeOff.quantity));
        }
        cloned.shiftStartTime = this.shiftStartTime;
        return cloned;
    }
    
    // Метод для демонстрации использования абстрактного класса
    public void printReportUsingAbstractClass() {
        reportGenerator.printReport();
    }
}

