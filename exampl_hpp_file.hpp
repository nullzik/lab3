class HorseCorral
{
public:
	// публичные: переопределение типом, внутренние нумерованные списки, константы
	using HorsesType = std::vector<Horse>;
	
	enum class Type
	{C:\Users\boyko\Desktop\Учёба\Програмирование\lab3\exampl_hpp_file.hpp
		eOpen = 0,
		eClose = 1,
	};
	
	static const int MAX_HORSE = 15;

private:
	// приватные константы
	static constexpr char* TAG_FOR_LOG = "name";
	
	// приватные переменные
	HorsesType m_horseArray;
	int m_countHorses;
	Type m_currentType;

public:	
	
	// конструткоры и деконструктор
	HorseCorral() = default;	
	~HorseCorral() = default;
	
	// публичные методы
	void AddHorse(Horse& horse);
	
private:
	// приватные методы
	void KillHorse(Horse* horseOld);
};