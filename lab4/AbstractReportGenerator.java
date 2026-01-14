// Абстрактный класс для генерации отчетов
// Определяет общую структуру для классов, генерирующих отчеты
public abstract class AbstractReportGenerator {
    // Защищенное поле для имени генератора отчета
    protected String generatorName;
    
    // Конструктор абстрактного класса
    public AbstractReportGenerator(String generatorName) {
        this.generatorName = generatorName;
    }
    
    // Абстрактный метод - должен быть реализован в производных классах
    public abstract String generateReport();
    
    // Абстрактный метод - должен быть реализован в производных классах
    public abstract String getReportType();
    
    // Конкретный метод с реализацией (не абстрактный)
    public void printReport() {
        System.out.println("=== Отчет: " + getReportType() + " ===");
        System.out.println("Генератор: " + generatorName);
        System.out.println(generateReport());
        System.out.println("================================");
    }
    
    // Геттер
    public String getGeneratorName() {
        return generatorName;
    }
}

