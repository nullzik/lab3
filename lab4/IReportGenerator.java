// Интерфейс для генерации отчетов
// Определяет контракт для классов, которые могут генерировать различные типы отчетов
public interface IReportGenerator {
    // Метод для генерации отчета (возвращает строку)
    String generateReport();
    
    // Метод для получения типа отчета
    String getReportType();
    
    // Метод по умолчанию (default method) - может быть переопределен
    default void printReport() {
        System.out.println("=== Отчет: " + getReportType() + " ===");
        System.out.println(generateReport());
        System.out.println("================================");
    }
}

