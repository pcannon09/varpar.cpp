#include <filesystem>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#include "../inc/varparse.cpp/VP_Parse.hpp"

namespace fs = std::filesystem;

#define __VP_ERROR_THROW_DEFAULT_MSG \
	std::string("Parser(" + this->id + "): ")

namespace vp
{
	Parser::Parser(const std::string &_id, const std::string &_file, const std::string &_extension)
		: id(_id), fpath(_file), extension(_extension)
	{
		if (!fs::exists(_file))
		{
			const std::string &error = __VP_ERROR_THROW_DEFAULT_MSG + _file + " : Does not exist";

			std::cerr << error << "\n";

			this->status.error = error;
			this->status.constructed = false;

			return;
		}

		const std::string &extensionSubstr = this->fpath.substr(fpath.size() - _extension.size());

		if (extensionSubstr != _extension)
		{
			const std::string &error = __VP_ERROR_THROW_DEFAULT_MSG + _file + " : Does not have the required file extension, required is: " + _extension;

			std::cerr << error << "\n";

			this->status.error = error;
			this->status.constructed = false;
			
			return;
		}

		this->status.constructed = true;
	}

	ParserReturn Parser::parse()
	{
		this->parseRet = this->__parse();

		return this->parseRet;
	}

	ParserReturn Parser::__parse()
	{
		std::vector<std::string> output;

		std::map<std::string, std::string> conf;
		std::ifstream file(this->fpath);
		std::string line;

		ssize_t lineNum = 0;

		while (std::getline(file, line))
		{
			lineNum++;

			// Skip if comment or empty line
			if (line.empty() || line[0] == ';') continue;

			std::istringstream iss(line);
			std::string key, val;

			if (std::getline(iss, key, '=') && std::getline(iss, val))
			{
            	key.erase(0, key.find_first_not_of(" \t"));
            	key.erase(key.find_last_not_of(" \t") + 1);

            	val.erase(0, val.find_first_not_of(" \t"));
            	val.erase(val.find_last_not_of(" \t") + 1);

				if (conf.find(key) != conf.end())
				{
					output.emplace_back(std::string("ERR: LINE: " + std::to_string(lineNum)));
					output.emplace_back("Duplicate member : " + line);

					return { conf, output, false };
				}

				conf[key] = val;
			}

			else
			{
				output.emplace_back(std::string("ERR: LINE: " + std::to_string(lineNum)));
				output.emplace_back(std::string("No equality operator to set value for `" + line + "`"));

				return { conf, output, false };
			}
		}

		return { conf, output, true };
	}

	std::string Parser::getVal(const std::string &_key) const
	{
		if (this->parseRet.config.find(_key) != this->parseRet.config.end())
			return this->parseRet.config.at(_key);

		return "";
	}

	ParserStatus Parser::checkStatus() const
	{ return this->status; }

	std::string Parser::getID() const
	{ return this->id; }
}
