#include "Vector2.h"
#include "LinearColor.h"
#include "RenderingSoftwareInterface.h"

class TriangleRasterizer
{

public:
	TriangleRasterizer();
	explicit TriangleRasterizer(VertexData InVertex0, VertexData InVertexData1, VertexData InVertexData2);

	const bool IsInside(const Vector2 & p) const;
	void RecaleBounds();

	FORCEINLINE bool HasColor() const { return bHasColor; }
	FORCEINLINE bool HasUV() const { return bHasUV; }

	FORCEINLINE LinearColor RainbowColor(const Vector2 &Position) const
	{

		if (!HasColor())
		{
			return LinearColor::Error;
		}

		Vector2 st = GetBaryCentricCoord(Position);
		float oneMinusST = 1 - st.X - st.Y;
		return VertexBuffer[0].Color * oneMinusST + VertexBuffer[1].Color * st.X + VertexBuffer[2].Color * st.Y;

	}

	FORCEINLINE Vector2 GetBaryCentricCoord(const Vector2& InScreenPosition) const
	{
		Vector2 w = InScreenPosition - Vector2(VertexBuffer[0].Position.X, VertexBuffer[0].Position.Y);
		float dotUW = UVector.Dot(w);
		float dotVW = VVector.Dot(w);
		float s = (DotVV * dotUW - DotUV * dotVW) * InDenom;
		float t = (DotUU * dotVW - DotUV * dotUW) * InDenom;
		return Vector2(s, t);
	}

public:
	VertexData VertexBuffer[3];
	ScreenPoint TopLeft;
	ScreenPoint BottomRight;

private:

	bool bHasColor;
	bool bHasUV;

	Vector2 UVector;
	Vector2 VVector;

	float DotUU, DotUV, DotVV, InDenom;

	

};