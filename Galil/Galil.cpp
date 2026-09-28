#include "Galil.h"

Galil::Galil() {
	// Default constructor implementation
	// Initialize variables, open Galil connection, and allocate memory
	// Assign default EmbeddedFunctions and Galil address
	Functions = new EmbeddedFunctions();
	Functions->GOpen("192.168.0.120", &g);
	ControlParameters[0] = 0.0; // Kp
	ControlParameters[1] = 0.0; // Ki
	ControlParameters[2] = 0.0; // Kd
	setPoint = 0;
	response = 0;
}

Galil::Galil(EmbeddedFunctions* Funcs, GCStringIn address) {
	// Constructor with pre-initialized EmbeddedFunctions
	Functions = Funcs;
	Functions->GOpen(address, &g);
	ControlParameters[0] = 0.0; // Kp
	ControlParameters[1] = 0.0; // Ki
	ControlParameters[2] = 0.0; // Kd
	setPoint = 0;
	response = 0;
}

Galil::Galil(const Galil& other) {
	// Copy constructor implementation
	Functions = new EmbeddedFunctions(*other.Functions);
	Functions->GOpen("192.168.0.120", &g);
	ControlParameters[0] = other.ControlParameters[0];
	ControlParameters[1] = other.ControlParameters[1];
	ControlParameters[2] = other.ControlParameters[2];
	setPoint = other.setPoint;
	response = other.response;
}

Galil::~Galil() {
	// Destructor implementation
	Functions->GClose(g);
	delete Functions;
}

// DIGITAL OUTPUTS
void Galil::DigitalOutput(uint16_t value) {
	uint16_t high = value >> 8;
	uint16_t low = value & 0x00FF;
	std::string cmd = "OP " + std::to_string(low) + "," + std::to_string(high) + ";";
	char buf[1024];
	response = Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);
}

void Galil::DigitalByteOutput(bool bank, uint8_t value) {
	std::string cmd = "OP ";

	if (bank) {
		cmd += ",";
	}
	
	cmd += std::to_string(value) + ";";

	char buf[1024];
	response = Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);
}

void Galil::DigitalBitOutput(bool val, uint8_t bit) {
	std::string cmd;
	if (val) {
		cmd = "SB ";
	}
	else {
		cmd = "CB ";
	}

	cmd += std::to_string(bit) + ";";

	char buf[1024];
	response = Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);
}

// DIGITAL INPUTS
uint16_t Galil::DigitalInput() {
	uint16_t res = 0;
	for (uint8_t i = 0; i < 16; i++) {
		std::string cmd = "MG @IN[" + std::to_string(i) + "];";
		char buf[1024];
		response = Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);
		uint8_t val = atoi(buf) << i;

		res = res | val;
	}

	return res;
}

uint8_t Galil::DigitalByteInput(bool bank) {
	uint8_t res = 0;
	uint8_t start = bank * 7;
	uint8_t end = (bank + 1) * 8;
	for (uint8_t i = start; i < end; i++) {
		std::string cmd = "MG @IN[" + std::to_string(i) + "];";
		char buf[1024];
		response = Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);
		uint8_t val = atoi(buf) << i;

		res = res | val;
	}

	return res;
}

bool Galil::DigitalBitInput(uint8_t bit) {
	std::string cmd = "MG @IN[" + std::to_string(bit) + "];";
	char buf[1024];
	response = Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);
	
	return atoi(buf);
}

bool Galil::CheckSuccessfulWrite() {
	if (response == 0) {
		return true;
	}
	return false;
}

float Galil::AnalogInput(uint8_t channel) {
	float res = 0.0;
	std::string cmd = "MG @AN[" + std::to_string(channel) + "];";
	char buf[1024];
	response = Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);

	return (float)atof(buf);
}