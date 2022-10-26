#pragma once

#ifdef SHARD_PLATFORM_WINDOWS
#ifdef SHARD_BUILD_DLL
#define SHARD_API __declspec(dllexport)
#else
#define SHARD_API __declspec(dllimport)
#endif
#else
#error SHARD only supports Windows!
#endif