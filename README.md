# DecartLine
Class that describing a two-point line and allows you to get all the points included in it. It is assumed that the line is in the Cartesian coordinate system. Designed for Embarcadero C++ 10.

int GetNextY(int next_X) - returns next Y-coordinate of line based on current X-coordinate.
int GetNextX(int next_Y) - returns next X-coordinate of line based on current Y-coordinate.
int CalculateLine() - calculate array of points based on starting coordinates and end coordinates.
std::vector<TPoint> *GetAllPointsOfLine() - return pointer to std::vector<TPoint> that contain array of points created by CalculateLine(). 
