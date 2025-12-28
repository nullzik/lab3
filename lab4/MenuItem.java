import java.util.ArrayList;
import java.util.List;

public class MenuItem {
    // Тип для технологической карты (список списков строк)
    // Каждый внутренний список представляет строку технологической карты
    public static class TechCardType extends ArrayList<List<String>> {
        // Наследуемся от ArrayList для удобства работы
    }

    // Приватные поля
    private String name;                  // Название блюда
    private double costPrice;             // Себестоимость
    private double sellingPrice;         // Цена продажи
    private TechCardType techCard;       // Технологическая карта
    private int salesCount;               // Количество продаж
    private boolean isAvailable;         // Доступно к продаже

    // Конструктор по умолчанию
    public MenuItem() {
        this.name = "";
        this.costPrice = 0.0;
        this.sellingPrice = 0.0;
        this.techCard = new TechCardType();
        this.salesCount = 0;
        this.isAvailable = true;
    }

    // Конструктор с параметрами
    public MenuItem(String name, double costPrice, double sellingPrice, boolean isAvailable) {
        this.name = name;
        this.costPrice = costPrice;
        this.sellingPrice = sellingPrice;
        this.techCard = new TechCardType();
        this.salesCount = 0;
        this.isAvailable = isAvailable;
    }

    // Расчет прибыли с единицы
    public double calculateProfitPerUnit() {
        return sellingPrice - costPrice;
    }

    // Расчет общей прибыли
    public double calculateTotalProfit() {
        return calculateProfitPerUnit() * salesCount;
    }

    // Расчет маржинальности (в процентах)
    public double calculateMargin() {
        if (sellingPrice == 0.0) {
            return 0.0;
        }
        return (calculateProfitPerUnit() / sellingPrice) * 100.0;
    }

    // Вывести информацию о блюде
    public void printInfo() {
        System.out.println("=== Информация о блюде ===");
        System.out.println("Наименование: " + name);
        System.out.printf("Себестоимость: %.2f%n", costPrice);
        System.out.printf("Цена продажи: %.2f%n", sellingPrice);
        System.out.println("Количество продаж: " + salesCount);
        System.out.println("Доступно к продаже: " + (isAvailable ? "Да" : "Нет"));
        System.out.printf("Прибыль с единицы: %.2f%n", calculateProfitPerUnit());
        System.out.printf("Общая прибыль: %.2f%n", calculateTotalProfit());
        System.out.printf("Маржинальность: %.2f%%%n", calculateMargin());
        System.out.println("=========================");
    }

    // Установить доступность
    public void setAvailability(boolean isAvailable) {
        this.isAvailable = isAvailable;
    }

    // Геттеры
    public String getName() {
        return name;
    }

    public double getCostPrice() {
        return costPrice;
    }

    public double getSellingPrice() {
        return sellingPrice;
    }

    public TechCardType getTechCard() {
        return techCard;
    }

    public int getSalesCount() {
        return salesCount;
    }

    public boolean isAvailable() {
        return isAvailable;
    }

    // Сеттеры
    public void setName(String name) {
        this.name = name;
    }

    public void setCostPrice(double costPrice) {
        this.costPrice = costPrice;
    }

    public void setSellingPrice(double sellingPrice) {
        this.sellingPrice = sellingPrice;
    }

    public void setTechCard(TechCardType techCard) {
        this.techCard = techCard;
    }

    public void setSalesCount(int salesCount) {
        this.salesCount = salesCount;
    }

    // Метод для увеличения счетчика продаж (будет использоваться при завершении заказа)
    public void incrementSalesCount() {
        // TODO: будет связано с Order.CompleteOrder() и Employee.addSales()
        this.salesCount++;
    }
}

