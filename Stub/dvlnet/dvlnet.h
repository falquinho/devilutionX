#pragma once
#include "sodium.h"
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <asio/ts/io_context.hpp>
#include <asio/ts/net.hpp>

namespace dvlnet {
	class dvlnet {
	public:
		virtual int create(std::string addrstr, std::string passwd) = 0;
		virtual int join(std::string addrstr, std::string passwd) = 0;
		virtual bool SNetReceiveMessage(int *sender, char **data, int *size) = 0;
		virtual bool SNetSendMessage(int dest, void *data, unsigned int size) = 0;
		virtual bool SNetReceiveTurns(char **data, unsigned int *size, DWORD *status) = 0;
		virtual bool SNetSendTurn(char *data, unsigned int size) = 0;
		virtual int SNetGetProviderCaps(struct _SNETCAPS *caps) = 0;
		virtual void *SNetRegisterEventHandler(event_type evtype, void(__stdcall *func)(struct _SNETEVENT *)) = 0;
		virtual void *SNetUnregisterEventHandler(event_type evtype, void(__stdcall *func)(struct _SNETEVENT *)) = 0;
		virtual ~dvlnet() {}
	};
}

#include "dvlnet/packet.h"
#include "dvlnet/loopback.h"
#include "dvlnet/base.h"
#include "dvlnet/udp_p2p.h"