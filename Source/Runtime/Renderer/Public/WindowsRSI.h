
#pragma once

#include <windows.h>
#include "WindowsGDI.h"
#include "RenderingSoftwareInterface.h"

class WindowsRSI : public WindowsGDI, public RenderingSoftwareInterface
{
public:
	
	const int *IndexBuffer = nullptr;
	VertexData *VertexBuffer = nullptr;

	WindowsRSI() { };
	~WindowsRSI() { Shutdown(); }


public:
	virtual void Init(const bool InbSRGBColorSpace = true) override;
	virtual void Shutdown() override;

	virtual bool IsIntialized() const override { return bGDIInitialized; }
	virtual bool IsSRGBSpace() const override { return bSRGBColorSpace; }

	virtual void Clear(const LinearColor& InClearColor) override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;
	virtual void DrawScreenPoint(const ScreenPoint& InScreenPos, const LinearColor& InColor) override;


	virtual void SetIndexBuffer(const int *InIndexData) override;
	virtual void SetVertexBuffer(VertexData *InvertexData) override;
	virtual void DrawPrimitive(UINT InVertexSize, UINT InIndexSize) override;

	virtual void DrawVerticalLine(int InX, const LinearColor & InColor) override;
	virtual void DrawHorizontalLine(int InY, const LinearColor & InColor) override;


private:
};