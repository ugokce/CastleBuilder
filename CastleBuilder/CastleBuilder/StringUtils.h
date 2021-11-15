#pragma once

#include <string>

namespace Utils
{
	static int TryParseToInt(const std::string& text)
	{
		try
		{
			return std::stoi(text);
		}
		catch (const std::exception& e)
		{
			std::printf("Integer Parse Error!");
		}
	}

	static int TryParseToFloat(const std::string& text)
	{
		try
		{
			return std::stof(text);
		}
		catch (const std::exception& e)
		{
			std::printf("Float Parse Error!");
		}
	}
}
