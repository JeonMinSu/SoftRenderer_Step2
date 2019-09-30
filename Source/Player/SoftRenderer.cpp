#include "WindowsPrecompiled.h"
#include "SoftRenderer.h"
#include "WindowsRSI.h"

void SoftRenderer::Initialize()
{
	RSI = new WindowsRSI();
	if (RSI != nullptr)
	{
		RSI->Init(false);
	}
}

void SoftRenderer::Shutdown()
{
	if (RSI != nullptr && RSI->IsIntialized())
	{
		RSI->Shutdown();
		delete RSI;
		RSI = nullptr;
	}
}

void SoftRenderer::Update()
{
	if (RSI != nullptr)
	{
		// Render Start
		//RSI->BeginFrame();
		RSI->Clear(LinearColor(0.125f, 0.5f, 1.f, 1.f));


		RSI->DrawVerticalLine(0, LinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		RSI->DrawHorizontalLine(0, LinearColor(1.0f, 0.0f, 0.0f, 1.0f));

		ScreenPoint screenSize = DisplaySetting::Inst().GetSize();
		static int gridSize = 10;

		int HalfX = Math::FloorToInt(((float)screenSize.X - 1.f) * 0.5f);
		int HalfY = Math::FloorToInt(((float)screenSize.Y - 1.f) * 0.5f);

		for (int ix = 0; ix < screenSize.X; ix+gridSize)
		{

		}


		VertexData vertex[3];

		vertex[0].Position = Vector2(0.0f, 0.0f);
		vertex[0].Color = LinearColor(1.0f, 0.0f, 0.0f);

		vertex[1].Position = Vector2(150.0f, -150.0f);
		vertex[1].Color = LinearColor(0.0f, 1.0f, 0.0f);

		vertex[2].Position = Vector2(-150.0f, -150.0f);
		vertex[2].Color = LinearColor(0.0f, 0.0f, 1.0f);

		int i[3];
		i[0] = 0;
		i[1] = 1;
		i[2] = 2;

		RSI->SetVertexBuffer(vertex);
		RSI->SetIndexBuffer(i);
		RSI->DrawPrimitive(3, 3);

		// Render Finish
		RSI->EndFrame();
	}
}

//bool SoftRenderer::isPointInTriangle(Vector2 a, Vector2 b, Vector2 c, Vector2 p)
//{
//	float s = 0;
//	float t = 0;
//
//	Vector2 w = p - a;
//	Vector2 u = b - a;
//	Vector2 v = c - a;
//
//	s = ((u.Dot(w) * v.Dot(v)) - (w.Dot(v) * u.Dot(v))) / ((u.Dot(u) * v.Dot(v)) - (u.Dot(v) * u.Dot(v)));
//	t = ((w.Dot(v) * u.Dot(u)) - (u.Dot(w) * u.Dot(v))) / ((u.Dot(u) * v.Dot(v)) - (u.Dot(v) * u.Dot(v)));
//
//	if ((0 <= s && s <= 1) && (0 <= t && t <= 1))
//	{
//		return true;
//	}
//
//	return false;
//}

