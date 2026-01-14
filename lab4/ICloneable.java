// Интерфейс для клонирования объектов
// Определяет методы для поверхностного и глубокого клонирования
public interface ICloneable<T> {
    // Поверхностное клонирование (shallow copy)
    T cloneShallow();
    
    // Глубокое клонирование (deep copy)
    T cloneDeep();
}

