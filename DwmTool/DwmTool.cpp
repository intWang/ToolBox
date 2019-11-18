#include "DwmTool.h"
#include "dwmapi.h"
DwmTool::DwmTool(QWidget *parent)
    : QMainWindow(parent)
{

    hDwmMod = LoadLibrary(L"dwmapi.dll");

    ui.setupUi(this);

    connect(ui.btnEnable, &QPushButton::clicked, this, [&]() {
        if (hDwmMod)
        {
            APIDwmEnableComposition EnableAeroFun = (APIDwmEnableComposition)::GetProcAddress(hDwmMod, "DwmEnableComposition");
            if (EnableAeroFun != NULL)
            {
                EnableAeroFun(DWM_EC_ENABLECOMPOSITION);
            }
        }
    });

    connect(ui.btnDisable, &QPushButton::clicked, this, [&]() {
        if (hDwmMod)
        {
            APIDwmEnableComposition EnableAeroFun = (APIDwmEnableComposition)::GetProcAddress(hDwmMod, "DwmEnableComposition");
            if (EnableAeroFun != NULL)
            {
                EnableAeroFun(DWM_EC_DISABLECOMPOSITION);
            }
        }
    });
}

DwmTool::~DwmTool()
{
    if (hDwmMod != NULL)
    {
        FreeLibrary(hDwmMod);
        hDwmMod = NULL;
    }
}
