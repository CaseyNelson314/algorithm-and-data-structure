# include <Siv3D.hpp> // Siv3D v0.6.14

void koch_curve(const Vec2& l, const Vec2& r, int n)
{
	if (n == 0) return;

	Vec2 distance = r - l;
	Vec2 distance_div_3 = distance / 3;
	Vec2 p0 = l + 1 * distance_div_3;
	Vec2 p1 = p0 + distance_div_3.rotated(ToRadians(-60));
	Vec2 p2 = l + 2 * distance_div_3;

	Line{ l, p0 }.draw();
	Line{ p0, p1 }.draw();
	Line{ p1, p2 }.draw();
	Line{ p2, r }.draw();

	koch_curve(l, p0, n - 1);
	koch_curve(p0, p1, n - 1);
	koch_curve(p1, p2, n - 1);
	koch_curve(p2, r, n - 1);
}


void Main()
{
	while (System::Update())
	{
		koch_curve({ 100, 100 }, { 500, 500 }, 7);
	}
}
