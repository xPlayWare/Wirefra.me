#pragma once
#include "INetChannelInfo.h"
#include "player_info_t.h"

namespace SDK
{
	class NetChannel;
	class IEngine
	{
	public:
		int GetPlayerForUserID(int id)
		{
			typedef int(__thiscall* Fn)(void*, int);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 9))(this, id);
		}
		INetChannelInfo* GetNetChannelInfo(void)
		{
			typedef INetChannelInfo*(__thiscall* Fn)(void*);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 78))(this);
		}
		template< typename Function > Function call_vfunc(PVOID Base, DWORD Index)
		{
			PDWORD* VTablePointer = (PDWORD*)Base;
			PDWORD VTableFunctionBase = *VTablePointer;
			DWORD dwAddress = VTableFunctionBase[Index];
			return (Function)(dwAddress);
		}
		bool GetPlayerInfo(int Index, player_info_t* PlayerInfo)
		{
			typedef bool(__thiscall* Fn)(void*, int, player_info_t*);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 8))(this, Index, PlayerInfo);
		}

		void GetScreenSize(int& Width, int& Height)
		{
			typedef void(__thiscall* Fn)(void*, int&, int&);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 5))(this, Width, Height);
		}

		int GetLocalPlayer()
		{
			typedef int(__thiscall* Fn)(void*);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 12))(this);
		}

		void ClientCmd(const char* Command)
		{
			typedef void(__thiscall* Fn)(void*, const char*);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 108))(this, Command);
		}

		void SetViewAngles(Vector& Angles)
		{
			typedef void(__thiscall* Fn)(void*, Vector&);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 19))(this, Angles);
		}

		void GetViewAngles(Vector& angle)
		{
			typedef void(__thiscall* Fn)(void*, Vector&);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 18))(this, angle);
		}

		void ClientCmd_Unrestricted(char  const* cmd)
		{
			typedef void(__thiscall* oClientCmdUnres)(PVOID, const char*, char);
			return call_vfunc<oClientCmdUnres>(this, 114)(this, cmd, 0);
		}
		const matrix3x4_t& GetMatrix()
		{
			typedef const matrix3x4_t& (__thiscall* Fn)(void*);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 37))(this);
		}
		bool IsInGame()
		{
			typedef bool(__thiscall* Fn)(void*);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 26))(this);
		}

		bool IsConnected()
		{
			typedef bool(__thiscall* Fn)(void*);
			return ((Fn)VMT::VMTHookManager::GetFunction<Fn>(this, 27))(this);
		}
		NetChannel* GetNetChannel()
		{
			auto client_state = *reinterpret_cast<uintptr_t*>(uintptr_t(GetModuleHandle("engine.dll")) + 0x57F84C);
			if (!client_state)
				return nullptr;

			auto net_channel = *reinterpret_cast<uintptr_t*>(client_state + 0x9C);
			return reinterpret_cast<NetChannel*>(net_channel);
		}
	};
}