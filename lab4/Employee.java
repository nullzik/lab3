public class Employee {
    // Приватные поля
    private String fullName;          // ФИО
    private int age;                  // Возраст
    private String contactNumber;     // Контактный номер
    private String address;           // Адрес
    private String position;          // Должность
    private double hoursWorked;       // Отработанные часы
    private double hourlyRate;        // Почасовая ставка
    private String login;             // Логин
    private String password;          // Пароль
    private double salaryBalance;     // Баланс з/п (для штрафов, премий, списаний)
    private int salesCount;           // Количество продаж

    // Конструктор по умолчанию
    public Employee() {
        this.fullName = "";
        this.age = 0;
        this.contactNumber = "";
        this.address = "";
        this.position = "";
        this.hoursWorked = 0.0;
        this.hourlyRate = 0.0;
        this.login = "";
        this.password = "";
        this.salaryBalance = 0.0;
        this.salesCount = 0;
    }

    // Конструктор с параметрами
    public Employee(String fullName, int age, String contactNumber,
                   String address, String position,
                   double hourlyRate, String login, String password) {
        this.fullName = fullName;
        this.age = age;
        this.contactNumber = contactNumber;
        this.address = address;
        this.position = position;
        this.hoursWorked = 0.0;
        this.hourlyRate = hourlyRate;
        this.login = login;
        this.password = password;
        this.salaryBalance = 0.0;
        this.salesCount = 0;
    }

    // Расчет заработной платы
    public double calculateSalary() {
        // Расчет з/п = отработанные часы * почасовая ставка + баланс (премии/штрафы)
        return hoursWorked * hourlyRate + salaryBalance;
    }

    // Добавить продажи
    public void addSales(int salesCount) {
        if (salesCount > 0) {
            this.salesCount += salesCount;
        }
    }

    // Открыть смену (проверка логина/пароля)
    public boolean openShift(String login, String password) {
        // Проверка логина и пароля для открытия смены
        if (login.equals(this.login) && password.equals(this.password)) {
            System.out.println("Смена открыта для сотрудника: " + fullName);
            return true;
        } else {
            System.out.println("Неверный логин или пароль!");
            return false;
        }
    }

    // Сменить логин/пароль
    public boolean changeCredentials(String oldLogin, String oldPassword,
                                    String newLogin, String newPassword) {
        // Проверка старых учетных данных перед изменением
        if (oldLogin.equals(this.login) && oldPassword.equals(this.password)) {
            this.login = newLogin;
            this.password = newPassword;
            System.out.println("Учетные данные успешно изменены.");
            return true;
        } else {
            System.out.println("Неверный текущий логин или пароль!");
            return false;
        }
    }

    // Геттеры
    public String getFullName() {
        return fullName;
    }

    public int getAge() {
        return age;
    }

    public String getContactNumber() {
        return contactNumber;
    }

    public String getAddress() {
        return address;
    }

    public String getPosition() {
        return position;
    }

    public double getHoursWorked() {
        return hoursWorked;
    }

    public double getHourlyRate() {
        return hourlyRate;
    }

    public String getLogin() {
        return login;
    }

    public double getSalaryBalance() {
        return salaryBalance;
    }

    public int getSalesCount() {
        return salesCount;
    }

    // Сеттеры
    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    public void setAge(int age) {
        if (age >= 0) {
            this.age = age;
        }
    }

    public void setContactNumber(String contactNumber) {
        this.contactNumber = contactNumber;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public void setHoursWorked(double hoursWorked) {
        if (hoursWorked >= 0.0) {
            this.hoursWorked = hoursWorked;
        }
    }

    public void setHourlyRate(double hourlyRate) {
        if (hourlyRate >= 0.0) {
            this.hourlyRate = hourlyRate;
        }
    }

    public void setSalaryBalance(double salaryBalance) {
        this.salaryBalance = salaryBalance;
    }
}

