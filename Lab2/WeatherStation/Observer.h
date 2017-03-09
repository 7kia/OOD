#pragma once

#include <set>
#include <functional>
#include <map>
#include <unordered_map>
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
	typedef std::set<std::pair<unsigned int, std::set<ObserverType *>>> ObserverSet;
	void RegisterObserver(ObserverType & observer, unsigned int priority = 0) override
	{
		auto iter = std::find_if(m_observers.begin(), m_observers.end(), [&](auto & pair) {
			return pair.second == &observer;
		});
		if (iter != m_observers.end())
		{
			return;
		}
		
		ObserverSet::iterator priorityIter = m_observers.end();
		for (ObserverSet::iterator iter = m_observers.begin(); iter != m_observers.end(); ++iter)
		{
			if (iter->first == priority)
			{
				auto set = iter->second;
				set.emplace(&observer);
				return;
			}
		}

		auto addSet = std::set<ObserverType *>();
		addSet.emplace(&observer);
		m_observers.emplace(std::pair<unsigned int, std::set<ObserverType *>>( priority , addSet ));		
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		auto copyObservers = m_observers;
		for (auto iter = copyObservers.begin(); iter != copyObservers.end(); ++iter)
		{
			std::cout << "Priority = " << iter->first << std::endl;

			for (auto & observer : iter->second)
			{
				observer->Update(data);
			}		
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto it = std::find_if(m_observers.begin(), m_observers.end(), [&](auto & pair) {
			return pair.second == &observer;
		});
		if (it != m_observers.end())
		{
			m_observers.erase(it);
		}		
	}
protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

//private:// For test
	ObserverSet m_observers;
};
