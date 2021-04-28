#include "dllrestapi.h"

DLLRestAPI::DLLRestAPI()
{
    objectEngineClass = new EngineClass;
    connect(objectEngineClass, SIGNAL(gotInfo()), this, SLOT(gotInfoSlot()));
}

DLLRestAPI::~DLLRestAPI()
{
    delete objectEngineClass;
    objectEngineClass = nullptr;
}

QString DLLRestAPI::getBalance(){
   return QString::number(objectEngineClass->getBalance(), 'f', 2);
}

QString DLLRestAPI::getCryptoBalance(){
   return QString::number(objectEngineClass->getCryptoBalance(), 'f', 8);
}

QString DLLRestAPI::getRate(){
    return QString::number(objectEngineClass->getRate(), 'f', 5);
}

void DLLRestAPI::login(QString card, QString pin)
{
    objectEngineClass->login(card, pin);
}

void DLLRestAPI::logout()
{
    objectEngineClass->logout();
}

void DLLRestAPI::withdrawMoney(QString amount)
{
    objectEngineClass->withdrawMoney(amount);
}

void DLLRestAPI::buyCrypto(QString amount)
{
    objectEngineClass->buyCrypto(amount);
}

void DLLRestAPI::sellCrypto(QString amount)
{
    objectEngineClass->sellCrypto(amount);
}

void DLLRestAPI::transferMoney(QString recipient, QString amount)
{
    objectEngineClass->transferMoney(recipient, amount);
}

bool DLLRestAPI::accountExists(QString account){
    return objectEngineClass->accountExists(account);
}

QString DLLRestAPI::getName(){
    return objectEngineClass->getName();
}

QString DLLRestAPI::getAddr(){
    return objectEngineClass->getAddr();
}

QString DLLRestAPI::getPhone(){
    return objectEngineClass->getPhone();
}

void DLLRestAPI::gotInfoSlot(){
    emit infoReceived();
}

