import java.text.SimpleDateFormat;
import java.util.Date;

public class Product {
    // Приватные поля
    private String name;              // Название продукта
    private double weight;            // Вес
    private String supplier;          // Поставщик
    private double purchasePrice;     // Цена закупки
    private long expiryDate;          // Срок годности (время окончания срока в миллисекундах)
    private long receiptDate;         // Дата поступления (в миллисекундах)

    // Конструктор по умолчанию
    public Product() {
        this.name = "";
        this.weight = 0.0;
        this.supplier = "";
        this.purchasePrice = 0.0;
        this.expiryDate = 0;
        this.receiptDate = 0;
    }

    // Конструктор с параметрами
    // Примечание: expiryDate и receiptDate принимаются в миллисекундах (как в Java Date)
    public Product(String name, double weight, String supplier,
                   double purchasePrice, long expiryDate, long receiptDate) {
        this.name = name;
        this.weight = weight;
        this.supplier = supplier;
        this.purchasePrice = purchasePrice;
        this.expiryDate = expiryDate;
        this.receiptDate = receiptDate;
    }

    // Добавить продукт (увеличить вес)
    public void addProduct(double quantity) {
        if (quantity > 0.0) {
            this.weight += quantity;
        }
    }

    // Удалить продукт (уменьшить вес)
    public void removeProduct(double quantity) {
        if (quantity > 0.0 && quantity <= weight) {
            this.weight -= quantity;
        }
    }

    // Проверка срока годности (true - если срок не истек)
    public boolean checkExpiryDate() {
        long currentTime = System.currentTimeMillis();
        return currentTime < expiryDate;
    }

    // Получить количество дней до истечения срока
    public int getDaysUntilExpiry() {
        long currentTime = System.currentTimeMillis();
        long diffMillis = expiryDate - currentTime;
        int daysDiff = (int)(diffMillis / (1000 * 60 * 60 * 24));
        return daysDiff;
    }

    // Вывести информацию о продукте
    public void printInfo() {
        System.out.println("=== Информация о продукте ===");
        System.out.println("Название: " + name);
        System.out.printf("Вес: %.2f кг%n", weight);
        System.out.println("Поставщик: " + supplier);
        System.out.println("Цена закупки: " + purchasePrice + " руб.");
        
        // Вывод даты поступления
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");
        if (receiptDate > 0) {
            System.out.println("Дата поступления: " + dateFormat.format(new Date(receiptDate)));
        } else {
            System.out.println("Дата поступления: не указана");
        }
        
        // Вывод срока годности
        if (expiryDate > 0) {
            System.out.println("Срок годности: " + dateFormat.format(new Date(expiryDate)));
        } else {
            System.out.println("Срок годности: не указан");
        }
        
        // Проверка срока годности
        boolean isExpired = !checkExpiryDate();
        System.out.println("Статус срока годности: " + (isExpired ? "Истек" : "Действителен"));
        
        if (!isExpired) {
            System.out.println("Дней до истечения: " + getDaysUntilExpiry());
        }
        
        System.out.println("=============================");
    }

    // Установить цену закупки
    public void setPurchasePrice(double price) {
        if (price >= 0.0) {
            this.purchasePrice = price;
        }
    }

    // Геттеры
    public String getName() {
        return name;
    }

    public double getWeight() {
        return weight;
    }

    public String getSupplier() {
        return supplier;
    }

    public double getPurchasePrice() {
        return purchasePrice;
    }

    public long getExpiryDate() {
        return expiryDate;
    }

    public long getReceiptDate() {
        return receiptDate;
    }

    // Сеттеры
    public void setName(String name) {
        this.name = name;
    }

    public void setWeight(double weight) {
        if (weight >= 0.0) {
            this.weight = weight;
        }
    }

    public void setSupplier(String supplier) {
        this.supplier = supplier;
    }

    public void setExpiryDate(long expiryDate) {
        this.expiryDate = expiryDate;
    }

    public void setReceiptDate(long receiptDate) {
        this.receiptDate = receiptDate;
    }
}

