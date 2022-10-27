#pragma once

#include <functional>
#include <vector>

namespace Shard::ShardEvents
{
	//Add Listener macro...

	//Subscribes _function to the Event.
	#define ADD_LISTENER(TSubscriber, ListenerMethod) AddListener(this, &TSubscriber::ListenerMethod)

	template<class TArgs>
	using Method = std::function<void(TArgs)>;

	/// <summary>
	/// Holds a method, that can be invoked by an Event, and an index.
	/// The only purpose of the index is to be compared.
	/// Index -1 indicates an uninitialized Listener.
	/// in Event class methods like: RemoveListener() or HasListener().
	/// </summary>
	template<class TArgs>
	struct Listener
	{
		int index = -1;
		Method<TArgs> method;

		Listener(const int _index, Method<TArgs> _method)
			: index(_index), method(_method) {}

		bool operator==(const Listener& other)
		{
			return index == other.index;
		}
	};

	/// <summary>
	/// Events enable a class to notify other classes when something of interest occurs.
	/// The class that sends(or raises) the Event is called the Publisher and the classes that receive(or handle) the
	/// Event are called Subscribers. The Publisher notifies through calling Subscriber methods called Listeners.
	/// So the Event class just stores and manages a vector of Listeners (class methods).
	/// It ONLY supports class member functions.
	/// </summary>
	template<typename TArgs>
	class Event
	{
	private:
		std::vector<Listener<TArgs>> m_Listeners;
		int m_Count = 0;

		template<typename TArgs>
		using ListenerIterator = typename std::vector<Listener<TArgs>>::iterator;

		//Check if the given Listener is subscribed.
		bool HasListener(Listener<TArgs> _listener, ListenerIterator<TArgs>& _it)
		{
			_it = std::find_if(m_Listeners.begin(), m_Listeners.end(),
				[_listener](Listener<TArgs>& i_listener) { return _listener == i_listener; });

			if (_it == m_Listeners.end())
				return false;

			return true;
		}

	public:
		Event() = default;
		Event(Event& other) = delete;
		Event(Event&& other) = delete;
		~Event() { RemoveAllListeners(); }

		//Subscribes _function to the Event.
		template<class TSubscriber>
		Listener<TArgs> AddListener(TSubscriber* _subscriber, void (TSubscriber::* _function)(TArgs))
		{
			Listener<TArgs> listener = m_Listeners.emplace_back(m_Count, std::bind(_function, _subscriber, std::placeholders::_1));
			m_Count++;
			return listener;
		}

		//Check if the given Listener is subscribed.
		bool HasListener(Listener<TArgs> _listener)
		{
			ListenerIterator<TArgs> it;
			return HasListener(_listener, it);
		}

		//Unsubscribes _function from the Event.
		void RemoveListener(Listener<TArgs> _listener)
		{
			if (ListenerIterator<TArgs> it; HasListener(_listener, it))
			{
				m_Listeners.erase(it);
				return;
			}
		}

		//Removes all the Event subscriptions.
		void RemoveAllListeners() { m_Listeners.clear(); }

		//Fires the event and dispatches a TArgs instance.
		void Invoke(TArgs _args)
		{
			for (const Listener<TArgs>& listener : m_Listeners)
				listener.method(_args);
		}
	};
}