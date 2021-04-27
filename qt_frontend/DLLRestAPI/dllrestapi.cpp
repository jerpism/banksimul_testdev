#include "dllrestapi.h"

DLLRestAPI::DLLRestAPI()
{
    objectEngineCLass = new EngineClass;
}

DLLRestAPI::~DLLRestAPI()
{
    delete objectEngineCLass;
    objectEngineCLass = nullptr;
}

QString DLLRestAPI::getBalance(){
   return QString::number(objectEngineCLass->getBalance(), 'f', 2);
}

QString DLLRestAPI::getCryptoBalance(){
   return QString::number(objectEngineCLass->getCryptoBalance(), 'f', 8);
}

QString DLLRestAPI::getRate(){
    return QString::number(objectEngineCLass->getRate(), 'f', 5);
}

void DLLRestAPI::login(QString card, QString pin)
{
    objectEngineCLass->login(card, pin);
}

void DLLRestAPI::logout()
{
    objectEngineCLass->logout();
}

void DLLRestAPI::withdrawMoney(QString amount)
{
    objectEngineCLass->withdrawMoney(amount);
}

void DLLRestAPI::buyCrypto(QString amount)
{
    objectEngineCLass->buyCrypto(amount);
}

void DLLRestAPI::sellCrypto(QString amount)
{
    objectEngineCLass->sellCrypto(amount);
}

void DLLRestAPI::transferMoney(QString recipient, QString amount)
{
    objectEngineCLass->transferMoney(recipient, amount);
}

bool DLLRestAPI::accountExists(QString account){
    return objectEngineCLass->accountExists(account);
}

