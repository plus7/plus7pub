#ifndef DEFS_H
#define DEFS_H

#include <QMap>
#include <QPair>

typedef QPair<int, int> Action;
typedef QPair<int, int> Status;
typedef QPair< Status, Action > MyQ;
typedef double Reward;

#endif // DEFS_H
