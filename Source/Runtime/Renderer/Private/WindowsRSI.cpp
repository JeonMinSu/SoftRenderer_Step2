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

void WindowsRSI::DrawBresenhamLine(const Vector2 & InStartPos, const Vector2 & InEndPos, const LinearColor & InColor)
{

	int W = InEndPos.X - InStartPos.X;
	int H = InEndPos.Y - InStartPos.Y;

	int x = InStartPos.X;
	int y = InStartPos.Y;

	int F, dF1, dF2;

	if (W < 0)
	{
		if ((W * W) <= (H * H))
		{
			F = 2 * W + H;

			dF1 = 2 * W;
			dF2 = 2 * (W + H);

			for (y = InStartPos.Y; y <= InEndPos.Y; y++)
			{
				DrawScreenPoint(ScreenPoint(x, y), InColor.ToColor32());

				if (F < 0)
				{
					F -= dF1;
				}
				else
				{
					F -= dF2;
					--x;
				}
			}


		}
		else
		{
			F = 2 * H + W;

			dF1 = 2 * H;
			dF2 = 2 * (H + W);


			for (x = InStartPos.X; x > InEndPos.X; x--)
			{
				DrawScreenPoint(ScreenPoint(x, y), InColor.ToColor32());

				if (F < 0)
				{
					F += dF1;
				}
				else
				{
					F += dF2;
					y++;
				}
			}


		}
	}
	else
	{
		if (W <= H)
		{
			F = 2 * W - H;

			dF1 = 2 * W;
			dF2 = 2 * (W - H);


			for (y = InStartPos.Y; y <= InEndPos.Y; y++)
			{
				DrawScreenPoint(ScreenPoint(x, y), InColor.ToColor32());

				if (F < 0)
				{
					F += dF1;
				}
				else
				{
					++x;
					F += dF2;
				}
			}

		}
		else
		{
			F = 2 * H - W;

			dF1 = 2 * H;
			dF2 = 2 * (H - W);

			for (x = InStartPos.X; x <= InEndPos.X; ++x)
			{
				DrawScreenPoint(ScreenPoint(x, y), InColor.ToColor32());
				if (F < 0)
				{
					F += dF1;
				}
				else
				{
					++y;
					F += dF2;
				}
			}
		}

	}

}

void WindowsRSI::DrawVerticalLine(int InX, const LinearColor & InColor)
{
	Color32 color = InColor.ToColor32();
	Color32* dest = ScreenBuffer;

	int xIndex = InX + Math::FloorToInt(((float)ScreenSize.X - 1.f) * 0.5f);
	if (xIndex < 0) return;
	for (int y = 0; y < ScreenSize.Y; ++y)
	{
		*(dest + xIndex) = color;
		dest += ScreenSize.X;
	}
}

void WindowsRSI::DrawHorizontalLine(int InY, const LinearColor & InColor)
{
	Color32 color = InColor.ToColor32();
	Color32* dest = ScreenBuffer;
	int startIndex = Math::FloorToInt(((float)ScreenSize.Y - 1.f) * 0.5f) - InY;
	dest = dest + startIndex * ScreenSize.X;
	for (int x = 0; x < ScreenSize.X; x++)
	{
		*dest = color;
		dest++;
	}
}
