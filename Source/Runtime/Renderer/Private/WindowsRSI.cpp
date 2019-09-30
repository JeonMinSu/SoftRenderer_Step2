#include "Precompiled.h"
#include "WindowsRSI.h"
#include "TriangleRasterizer.h"


void WindowsRSI::Init(const bool InbSRGBColorSpace)
{
	InitializeGDI(DisplaySetting::Inst().GetSize(), InbSRGBColorSpace);
}

void WindowsRSI::Shutdown()
{
	ReleaseGDI();
}

void WindowsRSI::Clear(const LinearColor & InClearColor)
{
	SetColor(InClearColor);
	FillBuffer();

	ClearDepthBuffer();
}

void WindowsRSI::BeginFrame()
{

}

void WindowsRSI::EndFrame()
{
	SwapBuffer();
}

void WindowsRSI::DrawScreenPoint(const ScreenPoint & InPoint, const LinearColor & InColor)
{
	PutPixel(InPoint, InColor.ToColor32());
}

void WindowsRSI::SetIndexBuffer(const int *InIndexData)
{
	IndexBuffer = InIndexData;

}

void WindowsRSI::SetVertexBuffer(VertexData *InvertexData)
{
	VertexBuffer = InvertexData;
}

void WindowsRSI::DrawPrimitive(UINT InVertexSize, UINT InIndexSize)
{

	if (VertexBuffer == nullptr || IndexBuffer == nullptr)
	{
		return;
	}

	UINT triangleCount = (int)(InIndexSize / 3);
	for (UINT ti = 0; ti < triangleCount; ti++)
	{
		TriangleRasterizer t(
			VertexBuffer[IndexBuffer[ti * 3]],
			VertexBuffer[IndexBuffer[ti * 3 + 1]],
			VertexBuffer[IndexBuffer[ti * 3 + 2]]);

		//t.RecalcBounds();

		for (int x = t.TopLeft.X; x < t.BottomRight.X; ++x)
		{
			for (int y = t.TopLeft.Y; y < t.BottomRight.Y; ++y)
			{
				ScreenPoint currentPixel(x, y);
				Vector2 currentPos = currentPixel.ToVector2();
				if (t.IsInside(currentPos))
				{
					PutPixel(currentPixel, t.RainbowColor(currentPos));
				}
			}
		}

	}

}

void WindowsRSI::DrawVerticalLine(int InX, const LinearColor & InColor)
{
/*
	X = InPos.X + ((ScreenSize.X - 1) * 0.5);
	Y = ((ScreenSize.Y - 1) * 0.5) - InPos.Y;*/

	Color32 Color = InColor.ToColor32();

	if (ScreenBuffer == NULL || !bGDIInitialized)
	{
		return;
	}
	Color32 *dest = ScreenBuffer;
	int xIndex = InX + Math::FloorToInt(((float)ScreenSize.X - 1.f) * 0.5f);

	for (int y = 0; y < ScreenSize.Y; ++y)
	{
		*(dest + xIndex) = Color;
		xIndex += ScreenSize.X;
	}


	return;
}

void WindowsRSI::DrawHorizontalLine(int InY, const LinearColor & InColor)
{
	Color32 Color = InColor.ToColor32();
	Color32 *dest = ScreenBuffer + (TopLeftPoint.Y - InY) * ScreenSize.X;

	for (int x = 0; x < ScreenSize.X; x++)
	{
		*dest = Color;
		dest++;
	}
}
