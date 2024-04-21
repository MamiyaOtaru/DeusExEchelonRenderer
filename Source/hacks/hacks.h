#pragma once

extern void InstallFSceneNodeHacks();
extern void InstallFSpanBufferHacks();
extern void InstallURenderHacks();
extern void InstallUMeshHacks();
extern void InstallUGameEngineHacks();
extern void InstallFDynamicItemFilterHacks();
extern void InstallULightManagerHacks();
extern void InstallThreadAffinityHacks();
extern void InstallBytePatches();
extern void InstallRTXConfigPatches();

extern void UninstallFSceneNodeHacks();
extern void UninstallFSpanBufferHacks();
extern void UninstallURenderHacks();
extern void UninstallUMeshHacks();
extern void UninstallUGameEngineHacks();
extern void UninstallULightManagerHacks();
extern void UninstallFDynamicItemFilterHacks();
extern void UninstallThreadAffinityHacks();
extern void UninstallBytePatches();
extern void UninstallRTXConfigPatches();
///

template<typename TFuncPtr>
struct HookableFunction
{
  union
  {
    TFuncPtr funcPtr;
    uint64_t func64;
  };

  HookableFunction(const TFuncPtr& pRH)
  {
    funcPtr = pRH;
    cpy.funcPtr = pRH;
  }

  HookableFunction() = delete;
  HookableFunction(const HookableFunction&) = delete;
  HookableFunction(HookableFunction&&) = delete;
  void Restore() { funcPtr = cpy.funcPtr; }
  operator TFuncPtr() { return funcPtr; }
  HookableFunction<TFuncPtr>& operator=(const TFuncPtr& pRH) { funcPtr = pRH; cpy.funcPtr = pRH; return *this; }
  HookableFunction<TFuncPtr>& operator=(const void* pRH) { func64 = reinterpret_cast<uint64_t>(pRH); cpy.func64 = func64; return *this; }
private:
  struct
  {
    union
    {
      TFuncPtr funcPtr;
      uint64_t func64;
    };
  } cpy;
};