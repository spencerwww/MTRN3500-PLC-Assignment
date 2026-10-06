#include "EmbeddedFunctions.h"
#using <System.dll>
#include <cstdint>


EmbeddedFunctions::EmbeddedFunctions() {
	GalilMngHndl, GalilStream = nullptr;
	Port = 0;
	SendData = gcnew array<uint8_t>(64);
	RecvData = gcnew array<uint8_t>(2048);
}

EmbeddedFunctions::~EmbeddedFunctions() {
	GClose();
}

void EmbeddedFunctions::GOpen(String^ address, const int port) {
	IPAddress = address;
	Port = port;
	GalilMngHndl = gcnew TcpClient(IPAddress, Port);
	GalilMngHndl->SendBufferSize = 64;
	GalilMngHndl->ReceiveBufferSize = 2048;
	GalilMngHndl->SendTimeout = 500;
	GalilMngHndl->ReceiveTimeout = 500;
	GalilMngHndl->NoDelay = true;
	GalilStream = GalilMngHndl->GetStream();
}

void EmbeddedFunctions::GClose() {
	GalilStream->Close();
	GalilMngHndl->Close();
	GalilMngHndl, GalilStream = nullptr;
}

String^ EmbeddedFunctions::GCommand(String^ command) {
	Command = command + "\r";
	SendData = System::Text::Encoding::ASCII->GetBytes(Command);
	GalilStream->Write(SendData, 0, SendData->Length);
	System::Threading::Thread::Sleep(10);

	GalilStream->Read(RecvData, 0, RecvData->Length);
	System::Threading::Thread::Sleep(25);
	Response = System::Text::Encoding::ASCII->GetString(RecvData);
	return Response;
}