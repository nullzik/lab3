#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <string>
#include <vector>
#include <memory>
#include "product.hpp"

class Inventory
{
public:
	using ProductsType = std::vector<std::shared_ptr<Product>>;

private:
	std::string m_warehouseName;
	ProductsType m_products;

public:
	// Конструкторы и деструктор
	Inventory();
	Inventory(const std::string& warehouseName);
	~Inventory() = default;

	// Публичные методы
	void AddProduct(std::shared_ptr<Product> product);			// Добавить продукт на склад
	void AddProduct(const Product& product);			// Добавить продукт на склад (копия)
	bool RemoveProduct(const std::string& productName);	// Удалить продукт со склада по имени
	std::shared_ptr<Product> FindProduct(const std::string& productName);	// Найти продукт по имени (возвращает указатель)
	void PrintExpiryDates() const;						// Вывести информацию о сроках годности всех продуктов
	void PrintInventoryReport() const;					// Вывести отчет о хранимых продуктах

	// Геттеры
	std::string GetWarehouseName() const;
	ProductsType GetProducts() const;
	int GetProductsCount() const;

	// Сеттеры
	void SetWarehouseName(const std::string& warehouseName);
};

#endif // INVENTORY_HPP


