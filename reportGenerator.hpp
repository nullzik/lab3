#ifndef REPORT_GENERATOR_HPP
#define REPORT_GENERATOR_HPP

#include <string>

// Абстрактный класс для генерации отчетов
// Определяет интерфейс для классов, которые могут генерировать различные типы отчетов
class IReportGenerator
{
public:
	// Виртуальный деструктор (обязателен для абстрактных классов)
	virtual ~IReportGenerator() = default;
	
	// Чисто виртуальная функция - должна быть реализована в производных классах
	// Генерирует отчет и возвращает его в виде строки
	virtual std::string GenerateReport() const = 0;
	
	// Чисто виртуальная функция - должна быть реализована в производных классах
	// Возвращает тип отчета, который генерирует данный класс
	virtual std::string GetReportType() const = 0;
	
	// Виртуальная функция с реализацией по умолчанию (не чистая виртуальная)
	// Может быть переопределена в производных классах
	virtual void PrintReport() const;
};

#endif // REPORT_GENERATOR_HPP

