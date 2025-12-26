import java.util.List;
import java.util.ArrayList;

/**
 * Класс MenuItem - представляет позицию в меню ресторана
 * Содержит информацию о блюде: название, себестоимость, цена продажи, технологическая карта, количество продаж, доступность
 */
public class MenuItem {
    // TechCardType будет представлен как List<List<String>>
    private String name;
    private double costPrice;
    private double sellingPrice;
    private List<List<String>> techCard;
    private int salesCount;
    private boolean isAvailable;

    /**
     * Конструктор по умолчанию
     */
    public MenuItem() {
        this.name = "";
        this.costPrice = 0.0;
        this.sellingPrice = 0.0;
        this.techCard = new ArrayList<>();
        this.salesCount = 0;
        this.isAvailable = true;
    }

    /**
     * Конструктор с параметрами
     */
    public MenuItem(String name, double costPrice, double sellingPrice, boolean isAvailable) {
        this.name = name;
        this.costPrice = costPrice;
        this.sellingPrice = sellingPrice;
        this.techCard = new ArrayList<>();
        this.salesCount = 0;
        this.isAvailable = isAvailable;
    }

    /**
     * Рассчитать прибыль с единицы продукции
     */
    public double calculateProfitPerUnit() {
        return this.sellingPrice - this.costPrice;
    }

    /**
     * Рассчитать общую прибыль (прибыль с единицы * количество продаж)
     */
    public double calculateTotalProfit() {
        return calculateProfitPerUnit() * this.salesCount;
    }

    /**
     * Рассчитать маржу (в процентах)
     */
    public double calculateMargin() {
        if (this.sellingPrice == 0.0) {
            return 0.0;
        }
        return ((this.sellingPrice - this.costPrice) / this.sellingPrice) * 100.0;
    }

    /**
     * Вывести информацию о позиции меню
     */
    public void printInfo() {
        System.out.println("=== Информация о позиции меню ===");
        System.out.println("Название: " + this.name);
        System.out.printf("Себестоимость: %.2f руб.%n", this.costPrice);
        System.out.printf("Цена продажи: %.2f руб.%n", this.sellingPrice);
        System.out.printf("Прибыль с единицы: %.2f руб.%n", calculateProfitPerUnit());
        System.out.printf("Маржа: %.2f%%%n", calculateMargin());
        System.out.println("Количество продаж: " + this.salesCount);
        System.out.printf("Общая прибыль: %.2f руб.%n", calculateTotalProfit());
        System.out.println("Доступность: " + (this.isAvailable ? "Доступно" : "Недоступно"));
        
        if (!this.techCard.isEmpty()) {
            System.out.println("Технологическая карта:");
            for (List<String> row : this.techCard) {
                System.out.println("  " + String.join(" | ", row));
            }
        }
        
        System.out.println("=================================");
    }

    /**
     * Установить доступность блюда
     */
    public void setAvailability(boolean isAvailable) {
        this.isAvailable = isAvailable;
    }

    // Геттеры
    public String getName() {
        return this.name;
    }

    public double getCostPrice() {
        return this.costPrice;
    }

    public double getSellingPrice() {
        return this.sellingPrice;
    }

    public List<List<String>> getTechCard() {
        return this.techCard;
    }

    public int getSalesCount() {
        return this.salesCount;
    }

    public boolean isAvailable() {
        return this.isAvailable;
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

    public void setTechCard(List<List<String>> techCard) {
        this.techCard = techCard;
    }

    public void setSalesCount(int salesCount) {
        this.salesCount = salesCount;
    }
}


