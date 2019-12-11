#pragma once
#include "apcom/apcom.h"
#include <QString>
#include <QVariant>
namespace Logic
{
    CON_DEFINE_IID(ITimestamp, "6ADF9485-F541-47FA-A3C5-8FEB5E387C61");
    CON_DEFINE_IID(IToolBoxLogicProvider, "F6926664-C573-4854-967C-612301764D4F");
    CON_DEFINE_IID(IStoreAble, "BEC9DC64-0120-498C-94BD-1D5BC5464BC5");
    CON_DEFINE_IID(ISettingOpoer, "A0DC07C7-A2B6-4182-8704-9BF6B89289F3");

    using ITimestampPtr = CConComPtr < ITimestamp >;
    using IToolBoxLogicProviderPtr = CConComPtr < IToolBoxLogicProvider >;
    using IStoreAblePtr = CConComPtr < IStoreAble >;
    using ISettingOpoerPtr = CConComPtr < ISettingOpoer >;
    
    class IToolBoxLogicProvider : public conIUnknown
    {
    public:
        static IToolBoxLogicProviderPtr CreateInstance();
        virtual ITimestampPtr QueryTimestampPtr() = 0;
        virtual ISettingOpoerPtr QuerySettingOperPtr() = 0;
        virtual IStoreAblePtr QueryStoreAblePtr() = 0;

    };

    class ITimestamp : public conIUnknown
    {
    public:
        static ITimestampPtr CreateInstance(IToolBoxLogicProviderPtr pServer);
        virtual std::string TimeT2String(time_t tm) = 0;
        virtual time_t String2TimeT(std::string) = 0;
    };

    class IStoreAble : public conIUnknown
    {
    public:
        enum class StoreType
        {
            MEMDATA,
            SQL,
            ACCESS,
            TEXT,
        };

    private:
        StoreType m_emStoreType;

    public:
        static IStoreAblePtr CreateInstance(IToolBoxLogicProviderPtr pServer);
        virtual void SetStoreType(StoreType emStoreType)
        {
            m_emStoreType = emStoreType;
        }
        virtual bool StoreData() = 0;
        virtual bool LoadData() = 0;

    protected:
        virtual bool ConnectDataPool() = 0;
        virtual bool DisconnectDataPool() = 0;
    };


    class ISettingOpoer : public conIUnknown
    {
    public:
        static ISettingOpoerPtr CreateInstance(IToolBoxLogicProviderPtr pServer);
        virtual void SetIniFile(QString& strFile) = 0;
        virtual bool Write(const QString& strApp, const QString& strName, const QVariant& strValue) = 0;
        virtual QVariant Read(const QString& strApp, const QString& strName) = 0;
    };
}
