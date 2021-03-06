#ifndef CWIDGETFACTORY_H
#define CWIDGETFACTORY_H

#include <QString>
#include <QSize>
#include <QPoint>

class QWidget;
class QLabel;

typedef std::pair<int, int> FixedSize;

typedef struct
{
  QWidget* parent;
  std::string styleSheet;
  QSize size;
  QPoint pos;
} WidgetOptions;

typedef struct
{
  QWidget* parent;
  QSize size;
  QPoint pos;
} LabelOptions;



class CWidgetFactory
{
public:

    CWidgetFactory() = default;
    ~CWidgetFactory() = default;

    QWidget* MakeWidgetFrame(WidgetOptions& options, bool visibility = true);
    QWidget* MakeWidgetFrame(WidgetOptions&& options, bool visibility = true);
    QLabel* MakeLabelFrame(LabelOptions& options, bool visibility = true);
    QLabel* MakeLabelFrame(LabelOptions&& options, bool visibility = true);
};

#endif // CWIDGETFACTORY_H
