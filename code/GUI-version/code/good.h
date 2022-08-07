#ifndef GOOD_H
#define GOOD_H
#include <QString>
class Goods {
public:
    Goods();
    void SetId(int id);
    int GetId();
    void SetName(QString name);
    QString GetName();
    void SetCount(int count);
    int GetCount();

private:
    int id_;
    QString name_;
    int count_;
};
#endif // GOOD_H
