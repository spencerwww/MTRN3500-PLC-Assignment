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