#pragma once

struct Vector2D
{
	int X = 0;
	int Y = 0;

	Vector2D(int InX = 0, int InY = 0) : X(InX), Y(InY)
	{

	}

	inline bool operator==(const Vector2D& InOther) const { return InOther.X == X && InOther.Y == Y; }
	inline bool operator!=(const Vector2D& InOther) const { return !(*this == InOther); }
	
	inline Vector2D operator+(const Vector2D& InOther) const { return Vector2D(this->X + InOther.X, this->Y + InOther.Y); }
	inline Vector2D& operator +=(const Vector2D& InOther) { X += InOther.X; Y += InOther.Y; return *this; }

	static const Vector2D Default;
	static const Vector2D Up;
	static const Vector2D Down;
	static const Vector2D Left;
	static const Vector2D Right;
};
