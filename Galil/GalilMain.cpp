#include "Galil.h"
#include <chrono>
#using <System.dll>

using namespace System;
using namespace System::Threading;

int main(void) {
	EmbeddedFunctions funcs;
	Galil myGalil(&funcs, "192.168.0.120 -d");

}