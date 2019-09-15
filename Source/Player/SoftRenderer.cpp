
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

		float MIN = -100.0f;
		float MAX = 100.0f;

		Vector2 A(0.0f, 0.0f);
		Vector2 B(MIN, MIN);
		Vector2 C(MAX, MIN);

		//float m_x = (A.X + B.X + C.X ) / 3;
		//float m_y = (A.Y + B.Y + C.Y) / 3;

		//ScreenPoint M = ScreenPoint(m_x, m_y);

		for (int x = MIN; x <= MAX; x++)
		{
			for (int y = MIN; y <= MAX; y++)
			{
				float s = 0;
				float t = 0;

				Vector2 P(x, y);			

				if (isPointInTriangle(A, B, C, P))
				{
					RSI->DrawScreenPoint(ScreenPoint(x, y), LinearColor(1.f, 1.f, 0.f, 1.f));					
				}

			}
		}

		// Render Code
		//RSI->DrawScreenPoint(A, LinearColor(1.f, 0.f, 0.f, 1.f));
		//RSI->DrawScreenPoint(B, LinearColor(1.f, 0.f, 0.f, 1.f));
		//RSI->DrawScreenPoint(C, LinearColor(1.f, 0.f, 0.f, 1.f));
		//RSI->DrawScreenPoint(M, LinearColor(1.f, 0.f, 0.f, 1.f));

		//Vector2 center(0.f, 0.f);
		//float radius = 30.f;

		//Vector2 minPos(center.X - radius, center.Y - radius);
		//Vector2 maxPos(center.X + radius, center.Y + radius);
		//ScreenPoint minPosScreen(minPos);
		//ScreenPoint maxPosScreen(maxPos);

		//LinearColor circleColor(1.f, 0.f, 0.f, 1.f);
		//for (int x = minPosScreen.X; x <= maxPosScreen.X; x++)
		//{
		//	for (int y = minPosScreen.Y; y <= maxPosScreen.Y; y++)
		//	{
		//		ScreenPoint targetPixel(x, y);
		//		Vector2 targetPos = targetPixel.ToVector2();
		//		float distSquare = (targetPos - center).SizeSquared();
		//		if (distSquare < (radius * radius))
		//		{
		//			RSI->DrawScreenPoint(targetPixel, circleColor);
		//		}
		//	}
		//}

		// Render Finish
		RSI->EndFrame();
	}
}

bool SoftRenderer::isPointInTriangle(Vector2 a, Vector2 b, Vector2 c, Vector2 p)
{
	float s = 0;
	float t = 0;

	Vector2 w = p - a;
	Vector2 u = b - a;
	Vector2 v = c - a;

	s = ((u.Dot(w) * v.Dot(v)) - (w.Dot(v) * u.Dot(v))) / ((u.Dot(u) * v.Dot(v)) - (u.Dot(v) * u.Dot(v)));
	t = ((w.Dot(v) * u.Dot(u)) - (u.Dot(w) * u.Dot(v))) / ((u.Dot(u) * v.Dot(v)) - (u.Dot(v) * u.Dot(v)));

	if ((0 <= s && s <= 1) && (0 <= t && t <= 1))
	{
		return true;
	}

	return false;
}

