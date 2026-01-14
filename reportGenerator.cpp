#include "reportGenerator.hpp"
#include <iostream>

void IReportGenerator::PrintReport() const
{
	// Реализация по умолчанию: вызывает GenerateReport() и выводит результат
	std::cout << "=== Отчет: " << GetReportType() << " ===" << std::endl;
	std::cout << GenerateReport() << std::endl;
	std::cout << "================================" << std::endl;
}

