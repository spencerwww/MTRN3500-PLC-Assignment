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
}

Galil::Galil(EmbeddedFunctions* Funcs, GCStringIn address) {
	// Constructor with pre-initialized EmbeddedFunctions
	Functions = Funcs;
	Functions->GOpen(address, &g);
	ControlParameters[0] = 0.0; // Kp
	ControlParameters[1] = 0.0; // Ki
	ControlParameters[2] = 0.0; // Kd
	setPoint = 0;
}

Galil::Galil(const Galil& other) {
	// Copy constructor implementation
	Functions = new EmbeddedFunctions(*other.Functions);
	Functions->GOpen("192.168.0.120", &g);
	ControlParameters[0] = other.ControlParameters[0];
	ControlParameters[1] = other.ControlParameters[1];
	ControlParameters[2] = other.ControlParameters[2];
	setPoint = other.setPoint;
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
	Functions->GCommand(g, cmd.c_str(), buf, sizeof(buf), nullptr);
}
