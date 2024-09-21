#include "BaseCommand.h"

using std::count;

BaseCommand::BaseCommand(std::wstring name, uint32_t id, vector<wstring> trigger) {
	this->name = name;
	this->trigger = trigger;
	this->id = id;

}


wstring BaseCommand::getName() {
	return this->name;
}

uint32_t BaseCommand::getId() {
	return this->id;
}

BOOL BaseCommand::isInTrigger(wstring trigger) {
	return count(this->trigger.begin(), this->trigger.end(), trigger) != 0;
}