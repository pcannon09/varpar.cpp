#pragma once

#include "VPpredefines.hpp"

#if  __cplusplus >= VP_DEFAULT_CPP_STD 
#include <string>
#include <vector>
#include <map>

namespace vp
{
	/**
	 * @brief Set the error and if the `Parser` class was constructed
	 */
	typedef struct ParserStatus
	{
		std::string error;

		bool constructed = false;
	} ParserStatus;

	/**
	 * @brief Returned parser information
	 * This includes the configuration, output and success of the `Parser`
	 */
	typedef struct ParserReturn
	{
		std::map<std::string, std::string> config;

		std::vector<std::string> output;

		bool success = false;
	} ParserReturn;

	class Parser
	{
	private:
		std::string id;
		std::string fpath;

 		ParserStatus status;
		ParserReturn parseRet;

		std::string extension;

	protected:
		/**
		 * @brief Private member of the parse function
		 * @return ParserReturn Parsed information
		 */
		virtual ParserReturn __parse();

	public:
		/**
		 * @brief Create the object, set errors if there are and set some configuration from the parameters
		 * @param _id Set the ID of the object
		 * @param _file Set the path of the file
		 * @param _extension Set the file extension
		 */
		Parser(const std::string &_id, const std::string &_file, const std::string &_extension = ".varpar");

		/**
		 * @brief Deconstructor
		 */
		~Parser();

		/**
		 * @brief Public API wrapper for `Parser::__parse()` function
		 * @return ParserReturn Parsed information
		 */
		ParserReturn parse();

		/**
		 * @brief Get value of _key
		 * @param _key Key value to find
		 * @return std::string Return the value
		 */
		std::string getVal(const std::string &_key) const;

		/**
		 * @brief Get the constructed starts
		 * @return ParserStatus
		 */
		ParserStatus checkStatus() const;

		/**
		 * @brief Get the current object ID
		 * @return std::string Current object ID
		 */
		std::string getID() const;
	};
}
#else
# 	error "Use C++17 as the minimum standard"
#endif // VP_DEFAULT_CPP_STD >= __cplusplus

