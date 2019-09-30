#pragma once

#include "WindowsRSI.h"

class SoftRenderer
{
public:
	enum class RenderMode
	{
		TWO,
		THREE_PERSP
	};

	SoftRenderer(SoftRenderer const&) = delete;
	void operator=(SoftRenderer const&) = delete;
	static SoftRenderer& Inst()
	{
		static SoftRenderer instance;
		return instance;
	}

public:
	void SetRenderMode(RenderMode InRenderMode) { CurrentRenderMode = InRenderMode; }
	RenderMode GetRenderMode() const { return CurrentRenderMode; }
	void Initialize();
	void Shutdown();
	void Update();
	//bool isPointInTriangle(Vector2 a, Vector2 b, Vector2 c, Vector2 p);

private:
	SoftRenderer() { }
	~SoftRenderer() { Shutdown(); }

	RenderMode CurrentRenderMode = RenderMode::TWO;

	WindowsRSI* RSI = nullptr;

	UINT32 screenSize;
};
