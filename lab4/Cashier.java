// Кассир, наследуется от Employee
// Отвечает за приём оплаты и суммарную выручку по кассе
public class Cashier extends Employee {
    private double cashRegisterTotal;  // Общая сумма, проведённая через кассу за смену

    // Конструктор по умолчанию
    public Cashier() {
        super();  // Вызов конструктора базового класса
        this.cashRegisterTotal = 0.0;
        setPosition("Кассир");
    }

    // Конструктор с параметрами - демонстрация вызова конструктора базового класса
    public Cashier(String fullName, int age, String contactNumber,
                   String address, double hourlyRate,
                   String login, String password) {
        // Вызов конструктора базового класса Employee с параметрами
        super(fullName, age, contactNumber, address, "Кассир", hourlyRate, login, password);
        this.cashRegisterTotal = 0.0;
    }

    // Проведение оплаты заказа
    public void processPayment(Order order) {
        if (order != null) {
            double amount = order.getTotalAmount();
            cashRegisterTotal += amount;

            System.out.println("Кассир " + getFullName()
                    + " провёл оплату заказа #" + order.getOrderId()
                    + " на сумму " + amount + " руб."
                    + " (выручка за смену: " + cashRegisterTotal + " руб.)");
        }
    }

    // Переопределение метода расчета зарплаты (без вызова базового метода)
    @Override
    public double calculateSalary() {
        // Переопределение без вызова super.calculateSalary()
        // Используем protected-поля напрямую
        double base = hoursWorked * hourlyRate;
        double performanceBonus = cashRegisterTotal * 0.02;  // 2% от проведенной выручки
        double total = base + performanceBonus + salaryBalance;

        System.out.println("[Cashier] Расчет зарплаты: базовая = " + base
                + ", бонус от выручки = " + performanceBonus
                + ", баланс = " + salaryBalance);

        return total;
    }

    // Геттер
    public double getCashRegisterTotal() {
        return cashRegisterTotal;
    }
}

