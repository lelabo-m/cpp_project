#include "Chipset.hh"

void	Chipset::AskDump(Memory::Memtype type) const
{
	_ram.AskDump(type);
}

IOperand *Chipset::AskOperand()
{
	return (_ram.GetData());
}

Inst *Chipset::AskInstruction()
{
	return (_ram.GetInst());
}

void Chipset::Forward(const std::string &msg, const HardWare::Composant device)
{
	if (device == HardWare::RAM)
	{
		sendToRamString(msg);
	}
	else if (device == HardWare::IO)
	{
		_io.Print(msg);
	}
}

void Chipset::Forward(IOperand *ope, const HardWare::Composant device)
{
	if (device == HardWare::RAM)
	{
		_ram.PutData(ope);
	}
}

bool Chipset::isDigit(const char c) const
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

NumberType Chipset::findNumberType(const std::string &number)
{
	bool dotFound = false;

	if (isDigit(number[0]) == false && number[0] != '-')
		return (UNKNOWN);
	if (number[0] == '-' && number.size() <= 1)
		return (UNKNOWN);

	if (number[0] == '-')
	{
		if (!isDigit(number[1]))
			return (UNKNOWN);
	}
	size_t i;
	for (i = 1; i < number.length(); i++)
	{
		if (number[i] == '.')
		{
			if (dotFound == true || i == (number.length() - 1))
				return (UNKNOWN);
			dotFound = true;
		}
		else
		{
			if (isDigit(number[i]) == false)
				return (UNKNOWN);
		}
	}

	if (dotFound == true)
		return (FLOTTANT);
	return (ENTIER);
}

eOperandType Chipset::checkNumber(const std::string &val)
{
	bool foundValue = false;
	size_t i;
	std::string type_only;

	size_t nb_begin;
	size_t nb_end;

	nb_end = val.find(")");
	nb_begin = val.find("(");
	if (nb_begin == val.npos || nb_end == val.npos || nb_end != (val.size() - 1)
		|| nb_end - nb_begin < 2)
		raiseException(SyntaxException());
	type_only = val.substr(0, nb_begin);

	for (i = 0; i < _valuesVect.size(); i++)
	{
		if (type_only == _valuesVect[i].name)
		{
			foundValue = true;
			break;
		}
	}
	if (foundValue == false)
		raiseException(SyntaxException());

	std::string nb;

	nb = val.substr(nb_begin + 1, (nb_end - nb_begin) - 1);

	NumberType nbType = findNumberType(nb);
	if (nbType == UNKNOWN)
		raiseException(SyntaxException());
	if (nbType == ENTIER)
	{
		if (_valuesVect[i].opeType >= 3)
			raiseException(SyntaxException());
	}
	else
	{
		if (_valuesVect[i].opeType <= 2)
			raiseException(SyntaxException());
	}
	return (_valuesVect[i].opeType);
}

void Chipset::sendToRamString(const std::string &msg)
{
	std::string word;
	std::vector<std::string> words;

	std::stringstream stream(msg);
	while (std::getline(stream, word, ' '))
	{
		if (word.length() > 0)
			words.push_back(word.c_str());
	}

	bool foundInstruction = false;
	size_t i;
	for (i = 0; i < _instVect.size(); i++)
	{
		if (words[0] == _instVect[i].name)
		{
			foundInstruction = true;
			break;
		}
	}

	if (foundInstruction == false)
		raiseException(BadInstException());
	if (_instVect[i].nb_param != (words.size() - 1))
		raiseException(SyntaxException());

	Inst *new_Instruction;
	if (_instVect[i].nb_param >= 1)
	{
		eOperandType type = checkNumber(words[1]);
		size_t nb_end = words[1].find(")");
		size_t nb_begin = words[1].find("(");
		std::string numberOnly = words[1].substr(nb_begin + 1, (nb_end - nb_begin) - 1);

		new_Instruction = new Inst(_instVect[i].inst, numberOnly, type);
	}
	else
	{
		new_Instruction = new Inst(_instVect[i].inst);
	}
	if (new_Instruction->getOpCode() == EXIT)
		_isExited = true;
	_ram.PutInst(new_Instruction);
}

void Chipset::raiseException(const AbstractException& e) const
{
	throw e;
}

void Chipset::parsingRules()
{
	_instVect.push_back(Instruction("push", 1, PUSH));
	_instVect.push_back(Instruction("assert", 1, ASSERT));
	_instVect.push_back(Instruction("pop", 0, POP));
	_instVect.push_back(Instruction("dump", 0, DUMP));
	_instVect.push_back(Instruction("add", 0, ADD));
	_instVect.push_back(Instruction("sub", 0, SUB));
	_instVect.push_back(Instruction("mul", 0, MUL));
	_instVect.push_back(Instruction("div", 0, DIV));
	_instVect.push_back(Instruction("mod", 0, MOD));
	_instVect.push_back(Instruction("print", 0, PRINT));
	_instVect.push_back(Instruction("exit", 0, EXIT));

	_valuesVect.push_back(Value("int8", ENTIER, Int8));
	_valuesVect.push_back(Value("int16", ENTIER, Int16));
	_valuesVect.push_back(Value("int32", ENTIER, Int32));
	_valuesVect.push_back(Value("float", FLOTTANT, Float));
	_valuesVect.push_back(Value("double", FLOTTANT, Double));
}

bool Chipset::isExited() const
{
	return (_isExited);
}

Chipset::Chipset(IInputOutput &io, IRam &ram, ICPU &cpu) : _io(io), _ram(ram), _cpu(cpu)
{
	_isExited = false;
	parsingRules();
}


Chipset::~Chipset()
{
}
