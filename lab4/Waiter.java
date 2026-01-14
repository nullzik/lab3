// Класс официанта, наследуется от Employee
// Добавляет учёт обслуженных столов и чаевых
public class Waiter extends Employee {
    // Приватные поля
    private int tablesServed;      // Количество обслуженных столов за смену
    private double tipsBalance;    // Баланс чаевых

    // Конструктор по умолчанию
    public Waiter() {
        super();  // Вызов конструктора базового класса
        this.tablesServed = 0;
        this.tipsBalance = 0.0;
        // Устанавливаем должность по умолчанию для официанта
        setPosition("Официант");
    }

    // Конструктор с параметрами - демонстрация вызова конструктора базового класса
    public Waiter(String fullName, int age, String contactNumber,
                  String address, double hourlyRate,
                  String login, String password) {
        // Вызов конструктора базового класса Employee с параметрами
        super(fullName, age, contactNumber, address, "Официант", hourlyRate, login, password);
        this.tablesServed = 0;
        this.tipsBalance = 0.0;
    }

    // Методы работы официанта
    public void serveOrder(Order order) {
        if (order != null) {
            ++tablesServed;
            System.out.println("Официант " + getFullName()
                    + " обслужил заказ #" + order.getOrderId()
                    + ". Всего обслужено столов: " + tablesServed);
        }
    }

    public void addTips(double amount) {
        if (amount > 0.0) {
            tipsBalance += amount;
            System.out.println("Официант " + getFullName()
                    + " получил чаевые: " + amount
                    + " руб. (всего: " + tipsBalance + " руб.)");
        }
    }

    // Переопределение метода расчета зарплаты (с вызовом базового метода)
    @Override
    public double calculateSalary() {
        // Используем protected-поля из базового класса напрямую
        // Вызываем базовый метод для расчета базовой части
        double base = super.calculateSalary();  // Вызов базового метода
        
        // Дополнительный бонус официанту: % от чаевых + премия за обслуженные столы
        double tipsBonus = tipsBalance * 0.3;        // 30% чаевых остаётся официанту
        double tablesBonus = tablesServed * 50.0;   // 50 руб. за стол
        double salesBonus = salesCount * 10.0;       // 10 руб. за каждую продажу/позицию
        
        System.out.println("[Waiter] Расчет зарплаты: базовая = " + base
                + ", бонус от чаевых = " + tipsBonus
                + ", бонус за столы = " + tablesBonus
                + ", бонус за продажи = " + salesBonus);
        
        return base + tipsBonus + tablesBonus + salesBonus;
    }

    // Геттеры
    public int getTablesServed() {
        return tablesServed;
    }

    public double getTipsBalance() {
        return tipsBalance;
    }
}

