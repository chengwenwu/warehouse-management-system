#include "good.h"
Goods::Goods()
{
    this->name_ = "";
    this->count_ = 0;
}

void Goods::SetId(int id)
{
    this->id_ = id;
}

int Goods::GetId()
{
    return this->id_;
}

void Goods::SetName(QString name)
{
    this->name_ = name;
}

QString Goods::GetName()
{
    return this->name_;
}

void Goods::SetCount(int count)
{
    this->count_ = count;
}

int Goods::GetCount()
{
    return this->count_;
}
