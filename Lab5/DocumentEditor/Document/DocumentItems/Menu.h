#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <stdio.h>
#include <tchar.h>
#include <iostream>

class CMenu
{
public:
	typedef std::function<void(std::istream &args)> Command;
	void AddItem(
		const std::string & shortcut,
		const std::string & description,
		const Command & command
	);
	void Run();
	void ShowInstructions()const;
	void Exit();
private:
	bool ExecuteCommand(const std::string & command);
private:
	struct Item
	{
		Item(
			const std::string & shortcut,
			const std::string & description,
			const Command & command
		);

		std::string shortcut;
		std::string description;
		Command command;
	};

	std::vector<Item> m_items;
	bool m_exit = false;
};