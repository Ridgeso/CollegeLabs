#pragma once


class Data;
class IntData;
class FloatData;

class Visitor
{
public:
    virtual void visit(const Data* data) const { };
    virtual void visit(const IntData* data) const { };
    virtual void visit(const FloatData* data) const { };

    virtual void visit(const Data* data) { };
    virtual void visit(const IntData* data) { };
    virtual void visit(const FloatData* data) { };

private:
};