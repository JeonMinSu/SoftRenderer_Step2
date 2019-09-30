#include "Precompiled.h"
#include "Public\TriangleRasterizer.h"

TriangleRasterizer::TriangleRasterizer()
{
	RecaleBounds();
}

TriangleRasterizer::TriangleRasterizer(VertexData InVertex0, VertexData InVertex1, VertexData InVertex2)
{
	VertexBuffer[0] = InVertex0;
	VertexBuffer[1] = InVertex1;
	VertexBuffer[2] = InVertex2;

	bHasColor = true;
	bHasUV = true;

	RecaleBounds();
}

const bool TriangleRasterizer::IsInside(const Vector2 & p) const
{
	Vector2 st = GetBaryCentricCoord(p);
	if (st.X < 0.f) return false;
	if (st.Y < 0.f) return false;
	if ((st.X + st.Y) > 1.f) return false;

	return true;
}

void TriangleRasterizer::RecaleBounds()
{
	Vector2 max = Vector2(-INFINITY, -INFINITY);
	Vector2 min = Vector2(INFINITY, INFINITY);

	for (int i = 0; i < 3; i++)
	{
		if (VertexBuffer[i].Position.X > max.X) max.X = VertexBuffer[i].Position.X;
		if (VertexBuffer[i].Position.Y > max.Y) max.Y = VertexBuffer[i].Position.Y;
		if (VertexBuffer[i].Position.X < min.X) min.X = VertexBuffer[i].Position.X;
		if (VertexBuffer[i].Position.Y < min.Y) min.Y = VertexBuffer[i].Position.Y;
	}

	UVector = VertexBuffer[1].Position - VertexBuffer[0].Position;
	VVector = VertexBuffer[2].Position - VertexBuffer[0].Position;

	DotUU = UVector.Dot(UVector);
	DotUV = UVector.Dot(VVector);
	DotVV = VVector.Dot(VVector);

	InDenom = 1.0f / (DotUU * DotVV - DotUV * DotUV);

	TopLeft = ScreenPoint(min);
	BottomRight = ScreenPoint(max);

}

