#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DwmTool.h"
#include <windows.h>

class DwmTool : public QMainWindow
{
    typedef HRESULT(WINAPI* APIDwmEnableComposition)(UINT uCompositionAction);
    Q_OBJECT

public:
    DwmTool(QWidget *parent = Q_NULLPTR);
    ~DwmTool();
private:
    Ui::DwmToolClass ui;
    HMODULE hDwmMod;
};
