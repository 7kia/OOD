#pragma once

#include <set>
#include <functional>
#include <map>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, unsigned int priority = 0) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, unsigned int priority = 0) override
	{
		for (auto iter = m_priority.begin(); iter != m_priority.end(); ++iter)
		{
			if (iter->second == &observer)
			{
				break;
			}
		}
		m_observers.emplace(&observer);
		m_priority.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto iter = m_priority.rbegin(); iter != m_priority.rend(); ++iter)
		{
			std::cout << "Priority = " << iter->first << std::endl;
			iter->second->Update(data);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto iterObserver = std::find(m_observers.begin(), m_observers.end(), &observer);

		if (iterObserver != m_observers.end())
		{
			m_observers.erase(iterObserver);
			for (auto iter = m_priority.begin(); iter != m_priority.end(); ++iter)
			{
				if (iter->second == &observer)
				{
					m_priority.erase(iter);
					break;
				}
			}
		}
		
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

//private:// For test
	std::set<ObserverType *> m_observers;
	std::multimap<unsigned int, ObserverType *> m_priority;
};
