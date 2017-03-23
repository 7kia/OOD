#pragma once

class CCircle;
class CLineSegment;
class CMyPoint;
class CRectangle;
class CTriangle;

class IShapeVisitor
{
public:
	virtual void	Visit(const CLineSegment & line) = 0;
	virtual void	Visit(const CTriangle & triangle) = 0;
	virtual void	Visit(const CRectangle & rectangle) = 0;
	virtual void	Visit(const CCircle & circle) = 0;
	virtual void	Visit(const CMyPoint & point) = 0;
	virtual			~IShapeVisitor() = default;
};
