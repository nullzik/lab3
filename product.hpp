#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <ctime>

class Product
{
private:
	std::string m_name;
	double m_weight;
	std::string m_supplier;
	double m_purchasePrice;
	std::time_t m_expiryDate;		// Срок годности (время окончания срока)
	std::time_t m_receiptDate;		// Дата поступления

public:
	// Конструкторы и деструктор
	Product();
	Product(const std::string& name, double weight, const std::string& supplier, 
			double purchasePrice, std::time_t expiryDate, std::time_t receiptDate);
	~Product() = default;

	// Публичные методы
	void AddProduct(double quantity);
	void RemoveProduct(double quantity);
	bool CheckExpiryDate() const;				// Проверка срока годности (true - если срок не истек)
	int GetDaysUntilExpiry() const;				// Получить количество дней до истечения срока
	void PrintInfo() const;
	void SetPurchasePrice(double price);

	// Геттеры
	std::string GetName() const;
	double GetWeight() const;
	std::string GetSupplier() const;
	double GetPurchasePrice() const;
	std::time_t GetExpiryDate() const;
	std::time_t GetReceiptDate() const;

	// Сеттеры
	void SetName(const std::string& name);
	void SetWeight(double weight);
	void SetSupplier(const std::string& supplier);
	void SetExpiryDate(std::time_t expiryDate);
	void SetReceiptDate(std::time_t receiptDate);
};

#endif // PRODUCT_HPP


