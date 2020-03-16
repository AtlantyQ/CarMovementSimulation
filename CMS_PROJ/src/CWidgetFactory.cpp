#include<QWidget>
#include<QLabel>
#include<CWidgetFactory.h>


QWidget* CWidgetFactory::MakeWidgetFrame(WidgetOptions& options, bool visibility)
{
    return CWidgetFactory::MakeWidgetFrame( std::move(options), visibility );
}

QWidget* CWidgetFactory::MakeWidgetFrame(WidgetOptions&& options, bool visibility)
{
    QWidget* qwidget = new QWidget( options.parent );
    qwidget->setStyleSheet( options.styleSheet.c_str() );
    qwidget->setFixedSize( options.size );
    qwidget->move( options.pos );
    qwidget->setVisible( visibility );

    return qwidget;
}

QLabel* CWidgetFactory::MakeLabelFrame(LabelOptions& options, bool visibility )
{
    return CWidgetFactory::MakeLabelFrame( std::move(options), visibility );
}

QLabel* CWidgetFactory::MakeLabelFrame(LabelOptions&& options, bool visibility)
{
    QLabel* label = new QLabel( "0 km/h", options.parent );
    label->setFixedSize(  options.fixedSize.first, options.fixedSize.second );
    label->move( options.pos );
    label->setVisible( visibility );

    return label;
}
