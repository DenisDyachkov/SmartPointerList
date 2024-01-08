#pragma once
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template<typename T>
class Node;

template<typename T>
class List;

/**
* @brief Опрератор сдвига.
* @param os Поток вывода.
* @param list Лист для вывода.
* @return Изменённый поток вывода.
*/
template<typename T>
std::ostream& operator<< (std::ostream& os, const List<T>& list);

/**
@brief Перегрузка оператора равно
@param rha Первый аргумент для сравнения
@param lha Второй аргумент для сравнения
@return false если равны и true если н ет
*/
template<typename T>
bool operator==(const List<T>& rha, const List<T>& lha) noexcept;

/**
@brief Перегрузка оператора не равно
@param rha Первый аргумент для сравнения
@param lha Второй аргумент для сравнения
@return true если равны и false если нет
*/
template<typename T>
bool operator!=(const List<T>& rha, const List<T>& lha) noexcept;


/*
@brief Класс, описывающий линейный односвязный список
*/
template<typename T>
class List
{
public:

	/*
	* @brief  Создает новый "пустой" объект класса List
	*/
	List();
	
	/*
	* @brief Деструктор, чистит память
	*/
	~List();

	/*
	* @brief  Создает новый объект класса List по данным
	* @param list Данные листа
	*/
	List(const std::initializer_list<T> list);
	
	/*
	* @brief Очистка списка
	*/
	void clear();

	/*
	* @brief Функция для преобразования списка в строку
	* @return Строка, созданная по списку
	*/
	std::string to_string() const noexcept;
	
	/*
	* @brief Добавляет элемент в начало списка
	* @param value Значение
	*/
	void push(const T& value);
	
	/*
	* @brief Убирает элемент из начала списка
	*/
	void pop();
	
	/*
	* @brief Проверяет наличие элемента в списке
	* @return true - есть, иначе false
	*/
	bool find(const T& item);

	/*
	* @brief Проверяет наличие элементов в списке
	* @return true - есть элементы, иначе false
	*/
	bool has_elements() const noexcept;
	
	/*
	* @brief Проверяет отсутствие элементов в списке
	* @return true - нет элементов, иначе false
	*/
	bool is_empty() const noexcept;

	/*
	* @brief Перегрузка оператора копирования
	* @param list Список для копирования
	* @return Скопированный объект типа List
	*/
	List<T>& operator=(const List<T>& list) = default;

	/*
	* @brief Перегрузка оператора перемещения
	* @param list Список для перемещения
	* @return Перемещенный объект типа List
	*/
	List<T>& operator=(List<T>&& list) = default;

	/*
	* @brief Конструктор копирования
	* @param list Список для копирования
	*/
	List(const List<T>& list) = default;

	/*
	* @brief Конструктор перемещения
	* @param list Список для перемещения
	*/
	List(List<T>&& list) = default;

	/*
	* @brief Получение значения из головы списка
	*/
	T peek();

private:
	std::unique_ptr<Node<T>> head;

};


template<typename T>
inline List<T>::List()
	:head(nullptr)
{
}

template<typename T>
inline List<T>::~List()
{
	while (head)
	{
		auto next = std::move(head->next_node);
		head = std::move(next);
	}
}

template<typename T>
inline List<T>::List(const std::initializer_list<T> list)
	: head(nullptr)
{
	std::vector<int> temp{};
	for (auto item : list)
	{
		temp.insert(temp.begin(), item);
	}
	for (size_t i = 0; i < temp.size(); i++)
	{
		this->push(temp[i]);
	}
}

template<typename T>
inline void List<T>::clear()
{
	this->head = nullptr;
}


template<typename T>
inline std::string List<T>::to_string() const noexcept
{
	std::stringstream result_string;
	result_string << "[ ";
	auto curr = this->head.get();
	while (curr != nullptr)
	{
		result_string << curr->value << " ";
		curr = curr->next_node.get();
	}
	result_string << "]";
	return result_string.str();
}

template<typename T>
inline void List<T>::push(const T& value)
{
	std::unique_ptr<Node<T>> element(new Node<T>(value));
	if (this->has_elements())
	{
		element->next_node = std::move(this->head);
		this->head = std::move(element);
	}
	else
	{
		this->head = std::move(element);
	}

}

template<typename T>
inline void List<T>::pop()
{
	if (this->has_elements())
	{
		std::unique_ptr<Node<T>> temp = std::move(head);
		this->head = std::move(temp->next_node);
	}
}

template<typename T>
inline bool List<T>::find(const T& item)
{
	auto curr = this->head.get();
	while (curr != nullptr)
	{
		if (curr->value == item) 
		{
			return true;
		}
		curr = curr->next_node.get();
	}
	return false;
}

template<typename T>
inline bool List<T>::has_elements() const noexcept
{
	return !(this->is_empty());
}

template<typename T>
inline bool List<T>::is_empty() const noexcept
{
	return this->head == nullptr;
}

template<typename T>
inline T List<T>::peek()
{
	return this->head.get()->value;
}

/*
* @brief Класс, описывающий элемент списка
*/
template<typename T>
class Node
{
public:
	/*
	@brief  Инициализирует новый экземпляр класса Node
	@param value Значение элемента
	@param next_node Следующий элемент
	*/
	Node(T value);

	std::unique_ptr<Node<T>> next_node;

	T value;
};

template<typename T>
inline Node<T>::Node(T value)
	:value(value), next_node(nullptr)
{
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
	return os << list.to_string();
}

template<typename T>
inline bool operator==(const List<T>& rha, const List<T>& lha) noexcept
{
	return rha.to_string() == lha.to_string();
}

template<typename T>
inline bool operator!=(const List<T>& rha, const List<T>& lha) noexcept
{
	return !(rha.to_string() == lha.to_string());
}
