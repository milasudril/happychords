//@	{"targets":[{"name":"tableload.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_TABLELOAD_HPP
#define HAPPYCHORDS_TABLELOAD_HPP

#include <vector>
#include <string>

namespace Happychords
	{
	template<class File,class Header,class Container>
	void tableLoad(File&& src,Header& header,Container& data)
		{
		int ch_in=0;
		enum class State:int{HEADER_KEY,HEADER_VALUE,HEADER_FIELDS,COMMENT,DATA,RECORD};
		auto state_current=State::HEADER_KEY;
		auto state_old=state_current;
		std::string header_key;
		std::string header_value;
		std::vector<std::string> fields;
		typename Container::value_type rec_current;
		size_t field_count=0;
		while((ch_in=getc(src))!=EOF)
			{
			switch(state_current)
				{
				case State::HEADER_KEY:
					if(ch_in>=0 && ch_in<=' ')
						{break;}
					switch(ch_in)
						{
						case '#':
							state_old=state_current;
							state_current=State::COMMENT;
							break;
						case ':':
							if(header_key=="data")
								{state_current=State::DATA;}
							else
							if(header_key=="fields")
								{state_current=State::HEADER_FIELDS;}
							else
								{state_current=State::HEADER_VALUE;}
							break;
						default:
							header_key+=ch_in;
						}
					break;

				case State::HEADER_VALUE:
					switch(ch_in)
						{
						case '#':
							state_old=State::HEADER_KEY;
							state_current=State::COMMENT;
							header.valueSet(header_key,header_value);
							header_key.clear();
							header_value.clear();
							break;
						case '\r':
							break;
						case '\n':
							state_current=State::HEADER_KEY;
							header.valueSet(header_key,header_value);
							header_key.clear();
							header_value.clear();
							break;
						
						default:
							if(!(ch_in>=0 && ch_in<=' '))
								{header_value+=ch_in;}
						}
					break;

				case State::HEADER_FIELDS:
					header_key.clear();
					switch(ch_in)
						{
						case '#':
							state_old=state_current;
							state_current=State::COMMENT;
							break;
						case '\n':
						case '\r':
							fields.push_back(header_value);
							state_current=State::HEADER_KEY;
							break;
						case ';':
							fields.push_back(header_value);
							header_value.clear();
							break;
						default:
							if(!(ch_in>=0 && ch_in<=' '))
								{header_value+=ch_in;}
						}
					break;

				case State::DATA:
					switch(ch_in)
						{
						case '\r':
							break;
						case '\n':
							if(fields.size()==0)
								{throw "Table contains no field header";}
							state_current=State::RECORD;
							header_value.clear();
							header_key.clear();
							break;
						default:
							throw "Expected newline after data marker";
						}
					break;

				case State::COMMENT:
					switch(ch_in)
						{
						  case '\n':
						  case '\r':
							state_current=state_old;
							break;
						}
					break;

				case State::RECORD:
					if(field_count==fields.size())
						{throw "To many fields in table";}
					switch(ch_in)
						{
						case '#':
							rec_current.valueSet(fields[field_count],header_value);
							if(!rec_current.empty())
								{data.push_back(rec_current);}
							header_value.clear();
							field_count=0;
							state_old=state_current;
							state_current=State::COMMENT;
							break;
						case '\t':
							rec_current.valueSet(fields[field_count],header_value);
							header_value.clear();
							++field_count;
							break;
						case '\r':
							break;
						case '\n':
							rec_current.valueSet(fields[field_count],header_value);
							if(!rec_current.empty())
								{data.push_back(rec_current);}
							header_value.clear();
							field_count=0;
							break;
						default:
							header_value+=ch_in;
						}
					break;
				}
			}
		if(field_count!=0)
			{
			rec_current.valueSet(fields[field_count],header_value);
			data.push_back(rec_current);
			}
		}
	}
#endif
