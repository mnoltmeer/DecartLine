/*!
Copyright 2019 Maxim Noltmeer (m.noltmeer@gmail.com)

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------

#ifndef DecartLineH
#define DecartLineH
#include <System.Classes.hpp>
#include <vector>
#include <cmath>
//---------------------------------------------------------------------------

//клас, що описує пряму по двом точкам (у декартових координатах)
//та дозволяє отримати всі точки, що входять у неї
class TDecartLine
{
  private:
	TPoint P1;
	TPoint P2;
	float K;
    float A;
	std::vector<TPoint> vecPoints;
	String err;

//рівняння прямої y = Kx + C тож
//y1 = Kx1 + A => A = y1 - Kx1
//y2 = Kx2 + A => y2 = Kx2 + y1 - Kx1 => K(x1 - x2) = y1 - y2 =>
//K = (y1 - y2) / (x1 - x2) =>
//A = y1 - x1((y1 - y2) / (x1 - x2)) =>
	int Calculate()
	{
	  float x1 = P1.X,
			y1 = P1.Y,
			x2 = P2.X,
		  	y2 = P2.Y;

	  try
		 {
		   if (x1 != x2)
		   	 K = (y2 - y1) / (x2 - x1);
		 }
	  catch (Exception &e)
		 {
		   err = e.ToString();

		   return -1;
		 }

      try
		 {
		   A = y1 - x1 * K;
		 }
	  catch (Exception &e)
		 {
		   err = e.ToString();

		   return -1;
		 }

      return 0;
	}

	inline float NextY(float next_X)
	{
	  if ((P1.X == P2.X) && (next_X != P1.X))
		throw Exception("Line isn't contain next_X");
	  else
		return _roundf(K * next_X + A);
	}

	inline float NextX(float next_Y)
	{
      if ((P1.Y == P2.Y) && (next_Y != P1.Y))
		throw Exception("Line isn't contain next_Y");
	  else if (P1.X == P2.X)
        return P1.X;
	  else
		return _roundf((next_Y - A) / K);
	}

	void AllPointsUseX(int start_X, int end_X)
	{
      TPoint next_pos;
	  float x = start_X;

	  while (x <= end_X)
		{
		  next_pos.X = x;

          try
			 {
			   next_pos.Y = _roundf(NextY(x));
			 }
		  catch (Exception &e)
			 {
			   err = e.ToString();
			 }

		  vecPoints.push_back(next_pos);
		  x++;
		}
	}

	void AllPointsUseY(int start_Y, int end_Y)
	{
      TPoint next_pos;
	  float y = start_Y;

	  while (y <= end_Y)
		{
		  next_pos.Y = y;

          try
			 {
			   next_pos.X = _roundf(NextX(y));
			 }
		  catch (Exception &e)
			 {
			   err = e.ToString();
			 }

		  vecPoints.push_back(next_pos);
		  y++;
		}
	}

	TPoint GetPoint1(){return P1;}
	void SetPoint1(const TPoint val){P1 = val;}

	TPoint GetPoint2(){return P2;}
    void SetPoint2(const TPoint val){P2 = val;}

  public:
	TDecartLine(){P1 = TPoint(0, 0); P2 = TPoint(0, 0); Calculate();}

	TDecartLine(TPoint beg_point, TPoint end_point)
	{
	  P1 = beg_point;
	  P2 = end_point;

	  Calculate();
	}

	virtual inline ~TDecartLine(){vecPoints.clear();}

	inline int GetNextY(int next_X){return NextY(next_X);}
	inline int GetNextX(int next_Y){return NextX(next_Y);}
    inline int CalculateLine(){return Calculate();}
	inline String GetError(){return err;}

	std::vector<TPoint> *GetAllPointsOfLine()
	{
	  vecPoints.clear();

	  if (abs(P1.X - P2.X) >= abs(P1.Y - P2.Y)) //пряма прогресує по горизонталі
		{
		  if (P1.X < P2.X)
			AllPointsUseX(P1.X, P2.X);
		  else if (P1.X > P2.X)
			AllPointsUseX(P2.X, P1.X);
		}
	  else //пряма прогресує по вертикалі
		{
		  if (P1.Y < P2.Y)
			AllPointsUseY(P1.Y, P2.Y);
		  else if (P1.Y > P2.Y)
			AllPointsUseY(P2.Y, P1.Y);
        }

	  return &vecPoints;
	}

	__property TPoint BeginPoint = {read = GetPoint1, write = SetPoint1};
	__property TPoint EndPoint = {read = GetPoint2, write = SetPoint2};
};

#endif
