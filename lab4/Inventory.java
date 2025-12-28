import java.util.ArrayList;

public class Inventory {
    // Тип для списка продуктов
    public static class ProductsType extends ArrayList<Product> {
        // Наследуемся от ArrayList для удобства работы
    }

    // Приватные поля
    private String warehouseName;     // Название склада
    private ProductsType products;    // Список продуктов

    // Конструктор по умолчанию
    public Inventory() {
        this.warehouseName = "";
        this.products = new ProductsType();
    }

    // Конструктор с параметрами
    public Inventory(String warehouseName) {
        this.warehouseName = warehouseName;
        this.products = new ProductsType();
    }

    // Добавить продукт на склад
    public void addProduct(Product product) {
        products.add(product);
    }

    // Удалить продукт со склада по имени
    public boolean removeProduct(String productName) {
        for (int i = 0; i < products.size(); i++) {
            if (products.get(i).getName().equals(productName)) {
                products.remove(i);
                return true;
            }
        }
        return false;
    }

    // Найти продукт по имени (возвращает ссылку на продукт)
    public Product findProduct(String productName) {
        for (Product product : products) {
            if (product.getName().equals(productName)) {
                return product;
            }
        }
        return null; // Продукт не найден
    }

    // Вывести информацию о сроках годности всех продуктов
    public void printExpiryDates() {
        System.out.println("=== Сроки годности продуктов на складе: " + warehouseName + " ===");
        
        boolean hasExpiredProducts = false;
        
        for (Product product : products) {
            if (!product.checkExpiryDate()) {
                hasExpiredProducts = true;
                System.out.println("ВНИМАНИЕ! Продукт '" + product.getName() + "' просрочен!");
            } else {
                int daysLeft = product.getDaysUntilExpiry();
                System.out.println("Продукт: " + product.getName() + " - дней до истечения: " + daysLeft);
            }
        }
        
        if (!hasExpiredProducts && products.isEmpty()) {
            System.out.println("Склад пуст.");
        } else if (!hasExpiredProducts) {
            System.out.println("Все продукты в сроке.");
        }
        
        System.out.println("===========================================================");
    }

    // Вывести отчет о хранимых продуктах
    public void printInventoryReport() {
        System.out.println("=== Отчет о складе: " + warehouseName + " ===");
        System.out.println("Количество продуктов на складе: " + products.size());
        System.out.println();
        
        if (products.isEmpty()) {
            System.out.println("Склад пуст.");
        } else {
            for (int i = 0; i < products.size(); i++) {
                System.out.println("--- Продукт #" + (i + 1) + " ---");
                products.get(i).printInfo();
                System.out.println();
            }
        }
        
        System.out.println("===================================================");
    }

    // Геттеры
    public String getWarehouseName() {
        return warehouseName;
    }

    public ProductsType getProducts() {
        return products;
    }

    public int getProductsCount() {
        return products.size();
    }

    // Сеттеры
    public void setWarehouseName(String warehouseName) {
        this.warehouseName = warehouseName;
    }
}

