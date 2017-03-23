#pragma once

class CCircle;
class CLineSegment;
class MyCPoint;
class CRectangle;
class CTriangle;

class IShapeVisitor
{
public:
	virtual void	Visit(const CLineSegment & line) = 0;
	virtual void	Visit(const CTriangle & triangle) = 0;
	virtual void	Visit(const CRectangle & rectangle) = 0;
	virtual void	Visit(const CCircle & circle) = 0;
	virtual void	Visit(const MyCPoint & point) = 0;
	virtual			~IShapeVisitor() = default;
};
