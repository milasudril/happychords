//@ {
//@	 "targets":[{"name":"gatesequence.o","type":"object"}]
//@	}

#include "gatesequence.hpp"
#include "tableload.hpp"
#include "rangereader.hpp"

using namespace Happychords;

void GateSequence::load(FILE* src)
	{
	tableLoad(src,*this,m_events);
	}


void GateSequence::load(const int8_t* input_begin,const int8_t* input_end)
	{
	tableLoad(RangeReader<const int8_t*>(input_begin,input_end),*this,m_events);
	}

void GateSequence::valueSet(const std::string& key,const std::string& value)
	{
	if(key=="tpqn")
		{m_tpqn=stol(value);}
	if(key=="name")
		{m_name=value;}
	}

void GateSequence::from_string(const std::string& value,GateSequence::Event::Type& type)
	{
	if(value=="")
		{type=GateSequence::Event::Type::NO_OPERATION;return;}
	if(value=="note on")
		{type=GateSequence::Event::Type::NOTE_ON;return;}
	if(value=="note off")
		{type=GateSequence::Event::Type::NOTE_OFF;return;}
	if(value=="loop")
		{type=GateSequence::Event::Type::LOOP;return;}
	throw "Unknown event type";
	}

void GateSequence::Event::valueSet(const std::string& key,const std::string& value)
	{
	if(key=="time")
		{
		time=value==""?size_t(-1):stol(value);
		return;
		}
	if(key=="type")
		{
		from_string(value,type);
		return;
		}
	throw "Unkown field";
	}
