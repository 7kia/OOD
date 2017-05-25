#pragma once
#include <vector>
#include "Signal.h"

struct ScopedConnectionsStorage
{
	ScopedConnectionsStorage& operator+=(const signals::Connection & conn)
	{
		m_items.emplace_back(conn);
		return *this;
	}
	ScopedConnectionsStorage& operator+=(signals::Connection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator+=(signals::ScopedConnection && conn)
	{
		m_items.emplace_back(std::move(conn));
		return *this;
	}
	ScopedConnectionsStorage& operator += (std::initializer_list<signals::Connection> const & connections)
	{
		for (const auto & con : connections)
		{
			*this += con;
		}
		return *this;
	}
private:
	std::vector<signals::ScopedConnection> m_items;
};